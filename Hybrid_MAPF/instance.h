#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iterator>

#ifndef INSTACE_H
#define INSTACE_H

class Instance
{
public:
	void ReadInput(std::string);
	void IncreaseAgentsNumber();
	void ResetAgentsNumber();

	void ParseMap(std::string);
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

	std::vector<std::vector<int> > graph;		// list of neighbours
	std::vector<std::vector<int> > int_graph;	// input grid

	std::vector<std::vector<int> > distance;

	/* DEBUG */

	void PrintPlan(std::vector<std::vector<int> >&);
	void CheckPlan(std::vector<std::vector<int> >&);

	int GetPlanMakespan(std::vector<std::vector<int> >&);
	int GetPlanSoC(std::vector<std::vector<int> >&);
};

#endif /* INSTACE_H */