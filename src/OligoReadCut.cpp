#ifndef FQ_CheckAdpter_H_
#define FQ_CheckAdpter_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <iomanip>
#include <math.h>
#include <zlib.h>
#include <cstdlib>
#include <unistd.h>
#include "gzstream/gzstream.c"
#include <thread>

//#define MAX_L 512
//#define MAX_Q 128
//typedef  long long LLongA;
//typedef  long long int LLongB;
using namespace std;

//  #define _A 0 #define _C 1    #define _G 2   #define _T 3   #define _N 4

int  print_usage_OligoCut()
{
	cout <<""
		"\n"
		"Usage:OligoReadCut -InFq1 Oligo.R1.fq -InFq2 Oligo.R2.fq  -OutFq1 NewOligo.R1.fq -OutFq2 NewOligo.R2.fq\n"
		"\n"
		"\t\t-InFq1       <str>   File of 30bp InFq Input\n"
		"\t\t-InFq2       <str>   File of 100bp InFq Input\n"
		"\t\t-OutFq1      <str>   OUT File of New 20bp Fq\n"
		"\t\t-OutFq2      <str>   OUT File of New 30bp Fq\n"
		"\n"
		"\t\t-Adapter1   <str>   Input adapter1 seq [TCTGCG]\n"
		"\t\t-Adapter2   <str>   Input adapter2 seq [CCTTCC]\n"
		//"\n"
		//"\t\t                  allow one misMatch on adapters seq\n"
		"\n"
		"\t\t-help               Show this help[hewm2008 v1.30]\n"
		"\n";
	return 1;
}

string &  replace_all(string &  str,const  string &  old_Avalue,const string &  new_Avalue)
{
	while(true)   {
		string::size_type  pos(0);
		if(   (pos=str.find(old_Avalue))!=string::npos   )
			str.replace(pos,old_Avalue.length(),new_Avalue);
		else   break;
	}
	return   str;
}

/*
string Int2Str (int A )
{
	stringstream   sstrm ;
	sstrm  <<  A ;
	return  sstrm.str();
}

int GetShiftQ ( string FQPath )
{
	igzstream INFQ ((FQPath).c_str(),ifstream::in);
	if (INFQ.fail())
	{
		cerr << "open File error: "<<(FQPath)<<endl;
		return 64 ;
	}
	string tmp ;
	int minQ=50000;
	int maxQ=0;
	for (int A=1 ; A<46888 && (!INFQ.eof())  ; A++ )
	{
		getline(INFQ,tmp);
		if (tmp.length()<=0)  { continue  ; }

		if(A%4!=0)
		{
			continue;
		}
		string::size_type SeqQLength =tmp.size();
		for(int i=0 ; i<SeqQLength ; i++)
		{
			if(minQ>tmp[i])
			{
				minQ=tmp[i];
			}
			if(maxQ<tmp[i])
			{
				maxQ=tmp[i];
			}
		}
	}
	INFQ.close();

	if(minQ >= 33 &&  minQ <= 78  &&  maxQ >= 33 && maxQ <=78 )
	{
		return 33;
	}
	else if (minQ >= 64  &&  minQ <= 108  &&  maxQ >= 64 && maxQ <= 108)
	{
		return 64;
	}
	else
	{
		return 64 ;
	}
}
*/


inline string add_Asuffix ( string path )
{
	string ext =path.substr(path.rfind('.') ==string::npos ? path.length() : path.rfind('.') + 1);
	if (ext != "gz")
	{
		path=path+".gz" ;
	}
	return path ;
}




void split(const string& str,vector<string>& tokens,  const string& delimiters = " ")
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos     = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}



class Para_A24 {
	public:
		string InFq1;
		string InFq2;
		string OutFq1;
		string OutFq2;

		string adapter1 ;
		string adapter2 ;

		int LowQint ;
		bool NoMisMatch ;
		Para_A24()
		{
			InFq1="";
			OutFq1="";
			InFq2="";
			OutFq2="";
			adapter1="TCTGCG" ;
			adapter2="CCTTCC" ;
			LowQint=5;
			NoMisMatch=true;
		}
}
;

inline void  LogLackArg( string  flag )
{
	cerr << "\t\tLack Argument for [ -"<<flag<<" ]"<<endl;
}


//int parse_cmd_OligoCut(int argc, char **argv , Para_A24 * para ,   Para_A24 * P2In )
int parse_cmd_OligoCut(int argc, char **argv , Para_A24 * para  )
{
	if (argc <=4  ) {print_usage_OligoCut();return 0;}

	int err_flag = 0;

	for(int i = 1; i < argc || err_flag; i++)
	{
		if(argv[i][0] != '-')
		{
			cerr << "command option error! please check." << endl;
			return 0;
		}
		string flag=argv[i] ;
		flag=replace_all(flag,"-","");

		if (flag  == "InFq1")
		{
			if(i + 1 == argc) { LogLackArg( flag ) ; return 0;}
			i++;
			para->InFq1=argv[i];
		}
		else if (flag  == "InFq2" )
		{
			if(i + 1 == argc) { LogLackArg( flag ) ; return 0;}
			i++;
			para->InFq2=argv[i];
		}
		else if (flag  ==  "Adapter1")
		{
			if(i + 1 == argc) { LogLackArg( flag ) ; return 0;}
			i++;
			para->adapter1=argv[i];
		}
		else if (flag  ==  "OutFq1")
		{
			if(i + 1 == argc) { LogLackArg( flag ) ; return 0;}
			i++;
			para->OutFq1=argv[i];
		}
		else if (flag  ==  "OutFq2" )
		{
			if(i + 1 == argc) { LogLackArg( flag ) ; return 0;}
			i++;
			para->OutFq2=argv[i];
		}
		else if (flag  ==  "Adapter2" )
		{
			if(i + 1 == argc) { LogLackArg( flag ) ; return 0;}
			i++;
			para->adapter2=argv[i];
		}
		else if (flag  ==  "NoMisMatch" )
		{
			para->NoMisMatch=false;
		}

		else if (flag  == "help")
		{
			print_usage_OligoCut();return 0;
		}
		else
		{
			cerr << "UnKnow argument -"<<flag<<endl;
			return 0;
		}
	}

	if ( (para->OutFq1).empty() || (para->InFq1).empty() )
	{
		cerr<< "-InFq1 -OutFq1 lack argument for the must"<<endl;
		return 0;
	}
	if ( (para->OutFq2).empty() || (para->InFq2).empty() )
	{
		cerr<< "-InFq2 -OutFq2 lack argument for the must"<<endl;
		return 0;
	}


	string subseqA=para->adapter1;
	string subseqB=para->adapter2;
	int subseqALen=subseqA.length();
	int subseqBLen=subseqA.length();

	if (subseqALen <3  ||  subseqALen >12 )
	{
		cerr << "\t-Adapter1 Seq maybe wrong,pls check it"<<endl;
		return 0;
	}
	if (subseqBLen <3  ||  subseqBLen >12 )
	{
		cerr << "\t-Adapter2 Seq maybe wrong,pls check it"<<endl;
		return 0;
	}

	para->OutFq1=add_Asuffix(para->OutFq1);
	para->OutFq2=add_Asuffix(para->OutFq2);
	return  1 ;
}



int  GetMisMatchAA (string & Ref, string & subseq , size_t &  AA_position ,int seq_len  )
{
	char Base[5];
	Base[0]='A';  Base[1]='C';  Base[2]='T';  Base[3]='G';  Base[4]='N';


	for (int i=0 ; i<seq_len ; i++)
	{
		for (int j=0  ;j<5;  j++)
		{
			string new_seq=subseq;
			new_seq[i]=Base[j];
			AA_position=Ref.find(new_seq,6 );
			if  ( (  AA_position != string::npos )  && (  AA_position < 14 )   && (  AA_position >6) )
			{
				return 0;
			}
		}
	}
	return 1;
}

int GetMisMatchBB (string & Ref, string & subseq , size_t &  BB_position ,int seq_len )
{
	char Base[5];
	Base[0]='A';  Base[1]='C';  Base[2]='T';  Base[3]='G';  Base[4]='N';

	for (int i=0 ; i<seq_len ; i++)
	{
		for (int j=0  ;j<5;  j++)
		{
			string new_seq=subseq;
			new_seq[i]=Base[j];
			BB_position=Ref.find(new_seq,22);
			if  ((  BB_position != string::npos )  && ( BB_position < 30 )  && (BB_position> 22 )  )
			{
				return 0;
			}
		}
	}

	return 1;
}


int DealReadAA(Para_A24 * para)
{

	igzstream INAA ((para->InFq1).c_str(),ifstream::in); // ifstream  + gz
	ogzstream OUTAA ((para->OutFq1).c_str());

	if(!INAA.good())
	{
		cerr << "open IN File error: "<<para->InFq1<<endl;
		return 1;
	}
	if(!OUTAA.good())
	{
		cerr << "open OUT File error: "<<para->OutFq1<<endl;
		return 1;
	}


	string ID_1 ,seq_1,temp_1,Quly_1 ;


	while(!INAA.eof())
	{
		getline(INAA,ID_1);
		getline(INAA,seq_1);
		getline(INAA,temp_1);
		getline(INAA,Quly_1);
		if (ID_1.length()<=0)  { continue ;}
		string SeqInDexAA=seq_1.substr(0,20);
		string SeqInDexAAQQ=Quly_1.substr(0,20);
		OUTAA<<ID_1<<"\n"<<SeqInDexAA<<"\n"<<temp_1<<"\n"<<SeqInDexAAQQ<<"\n";
	}
	INAA.close();
	OUTAA.close();

	return 0;

}



int  DealReadBB(Para_A24 * para)
{

	igzstream IN ((para->InFq2).c_str(),ifstream::in); // ifstream  + gz
	ogzstream OUT ((para->OutFq2).c_str());

	if(!IN.good())
	{
		cerr << "open IN File error: "<<para->InFq2<<endl;
		return 1;
	}
	if(!OUT.good())
	{
		cerr << "open OUT File error: "<<para->OutFq2<<endl;
		return 1;
	}



	string ID_1 ,seq_1,temp_1,Quly_1 ;

	string subseqA=para->adapter1;
	string subseqB=para->adapter2;
	int subseqALen=subseqA.length();
	int subseqBLen=subseqA.length();

	while(!IN.eof())
	{
		getline(IN,ID_1);
		getline(IN,seq_1);
		getline(IN,temp_1);
		getline(IN,Quly_1);
		if (ID_1.length()<=0)  { continue ;}
		size_t AA_position =0;
		AA_position=seq_1.find(subseqA,6);
		if  ((AA_position!=string::npos) && (  AA_position <  14)   && (  AA_position >6) )
		{

		}
		else
		{
			GetMisMatchAA (seq_1 , subseqA , AA_position ,subseqALen ) ;
			if  ((AA_position!=string::npos) && (  AA_position <  14)   && (  AA_position >6) )
			{
			}
			else
			{
				AA_position=seq_1.find(subseqA,4);
				if  ((AA_position!=string::npos) && (  AA_position <  18)   && ( AA_position >5))
				{
				}
				else
				{
					AA_position=10;
				}
			}
		}

		size_t BB_position =0;
		BB_position=seq_1.find(subseqB, 22 );
		if  ((BB_position!=string::npos) && (  BB_position <  30)   && (  AA_position >22) )
		{
		}
		else
		{
			GetMisMatchBB (seq_1 , subseqB , BB_position ,subseqBLen );
			if  ((BB_position!=string::npos) && (  BB_position <  30)   && (  BB_position >22) )
			{
			}
			else
			{
				BB_position=seq_1.find(subseqB, 20 );
				if  ((BB_position!=string::npos) && (  BB_position <  34)   && (  BB_position >20) )
				{
				}
				else
				{
					BB_position=26;
				}
			}
		}
	
		AA_position+=subseqALen;
		BB_position+=subseqBLen;
		string SeqInDexAA=seq_1.substr(AA_position,10);
		string SeqInDexAAQQ=Quly_1.substr(AA_position,10);
		string SeqInDexBB=seq_1.substr(BB_position,10);
		string SeqInDexBBQQ=Quly_1.substr(BB_position,10);
		int AA=AA_position-10-subseqALen; if (AA<0) {AA=0;}
		string SeqUMI=seq_1.substr(AA,10);
		string SeqUMIQQ=Quly_1.substr(AA,10);
		OUT<<ID_1<<"\n"<<SeqUMI<<SeqInDexAA<<SeqInDexBB<<"\n"<<temp_1<<"\n"<<SeqUMIQQ<<SeqInDexAAQQ<<SeqInDexBBQQ<<"\n";
	}



	IN.close();
	OUT.close();
	


	return 0;
}


int main (int argc, char *argv[ ])
{
	Para_A24 * para = new Para_A24;
	if( parse_cmd_OligoCut(argc, argv, para )==0)
	{
		delete para ;
		return 0 ;
	}


	



	thread t1 (DealReadAA,para );
	thread t2 (DealReadBB,para );
	t1.join();
	t2.join();


	delete para ;
	return (0);
}

#endif  // FQ_OligoCut_H_




