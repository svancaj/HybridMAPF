#include "CBS.h"

using namespace std;

CBSSolver::CBSSolver(Instance* in)
{
	// parameters
	solver_input = "cbs_instance.in";
	solver_output = "cbs_solution.out";
	solver_name = "cbs.exe";

	inst = in;
}

void CBSSolver::Solve(vector<int>& agents_to_plan, vector<vector<int> >& agents_to_avoid, int Cost, long long timeout_ms)
{
	/*vector<vector<int> > graph = inst->int_graph;
	vector<pair<int,int> > start;
	vector<pair<int,int> > goal;

	// construct graph
	for (size_t i = 0; i < graph.size(); i++)
	{
		for (size_t j = 0; j < graph[i].size(); j++)
		{
			if (inst->Contains(nodes, graph[i][j]) == -1)
				graph[i][j] = -1;
		}
	}

	// set starts and goals
	for (size_t i = 0; i < agents.size(); i++)
	{
		start.push_back(FindCoordinates(graph, inst->start[agents[i]]));
		goal.push_back(FindCoordinates(graph, inst->goal[agents[i]]));
	}

	// print
	ofstream cbs;
	cbs.open(solver_input);
	if (!cbs.is_open())
		cout << "fail" << endl;

	cbs << "Grid:" << endl;
	cbs << inst->rows << "," << inst->columns << endl;

	for (size_t i = 0; i < graph.size(); i++)
	{
		for (size_t j = 0; j < graph[i].size(); j++)
		{
			if (graph[i][j] == -1)
				cbs << "@";
			else
				cbs << ".";
		}
		cbs << endl;
	}

	cbs << "Agents:" << endl;
	cbs << agents.size() << endl;

	for (size_t i = 0; i < agents.size(); i++)
	{
		cbs << i << "," << goal[i].first << "," << goal[i].second << "," << start[i].first << "," << start[i].second << endl;
	}
	

	cbs.close();

	// solve by CBS
	stringstream ss_exec;
	ss_exec << solver_name << " " << inst->timeout * 1000 << " > " << solver_output;
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
			if (s_dump.compare("Time") == 0)
			{
				ss >> s_dump;
				ss >> s_dump;
				ss >> elapsed_time; // this is time elapsed in ms
				total_time = elapsed_time;
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
				int x_location, y_location;
				single_agent_plan >> x_location >> y_location;
				plan[i][j] = graph[x_location][y_location];
			}
		}
		input.close();

	}*/
}

int CBSSolver::ReadResults(vector<vector<int> >& plan)
{
	return 1;
}

pair<int, int> CBSSolver::FindCoordinates(vector<vector<int> > graph, int node_id)
{
	for (size_t i = 0; i < graph.size(); i++)
	{
		for (size_t j = 0; j < graph[i].size(); j++)
		{
			if (graph[i][j] == node_id)
				return make_pair(i,j);
		}
	}
}