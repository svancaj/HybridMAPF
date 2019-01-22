#include "instance.h"
#include "Solver.h"
#include "Picat.h"
#include "CBS.h"
#include "Dijkstra.h"

#ifndef ID_H
#define ID_H

class ID
{
public:
	ID(Instance*);
	int SolveProblem(int solver = -1);

private:
	Instance* inst;
	Dijkstra* single_path;
	std::vector<Solver*> solvers;
	std::vector<int> solver_computed;
	std::vector<int> solver_used;
	std::vector<std::vector<long long> > solver_time;

	std::vector<std::vector<int> > groups;
	std::vector<int> agent_to_group;
	std::vector<std::pair<int, int> > conflicted_groups;
	std::vector<std::vector<int> > current_plan;

	long long runtime;

	bool CheckForConflicts(int&, int&);
	bool CheckPastConflicts(int, int);
	void MergeGroups(int, int);
	int ComputeGroupCost(int);
	void FixPlan(std::vector<int>&, std::vector<std::vector<int> >&);

	int PlanForGroups(int, int, int);

	int CleanUp(int);
};

#endif /* ID_H */