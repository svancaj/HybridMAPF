#include "instance.h"
#include "Solver.h"

#ifndef PICAT_H
#define PICAT_H

class PicatSolver : public Solver
{
public:
	PicatSolver(Instance*);
	void Solve(std::vector<int>&, std::vector<std::vector<int> >&, int, long long);
	int ReadResults(std::vector<std::vector<int> >&);

private:
	Instance* inst;
	std::string solver_input;
	std::string solver_output;
	std::string solver_name;
};

#endif /* PICAT_H */