#include"Processor_EDF.h"
Processor_EDF::Processor_EDF(int N,int id,string name,int MAX_SIZE):Processor(N,id,name)
{
	num = 0;
	RDYlist = new PeriorityQueue<Process*>(MAX_SIZE);
}
void Processor_EDF::AddToList(Process* p)
{
	count++;
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
		count--;
		RDYlist->dequeue(Runprocess);
		state = true;
		//Runprocess->SetRunState(true);
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
bool Processor_EDF::IsIdle() 
{
	if (Runprocess == nullptr)
		state = false;
	return!state;
}
Process* Processor_EDF::GetRunProcess()
{
	return Runprocess;
}
bool Processor_EDF::IsRdyEmpty() { return (RDYlist->isEmpty()); }
Processor_EDF::~Processor_EDF()
{
	delete RDYlist;
}
int Processor_EDF::GetRdyCount()
{
	return count;
}
bool  Processor_EDF::GetProcessById(int id, Process*& p) 
{
	return true;
}

void Processor_EDF::removerunprocess()
{
	Runprocess = nullptr;
}