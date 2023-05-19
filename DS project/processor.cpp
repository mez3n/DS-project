#include"processor.h"
#include"scheduler.h"
Processor::Processor(int N, int id, string name, scheduler* p) :n(N)
{
	state = false;
	count = 0;
	TotalBusyTime = 0;
	FinishTime = 0;
	TotalIDLETime = 0;
	Runprocess = nullptr;
	ID = id;
	Name = name;
	assistant = p;
	leftn = 0;
}
float Processor::GetPload(int TotalTRTProcesses)
{
	return(TotalBusyTime / TotalTRTProcesses);
}
float Processor::calcPutil()
{
	return ((TotalBusyTime) / (TotalBusyTime + TotalIDLETime));
}
bool Processor::IsIdle()
{
	return !state;
}
void Processor::checkIO_request() 
{
	if (Runprocess)
	{
		if (Runprocess->is_forked())
			return;
		int ct = Runprocess->get_CT();
		int lct = Runprocess->getLeftCT();
		int ior = Runprocess->get_IO_R();
		if (ct - lct == ior)
		{
			assistant->RUNtoBLK(Runprocess);
			Runprocess = nullptr;
			state = false;
		}
	}
}
float Processor::ExpectedFinishTime()
{
	return FinishTime;
}
bool Processor::IsStop()
{
	return (leftn > 0);
}
Process* Processor::GetRunProcess()
{
	return Runprocess;
}
void Processor::removerunprocess()
{
	Runprocess = nullptr;
	state = false;
}
void Processor::UpdateProcessor()
{
	if (state)
		TotalBusyTime++;
	else
		TotalIDLETime++;
}