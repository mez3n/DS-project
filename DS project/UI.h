
#include"scheduler.h"
#ifndef UI_
#define UI_
class UI
{
private:
	int mode;    //0 is interactive mode, 1 is step by step mode(timer),2 is silent mode 
public:
	UI();
	void set_mode();
	void PrintOutput(LinkedList<Process*>& RUN_List,LinkedQueue<Process*>& NEW_LIST, LinkedQueue<Process*>& BLK_LIST, LinkedList<Process*>& TRM_LIST, LinkedList<Processor*>& Processors,
		int timestep, int Processes_no, int Term_no); // print all function called by scheduler at the end of each time step
	~UI();
};
#endif


ostream& operator << (ostream& out, Process* P);

ostream& operator << (ostream& out, Processor* P);

