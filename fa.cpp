/* File: fa.cpp
 * Author: CRE
 * Last Edited: Mon Oct 29 19:19:03 2018
 */

#include "fa.h"
#include "string.h"
#include <stdlib.h>

using namespace std;

//fa
fa::fa()
	:Bases(NULL),Size(0)
{
}
fa::~fa()
{
	if (Bases!=NULL) free(Bases);
}

FaParser* fa::generateFaParser(string FaFileName)
{
	FaParser* FP=NULL;
	try
	{
	FP= new FaParser(FaFileName);
	}
	catch(int e)
	{
		if (e==NO_SUCH_FILE)
		{
			fprintf(stderr, "read file %s error", FaFileName.c_str());
		}
	}
	return FP;
}

bool fa::haveBases() const
{
	if (Bases!=NULL && Size!=0) return true;
	return false;
}

bool fa::readBases(string FaFileName)
{
	unsigned TN=0, FileSize=0, i=0;
	chr TChr;
	FILE* FaFile=fopen(FaFileName.c_str(), "r");
	if (FaFile==NULL) throw NO_SUCH_FILE;
	
	fseek(FaFile,0,SEEK_END);
	FileSize=ftell(FaFile);
	rewind(FaFile);

	if (Bases!=NULL) free(Bases);
	Bases=new char[FileSize];

	char * Buffer=new char[BUFFER_SIZE];
	
	while (fgets(Buffer,BUFFER_SIZE,FaFile)!=NULL)
	{
		if (Buffer[0]=='>') 
		{
			TChr.Name=Buffer+1;
			TChr.StartPoint=i;
			Chrs.push_back(TChr);
		}
		else
		{
			for (unsigned j=0;j!=BUFFER_SIZE;++j)
			{
				if (Buffer[j]=='\n' or Buffer[j]==' ' or Buffer[j]=='\t') continue;
				if (Buffer[j]=='\0') break;
				Bases[i++]=Buffer[j];
			}
		}
		if (feof(FaFile)) break;
	}
	Size=i;
	fclose(FaFile);
	return true;
}

unsigned fa::getChrIndex(unsigned SiteIndex) const
{
	unsigned i;
	for (i = 1; i<Chrs.size(); ++i)
	{
		if (SiteIndex<Chrs[i].StartPoint)
		{
			return i-1;
		}
	}
	return i;
}


//FaParser

FaParser::FaParser(std::string FaFileName)
{
	FaFile=fopen(FaFileName.c_str(), "r");
	if (FaFile==NULL) throw NO_SUCH_FILE;
	NextBuffer=new char[MAX_NEXT_SIZE+1];
	Buffer=new char[BUFFER_SIZE];
	BI=0;
	BN=0;
	Parsed=0;
}

FaParser::~FaParser()
{
	fclose(FaFile);
	delete NextBuffer;
	delete Buffer;
}

string FaParser::getFaFileName () const
{
	return FaFileName;
}

unsigned FaParser::getParsed () const
{
	return Parsed;
}

char * FaParser::next(unsigned N)
{
	if (N==0) return NULL;
	if (feof(FaFile)&&BI>=BN) return NULL;
	unsigned Fulfiled=0, TN=0;
	while (Fulfiled<N)
	{
		if (BI<BN)
		{
			while(BI<BN)
			{
				NextBuffer[Fulfiled++]=Buffer[BI++];
				if (Fulfiled>=N) break;
			}
			if (feof(FaFile)) break;
		}
		else
		{
			if (fgets(Buffer,BUFFER_SIZE,FaFile)!=NULL)
			{
				TN=strlen(Buffer);
				if (TN>=BUFFER_SIZE-1) throw LINE_TOO_LARGE;
				if (Buffer[0]=='>') 
				{
					if (feof(FaFile)) break;
				}
				else
				{
					BN=TN;
					if (Buffer[BN-1]=='\n') --BN;
					BI=0;
				}
			}
			else break;
		}
	}
	if (Fulfiled==0) return NULL;
	Parsed+=Fulfiled;
	NextBuffer[Fulfiled]='\0';
	return NextBuffer;
}

