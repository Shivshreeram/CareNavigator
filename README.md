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

1. **Compile the Code**:
   Use a C++ compiler to compile the program. For example:
   ```bash
   g++ -std=c++11 HealthcareNetworkPlanner.cpp -o planner

