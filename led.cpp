#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#define TRUE 1
#define FALSE 0
using namespace std;

class command{
	public:
	void parse(string & cmd)
	{
		
	}


};

class LineEditor{
	list<string> buffer;
	string line; //to read from file to buffer
	command cmd;
	int current_line=0;
	public:
	LineEditor(fstream & fmanip,char *str)
	{
		int ct=0;
	
		while(getline(fmanip,line))
		{
			buffer.push_back(line);
			ct++;
		}
		cout<<"\""<<str<<"\""<<" ["<<ct<<" lines"<<endl;
	}
	void run()
	{
		
	}
};


int main(int argc, char * argv[])
{
	fstream filemanip;
	bool fname,exists;
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
			exists = TRUE;
			while(getline(filemanip,line))
			{
				//read entire line from file and add it as a element of buffer.
				LineEditor cmdline(filemanip,argv[1]);
				cout<<""
			}
		}
		else
		{
			exists = FALSE;
			LineEditor cmdline;
			cout<<"\""<<argv[1]<<"\""<<" [New File]"<<endl;
		}
	}
	//till now, object of LineEditor is created. Now we enter command mode!
	cout<<"Entering Command Mode."<<endl;
	cout<<":";
	cmdline.run() //run until user quits 
	
	return 0;
}

