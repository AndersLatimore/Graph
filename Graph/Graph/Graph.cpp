//
//  Graph.cpp
//  Graph
//
//  Created by Anders Akesson on 2/17/13.
//  Copyright (c) 2013 Anders Akesson. All rights reserved.
//

#include "Graph.h"
#include <iostream>
#include <fstream>

Graph::Graph()
{
    this->nrOfNodes = nodes.size();
 
}
Graph::Graph(string cities[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Node* node = new Node(cities[i]);
        nodes.push_back(node);
    }
}
Graph::Graph(const Graph& g) 
{
    this->nodes = g.nodes;
    this->edges = g.edges;
    this->nrOfNodes = g.nrOfNodes;
}
Graph::~Graph()
{
    clear();
}
Graph& Graph::operator=(const Graph& g) // obs! att det verkligen blir en kopia
{
    clear();
    
    this->nodes = g.nodes;
    this->edges = g.edges;
    this->nrOfNodes = g.nrOfNodes;
    
    return *this;
}
void Graph::addEdge(string from, string to, int distance)
{
    Edge* e1 = new Edge(nodes[0], nodes[2], 80);
	Edge* e2 = new Edge(nodes[0], nodes[3], 20);
	Edge* e3 = new Edge(nodes[1], nodes[2], 40);
	Edge* e4 = new Edge(nodes[2], nodes[3], 90);
	Edge* e5 = new Edge(nodes[1], nodes[5], 130);
	Edge* e6 = new Edge(nodes[2], nodes[4], 150);
	Edge* e7 = new Edge(nodes[4], nodes[5], 50);
	Edge* e8 = new Edge(nodes[3], nodes[6], 160);
	Edge* e9 = new Edge(nodes[6], nodes[5], 60);
    Edge* e10 = new Edge(nodes[7], nodes[2], 30);
    
    edges.push_back(e1);
    edges.push_back(e2);
    edges.push_back(e3);
    edges.push_back(e4);
    edges.push_back(e5);
    edges.push_back(e6);
    edges.push_back(e7);
    edges.push_back(e8);
    edges.push_back(e9);
    edges.push_back(e10);
}
bool Graph::removeEdge(string from, string to)
{
    bool removed = false;
	
	return removed;
}
bool Graph::hasEdge(string from, string to) const
{
    bool has = false;
    
    return has;
}
int Graph::shortestPath(string from, string to) 
{
    return 0;
}
void Graph::printShortestPath(string from, string to) 
{
   
}
int Graph::getNumberOfNodes() const
{
    return this->nrOfNodes;
}
    // fler funktioner som Du anser vara lämpliga

void Graph::clear()
{
        // clean up
    nodes.erase (nodes.begin(),nodes.end());
    
    edges.erase(edges.begin(), edges.end());
}

    //*****************************************************
    // Here are the functions that actually matters
void Graph::DijkstrasTest()
{
    addEdge("", "", 0);
    
    cout << "This program will tell you the shortest path between 2 cities. " << endl;
    
    Node* start = getStart(nodes);
    while(!start)
    {
        cout << "Not a valid starting point, please re-enter: " << endl;
        start = getStart(nodes);
    }
    
    Node* destination = getDestination(nodes);
    while (!destination)
    {
        cout << "Not a valid destination, please re-enter: " << endl;
        destination = getDestination(nodes);
    }
    
    
    start->distanceFromStart = 0; // set start node
    Dijkstras(edges, nodes);
    printShortestRouteTo(destination, start);
    
}
    //*********************************************************

int Graph::readNodesFromFile(vector<Node*> nodes)
{
	ifstream in;
    int nr = -1;
	
	in.open("cities.txt");
	if(in.is_open())
	{
		in >> nr;
		in.ignore();
        
		for(int i = 0; i < nr; i++)
		{
			string c;
			getline(in, c);
			nodes.push_back(new Node(c));
		}
	}
	in.close();
    
	return nr;
}
void Graph::readEdgeFromFile(vector<Edge*> edges) // read edges from file
{
	ifstream in;
	string from;
	string to;
	int distance;
	
    in.open("distances.txt");
    if(in.is_open())
    {
        while (!in.eof())
        {
            in >> from;
            in >> to;
            in >> distance;
            in.ignore();
            
            edges.push_back(new Edge(new Node(from), new Node(to), distance));
        }
        
    }
    in.close();
}

void Graph::Dijkstras(vector<Edge*>& edges, vector<Node*>& nodes)
{
	while (nodes.size() > 0)
	{
		Node* smallest = extractSmallest(nodes);
		vector<Node*>* adjacentNodes = adjacentRemainingNodes(smallest, edges, nodes);
        
		for (int i = 0; i < adjacentNodes->size(); ++i)
		{
			Node* adjacent = adjacentNodes->at(i);
			int iDistance = distance(smallest, adjacent, edges, nodes) + smallest->distanceFromStart;
			
			if (iDistance < adjacent->distanceFromStart)
			{
				adjacent->distanceFromStart = iDistance;
				adjacent->previous = smallest;
			}
		}
		delete adjacentNodes;
	}
}

    // Find the node with the smallest distance,
    // remove it, and return it.
Node* Graph::extractSmallest(vector<Node*>& nodes)
{
	if (nodes.size() == 0) return NULL;
    
	int smallestPosition = 0;
	Node* smallest = nodes.at(0);
    
	for (int i = 1; i < nodes.size(); ++i)
	{
		Node* current = nodes.at(i);
		if (current->distanceFromStart < smallest->distanceFromStart)
		{
			smallest = current;
			smallestPosition = i;
		}
	}
    nodes.erase(nodes.begin() + smallestPosition);
	return smallest;
}

    // Return all nodes adjacent to 'node' which are still
    // in the 'nodes' collection.
vector<Node*>* Graph::adjacentRemainingNodes(Node* node, vector<Edge*>& edges, vector<Node*>& nodes)
{
	vector<Node*>* adjacentNodes = new vector<Node*>();
    
	for(int i = 0; i < edges.size(); ++i)
	{
		Edge* edge = edges.at(i);
		Node* adjacent = NULL;
        
		if (edge->node1 == node)
		{
			adjacent = edge->node2;
		}
		else if (edge->node2 == node)
		{
			adjacent = edge->node1;
		}
		if (adjacent && contains(nodes, adjacent))
		{
			adjacentNodes->push_back(adjacent);
		}
	}
	return adjacentNodes;
}

    // Return distance between two connected nodes
int Graph::distance(Node* node1, Node* node2, vector<Edge*>& edges, vector<Node*>& nodes)
{
	for(int i = 0; i < edges.size(); ++i)
	{
		Edge* edge = edges.at(i);
        
		if (edge->connects(node1, node2))
		{
			return edge->distance;
		}
	}
	return -1; // should never happen
}

    // Does the 'nodes' vector contain 'node'
bool Graph::contains(vector<Node*>& nodes, Node* node)
{
	for(int i = 0; i < nodes.size(); ++i)
	{
		if (node == nodes.at(i))
		{
			return true;
		}
	}
	return false;
}

    //*********************************************************

void Graph::printShortestRouteTo(Node* destination, Node* start)
{
	Node* previous = destination;
    
	cout << "Distance from " << start->getId() << " to " << destination->getId() << " is " << destination->distanceFromStart << endl;
	while (previous)
	{
		cout << previous->id << "<-";
		previous = previous->previous;
	}
	cout << endl;
}

Node* Graph::getStart(vector<Node*> nodes)
{
    string city = "";
    Node* rtrNode = NULL;
    
    cout << "Enter the starting point: " << endl;
    getline(cin, city);
    
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes.at(i)->getId() == city)
        {
            rtrNode = (nodes.at(i));
        }
        
    }
    return rtrNode;
}

Node* Graph::getDestination(vector<Node*> nodes)
{
    string city = "";
    Node* rtrNode = NULL;
    cout << "Enter the destination: " << endl;
    getline(cin, city);
    
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes.at(i)->getId() == city)
        {
            rtrNode = (nodes.at(i));
        }
        
    }
    return rtrNode;
}

vector<Edge*>* Graph::adjacentEdges(vector<Edge*>& edges, Node* node)
{
	vector<Edge*>* adjacentEdges = new vector<Edge*>();
    
	for(int i = 0; i < edges.size(); ++i)
	{
		Edge* edge = edges.at(i);
		if (edge->node1 == node)
		{
			cout << "adjacent: " << edge->node2->id << endl;
			adjacentEdges->push_back(edge);
		}
		else if (edge->node2 == node)
		{
			cout << "adjacent: " << edge->node1->id << endl;
			adjacentEdges->push_back(edge);
		}
	}
	return adjacentEdges;
}

void Graph::removeEdge(vector<Edge*>& edges, Edge* edge)
{
	vector<Edge*>::iterator it;
	for (it = edges.begin(); it < edges.end(); ++it)
	{
		if (*it == edge)
		{
			edges.erase(it);
			return;
		}
	}
}
