#include <numeric>

#include "dirent.h"
#include "CBS.h"
#include "Picat.h"
#include "ID.h"

using namespace std;

void PrintStatistic(int, ID*, Instance*, string, string);

int main()
{
	DIR *dir1;
	int test;
	struct dirent *ent1;
	if ((dir1 = opendir("../instances")) != NULL)
	{
		while ((ent1 = readdir(dir1)) != NULL)
		{
			if (string(ent1->d_name).compare(".") == 0 || string(ent1->d_name).compare("..") == 0 || string(ent1->d_name).compare("solved") == 0 || string(ent1->d_name).compare("maps") == 0)
				continue;

			// Read input
			Instance* inst = new Instance();
			inst->ReadInput(string("../instances/").append(string(ent1->d_name)));
			
			// Makespan
			ID* Solver_mks = new ID(inst, 1);
			int ret_val_mks = 0;
			
			// Solve the instance - use only Picat
			ret_val_mks = 0;
			inst->ResetAgentsNumber();
			while (ret_val_mks == 0)
			{
				inst->IncreaseAgentsNumber();
				ret_val_mks = Solver_mks->SolveProblem(1);
				PrintStatistic(ret_val_mks, Solver_mks, inst, "Picat", "mks");
			}

			// Solve the instance - use only CBS
			ret_val_mks = 0;
			inst->ResetAgentsNumber();
			while (ret_val_mks == 0)
			{
				inst->IncreaseAgentsNumber();
				ret_val_mks = Solver_mks->SolveProblem(2);
				PrintStatistic(ret_val_mks, Solver_mks, inst, "CBS", "mks");
			}
			
			// Solve the instance - use both algorithms
			/*ret_val_mks = 0;
			inst->ResetAgentsNumber();
			while (ret_val_mks == 0)
			{
				inst->IncreaseAgentsNumber();
				ret_val_mks = Solver_mks->SolveProblem();
				PrintStatistic(ret_val_mks, Solver_mks, inst, "Hybrid", "mks");
			}*/
			
			// Sum of Costs
			/*ID* Solver_soc = new ID(inst, 2);
			int ret_val_soc = 0;

			// Solve the instance - use only Picat
			ret_val_soc = 0;
			inst->ResetAgentsNumber();
			while (ret_val_soc == 0)
			{
				inst->IncreaseAgentsNumber();
				ret_val_soc = Solver_soc->SolveProblem(1);
				PrintStatistic(ret_val_soc, Solver_soc, inst, "Picat", "soc");
			}

			// Solve the instance - use only CBS
			ret_val_soc = 0;
			inst->ResetAgentsNumber();
			while (ret_val_soc == 0)
			{
				inst->IncreaseAgentsNumber();
				ret_val_soc = Solver_soc->SolveProblem(2);
				PrintStatistic(ret_val_soc, Solver_soc, inst, "CBS", "soc");
			}

			// Solve the instance - use both algorithms
			ret_val_soc = 0;
			inst->ResetAgentsNumber();
			while (ret_val_soc == 0)
			{
				inst->IncreaseAgentsNumber();
				ret_val_soc = Solver_soc->SolveProblem();
				PrintStatistic(ret_val_soc, Solver_soc, inst, "Hybrid", "soc");
			}*/
			

			delete inst;
			delete Solver_mks;
			//delete Solver_soc;

			string executable;
			executable = string("move ../instances/").append(string(ent1->d_name)).append(" ../instances/solved");
			system(executable.c_str());
		}
		closedir(dir1);
	}

}


void PrintStatistic(int ret_val, ID* Solver, Instance* inst, string solver_type, string note)
{
	string delimiter = "_";
	ofstream statistic;

	int cbs_computed = 0;
	int picat_computed = 0;
	int cbs_used = 0;
	int picat_used = 0;
	long long cbs_time = 0;
	long long picat_time = 0;

	if (solver_type.compare("Hybrid") == 0)
	{
		cbs_computed = Solver->solver_computed[0];
		picat_computed = Solver->solver_computed[1];

		cbs_used = Solver->solver_used[0];
		picat_used = Solver->solver_used[1];

		cbs_time = accumulate(Solver->solver_time[0].begin(), Solver->solver_time[0].end(), 0);
		picat_time = accumulate(Solver->solver_time[1].begin(), Solver->solver_time[1].end(), 0);
	}
	else if (solver_type.compare("CBS") == 0)
	{
		cbs_computed = Solver->solver_computed[0];

		cbs_used = Solver->solver_used[0];

		cbs_time = accumulate(Solver->solver_time[0].begin(), Solver->solver_time[0].end(), 0);
	}
	else if (solver_type.compare("Picat") == 0)
	{
		picat_computed = Solver->solver_computed[0];

		picat_used = Solver->solver_used[0];

		picat_time = accumulate(Solver->solver_time[0].begin(), Solver->solver_time[0].end(), 0);
	}

	statistic.open(inst->statistic_file, ofstream::out | ofstream::app);
	if (statistic.is_open())
	{
		// name of the instance
		statistic << inst->input_filename << delimiter;

		// number of agents used
		statistic << inst->agents << delimiter;

		// what solver was used
		statistic << solver_type << delimiter;

		// what was the objective function
		statistic << note << delimiter;

		// final mks
		statistic << Solver->final_makespan << delimiter;

		// final soc
		statistic << Solver->final_soc << delimiter;

		// was the computation successful
		statistic << (ret_val == 0 ? "success" : "fail") << delimiter;

		// how many times each solver was computed
		statistic << cbs_computed << delimiter;
		statistic << picat_computed << delimiter;

		// how many times each solver was used
		statistic << cbs_used << delimiter;
		statistic << picat_used << delimiter;

		// how much time each solver take
		statistic << cbs_time << delimiter;
		statistic << picat_time << delimiter;

		// how much time it take together - should be just added the two previous
		statistic << cbs_time + picat_time;

		statistic << endl;

		statistic.close();
	}
}