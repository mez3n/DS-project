#pragma once
#include"Process.h"
#include"LinkedList.h"
#include"Processor.h"
#include"Processor_FCFS.h"
#include"Processor_RR.h"
#include"Processor_SJF.h"
#include"Stream.h"
#include"queue.h"
class scheduler :public Stream{
	LinkedList<Processor*> ProcessorsList;
	LinkedQueue<Process> processesList; // first process enter is the first process executed
	int FCFS_no, SJF_no, RR_no, Processes_no;
public:
	scheduler();
};
