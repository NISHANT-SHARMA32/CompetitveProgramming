#include <iostream>
#include <string>
#include <climits>
using namespace std;

#define N 100

int mindistance(int distance[], bool visited[]) {
    int minDist = INT_MAX, index;
    for (int i = 0; i < N; i++) {
        if (!visited[i] && distance[i] <= minDist) {
            minDist = distance[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int graph[N][N], int source, string stations[N]) {
    int distance[N];
    bool visited[N];

    for (int i = 0; i < N; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[source] = 0;

    for (int count = 0; count < N - 1; count++) {
        int u = mindistance(distance, visited);
        visited[u] = true;

        for (int v = 0; v < N; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    cout << "\nShortest number of stations from " << stations[source] << ":\n";
    for (int i = 0; i < N; i++) {
        cout << stations[source] << " → " << stations[i] << " = " << distance[i] << " stations\n";
    }
}

int main() {
    // Simplified Delhi Metro simulation (100 stations)
    string stations[N] = {
        "Noida Sector 62", "Botanical Garden", "Noida City Centre", "Mayur Vihar", "Akshardham", "Yamuna Bank", 
        "Indraprastha", "Rajiv Chowk", "Karol Bagh", "Rajendra Place", "Patel Nagar", "Shadipur", "Kirti Nagar", "Moti Nagar",
        "Punjabi Bagh", "Ashok Park", "Inderlok", "Kashmere Gate", "Tis Hazari", "Pulbangash", "Pratap Nagar", 
        "Shastri Nagar", "Inderlok (Red Line)", "Kanhaiya Nagar", "Keshav Puram", "Netaji Subhash Place", 
        "Pitampura", "Rohini East", "Rohini West", "Rithala", "Dilshad Garden", "Seelampur", "Shahdara", "Welcome",
        "Karkardooma", "Preet Vihar", "Laxmi Nagar", "Mandi House", "Central Secretariat", "Udyog Bhawan", 
        "Race Course", "Jor Bagh", "INA", "AIIMS", "Green Park", "Hauz Khas", "Malviya Nagar", "Saket", 
        "Qutub Minar", "Chhatarpur", "Sultanpur", "Ghitorni", "Arjan Garh", "Guru Dronacharya", "Sikandarpur", 
        "MG Road", "IFFCO Chowk", "HUDA City Centre", "Kalkaji Mandir", "Nehru Place", "Greater Kailash", "Chirag Delhi", 
        "Panchsheel Park", "Hauz Khas (Magenta)", "IIT Delhi", "R.K. Puram", "Munirka", "Vasant Vihar", "Shankar Vihar", 
        "Terminal 1 IGI", "IGI Terminal 2", "Dwarka Sector 21", "Dwarka Sector 14", "Dwarka Sector 12", "Dwarka Sector 9", 
        "Dwarka Mor", "Nawada", "Uttam Nagar", "Janakpuri West", "Janakpuri East", "Tilak Nagar", "Subhash Nagar", 
        "Tagore Garden", "Rajouri Garden", "Maya Puri", "Naraina Vihar", "Delhi Cantt", "Palam", "Dashrathpuri", 
        "Dabri Mor", "Janakpuri South", "Indira Gandhi Airport", "Vasant Kunj", "Ambience Mall", "Cyber City", 
        "Udyog Vihar", "IFFCO Chowk (Rapid)", "Sector 54 Chowk", "Sector 55-56", "Sector 45", "Sector 42", "Golf Course", 
        "Noida Sector 18", "Okhla Bird Sanctuary"
    };

    // Create an adjacency matrix initialized with 0
    int graph[N][N] = {0};

    // Simulating connectivity between consecutive stations (like a metro line)
    for (int i = 0; i < N - 1; i++) {
        graph[i][i + 1] = 1;
        graph[i + 1][i] = 1;
    }

    // Adding interchanges (connecting key metro lines)
    graph[7][37] = graph[37][7] = 1;  // Rajiv Chowk ↔ Central Secretariat
    graph[7][17] = graph[17][7] = 1;  // Rajiv Chowk ↔ Kashmere Gate
    graph[17][33] = graph[33][17] = 1; // Kashmere Gate ↔ Welcome
    graph[45][61] = graph[61][45] = 1; // Hauz Khas ↔ Hauz Khas (Magenta)
    graph[71][79] = graph[71][79] = 1; // Dwarka ↔ Janakpuri West
    graph[57][92] = graph[57][92] = 1; // HUDA ↔ IFFCO Chowk (Rapid)
    graph[55][95] = graph[55][95] = 1; // MG Road ↔ Sector 45
    graph[5][99] = graph[5][99] = 1;   // Yamuna Bank ↔ Okhla Bird Sanctuary

    int source;
    cout << "Select source station (0 - " << N-1 << "):" << endl;
    for (int i = 0; i < N; i++) {
        cout << i << " → " << stations[i] << endl;
    }
    cin >> source;

    if (source >= 0 && source < N)
        dijkstra(graph, source, stations);
    else
        cout << "Invalid station number!" << endl;

    return 0;
}
