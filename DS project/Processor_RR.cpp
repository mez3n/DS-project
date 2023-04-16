#include"Processor_RR.h"
void Processor_RR::AddToList(Process* p)
{
	FinishTime += p->get_CT();
	RDYlist.InsertEnd(p, p->getPID(), 0);
}
bool Processor_RR::RunProcess()
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
int Processor_RR::ExpectedFinishTime()
{
	return FinishTime;
}
void Processor_RR::print()
{
	RDYlist.PrintList();
}
float Processor_RR::GetPload()
{
	return(TotalBusyTime / TotalTRTProcesses);
}
bool Processor_RR::IsIdle() { return!state; }
Process* Processor_RR::GetRunProcess()
{
	return Runprocess;
}
bool Processor_RR::IsRdyEmpty() { return (RDYlist.isEmpty()); }