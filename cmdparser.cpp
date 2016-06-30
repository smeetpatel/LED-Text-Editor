#include <iostream>
#include <string>
#include <list>
#define TRUE 1
#define FALSE 0
using namespace std;
//cl:current line
//max: last line
class command{
	bool valid;
	char cmdsymbol,seprator;
	char add1,add2;
	list<char> parse;
	//int i=0,sizemanage=0;
	list<char>::iterator pitr;
	public:
	command()
	{
		valid=FALSE;
		cmdsymbol='\0';
		seprator=',';
		add1='\0';
		add2='\0';
	}
	void commandParser(string & cmd,int cl,int max)
	{
		int i=0,sizemanage=0;
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
				cout<<"Error"<<endl;
				return;
			}
		}
		//list with all required element is formed.
		if(parse.size()>4) //not known command
		{
			valid = FALSE;
			cout<<"Size Error"<<endl;
			return;
		}
		i=0;
		pitr=parse.begin();
		if(isdigit(*pitr))
		{
			//check possiblities of theta
			theta(cmd,cl,max);
		}
		else if(ispunct(*pitr))
		{
			if(*pitr==46) //*pitr = .
			{
				//check possiblities of BETA
				beta(cmd,cl,max);
			}
			else if(*pitr == 36) //*pitr = $
			{
				//check possiblities of ALPHA
				alpha(cmd,cl,max);
			}
			else if(*pitr == 44) //*pitr = ,
			{
				//check possiblities of MYU
				myu(cmd,cl,max);
			}
			else if(*pitr == 61) //*pitr = =
			{
				//check possiblities of =
				cout<<"Current Line: "<<cl<<endl;
				
			}
			else
			{
				valid = FALSE;
				cout<<"Unexpected PUNCT ERROR"<<endl;
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
				cmdsymbol = *pitr;
				if(cmdsymbol=='p')
				{
					add1=cl+'0';
					add2=add1;
					a=add1-'0';
					if(1<=a && a<=max)
						valid = TRUE;
					else
					{
						valid = FALSE;
						cout<<"CMD OoR ERROR"<<endl;
						return;
					}
				}
			}
			else
			{
				valid = FALSE;
				cout<<"Size Error"<<endl;
				return;
			}
			
		}
	
		cout<<"Done"<<endl;
	}
	void theta(string pop,int cl,int max)
	{
		pitr=parse.begin();
		int size=parse.size();
		int a=0;
		int b=0;
		switch(size)
		{
			case 1:
			{
				//move current line to given line
				add1=*pitr;
				add2='0';
				seprator='\0';
				cmdsymbol='\0';
				a=add1 - '0';
				if(1<=a && a<=max)
					valid=TRUE;
				else
				{
					valid = FALSE;
					cout<<"OoR ERROR(1)"<<endl;
				}
				break;
			}
			case 2:
			{
				add1=*pitr;
				
				++pitr;
				if(isalpha(*pitr))
				{
					cmdsymbol=*pitr;
					add2=add1;
					
					seprator=',';
					a=add1 - '0';
					if(a<1 || a>max)
					{
						valid = FALSE;
						cout<<"OoR ERROR(2)"<<endl;
					}
					else
					{
						valid = TRUE;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(1)"<<endl;
				}
				break;
			}
			case 3:
			{
				add1=*pitr;
				cout<<"ADD 1:"<<add1<<endl;
				cout<<"CL:"<<cl<<endl;
				cout<<"ML:"<<max<<endl;
				++pitr;
				if(*pitr == 44)
				{
					seprator=',';
					++pitr;
					if(isalpha(*pitr))
					{
						cout<<"CL:"<<cl<<endl;
						add2 =cl + '0';
						cout<<"ADD 2:"<<add2<<endl;
						cmdsymbol=*pitr;
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
					else if(isdigit(*pitr) || ispunct(*pitr))
					{
						if(isdigit(*pitr))
							add2 = *pitr;
						else if(*pitr==44)
							add2=cl+'0';
						else if(*pitr==36)
							add2=max+'0';
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(2)"<<endl;
						}
						
						cmdsymbol='p';
						a=add1-'0';
						b=add2-'0';
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
						valid = FALSE;
						cout<<"Unexpected Character ERROR(3)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(4)"<<endl;
				}
				break;
			}
			case 4:
			{
				add1=*pitr;
				++pitr;	
				if(*pitr == 44)
				{
					seprator=',';
					++pitr;
					if(isdigit(*pitr) || ispunct(*pitr))
					{
						if(isdigit(*pitr))
							add2 = *pitr;
						else if(*pitr==44)
							add2=cl+'0';
						else if(*pitr==36)
							add2=max+'0';
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(5)"<<endl;
						}
						++pitr;
						if(isalpha(*pitr))
						{
							cmdsymbol=*pitr;
							a=add1-'0';
							b=add2-'0';
							if(1<=a && a<=b && b<=max)
								valid = TRUE;
							else
							{
								valid = FALSE;
								cout<<"OoR ERROR(5)"<<endl;
							}
						}
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(6)"<<endl;
						}
					}
					else
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(7)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(8)"<<endl;
				}
				break;
			}
		}
		return;
	}
	void beta(string pop,int cl,int max)
	{
		pitr=parse.begin();
		int size=parse.size();
		int a=0;
		int b=0;
		switch(size)
		{
			case 1:
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
					cout<<"OoR ERROR(6)"<<endl;
				}
				break;
			}
			case 2:
			{
				add1=cl+'0';
				++pitr;
				if(isalpha(*pitr))
				{
					cmdsymbol=*pitr;
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
						cout<<"OoR ERROR(7)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(9)"<<endl;
				}
				break;
			}
			case 3:
			{
				add1=cl+'0';
				++pitr;
				if(*pitr == 44)
				{
					seprator=',';
					++pitr;
					if(isalpha(*pitr))
					{
						add2=cl+'0';
						cmdsymbol=*pitr;
						a=add1-'0';
						b=add2-'0';
						if(1<=a && a<=b && b<=max)
							valid = TRUE;
						else
						{
							valid = FALSE;
							cout<<"OoR ERROR(8)"<<endl;
						}
					}
					else if(isdigit(*pitr) || ispunct(*pitr))
					{
						if(isdigit(*pitr))
							add2 = *pitr;
						else if(*pitr==44)
							add2=cl+'0';
						else if(*pitr==36)
							add2=max+'0';
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(10)"<<endl;
						}
						
						cmdsymbol='p';
						a=add1-'0';
						b=add2-'0';
						if(1<=a && a<=b && b<=max)
							valid = TRUE;
						else
						{
							valid = FALSE;
							cout<<"OoR ERROR(9)"<<endl;
						}
					}
					else
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(11)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(12)"<<endl;
				}
				break;
			}
			case 4:
			{
				add1=cl+'0';
				++pitr;	
				if(*pitr == 44)
				{
					seprator=',';
					++pitr;
					if(isdigit(*pitr) || ispunct(*pitr))
					{
						if(isdigit(*pitr))
							add2 = *pitr;
						else if(*pitr==44)
							add2=cl+'0';
						else if(*pitr==36)
							add2=max+'0';
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(13)"<<endl;
						}
						++pitr;
						if(isalpha(*pitr))
						{
							cmdsymbol=*pitr;
							a=add1-'0';
							b=add2-'0';
							if(1<=a && a<=b && b<=max)
								valid = TRUE;
							else
							{
								valid = FALSE;
								cout<<"OoR ERROR(10)"<<endl;
							}
						}
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(14)"<<endl;
						}
					}
					else
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(15)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(16)"<<endl;
				}
				break;
			}
		}
		return;
	}
	void alpha(string pop,int cl,int max)
	{
		pitr=parse.begin();
		int size=parse.size();
		int a=0,b=0;
		switch(size)
		{
			case 1:
			{
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
					cout<<"OoR ERROR(11)"<<endl;
				}
				break;
			}
			case 2:
			{
				add1=max+'0';
				++pitr;
				if(isalpha(*pitr))
				{
					cmdsymbol=*pitr;
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
						cout<<"OoR ERROR(12)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(17)"<<endl;
				}
				break;
			}
			case 3:
			{
				add1=max+'0';
				++pitr;
				if(*pitr == 44)
				{
					seprator=',';
					++pitr;
					if(isalpha(*pitr))
					{
						add2=max+'0';
						cmdsymbol=*pitr;
						a=add1-'0';
						b=add2-'0';
						if(1<=a && a<=b && b<=max)
							valid = TRUE;
						else
						{
							valid = FALSE;
							cout<<"OoR ERROR(13)"<<endl;
						}
					}
					else if(isdigit(*pitr) || ispunct(*pitr))
					{
						if(isdigit(*pitr))
							add2 = *pitr;
						else if(*pitr==44)
							add2=cl+'0';
						else if(*pitr==36)
							add2=max+'0';
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(18)"<<endl;
						}
						
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
					else
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(19)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(20)"<<endl;
				}
				break;
			}
			case 4:
			{
				add1=max+'0';
				++pitr;	
				if(*pitr == 44)
				{
					seprator=',';
					++pitr;
					if(isdigit(*pitr) || ispunct(*pitr))
					{
						if(isdigit(*pitr))
							add2 = *pitr;
						else if(*pitr==44)
							add2=cl+'0';
						else if(*pitr==36)
							add2=max+'0';
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(21)"<<endl;
						}
						++pitr;
						if(isalpha(*pitr))
						{
							cmdsymbol=*pitr;
							a=add1-'0';
							b=add2-'0';
							if(1<=a && a<=b && b<=max)
								valid = TRUE;
							else
							{
								valid = FALSE;
								cout<<"OoR ERROR(15)"<<endl;
							}
						}
						else
						{
							valid = FALSE;
							cout<<"Unexpected Character ERROR(22)"<<endl;
						}
					}
					else
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(23)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(24)"<<endl;
				}
				break;
			}
		}
		return;
	}
	void myu(string pop,int cl,int max)
	{
		pitr=parse.begin();
		int size=parse.size();
		int a=0,b=0;
		switch(size)
		{
			case 1:
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
					cout<<"OoR ERROR(16)"<<endl;
				}
				break;
			}
			case 2:
			{
				add1=cl+'0';
				++pitr;
				if(isalpha(*pitr))
				{
					cmdsymbol=*pitr;
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
						cout<<"OoR ERROR(17)"<<endl;
					}
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(25)"<<endl;
				}
				break;
			}
			case 3:
			{
				add1=cl+'0';
				++pitr;
				if(*pitr == 46)
				{
					add2=cl+'0';
					seprator=',';
					++pitr;
					if(isalpha(*pitr))
					{
						cmdsymbol=*pitr;
						a=add1-'0';
						if(1<=a && a<=max)
						{
							valid = TRUE;
						}
						else
						{
							valid = FALSE;
							cout<<"OoR ERROR(18)"<<endl;
						}
					}
					else
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(26)"<<endl;
					}
				}
				else if(isdigit(*pitr) || ispunct(*pitr))
				{
					if(isdigit(*pitr))
						add2=*pitr;
					else if(*pitr == 36)
						add2=max+'0';
					else
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(27)"<<endl;
					}
					++pitr;
					if(isalpha(*pitr))
					{
						cmdsymbol=*pitr;
						a=add1-'0';
						b=add2-'0';
						if(1<=a && a<=b && b<=max)
						{
							valid = TRUE;
						}
						else
						{
							valid = FALSE;
							cout<<"OoR ERROR(19)"<<endl;
						}
					}
					else
					{
						valid = FALSE;
						cout<<"Unexpected Character ERROR(28)"<<endl;
					}
					
				}
				else
				{
					valid = FALSE;
					cout<<"Unexpected Character ERROR(29)"<<endl;
				}
				break;
			}
			default:
			{
				valid = FALSE;
				cout<<"Unexpected Size Error(30)"<<endl;
			}
		}
		return;
	}
	void print()
	{
		int a=add1-'0';
		int b=add2-'0';
		cout<<a<<seprator<<b<<cmdsymbol<<endl;
		//cout<<add1<<seprator<<add2<<cmdsymbol<<endl;
		cout<<valid<<endl;
		return;
	}
};

int main()
{
	string comm;
	int max,cl;
	command obj1;
	cout<<"Enter command."<<"\n"<<":";
	getline(cin,comm);
	cout<<comm<<endl;
	cout<<"Enter Current line: "<<endl;
	cin>>cl;
	cout<<"CL:"<<cl<<endl;
	cout<<"Enter Last line: "<<endl;
	cin>>max;
	cout<<"ML:"<<max<<endl;
	obj1.commandParser(comm,cl,max);
	obj1.print();
	return 0;
}
