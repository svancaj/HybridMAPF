#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <algorithm>

#ifndef INSTACE_H
#define INSTACE_H

class Instance
{
public:
	void ReadInput(std::string);
	void PrintStatistic(long long, long long, long long);

	int Contains(std::vector<int>&, int);

	std::string input_filename;
	std::string statistic_file;

	int timeout;		//timeout in s
	int nodes;
	int agents;

	int rows;
	int columns;

	std::vector<int> start;
	std::vector<int> goal;

	std::vector<int> picat_agents;
	std::vector<int> picat_nodes;

	std::vector<int> cbs_agents;
	std::vector<int> cbs_nodes;

	std::vector<int> all_agents;
	std::vector<int> all_nodes;

	std::vector<std::vector<int> > graph;		// list of neighbours
	std::vector<std::vector<int> > int_graph;	// input grid
};

#endif /* INSTACE_H */