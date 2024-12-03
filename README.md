# Healthcare Network Planner

## Overview

The **Healthcare Network Planner** is a C++ program designed to model and manage a network of healthcare facilities, such as hospitals, labs, and clinics. The application allows users to add facilities, establish connections, and find the nearest facility of a specific type based on distance. It uses **Dijkstra's algorithm** for shortest-path computation and incorporates advanced data structures like **graphs**, **red-black trees**, and **minimum spanning trees (MST)** for efficient operations.

---

## Features

- **Facility Management**:
  - Add facilities with unique IDs, names, and types (Hospital, Lab, Clinic).
  - Automatically assign a random ID to new facilities.

- **Connection Management**:
  - Establish bidirectional connections between facilities with weighted distances.

- **Pathfinding and Recommendations**:
  - Find the nearest facility of a specific type (e.g., nearest lab from a hospital).
  - Display the shortest path and total distance.

- **Interactive Options**:
  - View the network's adjacency list representation.
  - Add new facilities with random connections.
  - Get recommendations based on current facility type.

---

## Prerequisites

- A C++ compiler supporting C++11 or later (e.g., GCC, Clang, or MSVC).
- Basic understanding of C++ for compilation and execution.

---

## Usage

### Compilation and Execution

1. **Clone the repository**:
   
        git clone https://github.com/<ShivShreeram>/healthcare-network-planner.git
        cd healthcare-network-planner

3. **Compile the code**:

        g++ -o HealthcareNetworkPlanner HealthcareNetworkPlanner.cpp

4. **Run the program**:

        ./HealthcareNetworkPlanner

### Commands

Upon running the program, you'll be presented with a menu:

  - **View the Network**:
      Enter 'n' to display the network in an adjacency list format.

  - **Add a New Facility**:
      Enter 'a' to add a new facility. You'll be prompted to provide the facility name and type (Hospital, Lab, or Clinic).

  - **View Recommendations**:
      Enter the facility ID to get recommendations based on its type:
          Hospital: Recommend the nearest lab for reports or the nearest clinic for outpatient services.
          Clinic: Recommend the nearest hospital or lab.
          Lab: Recommend the nearest hospital or clinic.

  - **Quit the Program**:
      Enter 'q' to exit the program.

### Example

**Connections:**

  City Hospital ↔ Greenwood Lab (Distance: 5)
  Greenwood Lab ↔ Downtown Clinic (Distance: 7)
  City Hospital ↔ Central Hospital (Distance: 10)

---

## Data Structures
1. **Graph**

   **Description**: The network is modeled as a graph where each healthcare facility is a node, and each connection is an edge with a weight (distance).

   **Implementation**:
        Adjacency List: Stores connections as a vector of pairs for each node. Each pair contains the destination node and the weight of the edge.
        Efficient for sparse graphs and operations like adding edges or traversing neighbors.

3. **Red-Black Tree**

    **Description**: Red-black trees are used internally by the unordered_map to manage the facilities. Each facility is a key-value pair where the key is the facility ID and the value is a Facility object.

   Why **Red-Black Trees**?
   Guarantees logarithmic time complexity for insertions, deletions, and lookups.
   Ensures balance, making operations efficient even with a large number of facilities.

4. **Minimum Spanning Tree (MST)**

    **Description**: Although the program doesn't explicitly compute an MST, the concept can be applied to optimize the network by connecting all facilities with the minimum total weight.

   Potential Enhancement: Implementing Kruskal's or Prim's algorithm to compute an MST for planning the optimal layout of new healthcare facilities or improving existing networks.

---

## Key Algorithms

  Dijkstra's Algorithm:
      Used to find the shortest path between facilities.
      Handles weighted edges effectively.

  Adjacency List Representation:
      Efficient data structure for storing sparse graphs.

---

## Future Enhancements

  Add functionality for dynamic removal of facilities and connections.
  Implement MST computation for network optimization.
  Visualize the network using tools like Graphviz or integrate graphical output.

---

## Author

Developed by ShivShreeram P and K Sai Charan as a project to demonstrate network modeling, advanced data structures, and shortest-path algorithms in C++.
