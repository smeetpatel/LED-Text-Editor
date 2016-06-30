#include <iostream>
#include <fstream>
#include <string>
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
	if(argc!=2)
	{
		fname=FALSE;
		LED cmdline;
		cout<<"\"?\" [New File]"<<endl;
		cout<<"Entering Command Mode."<<endl;
		cout<<":";
		cmdline.run(fname,NULL);
	}
	else
	{
		fname=TRUE;
		filemanip.open(argv[1],ios::in);
		if(filemanip.good())
		{
			LED cmdline1(filemanip,argv[1]);
			cout<<"Entering Command Mode."<<endl;
			cout<<":";
			cmdline1.run(fname,argv[1]); //run until user quits 
		}
		else
		{
			LED cmdline2;
			cout<<"\""<<argv[1]<<"\""<<" [New File]"<<endl;
			cout<<"Entering Command Mode."<<endl;
			cout<<":";
			cmdline2.run(fname,argv[1]); //run until user quits 
		}
		
	}	
	return 0;
}

