#ifndef _cmdparser_h_included_
#define _cmdparser_h_included_

class command{
	bool valid;
	char cmdsymbol,seprator;
	char add1,add2;
	list<char> parse;
	//int i=0,sizemanage=0;
	list<char>::iterator pitr;
	public:
	command();
	void commandParser(string &,int,int);
	void theta(string ,int,int);
	void beta(string,int,int);
	void alpha(string,int,int);
	void myu(string,int,int);
	void print();
};

#endif
