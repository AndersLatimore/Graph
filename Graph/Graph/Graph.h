//
//  Graph.h
//  Graph
//
//  Created by Anders Akesson on 2/17/13.
//  Copyright (c) 2013 Anders Akesson. All rights reserved.
//

#ifndef __Graph__Graph__
#define __Graph__Graph__

#include "Edge.h"
using namespace std;

const int MAX_CITIES = 10000;

class Graph
{
private:
    /*
     Deklarationer för att representera grafen genom
     användande av matris (2-dimensionellt fält)
     samt eventuella hjälpfunktioner
     */
    
    vector<Edge*> edges;
    vector<Node*> nodes;
    unsigned long nrOfNodes;
    
    public:
    Graph();
    Graph(string cities[], int n);
    Graph(const Graph& g); // obs! att det verkligen blir en kopia
    virtual ~Graph();
    Graph& operator=(const Graph& g); // obs! att det verkligen
                                      //blir en kopia
    void addEdge(string from, string to, int distance);
    bool removeEdge(string from, string to);
    bool hasEdge(string from, string to) const;
    int shortestPath(string from, string to);
    void printShortestPath(string from, string to);
    int getNumberOfNodes() const;
        // fler funktioner som Du anser vara lämpliga
    void clear();
    void DijkstrasTest();
    int readNodesFromFile(vector<Node*> nodes);
    void readEdgeFromFile(vector<Edge*> edges);
    void Dijkstras(vector<Edge*>& edges, vector<Node*>& nodes);
    vector<Node*>* adjacentRemainingNodes(Node* node, vector<Edge*>& edges, vector<Node*>& nodes);
    Node* extractSmallest(vector<Node*>& nodes);
    int distance(Node* node1, Node* node2, vector<Edge*>& edges, vector<Node*>& nodes);
    bool contains(vector<Node*>& nodes, Node* node);
    void printShortestRouteTo(Node* destination, Node* start);
    Node* getStart(vector<Node*> nodes);
    Node* getDestination(vector<Node*> nodes);
    vector<Edge*>* adjacentEdges(vector<Edge*>& Edges, Node* node);
    void removeEdge(vector<Edge*>& Edges, Edge* edge);
};

#endif /* defined(__Graph__Graph__) */
