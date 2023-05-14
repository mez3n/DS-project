#include"scheduler.h"
int main()
{
	Process* process1= new Process;
	process1->AddProcess(1, 1, 5, 0, nullptr, nullptr);
	Processor* fcfs1 = new Processor_FCFS(8, 1, "FCFS", nullptr , 5,5);
	int timestep = 1;
	int process_no = 1;
	Process* process2 = process1->fork_process(timestep,process_no);
	timestep++;
	Process* process3 = process1->fork_process(timestep,process_no);
	cout << process1->can_fork();
	timestep++;
	process2->fork_process(timestep, process_no);
	timestep++;
	process2->fork_process(timestep, process_no);
	process1->kill_children();
}