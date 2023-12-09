#ifndef TXT_READER_H
#define TXT_READER_H

#include <iostream>
#include "structure.h"


void readVertex(istream& iss, int vertex_coords[][2]);
void readEdge(GraphAdjList& g, istream& iss, int vertex_coords[][2]);
void readProduct(GraphAdjList& g, istream& iss);
void readSeller(GraphAdjList& g, istream& iss);
void readDeliveryPerson(GraphAdjList& g, istream& iss);
void readDistributionCenter(GraphAdjList& g, istream& iss);
void readClient(GraphAdjList& g, istream& iss);
void readOrder(GraphAdjList& g, istream& iss);
void readLine(GraphAdjList& g, string line, int vertex_coords[][2]);
GraphAdjList readFile(string filename);

#endif