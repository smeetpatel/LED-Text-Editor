#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include "cmdparser.h"
#define TRUE 1
#define FALSE 0
using std::cout;
using std::endl;
using std::string;

command::command()
{
	valid=FALSE;
	cmdsymbol='\0';
	seprator=',';
	add1='\0';
	add2='\0';
};

void command::commandParser(string cmd,int cl,int max)
{
	int i=0;
	while(i<cmd.length()) //form proper list
	{
		if(isalnum(cmd[i]) || ispunct(cmd[i]))
		{
			parse.push_back(cmd[i]);
			i++;
		}
		else if(isspace(cmd[i]))
		{
			i++;
		}
		else
		{
			valid = FALSE;
			cout<<"Initial Error"<<endl;
			return;
		}
	}
	if(parse.size()==0) //if command is enter...do same as 1d
	{
		add1=1+'0';
		add2=add1;
		seprator=',';
		cmdsymbol='d';
		valid=TRUE;
		emptylist();
		return;
	}
	std::string pop(parse.begin(),parse.end());
	i=0;
	//pitr=parse.begin();
	if(isdigit(parse[0]))
	{
		//check possiblities of theta
		command::theta(pop,cl,max);
	}
	else if(ispunct(parse[0]))
	{
		if(parse[0]==46) //*pitr = .
		{
			//check possiblities of BETA
			command::beta(pop,cl,max);
		}
		else if(parse[0] == 36) //*pitr = $
		{
			//check possiblities of ALPHA
			command::alpha(pop,cl,max);
		}
		else if(parse[0] == 44) //*pitr = ,
		{
			//check possiblities of MYU
			command::myu(pop,cl,max);
		}
		else if(parse[0] == 61) //*pitr = '='
		{
			//check possiblities of =
			valid = TRUE;
			cmdsymbol='z';
			cout<<"Current Line: "<<cl<<endl;	
		}
		else
		{
			valid = FALSE;
			cout<<"Unexpected PUNCT ERROR"<<endl;
			emptylist();
			return;
		}
	}
	else
	{
		//check possiblities of command
		int a=0;
		int size=parse.size();
		if(size==1)
		{
			cmdsymbol = parse[0];
			
			if(cmdsymbol=='p')
			{
				add1=cl+'0';
				add2=add1;
				a=cl;
				if(1<=a && a<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"CMD OoR ERROR"<<endl;
					emptylist();
					return;
				}
			}
			else
				valid=TRUE;
		}
		else
		{
			valid = FALSE;
			cout<<"Size Error"<<endl;
			emptylist();
			return;
		}
	}
	emptylist();
}

void command::theta(string pop,int cl,int max)
{
	int i=0,x;
	string s;
	int size=pop.length();
	int a=0,b=0;
	size_t found=pop.find(',');
	if(found==std::string::npos)
	{
		//code for yz
		if(isalpha(pop[size-1]))
		{
			s=pop.substr(0,size-1);
			for(i=0;i<s.length();i++)
			{
				if(!isdigit(s[i]))
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(1)"<<endl;
					return;
				}
			}
			std::istringstream con(s);
			con>>x;
			add1=add2=x+'0';
			cmdsymbol=pop[size-1];
			seprator=',';
			//a=add1 - '0';
			if(1<=x && x<=max)
				valid=TRUE;
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(1)"<<endl;
			}
		}
		else if(ispunct(pop[size-1]))
		{
			valid = FALSE;
			cout<<"Unexpected Character ERROR(2)"<<endl;
		}
		else
		{
			//code for x
			std::istringstream con(s);
			con>>x;
			add1=x+'0';
			add2='\0';
			seprator='\0';
			cmdsymbol='m';
			if(1<=x && x<=max)
				valid=TRUE;
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(2)"<<endl;
			}
		}
		
	}
	else
	{
		//code for x,z or x,yz or x,y
		s=pop.substr(0,found);
		for(i=0;i<s.length();i++)
		{
			if(!isdigit(s[i]))
			{
				valid = FALSE;
				cout<<"Unexpected Character ERROR(3)"<<endl;
				return;
			}
		}
		std::istringstream con(s);
		con>>x;
		add1=x+'0';
		if(isalpha(pop[size-1])) //code for x,z and x,yz
		{
			s=pop.substr(found,size);
			cout<<s<<endl;
			if(s.length()==2)
			{
				//code for x,z
				add2 =cl + '0';
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(3)"<<endl;
				}
			}
			else if(s.length()==3)
			{
				//code for x,.z and x,$z
				cout<<"pop[found+1]:"<<pop[found+1]<<endl;
				if(pop[found+1]==46)
					add2=cl+'0';
				else if(pop[found+1]==36)
					add2=max+'0';
				else if(isdigit(pop[found+1]))
				{
					add2=pop[found+1];
					cout<<add2<<endl;
				}
				else
				{
					valid = FALSE;
						cout<<"Unexpected Character ERROR(4)"<<endl;
				}
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				cout<<"A: "<<a<<" B: "<<b<<endl;
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(4)"<<endl;
				}
			}
			else
			{
				s=pop.substr(found+1,size-3);
				cout<<s<<endl;
				for(i=0;i<s.length();i++)
				{
					if(!isdigit(s[i]))
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(5)"<<endl;
						return;
					}
				}
				std::istringstream con(s);
				con>>x;
				add2=x+'0';
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				cout<<"A: "<<a<<" B: "<<b<<endl;
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(5)"<<endl;
				}
				
			}
		}
		else if(isdigit(pop[size-1]) || pop[size-1]==46 || pop[size-1]==36) //code for x,y or x,. or x,$
		{
			s=pop.substr(found+1,size);
			if(s.length()==1)	//code for x,. and x,$
			{
				if(isdigit(pop[found+1]))
					goto down;
				else if(pop[found+1]==46)
					add2=cl+'0';
				else if(pop[found+1]==36)
					add2=max+'0';
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(6)"<<endl;
				}		
				cmdsymbol='p';
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(6)"<<endl;
				}
				return;
			}
			down:
			for(i=0;i<s.length();i++)
			{
				if(!isdigit(s[i]))
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(7)"<<endl;
					return;
				}
			}
			std::istringstream con(s);
			con>>x;
			add2=x+'0';
			cmdsymbol='p';
			a=add1-'0';
			b=add2-'0';
			if(1<=a && a<=b && b<=max)
				valid = TRUE;
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(7)"<<endl;
			}
		}
		else
		{
			valid = FALSE;
			cout<<"Unexpected Character ERROR(8)"<<endl;
		}
	}
	return;
}

void command::beta(string pop,int cl,int max)
{
	int i=0,x;
	string s;
	int size=pop.length();
	int a=0,b=0;
	size_t found=pop.find(',');
	if(found==std::string::npos)	//code for . and .z
	{
		if(isalpha(pop[size-1]))
		{
			//code for .z
			add1=cl+'0';
			cmdsymbol=pop[size-1];
			add2=add1;
			seprator=',';
			a=add1-'0';
			if(1<=a && a<=max)
			{
				valid = TRUE;
			}
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(8)"<<endl;
			}
		}
		else if(size==1)
		{
			add1=cl+'0';
			add2=cl+'0';
			seprator=',';
			cmdsymbol='p';
			a=add1-'0';
			if(1<=a && a<=max)
				valid=TRUE;
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(9)"<<endl;
			}
		}
		else
		{
			valid = FALSE;
			cout<<"Unexpected Character ERROR(9)"<<endl;
		}
			
	}
	else	//code for .,z and .,yz and .,y
	{
		add1=cl+'0';
		if(isalpha(pop[size-1]))
		{
			//code for .,z and .,yz
			s=pop.substr(found+1,size);
			cout<<s<<" Length:"<<s.length()<<endl;
			if(s.length()==1)	 //.,z
			{
				
				add2=cl+'0';
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				cout<<"A: "<<a<<" B: "<<b<<endl;
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(10)"<<endl;
				}
			}
			else if(s.length()==2)	//.,.z and .,$z
			{
				if(isdigit(pop[found+1]))
					add2 = pop[found+1]+'0';
				else if(pop[found+1]==46)
					add2=cl+'0';
				else if(pop[found+1]==36)
					add2=max+'0';
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(10)"<<endl;
				}	
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(11)"<<endl;
				}
			}
			else
			{
				string str=pop.substr(found+1,size-3);
				cout<<str<<" Length:"<<str.length()<<endl;
				for(i=0;i<str.length();i++)
				{
					if(!isdigit(str[i]))
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(11)"<<endl;
						return;
					}
				}
				std::istringstream con(str);
				con>>x;
				add2=x+'0';
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(12)"<<endl;
				}
			}
			
		}
		else if(isdigit(pop[size-1]) || pop[size-1]==46 || pop[size-1]==36)
		{
			//code for .,. and .,d and .,$
			s=pop.substr(found+1,size);
			cout<<s<<" Length:"<<s.length()<<endl;
			if(s.length()==1)
			{
				if(isdigit(pop[found+1]))
					goto down;
				else if(pop[found+1]==46)
					add2=cl+'0';
				else if(pop[found+1]==36)
					add2=max+'0';
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(12)"<<endl;
				}		
				cmdsymbol='p';
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(13)"<<endl;
				}
				return;
			}
			down:
			for(i=0;i<s.length();i++)
			{
				if(!isdigit(s[i]))
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(13)"<<endl;
					return;
				}
			}
			std::istringstream con(s);
			con>>x;
			add2=x+'0';
			cmdsymbol='p';
			a=add1-'0';
			b=add2-'0';
			if(1<=a && a<=b && b<=max)
				valid = TRUE;
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(14)"<<endl;
			}
			
		}
	}
	return;
}

void command::alpha(string pop,int cl,int max)
{
	int i=0,x;
	string s;
	int size=pop.length();
	int a=0,b=0;
	size_t found=pop.find(',');
	if(found==std::string::npos)	//code for $ and $z
	{
		if(isalpha(pop[size-1]))
		{
			//code for $z
			add1=max+'0';
			cmdsymbol=pop[size-1];
			add2=add1;
			seprator=',';
			a=add1-'0';
			if(1<=a && a<=max)
			{
				valid = TRUE;
			}
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(15)"<<endl;
			}	
		}
		else if(size==1)
		{
			//code for $
			add1=max+'0';
			add2=max+'0';
			seprator=',';
			cmdsymbol='p';
			a=add1-'0';
			if(1<=a && a<=max)
				valid=TRUE;
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(16)"<<endl;
			}
		}
		else
		{
			valid = FALSE;
			cout<<"Unexpected Character ERROR(14)"<<endl;
		}
	}
	else	//$,z and $,yz and $,y(./$/d)
	{
		add1=max+'0';
		if(isalpha(pop[size-1]))
		{
			//code for $,z and $,yz
			s=pop.substr(found,size);
			if(s.length()==2)
			{
				//$,z
				add2=max+'0';
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(17)"<<endl;
				}
			}
			else if(s.length()==3)
			{
				//$,.z and $,$z
				if(isdigit(pop[found+1]))
					add2 = pop[found+1]+'0';
				else if(pop[found+1]==46)
					add2=cl+'0';
				else if(pop[found+1]==36)
					add2=max+'0';
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(15)"<<endl;
				}
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(18)"<<endl;
				}	
			}
			else
			{
				s=pop.substr(found+1,size-3);
				cout<<s<<endl;
				for(i=0;i<s.length();i++)
				{
					if(!isdigit(s[i]))
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(16)"<<endl;
						return;
					}
				}
				std::istringstream con(s);
				con>>x;
				add2=x+'0';
				cmdsymbol=pop[size-1];
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(19)"<<endl;
				}
			}
		
			
		}
		else if(isdigit(pop[size-1]) || pop[size-1]==46 || pop[size-1]==36)
		{
			//code for $,. and $,$ and $,d
			s=pop.substr(found+1,size);
			if(s.length()==1)
			{
				if(isdigit(pop[found+1]))
					goto down;
				else if(pop[found+1]==46)
					add2=cl+'0';
				else if(pop[found+1]==36)
					add2=max+'0';
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(17)"<<endl;
				}		
				cmdsymbol='p';
				a=add1-'0';
				b=add2-'0';
				if(1<=a && a<=b && b<=max)
					valid = TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(20)"<<endl;
				}
				return;
			}
			down:
			for(i=0;i<s.length();i++)
			{
				if(!isdigit(s[i]))
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(18)"<<endl;
					return;
				}
			}
			std::istringstream con(s);
			con>>x;
			add2=x+'0';
			cmdsymbol='p';
			a=add1-'0';
			b=add2-'0';
			if(1<=a && a<=b && b<=max)
				valid = TRUE;
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(21)"<<endl;
			}
			
		}
		else
		{
			valid = FALSE;
			cout<<"Unexpected Character ERROR(19)"<<endl;
		}
	}
	return;
}

void command::myu(string pop,int cl,int max)
{
	int size=pop.length();
	int i=0,a=0,b=0,x=0;
	if(size==1)	//,
	{
		add1=1+'0';
		add2=max+'0';
		seprator=',';
		cmdsymbol='p';
		a=add1-'0';
		b=add2-'0';
		if(1==a && b==max)
			valid=TRUE;
		else
		{
			valid = FALSE;
			cout<<"OoR ERROR(22)"<<endl;
		}
		return;
	}
	if(size==2)	//,z
	{
		add1=cl+'0';
		if(isalpha(pop[size-1]))
		{
			cmdsymbol=pop[size-1];
			add2=add1;
			seprator=',';
			a=add1-'0';
			if(1<=a && a<=max)
			{
				valid = TRUE;
			}
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(23)"<<endl;
			}
		}
		else
		{
			valid = FALSE;
			cout<<"Unexpected Character ERROR(20)"<<endl;
		}
		return;
	}
	if(size==3 && (pop[1]==46 || pop[1]==36))	//,.z
	{
		add1=cl+'0';
		if(pop[1]==46)
			add2=add1;	
		else
			add2=max+'0';
		seprator=',';
		if(isalpha(pop[size-1]))
		{
			cmdsymbol=pop[size-1];
			a=add1-'0';
			b=add2-'0';
			if(pop[1]==46 && 1<=a && a<=max)
			{
				valid = TRUE;
			}
			else if(pop[1]==36 && 1<=a && a<=b && b<=max)
				valid=TRUE;
			else
			{
				valid = FALSE;
				cout<<"OoR ERROR(24)"<<endl;
			}
		}
		else
		{
			valid = FALSE;
			cout<<"Unexpected Character ERROR(21)"<<endl;
		}
		return;
	}
	string s=pop.substr(1,size-2);
	cout<<s<<endl;
	for(i=0;i<s.length();i++)
	{
		if(!isdigit(s[i]))
		{
			valid = FALSE;
			cout<<"Unexpected Character ERROR(22)"<<endl;
			return;
		}
	}
	std::istringstream con(s);
	con>>x;
	add2=x+'0';
	cmdsymbol=pop[size-1];
	a=add1-'0';
	b=add2-'0';
	if(1<=a && a<=b && b<=max)
	{
		valid = TRUE;
	}
	else
	{
		valid = FALSE;
		cout<<"OoR ERROR(25)"<<endl;
	}
	return;
}

void command::print()
{
	int a=add1-'0';
	int b=add2-'0';
	cout<<a<<seprator<<b<<cmdsymbol<<endl;
	cout<<valid<<endl;
	return;
}

void command::emptylist()
{
	std::vector<char>::iterator pitr2;
	pitr=pitr2=parse.begin();
	advance(pitr2,parse.size());
	parse.erase(pitr,pitr2);
}
