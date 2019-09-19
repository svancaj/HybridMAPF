#include "instance.h"

#ifndef CBS_H
#define CBS_H

class CBSInstance
{
public:
	CBSInstance(Instance*);
	void Solve(std::vector<int>&, std::vector<int>&);

	long long total_time;
	int makespan;
	std::vector<std::vector<int> > plan;
private:
	Instance* inst;
	std::string solver_input;
	std::string solver_output;
	std::string solver_name;

	std::pair<int, int> CBSInstance::FindCoordinates(std::vector<std::vector<int> >, int);
};

#endif /* CBS_H */