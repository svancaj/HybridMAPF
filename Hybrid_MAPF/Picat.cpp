#include "Picat.h"

using namespace std;

PicatSolver::PicatSolver(Instance* in)
{
	// parameters
	solver_input = "picat_instance.pi";
	solver_output = "picat_solution.out";
	solver_name = "mks";

	inst = in;
}

void PicatSolver::Solve(vector<int>& agents_to_plan, vector<vector<int> >& agents_to_avoid, int Cost, long long timeout_ms)
{
	ofstream picat;
	picat.open(solver_input);
	if (!picat.is_open())
		cout << "fail" << endl;
	picat << "ins(Graph, As, Avoid, Cost) =>" << endl;
	picat << "    Graph = [" << endl;
	for (size_t i = 0; i < inst->graph.size(); i++)
	{
		if (i != 0)
			picat << "," << endl;
		picat << "    $neibs(" << i + 1 << ",[" << i + 1;

		for (size_t j = 0; j < inst->graph[i].size(); j++)
			picat << "," << inst->graph[i][j] + 1;

		picat << "])";
	}

	picat << endl << "    ]," << endl;
	picat << "    As = [";
	for (size_t i = 0; i < agents_to_plan.size(); i++)
	{
		if (i != 0)
			picat << ",";
		picat << "(" << inst->start[agents_to_plan[i]] + 1 << "," << inst->goal[agents_to_plan[i]] + 1 << ")";
	}

	picat << "]," << endl;

	// avoid
	picat << "    Avoid = new_array(" << max(Cost, 0) << "," << agents_to_avoid.size() << ")," << endl;
	for (size_t i = 0; i < agents_to_avoid.size(); i++)
	{
		for (size_t j = 0; j < agents_to_avoid[i].size(); j++)
		{
			picat << "    Avoid[" << j + 1 << "," << i + 1 << "] = " << agents_to_avoid[i][j] + 1 << "," << endl;
		}
	}

	picat << "    Cost = " << Cost << "." << endl;

	picat.close();

	// solve by picat
	stringstream ss_exec;
	ss_exec << "bash -c \'timeout " << (int)(timeout_ms/1000) << " ./picat " << solver_name << " " << solver_input << "' > " << solver_output;
	string execute = ss_exec.str();
	cout << execute << endl;
	system(execute.c_str());
}


int PicatSolver::ReadResults(vector<vector<int> >& plan)
{
	// read output
	string line;
	string s_dump;
	float elapsed_time;
	int agents, makespan;
	bool valid_solution = false;
	ifstream input(solver_output);
	if (input.is_open())
	{
		// TODO - read agents and makespan correctly
		while (getline(input, line))
		{
			// ok solution
			if (line.compare("agents | timesteps") == 0)
			{
				valid_solution = true;
				break;
			}
			// no solution
			if (line.compare("*** error(failed,main/1)") == 0)
			{
				input.close();
				return 1;
			}
		}

		// timeout or error
		if (!valid_solution)
		{
			input.close();
			return -1;
		}

		getline(input, line);
		stringstream ss(line);
		ss >> agents;
		ss >> makespan;

		plan = vector<vector<int> >(agents, vector<int>(makespan));

		for (int i = 0; i < agents; i++)
		{
			getline(input, line);
			stringstream single_agent_plan(line);
			for (int j = 0; j < makespan; j++)
			{
				int location;
				single_agent_plan >> location;
				plan[i][j] = location - 1;
			}
		}
		input.close();

		return 0;

	}

	return -1;
}