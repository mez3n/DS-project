#include"Processor_SJF.h"
Processor_SJF::Processor_SJF(int MAX_SIZE,int N):Processor(N)
{
	RDYlist = new PeriorityQueue<Process*>(MAX_SIZE);
}
void Processor_SJF::AddToList(Process* p)
{
	count++;
	state = true;
	FinishTime += p->get_CT();
	RDYlist->enqueue( p,p->get_CT());
}
bool Processor_SJF::RunProcess()
{
	if (RDYlist->isEmpty())
	{
		state = false;
		Runprocess = nullptr;
	}
	else
	{
		RDYlist->dequeue(Runprocess);
		state = true;
		Runprocess->SetRunState(true);
	}
	return false;
}
int Processor_SJF::ExpectedFinishTime()
{
	return FinishTime;
}
void Processor_SJF::print()
{
	RDYlist->PrintList();
}
float Processor_SJF::GetPload()
{
	return(TotalBusyTime / TotalTRTProcesses);
}
bool Processor_SJF::IsIdle() { return!state; }
Process* Processor_SJF::GetRunProcess()
{
	return Runprocess;
}
bool Processor_SJF::IsRdyEmpty() { return (RDYlist->isEmpty()); }
Processor_SJF::~Processor_SJF() 
{
	delete RDYlist;
}
int Processor_SJF::GetRdyCount()
{
	return count;
}
bool  Processor_SJF::GetProcessById(int id, Process*& p)
{
	return true;
}