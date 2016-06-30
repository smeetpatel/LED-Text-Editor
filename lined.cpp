#include <iostream>
#include <fstream>
#include <string>
#include "cmdparser.h"
#define TRUE 1 //mode: command
#define FALSE 0 //mode: input
using std::cout;
using std::endl;
using std::string;
using std::cin;


LED::LED()
{
	current_line=last_line=0;
}

LED::LED(std::fstream & fmanip,const char *str)
{
	int ct=0;
	while(getline(fmanip,line))
	{
		buffer.push_back(line);
		ct++;
	}
	last_line=current_line=ct;
	cout<<"\""<<str<<"\""<<" ["<<ct<<" lines"<<"]"<<endl;
}

//following function runs continously until user decides to quit!!
void LED::run(bool fname,const char *str)
{
	string line;
	int a=0;
	mode = TRUE; //initially command mode
	getline(cin,line);
	while(cin.good() && line!="q")
	{
		switch(mode)
		{
			case 1:
			{
				cmd.commandParser(line,current_line,last_line);
				if(cmd.valid==FALSE)
				{
					cout<<"ERROR"<<endl;
					break;
				}
				if(cmd.cmdsymbol=='a' || cmd.cmdsymbol == 'i')
				{
					mode=0; //switch to input mode
					break;
				}
				if(cmd.cmdsymbol=='r')
					remove();
				else if(cmd.cmdsymbol=='p')
					printbuff();
				else if(cmd.cmdsymbol=='n')
					printLineTab();
				else if(cmd.cmdsymbol=='c')
					change();
				else if(cmd.cmdsymbol=='u')
					moveUp();
				else if(cmd.cmdsymbol=='d')
					moveDown();
				else if(cmd.cmdsymbol=='w')
					writes(fname,str);
				else if(cmd.cmdsymbol=='m')	
					move();
				else if(cmd.cmdsymbol=='z')
					pcl();
				else
				{
					cout<<"Unrecognized command"<<endl;
					break;
				}
				break;
			}
			case 0:
			{
				if(cmd.cmdsymbol=='a')
				{
					bitr=buffer.begin();
					if(current_line!=0) //would allow appending to empty buffer
					{
						current_line=(cmd.add1 - '0');	
						for(a=0;a<(cmd.add1-'0');a++)
						++bitr;
					}	
					else
						current_line=0;
				}
				else   //cannot work on empty buffer
				{
					bitr=buffer.begin();
					current_line=((cmd.add1 - '0')-1);
					for(a=0;a<((cmd.add1-'0')-1);a++)
						++bitr;
				}
				getline(cin,line);
				while(cin.good() && line!=".")
				{
					buffer.insert(bitr,line);
					++current_line;
					getline(cin,line);
				}
				last_line=buffer.size();
				cout<<":";
				mode=1;
				break;
				//above code would set current line and last line
			}
		}
		if(mode!=0)
			getline(cin,line);
	}
	if(line=="q")
	{
		char ch;
		cout<<"Save changes?(y/n) "<<endl;
		cin>>ch;
		std::cin.ignore(1,'\n');
		if(ch==89 || ch==121)
		{
			writes(fname,str);
		}
		else
		{
		return;
		}
		
	}
	return;
}

void LED::remove()
{
	std::list<string>::iterator bitr2;
	int i;
	bitr=bitr2=buffer.begin();
	for(i=0;i<((cmd.add1-'0')-1);i++)
		++bitr;
	if((cmd.add2-'0')==last_line || (cmd.add2-'0')>last_line)
	{
		for(i=0;i<(cmd.add2-'0')-1;i++)
			++bitr2;
	}
	else
	{
		for(i=0;i<(cmd.add2-'0');i++)
			++bitr2;
	}
	buffer.erase(bitr,bitr2);
	if((cmd.add2-'0')==last_line || (cmd.add2-'0')>last_line)
		buffer.erase(bitr2);
	last_line=buffer.size();
	current_line=(cmd.add1-'0');
	if(current_line>last_line)
		current_line = ((cmd.add1-'0')-1);
	if(last_line==0)
		current_line=0;
	cout<<":";
	return;
}

void LED::printbuff()
{
	int i;
	bitr=buffer.begin();
	for(i=0;i<((cmd.add1-'0')-1);i++)
		++bitr;
	for(i=(cmd.add1-'0');i<((cmd.add2-'0')+1);i++)
	{
		cout<<*bitr<<endl;
		++bitr;
	}
	current_line=(cmd.add2-'0');
	cout<<":";
	return;
}

void LED::printLineTab()
{
	int i,a;
	bitr=buffer.begin();
	a=(cmd.add1 - '0');
	for(i=0;i<((cmd.add1-'0')-1);i++)
		++bitr;
	for(i=(cmd.add1-'0');i<((cmd.add2-'0')+1);i++)
	{
		cout<<a<<"\t"<<*bitr<<endl;
		a++;
		++bitr;
	}
	current_line=(cmd.add2-'0');
	cout<<":";
	return;
}

void LED::change()
{
	string line1,line2;
	int i;
	bitr=buffer.begin();
	for(i=0;i<((cmd.add1-'0')-1);i++)
		++bitr;
	for(i=(cmd.add1-'0');i<((cmd.add2-'0')+1);i++)
	{
		cout<<*bitr<<endl;
		line=*bitr;
		cout<<"Enter text to be changed:"<<endl;
		getline(cin,line1);
		cout<<"Enter text to be replaced with:"<<endl;
		getline(cin,line2);
		std::size_t found = line.find(line1);
		if(found==std::string::npos) //error
		{
			cout<<"String not present"<<endl;
			return;	
		}
		else	//error free
		{
			line.replace(line.find(line1),line1.length(),line2);
		}
		*bitr=line;
		++bitr;
	}
	current_line=(cmd.add2-'0');
	cout<<":";
	return;
}

void LED::moveUp()
{
	current_line=current_line-(cmd.add1-'0');
	if(current_line<1)
	{
		cout<<"Not possible"<<endl;
		current_line=1;
		cout<<":";
		return;
	}
	cout<<":";
	return;
}

void LED::moveDown()
{
	current_line=current_line+(cmd.add1-'0');
	if(current_line>last_line)
	{
		cout<<"Not possible"<<endl;
		current_line=last_line;
		cout<<":";
		return;
	}
	cout<<":";
	return;
}

void LED::writes(bool fname,const char *str)
{
	string file_name;
	std::ofstream filemanip;
	if(fname==FALSE)
	{
		cout<<"Enter file name: "<<endl;
		getline(cin,file_name);
		filemanip.open(file_name.c_str());
	}
	else
	{
		filemanip.open(str,std::ios::out);
	}
	bitr=buffer.begin();
	if(filemanip.good())
	{
		while(bitr!=buffer.end())
		{
			filemanip<<*bitr;
			filemanip<<endl;
			++bitr;
		}
	}
	filemanip.close();
	cout<<":";
	return;
}

void LED::move()
{
	current_line=(cmd.add1-'0');
	cout<<":";
	return;
}

void LED::pcl()
{
	cout<<"Current Line: "<<current_line<<endl;
	cout<<":";
	return;
}
