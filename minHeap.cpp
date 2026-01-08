class minHeap {
  private:
    // Initialize your data members
    vector<int> heap;
    
    void heapifyUp(int i){
        while(i > 0){
            int parent = (i - 1) / 2;
            if(heap[parent] <= heap[i]) break;
            swap(heap[parent], heap[i]);
            i = parent;
        }
    }
    
    void heapifyDown(int i){
        int n = heap.size();
        
        while(true){
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            
            if(left < n and heap[left] < heap[smallest]) smallest = left;
            if(right < n and heap[right] < heap[smallest]) smallest = right;
            
            if(smallest == i) break;
            
            swap(heap[i], heap[smallest]);
            
            i = smallest;
        }
    }

  public:

    void push(int x) {
        // Insert x into the heap
        heap.push_back(x);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        // Remove the top (minimum) element
        if(heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    int peek() {
        // Return the top element or -1 if empty
        if(heap.empty()) return -1;
        return heap[0];
    }

    int size() {
        // Return the number of elements in the heap
        return heap.size();
    }
};
