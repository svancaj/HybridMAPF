#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <algorithm>

#include "maps.h"

using namespace std;

constexpr int AGENTS = 40;

int create(int, int, int);
void set_agents(vector<vector<char> >&, vector<pair<int, int> >&, vector<pair<int, int> >&, int);
bool contains(vector<pair<int, int> >&, int, int);

int main()
{
	vector<int> map = {2,3};
	vector<int> locations = {1,2}; // 1 = random, 2 = centered
	int number_of_instances = 10;

	srand(time(NULL));

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < locations.size(); j++)
		create(number_of_instances, map[i], locations[j]);
}

int create(int number_of_instances, int map_type, int locations_type)
{
	vector<vector<char> > map;
	string map_name;
	string locations_name;
	switch (map_type)
	{
	case 1:
		map = map1;
		map_name = "test";
		break;
	case 2:
		map = map2;
		map_name = "maze-16-16-2";
		break;
	case 3:
		map = map3;
		map_name = "room-16-16-2";
		break;
	default:
		cout << "Illegal type of map!" << endl;
		return -1;
	}

	switch (locations_type)
	{
	case 1:
		locations_name = "random";
		break;
	case 2:
		locations_name = "grouped";
		break;
	default:
		cout << "Illegal starting and goal type of map!" << endl;
		return -1;
	}
	
	for (int instance_nr = 0; instance_nr < number_of_instances; instance_nr++)
	{
		// name
		stringstream ss;
		ss << map_name << "-" << locations_name << "-" << instance_nr << ".scen";
		string filename = ss.str();

		// start and goals
		vector<pair<int, int> > start;
		vector<pair<int, int> > goal;

		set_agents(map, start, goal, locations_type);

		// print
		ofstream out1(string("../instances/").append(filename));
		streambuf *coutbuf1 = cout.rdbuf(); //save old buf
		cout.rdbuf(out1.rdbuf()); //redirect std::cerr to out.txt!

		cout << "version 1" << endl;

		for (size_t i = 0; i < start.size(); i++)
		{
			cout << "0\t" << map_name << ".map\t" << map.size() << "\t" << map.size() << "\t";
			cout << start[i].second << "\t" << start[i].first << "\t" << goal[i].second << "\t" << goal[i].first << "\t";
			cout << "0" << endl;
		}
		
		cout.rdbuf(coutbuf1); //reset to standard output again
	}

	//("pause");
}

void set_agents(vector<vector<char> >& map, vector<pair<int, int> >& start, vector<pair<int, int> >& goal, int locations_type)
{
	if (locations_type == 1) // random
	{
		int placed = 0;
		while (placed < AGENTS)
		{
			int x = rand() % map.size();
			int y = rand() % map.size();
			if (map[x][y] == '@')
				continue;
			if (contains(start, x, y))
				continue;
			start.push_back(make_pair(x, y));
			placed++;
		}

		placed = 0;
		while (placed < AGENTS)
		{
			int x = rand() % map.size();
			int y = rand() % map.size();
			if (map[x][y] == '@')
				continue;
			if (contains(goal, x, y))
				continue;
			goal.push_back(make_pair(x, y));
			placed++;
		}
	}

	if (locations_type == 2) // half is grouped
	{
		int placed = 0;
		while (placed < AGENTS)
		{
			if (placed % 2) // random
			{
				int x = rand() % map.size();
				int y = rand() % map.size();
				if (map[x][y] == '@')
					continue;
				if (contains(start, x, y))
					continue;
				start.push_back(make_pair(x, y));
				placed++;
			}
			else // center
			{
				int x = rand() % (map.size() / 2);
				int y = rand() % (map.size() / 2);
				if (map[x][y] == '@')
					continue;
				if (contains(start, x, y))
					continue;
				start.push_back(make_pair(x, y));
				placed++;
			}
		}

		placed = 0;
		while (placed < AGENTS)
		{
			if (placed % 2) // random
			{
				int x = rand() % map.size();
				int y = rand() % map.size();
				if (map[x][y] == '@')
					continue;
				if (contains(goal, x, y))
					continue;
				goal.push_back(make_pair(x, y));
				placed++;
			}
			else // center
			{
				int x = rand() % (map.size() / 2);
				int y = rand() % (map.size() / 2);
				if (map[x][y] == '@')
					continue;
				if (contains(goal, x, y))
					continue;
				goal.push_back(make_pair(x, y));
				placed++;
			}
		}
	}
}


bool contains(vector<pair<int, int> >& vc, int x, int y)
{
	for (size_t i = 0; i < vc.size(); i++)
		if (vc[i].first == x && vc[i].second == y)
			return true;
	return false;
}