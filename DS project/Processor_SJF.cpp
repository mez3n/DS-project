#include"Processor_SJF.h"
#include"scheduler.h"
Processor_SJF::Processor_SJF(int N, int id, string name, scheduler* p, int MAX_SIZE) :Processor(N, id, name, p)
{
	RDYlist = new PeriorityQueue<Process*>(MAX_SIZE);
}
void Processor_SJF::AddToList(Process* p)
{
	count++;
	FinishTime += p->getLeftCT();
	RDYlist->enqueue(p, p->getLeftCT());
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
		count--;
		RDYlist->dequeue(Runprocess);
		state = true;
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
Process* Processor_SJF::GetRunProcess()
{
	return Runprocess;
}
bool Processor_SJF::IsRdyEmpty() { return (RDYlist->isEmpty()); }
Processor_SJF::~Processor_SJF()
{
	delete RDYlist;
}
void Processor_SJF::set_sigkill(LinkedQueue<sigkill>& kill_queue)
{
}
int Processor_SJF::GetRdyCount()
{
	return count;
}
bool  Processor_SJF::GetProcessById(int id, Process*& p)
{
	return true;
}
void Processor_SJF::removerunprocess()
{
	Runprocess = nullptr;
}

void Processor_SJF::ScheduleAlgo()
{
	// first check runprocess
	if (!Runprocess)
	{
		if (!RDYlist->isEmpty())
		{
			RDYlist->dequeue(Runprocess);
			FinishTime -= Runprocess->getLeftCT();
			count--;
		}
		else
		{
			state = false;
			TotalIDLETime++;
			return;
		}
	}
	// second excute
	Runprocess->decrementCT();
	TotalBusyTime++;
	if (Runprocess->getLeftCT() == 0)
	{
		assistant->move_to_trm(Runprocess);
		Runprocess = nullptr;
	}
	// fifth check for I_O request
	int ct = Runprocess->get_CT();
	int lct = Runprocess->getLeftCT();
	int ior = Runprocess->get_IO_R();
	if (ct - lct == ior)
	{
		assistant->RUNtoBLK(Runprocess);
	}




}

Process* Processor_SJF::get_chosen_process()
{
	if (!Runprocess)
	{
		if (!RDYlist->isEmpty())
		{
			Process* choosen;
			RDYlist->peek(choosen);
			return choosen;
		}
		else
		{
			return nullptr;
		}
	}
	return Runprocess;
}