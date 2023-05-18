#include"Processor_EDF.h"
#include"scheduler.h"
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
void Processor_EDF::print()
{
	RDYlist->PrintList();
}
bool Processor_EDF::IsRdyEmpty() { return (RDYlist->isEmpty()); }
void Processor_EDF::set_sigkill(LinkedQueue<sigkill>& kill_queue)
{
}
void Processor_EDF::kill_sig(int timestep)
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


void Processor_EDF::ScheduleAlgo()
{
	if (!Runprocess)
	{
		if (!RDYlist->isEmpty())
		{
			RDYlist->dequeue(Runprocess);
			state = true;
			FinishTime -= Runprocess->getLeftCT();
			count--;
			if (Runprocess->get_RT() == -1)
			{
				Runprocess->set_RT(assistant->get_timestep());
			}
		}
		else
		{
			state = false;
			return;
		}
	}
	else
	{
		Process* tmp;
		RDYlist->peek(tmp);
		if (tmp->getdeadline() < Runprocess->getdeadline())
		{
			FinishTime += Runprocess->getLeftCT();
			RDYlist->enqueue(Runprocess, Runprocess->getdeadline());
			RDYlist->dequeue(Runprocess);
			state = true;
			FinishTime -= Runprocess->getLeftCT();
			if (Runprocess->get_RT() == -1)
			{
				Runprocess->set_RT(assistant->get_timestep());
			}
		}
	}
}

Process* Processor_EDF::get_first_process()
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

void Processor_EDF::overheat_check()
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
			while (!RDYlist->isEmpty())// modified (not added)
			{
				RDYlist->dequeue(p);
				assistant->Add_To_Shortest_RDY(p);
			}
		}
	}
}
void Processor_EDF::switch_processes(Processor*& p)
{
	// check implement please (a function that take take the first process in (this) and give it to p)
	Process* px;
	RDYlist->dequeue(px);
	count--;
	FinishTime -= px->getLeftCT();
	p->AddToList(px);
}