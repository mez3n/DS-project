#pragma once
#include"Processor_FCFS"
#include"Processor_SJF"
#include"Processor_RR"
#include"Process.h"
#include"Processor.h"
#include"LinkedList.h"
#include"Linkedqueue.h"
#include"Stream.h"
class scheduler:public Stream{
LinkedList<Processor*> Processors;
LinkedQueue<Process> Processes;
int FCFS_no, SJF_no, RR_no,Process_no;
public:
scheduler();
}
