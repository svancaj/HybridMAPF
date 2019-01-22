#include "instance.h"

using namespace std;

void Instance::ReadInput(string f)
{
	// Parameters for solving
	statistic_file = "../statistics/stat.txt";
	timeout = 600; // timeout

	// Read input
	input_filename = f;
	ifstream in;
	in.open(input_filename);
	if (!in.is_open())
		return;

	char c_dump;
	string s_dump;

	// grid size
	in >> rows >> c_dump >> columns;

	getline(in, s_dump);

	// graph
	int_graph = vector<vector<int> >(rows, vector<int>(columns, -1));
	nodes = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			in >> c_dump;
			if (c_dump == '.')
			{
				int_graph[i][j] = nodes;
				nodes++;
			}
		}
	}

	graph = vector<vector<int> >(nodes, vector<int>());

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (int_graph[i][j] != -1)
			{
				// down
				if (i < rows - 1 && int_graph[i + 1][j] != -1)
				{
					graph[int_graph[i][j]].push_back(int_graph[i + 1][j]);
					graph[int_graph[i + 1][j]].push_back(int_graph[i][j]);
				}

				// left
				if (j > 0 && int_graph[i][j - 1] != -1)
				{
					graph[int_graph[i][j]].push_back(int_graph[i][j - 1]);
					graph[int_graph[i][j - 1]].push_back(int_graph[i][j]);
				}
			}
		}
	}

	// agents
	getline(in, s_dump);	//empty line
	getline(in, s_dump);	//"Agents:"

	in >> agents;

	for (int i = 0; i < agents; i++)
	{
		int s, g;
		in >> s >> g;
		start.push_back(s);
		goal.push_back(g);
	}


	/* TODO: do this part automaticaly */

	// picat
	getline(in, s_dump);	//empty line
	getline(in, s_dump);	//"Picat:"

	int picat_agents_nr;
	in >> picat_agents_nr;

	for (int i = 0; i < picat_agents_nr; i++)
	{
		int id;
		in >> id;
		picat_agents.push_back(id);
		all_agents.push_back(id);
	}

	int picat_nodes_nr;
	in >> picat_nodes_nr;

	for (int i = 0; i < picat_nodes_nr; i++)
	{
		int id;
		in >> id;
		picat_nodes.push_back(id);
		all_nodes.push_back(id);
	}

	// CBS
	getline(in, s_dump);	//empty line
	getline(in, s_dump);	//"CBS:"

	int cbs_agents_nr;
	in >> cbs_agents_nr;

	for (int i = 0; i < cbs_agents_nr; i++)
	{
		int id;
		in >> id;
		cbs_agents.push_back(id);
		all_agents.push_back(id);
	}

	int cbs_nodes_nr;
	in >> cbs_nodes_nr;

	for (int i = 0; i < cbs_nodes_nr; i++)
	{
		int id;
		in >> id;
		cbs_nodes.push_back(id);
		all_nodes.push_back(id);
	}

	sort(all_agents.begin(), all_agents.end());

	sort(all_nodes.begin(), all_nodes.end());
	all_nodes.erase(unique(all_nodes.begin(), all_nodes.end()), all_nodes.end());

	/* TODO: do this part automaticaly */
	
	in.close();
}

void Instance::PrintStatistic(long long picat_all, long long cbs_all, long long combined)
{
	string delimiter = "_";
	ofstream statistic;
	statistic.open(statistic_file, ofstream::out | ofstream::app);
	if (statistic.is_open())
	{
		// file name
		statistic << input_filename << delimiter;
		statistic << picat_all << delimiter;
		statistic << cbs_all << delimiter;
		statistic << combined;

		statistic << endl;
	}
}

int Instance::Contains(vector<int>& v, int x)
{
	for (size_t i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;
	return -1;
}