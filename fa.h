#include <stdio.h>
#include <string>
#include <vector>

//errors
#define NO_SUCH_FILE 1
#define LINE_TOO_LARGE 2

#define MAX_NEXT_SIZE 1000
#define BUFFER_SIZE 1024

class FaParser
{
	FILE* FaFile;
	std::string FaFileName;
	FaParser();
	char * Buffer;
	unsigned BI,BN,Parsed;
	char * NextBuffer;
	public:
	FaParser(std::string FaFileName);
	~FaParser();
	char * next(unsigned N=1);//return the first pointer to the next at most N bases, end marked with \0, if no more bases return nullptr
	std::string getFaFileName() const;
	unsigned getParsed() const;
};

class chr
{
	public:
		std::string Name;
		unsigned StartPoint;
};
class fa
{
	public:
	char* Bases;
	unsigned Size;
	std::vector<chr> Chrs;
	fa();
	~fa();
	bool haveBases() const;
	static FaParser* generateFaParser(std::string FaFileName);//generate a parser for FaFileName, return nullptr if failed
	bool readBases(std::string FaFileName);//read Bases and Chrs from FaFileName, return true if succeeded
};

