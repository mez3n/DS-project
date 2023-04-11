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
public:
	Stream();
	~Stream();
	void LoadInputs(int& fcfs_no,int& sjf_no,int& rr_no,int& Processes_no); // will be called in main, the function behind reading all inputs from txt file 
};

























#endif
