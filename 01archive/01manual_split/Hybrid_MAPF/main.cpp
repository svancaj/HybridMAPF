#include "dirent.h"
#include "CBS.h"
#include "Picat.h"

using namespace std;

int main()
{
	DIR *dir1;
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
			
			// Pure Picat
			/*PicatInstance* pure_picat = new PicatInstance(inst);
			pure_picat->Solve(inst->all_nodes, inst->all_agents);

			// Pure CBS
			CBSInstance* pure_CBS = new CBSInstance(inst);
			pure_CBS->Solve(inst->all_nodes, inst->all_agents);

			// Mixed instance
			PicatInstance* picat = new PicatInstance(inst);
			picat->Solve(inst->picat_nodes, inst->picat_agents);
			CBSInstance* CBS = new CBSInstance(inst);
			CBS->Solve(inst->cbs_nodes, inst->cbs_agents);

			inst->PrintStatistic(pure_picat->total_time, pure_CBS->total_time, picat->total_time + CBS->total_time);*/


			// small maps
			PicatInstance* picat1 = new PicatInstance(inst);
			picat1->Solve(inst->picat_nodes, inst->picat_agents);
			//CBSInstance* CBS1 = new CBSInstance(inst);
			//CBS1->Solve(inst->picat_nodes, inst->picat_agents);
			long long small_picat = picat1->total_time;
			//long long small_cbs = CBS1->total_time;

			// big maps
			PicatInstance* picat2 = new PicatInstance(inst);
			picat2->Solve(inst->cbs_nodes, inst->cbs_agents);
			CBSInstance* CBS2 = new CBSInstance(inst);
			CBS2->Solve(inst->cbs_nodes, inst->cbs_agents);
			long long big_picat = picat2->total_time;
			long long big_cbs = CBS2->total_time;

			inst->PrintStatistic(small_picat + big_picat, /*small_cbs*/ 0 + big_cbs, small_picat + big_cbs);

			/*PicatInstance* picat = new PicatInstance(inst);
			picat->Solve(inst->all_nodes, inst->all_agents);
			CBSInstance* CBS = new CBSInstance(inst);
			CBS->Solve(inst->all_nodes, inst->all_agents);
			long long small_picat = picat->total_time;
			long long small_cbs = CBS->total_time;*/

			// inst->MergeSolutions();

			//inst->PrintStatistic(small_picat, /*big_picat*/ 0, small_cbs, /*big_cbs*/ 0);

			delete inst;

			string executable;
			executable = string("move ../instances/").append(string(ent1->d_name)).append(" ../instances/solved");
			system(executable.c_str());
		}
		closedir(dir1);
	}

}
