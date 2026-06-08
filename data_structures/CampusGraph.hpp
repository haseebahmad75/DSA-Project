#ifndef CAMPUS_GRAPH_HPP
#define CAMPUS_GRAPH_HPP

#include<iostream>
#include<string>
using namespace std;

struct GraphEdge
{
    int targetIndex;
    int distance;
    GraphEdge * next;

    GraphEdge(int target, int dist) : targetIndex(target) , distance(dist), next(nullptr) {}
};

class CampusGraph
{
    private:
    static const int MAX_BUILDINGS = 10;
    string names[MAX_BUILDINGS];
    GraphEdge * list[MAX_BUILDINGS];
    int totalBuildings;

    int getBuildingIndex(const string& name)
    {
        for(int i=0; i<totalBuildings; i++)
        {
            if(names[i] == name)
            return i;
        }
        return -1;
    }

    int findMinDistanceVertex(int distances[], bool visited[])
    {
        int minDistance = 2147483647; // Simulating INT_MAX
        int minIndex = -1;

        for (int v = 0; v < totalBuildings; v++) {
            if (!visited[v] && distances[v] <= minDistance) 
            {
                minDistance = distances[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    void printPathTrace(int parent[], int j)
    {
        if (parent[j] == -1)
        return;
        printPathTrace(parent, parent[j]);
        cout << " -> " << names[j];
    }

    public:

    CampusGraph() : totalBuildings(0) {
        // Initialize all head pointers to nullptr (empty neighbor lists)
        for (int i = 0; i < MAX_BUILDINGS; i++) {
            list[i] = nullptr;
        }
    }

    // Destructor to clean up all dynamically allocated edge nodes in heap memory
    ~CampusGraph()
    {
        for (int i = 0; i < totalBuildings; i++) 
        {
            GraphEdge* current = list[i];
            while (current != nullptr) 
            {
                GraphEdge* nextEdge = current->next;
                delete current;
                current = nextEdge;
            }
        }
    }

    bool addBuilding(const string& name) {
        if (totalBuildings >= MAX_BUILDINGS) 
        return false;
        if (getBuildingIndex(name) != -1) 
        return true; // Already registered

        names[totalBuildings] = name;
        list[totalBuildings] = nullptr; // Ensure empty head initialization
        totalBuildings++;
        return true;
    }

    // Create a bi-directional walkway using an Adjacency List (Inserting to the front of the linked list)
    void addWalkway(const string& from, const string& to, int distanceMeters)
    {
        addBuilding(from);
        addBuilding(to);
        int i = getBuildingIndex(from);
        int j = getBuildingIndex(to);
        
        // 1. Add edge from 'from' -> 'to'
        GraphEdge* newEdge1 = new GraphEdge(j, distanceMeters);
        newEdge1->next = list[i];
        list[i] = newEdge1;

        // 2. Add edge from 'to' -> 'from' (Undirected Graph requirement)
        GraphEdge* newEdge2 = new GraphEdge(i, distanceMeters);
        newEdge2->next = list[j];
        list[j] = newEdge2;
    }

    void calculateShortestRoute(const string& startBuilding, const string& endBuilding)
    {
        int src = getBuildingIndex(startBuilding);
        int dest = getBuildingIndex(endBuilding);

        if(src == -1 || dest == -1)
        {
            cout<<"Navigation error: Campus names not found.\n";
            return;
        }

        int distances[MAX_BUILDINGS];
        bool visited[MAX_BUILDINGS];
        int parent[MAX_BUILDINGS]; // stores from which node the next node is

        for(int i = 0; i < totalBuildings; i++)
        {
            distances[i] = 2147483647; // infinite value is assigned to each node in the beginning
            visited[i] = false;
            parent[i] = -1;
        }

        distances[src] = 0;

        for(int count  = 0; count < totalBuildings-1; count++)
        {
            int u = findMinDistanceVertex(distances, visited);
            if(u == -1) break;

            visited[u] = true;

            GraphEdge * edgeCrawler = list[u];
            while(edgeCrawler != nullptr)
            {
                int v = edgeCrawler->targetIndex;
                int weight = edgeCrawler->distance;

                if(!visited[v] && distances[u] != 2147483647 && distances[u] + weight < distances[v])
                {
                    distances[v] = distances[u] + weight;
                    parent[v] = u;
                }
                edgeCrawler = edgeCrawler->next;
            }
        }
        if(distances[dest] == 2147483647)
        {
            cout<<"No walking paths connect " <<startBuilding <<" to " <<endBuilding <<"\n";
            return;
        }

        cout << "\n==================================================\n";
        cout << "        OPTIMAL ROUTE FOUND (ADJACENCY LIST)      \n";
        cout << "==================================================\n";
        cout << " Origin        : " << startBuilding << "\n";
        cout << " Destination   : " << endBuilding << "\n";
        cout << " Shortest Distance: " << distances[dest] << " meters\n";
        cout << " Path Guidance : " << names[src];
        printPathTrace(parent, dest);
        cout << "\n==================================================\n";
    }
};

#endif