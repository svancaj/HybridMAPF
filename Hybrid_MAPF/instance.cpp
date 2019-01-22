#include "instance.h"

using namespace std;

void Instance::ReadInput(string f)
{
	// Parameters for solving
	statistic_file = "../statistics/stat.txt";
	timeout = 600000; // timeout in milliseconds

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
	
	in.close();
}

int Instance::Contains(vector<int>& v, int x)
{
	for (size_t i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;
	return -1;
}

/* DEBUG */

void Instance::PrintPlan(std::vector<std::vector<int> >& plan)
{
	for (size_t i = 0; i < plan.size(); i++)
	{
		cout << "agent " << i << ": ";
		for (size_t j = 0; j < plan[i].size(); j++)
		{
			if (plan[i][j] == -1)
				cout << "X";
			else if (plan[i][j] == -2)
				cout << "G";
			else
				cout << plan[i][j];
			if (j != plan[i].size() - 1)
				cout << "=>";
		}
		cout << endl;
	}
}

void Instance::CheckPlan(std::vector<std::vector<int> >& plan)
{
	size_t plan_length = 0;
	for (size_t i = 0; i < plan.size(); i++)
		plan_length = max(plan_length, plan[i].size());

	if (plan_length == 0)
	{
		cout << "Empty plan!" << endl;
		return;
	}

	for (size_t i = 0; i < plan_length; i++)
	{
		for (size_t j = 0; j < plan.size(); j++)
		{
			for (size_t k = 0; k < plan.size(); k++)
			{
				if (j == k)
					continue;
				if (plan[j][i] != -1 && plan[j][i] != -2 && plan[j][i] == plan[k][i])
					cout << "Node collision!!! Agents [" << j << "], [" << k << "] at time [" << i << "]" << endl;
				if (i > 0 && plan[j][i] != -1 && plan[j][i] != -2 && plan[j][i - 1] == plan[k][i] && plan[k][i - 1] == plan[j][i])
					cout << "Swap collision!!! Agents [" << j << "], [" << k << "] at times [" << i - 1 << "," << i << "]" << endl;
			}
		}
	}


}
