#pragma once
#include"Processor_FCFS.h"
#include"Processor_SJF.h"
#include"Processor_RR.h"
#include"Process.h"
#include"Processor.h"
#include"LinkedList.h"
#include"Linkedqueue.h"
#include"Stream.h"
class scheduler:public Stream{
LinkedList<Processor*> Processors;
LinkedQueue<Process> NEW_LIST;
Stream IO;
int FCFS_no, SJF_no, RR_no,Processes_no;
public:
scheduler();
}
