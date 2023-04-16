#include"Processor_FCFS.h"
void Processor_FCFS::AddToList(Process* p)
{
	FinishTime += p->get_CT();
	RDYlist.InsertEnd(p);
}
bool Processor_FCFS::RunProcess()
{
	if (RDYlist.isEmpty())
	{
		state = false;
		Runprocess = nullptr;
	}
	else
	{
		RDYlist.DeleteFirst(Runprocess);
		state = true;
		Runprocess->SetRunState(true);
	}
	return false;
}
int Processor_FCFS::ExpectedFinishTime()
{
	return FinishTime;
}
void Processor_FCFS::print()
{
	RDYlist.PrintList();
}
float Processor_FCFS::GetPload()
{
	return(TotalBusyTime / TotalTRTProcesses);
}
bool Processor_FCFS::IsIdle() { return!state; }
Process* Processor_FCFS::GetRunProcess()
{
	return Runprocess;
}
bool Processor_FCFS::IsRdyEmpty() { return (RDYlist.isEmpty()); }
bool  Processor_FCFS::GetProcessById(int id, Process*& p)
{
	p = nullptr;
	bool b = RDYlist.DeleteNode(p, id);
	return b;
}
