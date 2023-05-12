#include"Processor_EDF.h"
Processor_EDF::Processor_EDF(int N, int id, string name, scheduler* p, int MAX_SIZE) :Processor(N, id, name, p)
{
	RDYlist = new PeriorityQueue<Process*>(MAX_SIZE);
}
void Processor_EDF::AddToList(Process* p)
{
	count++;
	FinishTime += p->getLeftCT();
	RDYlist->enqueue(p, p->getdeadline());
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
Process* Processor_EDF::GetRunProcess()
{
	return Runprocess;
}
bool Processor_EDF::IsRdyEmpty() { return (RDYlist->isEmpty()); }
void Processor_EDF::set_sigkill(LinkedQueue<sigkill>& kill_queue)
{
}
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

void Processor_EDF::ScheduleAlgo()
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
	else
	{
		Process* tmp;
		RDYlist->peek(tmp);
		if (tmp->getdeadline() < Runprocess->getdeadline())
		{
			RDYlist->enqueue(Runprocess, Runprocess->getdeadline());
			RDYlist->dequeue(Runprocess);
		}
	}
	// second excute
	Runprocess->decrementCT();
	TotalBusyTime++;
	if (Runprocess->getLeftCT() == 0)
	{
		RDYlist->dequeue(Runprocess);
		assistant->move_to_trm(Runprocess);
		Runprocess == nullptr;
	}
	// third check for I_O request
	int ct = Runprocess->get_CT();
	int lct = Runprocess->getLeftCT();
	int ior = Runprocess->get_IO_R();
	if (ct - lct == ior)
	{
		assistant->RUNtoBLK(Runprocess);
	}
}

Process* Processor_EDF::get_chosen_process()
{
	Process* choosen = nullptr;
	if (!Runprocess)
	{
		if (!RDYlist->isEmpty())
		{
			RDYlist->peek(choosen);
		}
	}
	else
	{
		Process* tmp;
		RDYlist->peek(tmp);
		if (tmp->getdeadline() < Runprocess->getdeadline())
		{
			choosen = tmp;
		}
		else
			choosen = Runprocess;
	}
	return choosen;
}