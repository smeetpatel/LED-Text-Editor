#ifndef _cmdparser_h_included_
#define _cmdparser_h_included_
#include <list>
#include <string>
#include <iostream>
//using std::list<string>;
class LED;
class command{
	bool valid;
	char cmdsymbol,seprator;
	char add1,add2;
	std::list<char> parse;
	//int i=0,sizemanage=0;
	std::list<char>::iterator pitr;
	public:
	friend class LED;
	command();
	void commandParser(std::string,int,int);
	void theta(std::string ,int,int);
	void beta(std::string,int,int);
	void alpha(std::string,int,int);
	void myu(std::string,int,int);
	void print();
};

class LED{
	std::list<std::string> buffer;
	std::string line; //to read from file to buffer
	std::list<std::string>::iterator bitr;
	command cmd;
	bool mode;
	int current_line,last_line;
	public:
	LED();
	LED(std::fstream &,char *);
	void run(bool,char *);
	void remove();
	void printbuff();
	void printLineTab();
	void change();
	void moveUp();
	void moveDown();
	void writes(bool,char *);
	void move();
	void pcl();
};
#endif
