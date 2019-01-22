#include "dirent.h"
#include "CBS.h"
#include "Picat.h"
#include "ID.h"

using namespace std;

void PrintStatistic(int, ID*, Instance*);

int main()
{
	DIR *dir1;
	int test;
	struct dirent *ent1;
	if ((dir1 = opendir("../instances")) != NULL)
	{
		while ((ent1 = readdir(dir1)) != NULL)
		{
			if (string(ent1->d_name).compare(".") == 0 || string(ent1->d_name).compare("..") == 0 || string(ent1->d_name).compare("solved") == 0)
				continue;

			// Read input
			Instance* inst = new Instance();
			inst->ReadInput(string("../instances/").append(string(ent1->d_name)));

			ID* Solver = new ID(inst);
			int ret_val;
			
			// Solve the instance - use only Picat
			ret_val = Solver->SolveProblem(1);
			PrintStatistic(ret_val, Solver, inst);

			// Solve the instance - use only CBS
			/*ret_val = Solver->SolveProblem(2);
			PrintStatistic(ret_val, Solver, inst);

			// Solve the instance - use both algorithms
			ret_val = Solver->SolveProblem();
			PrintStatistic(ret_val, Solver, inst);*/


			delete inst;
			delete Solver;

			string executable;
			executable = string("move ../instances/").append(string(ent1->d_name)).append(" ../instances/solved");
			system(executable.c_str());
		}
		closedir(dir1);
	}

}


void PrintStatistic(int ret_val, ID* Solver, Instance* inst)
{
	string delimiter = "_";
	ofstream statistic;
	statistic.open(inst->statistic_file, ofstream::out | ofstream::app);
	if (statistic.is_open())
	{
		statistic << "test" << endl;

		statistic.close();
	}
}