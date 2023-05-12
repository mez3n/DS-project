#include"processor.h"
Processor::Processor(int N, int id, string name, scheduler* p):n(N)
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
