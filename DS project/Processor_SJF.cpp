#include"Processor_SJF.h"
void Processor_SJF::AddToList(Process* p)
{
	FinishTime += p->get_CT();
	RDYlist.InsertEnd(p, p->getPID(), 0);
}
bool Processor_SJF::RunProcess()
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
int Processor_SJF::ExpectedFinishTime()
{
	return FinishTime;
}
void Processor_SJF::print()
{
	RDYlist.PrintList();
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
bool Processor_SJF::IsRdyEmpty() { return (RDYlist.isEmpty()); }