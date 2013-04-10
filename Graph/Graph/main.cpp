//
//  main.cpp
//  Graph
//  A program to calculate the shortest path between two cities
//
//  Created by Anders Akesson on 2/17/13.
//  Copyright (c) 2013 Anders Akesson. All rights reserved.
//

#include <iostream>
#include "Graph.h"

int main()
{
    string cities[] = {"Stockholm", "Gothenburg", "Malmo", "Uppsala", "Sundsvall", "Umea", "Kiruna", "Karlskrona"};
	Graph* myGraph = new Graph(cities, 8);
    
    cout << "\nHere are the cities you can choose from. " << endl;
    cout << "Make sure you spell them correctly. " << endl;
    cout << "\nStockholm\nGothenburg\nMalmo\nUppsala\nSundsvall\nUmea\nKiruna\nKarlskrona\n " << endl;
    
    myGraph->DijkstrasTest();
    
    delete myGraph;
    
    return 0;
}
