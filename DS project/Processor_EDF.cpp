#include"Processor_EDF.h"
void Processor_EDF::AddToList(Process* p)
{
	FinishTime += p->get_CT();
	RDYlist.InsertEnd(p, p->getPID(), 0);
}
bool Processor_EDF::RunProcess()
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
int Processor_EDF::ExpectedFinishTime()
{
	return FinishTime;
}
void Processor_EDF::print()
{
	RDYlist.PrintList();
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
bool Processor_EDF::IsRdyEmpty() { return (RDYlist.isEmpty()); }