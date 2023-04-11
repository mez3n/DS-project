#ifndef STREAM_
#define STREAM_
#include <fstream>
#include<iostream>
#include<string>
using namespace std;
class Stream //reading all data from input file and making the output file
{
private:
	ifstream* InputFile;
	ofstream* OutputFile;
	int FCFS_no, SJF_no, RR_no, processes_no;
public:
	Stream();
	~Stream();
	void LoadProcesses(int pid ,int no_IO, int at, int rt, int ct,int*& IO_r,int*& IO_d); // will be called in main, the function behind reading all inputs from txt file 
	void get_counts(int& no_fcfs, int& no_sjf, int& rr, int& process_no);
	void load_sigkill(int*& kill_arr);
};

























#endif
