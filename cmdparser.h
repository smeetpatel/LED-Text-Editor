#ifndef _cmdparser_h_included_
#define _cmdparser_h_included_
#include <list>
#include <string>
#include <iostream>
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


#endif
