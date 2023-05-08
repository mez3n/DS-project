#include"Processor_RR.h"
Processor_RR::Processor_RR(int N, int id, string name,scheduler* p, int rtf, int rrslice) :Processor(N, id, name,p)
{
	RTF = rtf;
	RRslice = rrslice;
	LeftRRslice = 0;
	numRTF = 0;
}
void Processor_RR::AddToList(Process* p)
{
	count++;
	FinishTime += p->get_CT();
	RDYlist.enqueue(p);
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
		count--;
		RDYlist.dequeue(Runprocess);
		state = true;
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
float Processor_RR::GetPload(int TotalTRTProcesses)
{
	return(TotalBusyTime / TotalTRTProcesses);
}
bool Processor_RR::IsIdle()
{
	if (Runprocess == nullptr)
		state = false;
	return!state;
}
Process* Processor_RR::GetRunProcess()
{
	return Runprocess;
}
bool Processor_RR::IsRdyEmpty() { return (RDYlist.isEmpty()); }
bool  Processor_RR::GetProcessById(int id, Process*& p)
{
	return true;
}

int Processor_RR::GetRdyCount()
{
	return count;
}

void Processor_RR::removerunprocess()
{
	Runprocess = nullptr;
}
