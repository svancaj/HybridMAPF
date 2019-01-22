#include <set>
#include "instance.h"

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

class Dijkstra
{
public:
	Dijkstra(Instance*);

	void ShortestPath(int, int, std::vector<int>&);

private:
	Instance* inst;
};

#endif /* DIJKSTRA_H */