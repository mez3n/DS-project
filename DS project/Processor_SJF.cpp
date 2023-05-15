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
	if (!Runprocess)
	{
		if (!RDYlist->isEmpty())
		{
			RDYlist->dequeue(Runprocess);
			FinishTime -= Runprocess->getLeftCT();
			count--;
			TotalBusyTime++;
			state = true;
			if (Runprocess->get_RT() == -1)
			{
				Runprocess->set_RT(assistant->get_timestep());
			}
		}
		else
		{
			state = false;
			TotalIDLETime++;
		}
	}
	else
	{
		state = true;
		TotalBusyTime++;
	}
}

Process* Processor_SJF::get_first_process()
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

void Processor_SJF::overheat_check()
{
	if (leftn > 0)
	{
		leftn--;
	}
	else
	{
		srand(time(0));
		int  r = 1 + (rand() % 100);
		if (r <= 5 && r > 0)
		{
			FinishTime = 0;
			leftn = n;
			if (Runprocess)
			{
				assistant->Add_To_Shortest_RDY(Runprocess);
				Runprocess = nullptr;
				state = false;
			}
			Process* p;
			while (RDYlist->isEmpty())
			{
				RDYlist->dequeue(p);
				assistant->Add_To_Shortest_RDY(Runprocess);
			}
		}
	}
}
void Processor_SJF::switch_processes(Processor*& p)
{
	// check implement please (a function that take take the first process in (this) and give it to p)
	Process* px;
	RDYlist->dequeue(px);
	p->AddToList(px);
}