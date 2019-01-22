#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <algorithm>

#include "maps.h"

void ParseMap(vector<vector<char> >&, vector<int>&, vector<int>&);
int create(int, int, int, int);

using namespace std;

int main()
{
	vector<int> map = {1};
	vector<int> picat_ag = {15};
	vector<int> cbs_ag = {10};
	int number_of_instances = 5;

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < picat_ag.size(); j++)
			for (int k = 0; k < cbs_ag.size(); k++)
				create(number_of_instances, map[i], picat_ag[j], cbs_ag[k]);
}

int create(int number_of_instances, int map_type, int picat_agents, int cbs_agents)
{
	vector<vector<char> > map;
	vector<int> cbs_nodes;
	vector<int> picat_nodes;
	switch (map_type)
	{
	case 1:
		map = map1;
		break;
	default:
		cout << "Illegal type of map!" << endl;
		return -1;
	}

	ParseMap(map, cbs_nodes, picat_nodes);

	for (int instance_nr = 0; instance_nr < number_of_instances; instance_nr++)
	{
		// name
		stringstream ss;
		ss << "IntersectionType" << map_type << "_" << cbs_agents << "_" << picat_agents << "_" << instance_nr << ".in";
		string filename = ss.str();

		// start and goals
		vector<int> cbs_start;
		vector<int> cbs_goal;
		vector<int> picat_start;
		vector<int> picat_goal;

		srand(time(NULL));

		int added = 0;
		while (added < picat_agents)
		{
			int start_node = rand() % picat_nodes.size();
			while (picat_nodes[start_node] < 0 || find(picat_start.begin(), picat_start.end(), picat_nodes[start_node]) != picat_start.end())
			{
				start_node = rand() % picat_nodes.size();
			}
			picat_start.push_back(picat_nodes[start_node]);

			int end_node = rand() % picat_nodes.size();
			while (picat_nodes[end_node] < 0 || find(picat_goal.begin(), picat_goal.end(), picat_nodes[end_node]) != picat_goal.end())
			{
				end_node = rand() % picat_nodes.size();
			}
			picat_goal.push_back(picat_nodes[end_node]);
			added++;
		}

		added = 0;
		while (added < cbs_agents)
		{
			int start_node = rand() % cbs_nodes.size();
			while (cbs_nodes[start_node] < 0 || find(cbs_start.begin(), cbs_start.end(), cbs_nodes[start_node]) != cbs_start.end())
			{
				start_node = rand() % cbs_nodes.size();
			}
			cbs_start.push_back(cbs_nodes[start_node]);

			int end_node = rand() % cbs_nodes.size();
			while (cbs_nodes[end_node] < 0 || find(cbs_goal.begin(), cbs_goal.end(), cbs_nodes[end_node]) != cbs_goal.end())
			{
				end_node = rand() % cbs_nodes.size();
			}
			cbs_goal.push_back(cbs_nodes[end_node]);
			added++;
		}

		// print
		ofstream out1(string("../instances/").append(filename));
		streambuf *coutbuf1 = cout.rdbuf(); //save old buf
		cout.rdbuf(out1.rdbuf()); //redirect std::cerr to out.txt!

		cout << map.size() << "," << map[0].size() << endl;
		for (size_t i = 0; i < map.size(); i++)
		{
			for (size_t j = 0; j < map[i].size(); j++)
			{
				if (map[i][j] == '@')
					cout << "@";
				else
					cout << ".";
			}
			cout << endl;
		}
		
		cout << "Agents:" << endl;
		cout << cbs_agents + picat_agents << endl;
		for (size_t i = 0; i < picat_goal.size(); i++)
			cout << picat_start[i] << " " << picat_goal[i] << endl;
		for (size_t i = 0; i < cbs_goal.size(); i++)
			cout << cbs_start[i] << " " << cbs_goal[i] << endl;

		cout << "Picat:" << endl;
		cout << picat_agents << endl;
		for (size_t i = 0; i < picat_goal.size(); i++)
			cout << i << " ";
		cout << endl << picat_nodes.size() << endl;
		for (size_t i = 0; i < picat_nodes.size(); i++)
			cout << abs(picat_nodes[i]) << " ";
		cout << endl;

		cout << "CBS:" << endl;
		cout << cbs_agents << endl;
		for (size_t i = 0; i < cbs_goal.size(); i++)
			cout << picat_agents + i << " ";
		cout << endl << cbs_nodes.size() << endl;
		for (size_t i = 0; i < cbs_nodes.size(); i++)
			cout << abs(cbs_nodes[i]) << " ";
		cout << endl;
		
		cout.rdbuf(coutbuf1); //reset to standard output again
	}

	//("pause");
}

void ParseMap(vector<vector<char> >& map, vector<int>& cbs, vector<int>& picat)
{
	int node = 0;
	
	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == '.')
			{
				picat.push_back(-node);
				cbs.push_back(-node);
			}
			if (map[i][j] == '@')
				continue;
			if (map[i][j] == 'c')
				cbs.push_back(node);
			if (map[i][j] == 'p')
				picat.push_back(node);
			node++;
		}
	}
}