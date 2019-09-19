#include "Picat.h"

using namespace std;

PicatInstance::PicatInstance(Instance* in)
{
	// parameters
	solver_input = "picat_instance.pi";
	solver_output = "picat_solution.out";
	solver_name = "soc2";

	inst = in;
}

void PicatInstance::Solve(vector<int>& nodes, vector<int>& agents)
{
	vector<vector<int> > graph (nodes.size());
	vector<int> start;
	vector<int> goal;

	// construct graph
	for (size_t i = 0; i < nodes.size(); i++)
	{
		for (size_t j = 0; j < inst->graph[nodes[i]].size(); j++)
		{
			int index = inst->Contains(nodes, inst->graph[nodes[i]][j]);
			if (index != -1)
				graph[i].push_back(index);
		}
	}

	// set starts and goals
	for (size_t i = 0; i < agents.size(); i++)
	{
		start.push_back(inst->Contains(nodes, inst->start[agents[i]]));
		goal.push_back(inst->Contains(nodes, inst->goal[agents[i]]));
	}

	// print
	ofstream picat;
	picat.open(solver_input);
	if (!picat.is_open())
		cout << "fail" << endl;
	picat << "ins(Graph, As) =>" << endl;
	picat << "    Graph = [" << endl;
	for (size_t i = 0; i < graph.size(); i++)
	{
		if (i != 0)
			picat << "," << endl;
		picat << "    $neibs(" << i + 1 << ",[" << i + 1;

		for (size_t j = 0; j < graph[i].size(); j++)
			picat << "," << graph[i][j] + 1;

		picat << "])";
	}

	picat << endl << "    ]," << endl;
	picat << "    As = [";
	for (size_t i = 0; i < agents.size(); i++)
	{
		if (i != 0)
			picat << ",";
		picat << "(" << start[i] + 1 << "," << goal[i] + 1 << ")";
	}

	picat << "].";

	picat.close();

	// solve by picat
	stringstream ss_exec;
	ss_exec << "bash -c \'timeout " << inst->timeout << " ./picat " << solver_name << " " << solver_input << "' > " << solver_output;
	string execute = ss_exec.str();
	cout << execute << endl;
	system(execute.c_str());

	// read output
	string line;
	string s_dump;
	float elapsed_time;
	ifstream input(solver_output);
	if (input.is_open())
	{
		while (getline(input, line))
		{
			stringstream ss(line);
			ss >> s_dump;
			if (s_dump.compare("CPU") == 0)
			{
				ss >> s_dump;
				ss >> elapsed_time; // this is time elapsed in s
				total_time = elapsed_time * 1000;
				break;
			}
		}
		while (getline(input, line))
		{
			stringstream ss(line);
			ss >> s_dump;
			if (s_dump.compare("timesteps") == 0)
			{
				ss >> makespan; // this is measured makespan
				break;
			}
		}

		plan = vector<vector<int> >(agents.size(), vector<int>(makespan));

		for (int i = 0; i < agents.size(); i++)
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

	}
}