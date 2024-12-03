#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Include this for reverse()

using namespace std;

// Enum to represent facility types
enum FacilityType { HOSPITAL, LAB, CLINIC };

// Structure to represent a healthcare facility
struct Facility {
    int id;
    string name;
    FacilityType type;

    // Constructor to initialize facility with ID, name, and type
    Facility(int i, const string& n, FacilityType t) : id(i), name(n), type(t) {}

    // Default constructor for unordered_map to work
    Facility() : id(-1), name(""), type(HOSPITAL) {}  // Default values
};

// Class to represent the network planner
class HealthcareNetworkPlanner {
private:
    int numFacilities;
    vector<vector<pair<int, int>>> adjList; // Adjacency list {destination, weight}
    unordered_map<int, Facility> facilities; // Map facility ID to Facility object

public:
    HealthcareNetworkPlanner(int n) : numFacilities(n), adjList(n) {
        srand(time(0));  // Seed for random number generation
    }

    // Add a facility
    void addFacility(int id, const string& name, FacilityType type) {
        facilities[id] = Facility(id, name, type);
    }

    // Add a connection between two facilities
    void addConnection(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // Undirected graph
    }

    // Add a new facility with random ID and position
    void addNewFacility() {
        string name;
        int type;
        cout << "Enter the name of the new facility: ";
        cin.ignore();  // To avoid issues with getline after other inputs
        getline(cin, name);

        cout << "Enter the type of the new facility (0 for Hospital, 1 for Lab, 2 for Clinic): ";
        cin >> type;

        if (type < 0 || type > 2) {
            cout << "Invalid type! Defaulting to Hospital.\n";
            type = HOSPITAL;
        }

        // Random ID generation and new facility addition
        int id = numFacilities++;  // Increment the facility count and assign the new ID
        FacilityType facilityType = static_cast<FacilityType>(type);
        addFacility(id, name, facilityType);

        // Resize adjacency list to accommodate the new facility
        adjList.push_back(vector<pair<int, int>>());  // Add empty adjacency list for the new facility

        // Print the details of the newly added facility
        cout << "New facility added:\n";
        cout << "ID: " << id << ", Name: " << name << ", Type: " 
             << (facilityType == HOSPITAL ? "Hospital" : (facilityType == LAB ? "Lab" : "Clinic")) 
             << endl;
        
        // Optionally add random connections for the new facility
        if (numFacilities > 1) {
            int randomConnection = rand() % (numFacilities - 1);  // Connect to a random existing facility
            addConnection(id, randomConnection, rand() % 10 + 1);  // Random weight between 1 and 10
            cout << "Added random connection to facility ID " << randomConnection << endl;
        }
    }

    // Find the nearest facility of a given type using Dijkstra's algorithm
    pair<int, vector<int>> findNearestFacility(int source, FacilityType type) {
        vector<int> distances(numFacilities, INT_MAX);
        vector<int> parent(numFacilities, -1);  // To track the path
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        distances[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (facilities[currentNode].type == type) {
                vector<int> path;
                int node = currentNode;
                while (node != -1) {
                    path.push_back(node);
                    node = parent[node];
                }
                reverse(path.begin(), path.end());  // This requires <algorithm>
                return {distances[currentNode], path}; // Return the distance and the path
            }

            for (auto& neighbor : adjList[currentNode]) {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (distances[currentNode] + edgeWeight < distances[nextNode]) {
                    distances[nextNode] = distances[currentNode] + edgeWeight;
                    parent[nextNode] = currentNode;
                    pq.push({distances[nextNode], nextNode});
                }
            }
        }

        return {-1, {}}; // Return -1 if no facility of the specified type is found
    }

    // View options and recommendations based on facility type
    void viewRecommendations(int source) {
        Facility sourceFacility = facilities[source];
        cout << "You are at: " << sourceFacility.name << " (" 
             << (sourceFacility.type == HOSPITAL ? "Hospital" : 
                 (sourceFacility.type == LAB ? "Lab" : "Clinic")) 
             << ")\n";

        if (sourceFacility.type == HOSPITAL) {
            string reason;
            cout << "Reason (lab_report_recommendation/clinic_recommendation): ";
            cin >> reason;

            if (reason == "lab_report_recommendation") {
                auto [dist, path] = findNearestFacility(source, LAB);
                if (dist != -1) {
                    cout << "Nearest Lab: " << facilities[path.back()].name << " (Distance: " << dist << ")\n";
                    cout << "Path: ";
                    for (int id : path) {
                        cout << facilities[id].name << " -> ";
                    }
                    cout << endl;
                } else {
                    cout << "No Labs available in the network.\n";
                }
            } else if (reason == "clinic_recommendation") {
                auto [dist, path] = findNearestFacility(source, CLINIC);
                if (dist != -1) {
                    cout << "Nearest Clinic: " << facilities[path.back()].name << " (Distance: " << dist << ")\n";
                    cout << "Path: ";
                    for (int id : path) {
                        cout << facilities[id].name << " -> ";
                    }
                    cout << endl;
                } else {
                    cout << "No Clinics available in the network.\n";
                }
            } else {
                cout << "Invalid reason entered.\n";
            }
        } else if (sourceFacility.type == CLINIC) {
            string reason;
            cout << "Reason (hospital_recommendation/lab_report_recommendation): ";
            cin >> reason;

            if (reason == "hospital_recommendation") {
                auto [dist, path] = findNearestFacility(source, HOSPITAL);
                if (dist != -1) {
                    cout << "Nearest Hospital: " << facilities[path.back()].name << " (Distance: " << dist << ")\n";
                    cout << "Path: ";
                    for (int id : path) {
                        cout << facilities[id].name << " -> ";
                    }
                    cout << endl;
                } else {
                    cout << "No Hospitals available in the network.\n";
                }
            } else if (reason == "lab_report_recommendation") {
                auto [dist, path] = findNearestFacility(source, LAB);
                if (dist != -1) {
                    cout << "Nearest Lab: " << facilities[path.back()].name << " (Distance: " << dist << ")\n";
                    cout << "Path: ";
                    for (int id : path) {
                        cout << facilities[id].name << " -> ";
                    }
                    cout << endl;
                } else {
                    cout << "No Labs available in the network.\n";
                }
            } else {
                cout << "Invalid reason entered.\n";
            }
        } else if (sourceFacility.type == LAB) {
            string query;
            cout << "Searching for? (hospital/clinic): ";
            cin >> query;

            if (query == "hospital") {
                auto [dist, path] = findNearestFacility(source, HOSPITAL);
                if (dist != -1) {
                    cout << "Nearest Hospital: " << facilities[path.back()].name << " (Distance: " << dist << ")\n";
                    cout << "Path: ";
                    for (int id : path) {
                        cout << facilities[id].name << " -> ";
                    }
                    cout << endl;
                } else {
                    cout << "No Hospitals available in the network.\n";
                }
            } else if (query == "clinic") {
                auto [dist, path] = findNearestFacility(source, CLINIC);
                if (dist != -1) {
                    cout << "Nearest Clinic: " << facilities[path.back()].name << " (Distance: " << dist << ")\n";
                    cout << "Path: ";
                    for (int id : path) {
                        cout << facilities[id].name << " -> ";
                    }
                    cout << endl;
                } else {
                    cout << "No Clinics available in the network.\n";
                }
            } else {
                cout << "Invalid search query.\n";
            }
        } else {
            cout << "Invalid facility type.\n";
        }
    }

    // Display the network as an adjacency list
    void displayNetwork() {
        cout << "\nHealthcare Network (Adjacency List Representation):\n";
        for (int u = 0; u < numFacilities; ++u) {
            cout << facilities[u].name << " (" << u << "): ";
            for (auto& neighbor : adjList[u]) {
                cout << " -> " << facilities[neighbor.first].name 
                     << " (Distance: " << neighbor.second << ")";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    int numFacilities = 7; // Total number of facilities
    HealthcareNetworkPlanner planner(numFacilities);

    // Pre-add facilities
    planner.addFacility(0, "City Hospital", HOSPITAL);
    planner.addFacility(1, "Greenwood Lab", LAB);
    planner.addFacility(2, "Downtown Clinic", CLINIC);
    planner.addFacility(3, "Central Hospital", HOSPITAL);
    planner.addFacility(4, "Metro Lab", LAB);
    planner.addFacility(5, "Northside Clinic", CLINIC);
    planner.addFacility(6, "Eastside Hospital", HOSPITAL);

    // Pre-add connections
    planner.addConnection(0, 1, 5); // City Hospital to Greenwood Lab
    planner.addConnection(1, 2, 7); // Greenwood Lab to Downtown Clinic
    planner.addConnection(0, 3, 10); // City Hospital to Central Hospital
    planner.addConnection(3, 4, 8); // Central Hospital to Metro Lab
    planner.addConnection(4, 5, 6); // Metro Lab to Northside Clinic
    planner.addConnection(5, 6, 9); // Northside Clinic to Eastside Hospital
    planner.addConnection(2, 6, 12); // Downtown Clinic to Eastside Hospital

    string input;

    cout << "Welcome to the Healthcare Network Planner!\n";

    do {
        cout << "\nEnter 'n' to view the entire network, 'a' to add a new facility, the facility ID to view recommendations, or 'q' to quit: ";
        cin >> input;

        if (input == "q") {
            cout << "Exiting the program. Goodbye!\n";
            break;
        } else if (input == "n") {
            planner.displayNetwork();
        } else if (input == "a") {
            planner.addNewFacility();
        } else {
            int source;
            try {
                source = stoi(input);
            } catch (...) {
                cout << "Invalid input. Please enter a valid facility ID, 'n' for network view, 'a' to add facility, or 'q' to quit.\n";
                continue;
            }

            if (source >= 0 && source < numFacilities) {
                planner.viewRecommendations(source);
            } else {
                cout << "Invalid facility ID.\n";
            }
        }
    } while (true);

    return 0;
}