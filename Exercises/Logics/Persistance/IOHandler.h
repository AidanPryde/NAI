#ifndef _I_O_HANDLER_H_
#define _I_O_HANDLER_H_

#include <iostream>
#include <fstream>
#include <ostream>

#include <vector>

class IOHandler
{
public:
	
	IOHandler(const std::string &rootDirectory = std::string(""));
	~IOHandler();

	void init(const int &exerciseNumbe, const int &specificInputNumber);

	bool openNext();
	void close();

	IOHandler & operator>> (std::string &val);
	IOHandler & operator>> (bool &val);
	IOHandler & operator>> (short &val);
	IOHandler & operator>> (unsigned short &val);
	IOHandler & operator>> (int &val);
	IOHandler & operator>> (unsigned int &val);
	IOHandler & operator>> (long &val);
	IOHandler & operator>> (unsigned long &val);
	IOHandler & operator>> (long long &val);
	IOHandler & operator>> (unsigned long long &val);
	IOHandler & operator>> (float &val);
	IOHandler & operator>> (double &val);
	IOHandler & operator>> (long double &val);
	IOHandler & operator>> (void*& val);
	IOHandler & operator>> (std::streambuf* sb);
	IOHandler & operator>> (std::istream& (*pf)(std::istream&));
	IOHandler & operator>> (std::ios& (*pf)(std::ios&));
	IOHandler & operator>> (std::ios_base& (*pf)(std::ios_base&));
	
	IOHandler & operator<< (std::string val);
	IOHandler & operator<< (bool val);
	IOHandler & operator<< (short val);
	IOHandler & operator<< (unsigned short val);
	IOHandler & operator<< (int val);
	IOHandler & operator<< (unsigned int val);
	IOHandler & operator<< (long val);
	IOHandler & operator<< (unsigned long val);
	IOHandler & operator<< (long long val);
	IOHandler & operator<< (unsigned long long val);
	IOHandler & operator<< (float val);
	IOHandler & operator<< (double val);
	IOHandler & operator<< (long double val);
	IOHandler & operator<< (void* val);
	IOHandler & operator<< (std::streambuf* sb);
	IOHandler & operator<< (std::ostream& (*pf)(std::ostream&));
	IOHandler & operator<< (std::ios& (*pf)(std::ios&));
	IOHandler & operator<< (std::ios_base& (*pf)(std::ios_base&));
	

	void getFilesInDirectory(std::vector< std::wstring > &fileNameVector, const std::wstring &directory);

	operator bool();

private:
	std::fstream IFHandler;
	std::fstream OFHandler;

	std::vector< std::wstring > FileNameVector;
	std::wstring RootDirectory;
	std::wstring WideExerciseNumberStr;
};

#endif