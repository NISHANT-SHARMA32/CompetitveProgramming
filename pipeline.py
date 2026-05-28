# === ECC-ENABLED STDM WATERMARKING PIPELINE WITH VARIABLE ROIs (CACHED, ROBUST VERSION) ===

import os
import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
from tqdm import tqdm
from google.colab import drive

import torch
from transformers import DetrImageProcessor, DetrForObjectDetection
from skimage.metrics import peak_signal_noise_ratio as compare_psnr
from skimage.metrics import structural_similarity as compare_ssim
import scipy.fftpack
import hashlib

# === 1. MOUNT GOOGLE DRIVE ===
drive.mount('/content/drive')  # Mount Google Drive so dataset can be accessed
image_folder = '/content/drive/MyDrive/filtered_coco500'  # Path to image dataset

# === 2. SETUP ===
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')  # Use GPU if available
processor = DetrImageProcessor.from_pretrained("facebook/detr-resnet-50")  # Image preprocessor for DETR
model = DetrForObjectDetection.from_pretrained("facebook/detr-resnet-50").to(device)  # Load DETR model

# === 3. PARAMETERS ===
num_images = 250          # Number of images to process
wm_length = 50            # Watermark length in bits
tauM = 1500               # Minimum ROI area threshold
delta = 50                # Quantization step for STDM (higher = more robust, less transparent)
redundancy = 4            # How many times each bit is repeated (for error resilience)
num_rois = 4              # Number of ROIs to use per image

# === 4. CONSTANTS ===
FIXED_MIDBAND_INDICES = [  # Fixed set of DCT mid-band coefficient positions
    (1,2),(2,1),(2,2),(3,0),(0,3),(3,1),(1,3),
    (2,3),(3,2),(4,0),(0,4),(4,1),(1,4),(4,2),(2,4)
]

# === 5. UTILS ===
def get_stable_seed(fname):
    """Generate a stable random seed based on filename hash."""
    return int(hashlib.md5(fname.encode()).hexdigest(), 16) % (2**32)

def get_projection_vector(length, seed=42):
    """Generate a fixed-length normalized random projection vector."""
    np.random.seed(seed)
    v = np.random.randn(length)
    return v / np.linalg.norm(v)

# === 6. WATERMARK GENERATION ===
def generate_watermark(length=50):
    """Generate random binary watermark bits."""
    return np.random.randint(0, 2, length).tolist()

# === 7. DETR + ROI SELECTION ===
def get_topN_rois(image_pil, area_thresh=tauM, N=4):
    """
    Detect objects using DETR, filter by area, 
    and return top-N regions of interest.
    """
    inputs = processor(images=image_pil, return_tensors="pt").to(device)
    outputs = model(**inputs)
    target_sizes = torch.tensor([image_pil.size[::-1]])  # (height, width)
    results = processor.post_process_object_detection(outputs, target_sizes=target_sizes)[0]

    all_boxes = []       # All detected bounding boxes
    filtered_boxes = []  # Boxes that pass filtering

    for score, label, box in zip(results["scores"], results["labels"], results["boxes"]):
        if score > 0.7:  # Confidence threshold
            x1, y1, x2, y2 = map(int, box.tolist())
            area = (x2 - x1) * (y2 - y1)
            all_boxes.append([x1, y1, x2, y2])

            # Expand small boxes to meet minimum area
            if area < area_thresh:
                cx, cy = (x1 + x2) // 2, (y1 + y2) // 2
                size = int(np.sqrt(area_thresh))
                half = size // 2
                new_box = [
                    max(0, cx - half), max(0, cy - half),
                    min(image_pil.width, cx + half), min(image_pil.height, cy + half)
                ]
                expanded_area = (new_box[2] - new_box[0]) * (new_box[3] - new_box[1])
                filtered_boxes.append((expanded_area, new_box))
            else:
                filtered_boxes.append((area, [x1, y1, x2, y2]))

    # Sort ROIs by area, take top-N
    filtered_boxes.sort(key=lambda x: x[0], reverse=True)
    selected = [box for _, box in filtered_boxes[:N]]
    return all_boxes, selected

# === 8. GET BLOCKS FROM ROI ===
def get_blocks_from_roi(roi, stride=4):
    """Generate coordinates of 8x8 DCT blocks inside ROI."""
    x1, y1, x2, y2 = roi
    blocks = []
    for r in range(y1, y2 - 7, stride):
        for c in range(x1, x2 - 7, stride):
            blocks.append((r, c))
    return blocks

# === 9. EMBEDDING (ROBUST) ===
def embed_watermark_stdm(image_rgb, rois, watermark_bits, fname, delta=50, redundancy=4):
    """
    Embed watermark bits using STDM in the DCT mid-band 
    of luminance channel inside the given ROIs.
    """
    img_ycbcr = cv2.cvtColor(image_rgb, cv2.COLOR_RGB2YCrCb)
    Y = img_ycbcr[:, :, 0].astype(np.float32)

    # Get all block positions from ROIs
    blocks = []
    for roi in rois:
        blocks.extend(get_blocks_from_roi(roi))

    # Repeat bits to increase robustness
    wm_bits_redundant = np.repeat(watermark_bits, redundancy)
    needed_blocks = len(wm_bits_redundant)
    print(f"[{fname}] Available blocks: {len(blocks)} / Needed: {needed_blocks}")

    if len(blocks) < needed_blocks:
        return None  # Not enough capacity

    # Shuffle blocks in a reproducible way
    np.random.seed(get_stable_seed(fname))
    np.random.shuffle(blocks)
    blocks = blocks[:needed_blocks]

    proj_dir = get_projection_vector(length=len(FIXED_MIDBAND_INDICES))

    wm_idx = 0
    h, w = Y.shape

    for (r, c) in blocks:
        if r + 8 > h or c + 8 > w:
            continue
        if wm_idx >= len(wm_bits_redundant):
            break

        # Apply 2D-DCT to block
        block = Y[r:r+8, c:c+8]
        dct_block = scipy.fftpack.dct(scipy.fftpack.dct(block.T, norm='ortho').T, norm='ortho')

        # Extract mid-band coefficients
        u = np.array([dct_block[i, j] for (i, j) in FIXED_MIDBAND_INDICES])
        proj = np.dot(u, proj_dir)  # Project onto projection vector

        # Quantize projection value for bit embedding
        bit = wm_bits_redundant[wm_idx]
        proj_w = (np.floor(proj / (2*delta)) * 2*delta) + (delta if bit else 0) + delta/2
        delta_proj = proj_w - proj
        u_embedded = u + delta_proj * proj_dir  # Modify coefficients

        # Write back modified coefficients
        for idx, (i, j) in enumerate(FIXED_MIDBAND_INDICES):
            dct_block[i, j] = u_embedded[idx]

        # Inverse DCT to reconstruct block
        block_w = scipy.fftpack.idct(scipy.fftpack.idct(dct_block.T, norm='ortho').T, norm='ortho')
        Y[r:r+8, c:c+8] = np.clip(block_w, 0, 255)
        wm_idx += 1

    img_ycbcr[:, :, 0] = np.round(Y)
    return cv2.cvtColor(img_ycbcr.astype(np.uint8), cv2.COLOR_YCrCb2RGB)

# === 10. EXTRACTION (ROBUST) ===
def extract_watermark_stdm(image_rgb, rois, fname, delta=50, watermark_length=50, redundancy=4):
    """
    Extract watermark bits using STDM inverse process 
    from luminance channel DCT mid-band coefficients.
    """
    img_ycbcr = cv2.cvtColor(image_rgb, cv2.COLOR_RGB2YCrCb)
    Y = img_ycbcr[:, :, 0].astype(np.float32)

    # Get same blocks as in embedding
    blocks = []
    for roi in rois:
        blocks.extend(get_blocks_from_roi(roi))

    expected_bits = watermark_length * redundancy
    np.random.seed(get_stable_seed(fname))
    np.random.shuffle(blocks)
    blocks = blocks[:expected_bits]

    proj_dir = get_projection_vector(length=len(FIXED_MIDBAND_INDICES))
    extracted_bits = []
    h, w = Y.shape

    for (r, c) in blocks:
        if r + 8 > h or c + 8 > w:
            continue
        block = Y[r:r+8, c:c+8]
        dct_block = scipy.fftpack.dct(scipy.fftpack.dct(block.T, norm='ortho').T, norm='ortho')
        u = np.array([dct_block[i, j] for (i, j) in FIXED_MIDBAND_INDICES])
        proj = np.dot(u, proj_dir)

        # Decide bit based on quantization remainder
        d_mod = proj % (2*delta)
        bit = 1 if d_mod >= delta else 0
        extracted_bits.append(bit)

    # Majority voting over redundant bits
    wm_bits = []
    for i in range(0, len(extracted_bits), redundancy):
        chunk = extracted_bits[i:i+redundancy]
        if chunk:
            wm_bits.append(int(np.round(np.mean(chunk))))
    return wm_bits

# === 11. VISUALIZE ===
def visualize(image_np, watermarked_np, all_rois, selected_rois):
    """Show original image, all ROIs, selected ROIs, and watermarked image."""
    fig, axs = plt.subplots(1, 4, figsize=(24, 6))
    axs[0].imshow(image_np)
    axs[0].set_title("Original Image")
    axs[1].imshow(image_np)
    for box in all_rois:
        axs[1].add_patch(plt.Rectangle((box[0], box[1]), box[2]-box[0], box[3]-box[1], edgecolor='blue', linewidth=1.5, fill=False))
    axs[1].set_title("All DETR RoIs")
    axs[2].imshow(image_np)
    for box in selected_rois:
        axs[2].add_patch(plt.Rectangle((box[0], box[1]), box[2]-box[0], box[3]-box[1], edgecolor='red', linewidth=2, fill=False))
    axs[2].set_title(f"Selected RoIs ({len(selected_rois)} used)")
    axs[3].imshow(watermarked_np)
    axs[3].set_title("Watermarked Image")
    for ax in axs:
        ax.axis('off')
    plt.tight_layout()
    plt.show()

# === 12. MAIN PIPELINE ===
all_images = sorted([f for f in os.listdir(image_folder) if f.lower().endswith(('.jpg', '.png'))])[:num_images]
psnr_total, ssim_total, ber_total = 0, 0, 0
count = 0
roi_cache = {}

for fname in tqdm(all_images):
    fpath = os.path.join(image_folder, fname)
    img = Image.open(fpath).convert('RGB')
    img_np = np.array(img)

    # Step 1: Get ROIs from DETR
    all_rois, rois = get_topN_rois(img, N=num_rois)
    roi_cache[fname] = rois

    # Step 2: Generate watermark bits
    watermark_bits = generate_watermark(wm_length)

    # Step 3: Embed watermark
    watermarked_np = embed_watermark_stdm(img_np, rois, watermark_bits, fname=fname, delta=delta, redundancy=redundancy)
    if watermarked_np is None:
        print(f"[{fname}] Skipped (not enough capacity)")
        continue

    # Step 4: Visualize
    visualize(img_np, watermarked_np, all_rois, rois)

    # Step 5: Quality metrics
    psnr_val = compare_psnr(img_np, watermarked_np, data_range=255)
    ssim_val = compare_ssim(img_np, watermarked_np, channel_axis=-1)

    # Step 6: Extract watermark from same ROIs
    rois = roi_cache[fname]
    extracted_bits = extract_watermark_stdm(watermarked_np, rois, fname=fname, delta=delta, watermark_length=wm_length, redundancy=redundancy)
    correct = sum(a == b for a, b in zip(watermark_bits, extracted_bits))
    ber = 1 - (correct / wm_length)

    print(f"[{fname}] Extracted: {correct}/{wm_length} correct bits, BER: {ber:.4f}")
    psnr_total += psnr_val
    ssim_total += ssim_val
    ber_total += ber
    count += 1

# Step 7: Final evaluation
if count > 0:
    print(f"\n=== FINAL EVALUATION ===")
    print(f"[✓] Avg PSNR: {psnr_total/count:.2f} dB")
    print(f"[✓] Avg SSIM: {ssim_total/count:.4f}")
    print(f"[✓] Avg BER: {ber_total/count:.4f}")
