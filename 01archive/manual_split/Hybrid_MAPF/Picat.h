#include "instance.h"

#ifndef PICAT_H
#define PICAT_H

class PicatInstance
{
public:
	PicatInstance(Instance*);
	void Solve(std::vector<int>&, std::vector<int>&);

	long long total_time;
	int makespan;
	std::vector<std::vector<int> > plan;
private:
	Instance* inst;
	std::string solver_input;
	std::string solver_output;
	std::string solver_name;
};

#endif /* PICAT_H */