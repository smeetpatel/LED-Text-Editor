#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "cmdparser.h"
#define TRUE 1
#define FALSE 0
using namespace std;



int main(int argc, char * argv[])
{
	fstream filemanip;
	bool fname;
	//fname: file name given or not
	//exists: given file exists or not
	if(argc!=2)
	{
		fname=FALSE;
		LineEditor cmdline;
		cout<<"\"?\" [New File]"<<endl;
	}
	else
	{
		fname=TRUE;
		filemanip.open(argv[1],ios::in);
		if(filemanip.good())
		{
			//exists = TRUE;
			LineEditor cmdline(filemanip,argv[1]);
		}
		else
		{
			//exists = FALSE;
			LineEditor cmdline;
			cout<<"\""<<argv[1]<<"\""<<" [New File]"<<endl;
		}
	}
	//till now, object of LineEditor is created. Now we enter command mode!
	cout<<"Entering Command Mode."<<endl;
	cout<<":";
	cmdline.run(fname,exists,argv[1]); //run until user quits 
	
	return 0;
}

