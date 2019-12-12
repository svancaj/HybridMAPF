# HybridMAPF
This algorithm solves the Multi-agent pathfinding (MAPF) problem. It uses the algorithm Independence Detection (ID) over several optimal MAPF solvers. The original ID algorithm gives us a guide on how to split the whole instance of MAPF into smaller sub-problems. However, there are no limitations on what solver to use on these smaller problems. So far we have incorporated CBS, ICTS, and SAT-based solver.

# Functionality
The code provides the option to compute either makespan optimal or sum of costs optimal solutions. The user can also choose to use either full ID algorithm or simple ID algorithm.

Simple ID - Start with groups consisting of single agents. Find a path for each group. While any two groups collide, merge them and replan for the new group.

Full ID - Start with groups consisting of single agents. Find a path for each group. While any two groups collide, try to replan either of the groups so that they do not collide (while keeping the solution cost). If such replan is not possible, merge the groups.

The switching of the parameters can be done in the main.cpp file.

For each group, each solver is used to find a solution in parallel and the result of the fastest one is used. !Note that the parallelism is only simulated. In the current implementation, each algorithm is run one by one and the fastest is used. Implementation of the threading is on a TODO list.

# SAT-based Solver
bin/mks.pi - makespan optimal model for SAT-based MAPF solver coded in Picat
bin/soc.pi - sum of costs optimal model for SAT-based MAPF solver coded in Picat
bin/picat_instance.pi - instance for either of the model
bin/picat_solution.out - output of the solver

To run the picat solver, only files [picat, exs, lib, mks.pi, soc.pi] are needed. The picat binary must be run on a Unix-based machine. Ubuntu for windows is sufficient.

Usage example> ./picat mks.pi picat_instance.pi

The output is the number of agents (a) and the number of timesteps used (n) and a matrix a times n. Each line corresponds to a path of a single agent.
