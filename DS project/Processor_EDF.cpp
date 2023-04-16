#include"Processor_EDF.h"
Processor_EDF::Processor_EDF(int MAX_SIZE)
{
	RDYlist = new PeriorityQueue<Process*>(MAX_SIZE);
}
void Processor_EDF::AddToList(Process* p)
{
	FinishTime += p->get_CT();
	RDYlist->enqueue(p,p->get_CT());
}
bool Processor_EDF::RunProcess()
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
int Processor_EDF::ExpectedFinishTime()
{
	return FinishTime;
}
void Processor_EDF::print()
{
	RDYlist->PrintList();
}
float Processor_EDF::GetPload()
{
	return(TotalBusyTime / TotalTRTProcesses);
}
bool Processor_EDF::IsIdle() { return!state; }
Process* Processor_EDF::GetRunProcess()
{
	return Runprocess;
}
bool Processor_EDF::IsRdyEmpty() { return (RDYlist->isEmpty()); }
Processor_EDF::~Processor_EDF()
{
	delete RDYlist;
}