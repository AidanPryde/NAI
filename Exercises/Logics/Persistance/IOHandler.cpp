#include "IOHandler.h"
#include <Windows.h>

#include <locale>
#include <codecvt>
#include <string>

IOHandler::IOHandler(const std::string &rootDirectory)
{
	
	std::wstring_convert<std::codecvt<wchar_t, char, mbstate_t> > converter; //ok
	//std::wstring_convert<std::codecvt_utf8<wchar_t>> converter; // error
	//std::wstring_convert<std::codecvt_utf16<wchar_t>> converter; // krix krax
	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter; // error

	RootDirectory = converter.from_bytes(rootDirectory);



}

IOHandler::~IOHandler()
{
}

void IOHandler::init(const int & exerciseNumber)
{
	FileNameVector.clear();
	WideExerciseNumberStr.clear();
	WideExerciseNumberStr = std::to_wstring(exerciseNumber);
	getFilesInDirectory(FileNameVector, RootDirectory + L"In-Outputs\\" + WideExerciseNumberStr + L"\\In");
}

bool IOHandler::openNext()
{
	if (!FileNameVector.empty())
	{
		std::wstring fileName = std::wstring();
		std::wstring fileOutDirectory = std::wstring();
		fileName = FileNameVector.back();
		FileNameVector.pop_back();
	
		IFHandler.open(fileName, std::fstream::in);
		auto pos = fileName.find(L"INPUT");
		fileOutDirectory = RootDirectory + L"In-Outputs\\" + WideExerciseNumberStr + L"\\Out\\" + fileName.replace(0, pos + 5, L"OUTPUT");
		OFHandler.open(fileOutDirectory, std::fstream::out | std::fstream::trunc);

		return true;
	}
	return false;
}

void IOHandler::close()
{
	IFHandler.close();
	OFHandler.close();
}

IOHandler & IOHandler::operator>>(std::string & val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (bool &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (short &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (unsigned short &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (int &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (unsigned int &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (long &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (unsigned long &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (long long &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (unsigned long long &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (float &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (double &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (long double &val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (void*& val)
{
	IFHandler >> val;
	return *this;
}

IOHandler & IOHandler::operator>> (std::streambuf* sb)
{
	IFHandler >> sb;
	return *this;
}

IOHandler & IOHandler::operator>> (std::istream& (*pf)(std::istream&))
{
	IFHandler >> pf;
	return *this;
}

IOHandler & IOHandler::operator>> (std::ios& (*pf)(std::ios&))
{
	IFHandler >> pf;
	return *this;
}

IOHandler & IOHandler::operator>> (std::ios_base& (*pf)(std::ios_base&))
{
	IFHandler >> pf;
	return *this;
}



IOHandler & IOHandler::operator<<(std::string val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (bool val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (short val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (unsigned short val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (int val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (unsigned int val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (long val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (unsigned long val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (long long val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (unsigned long long val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (float val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (double val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (long double val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (void* val)
{
	OFHandler << val;
	return *this;
}

IOHandler & IOHandler::operator<< (std::streambuf* sb)
{
	OFHandler << sb;
	return *this;
}

IOHandler & IOHandler::operator<< (std::ostream& (*pf)(std::ostream&))
{
	OFHandler << pf;
	return *this;
}

IOHandler & IOHandler::operator<< (std::ios& (*pf)(std::ios&))
{
	OFHandler << pf;
	return *this;
}

IOHandler & IOHandler::operator<< (std::ios_base& (*pf)(std::ios_base&))
{
	OFHandler << pf;
	return *this;
}



void IOHandler::getFilesInDirectory(std::vector< std::wstring > &fileNameVector, const std::wstring &directory)
{
#ifdef _WIN32
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if ((dir = FindFirstFile((directory + L"\\*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		const std::wstring file_name = file_data.cFileName;
		const std::wstring full_file_name = directory + L"\\" + file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
		{
			continue;
		}

		if (is_directory)
		{
			continue;
		}

		fileNameVector.push_back(full_file_name);
	}
	while (FindNextFile(dir, &file_data));

	FindClose(dir);
#else
	not tested!!!
	DIR *dir;
	class dirent *ent;
	class stat st;

	dir = opendir(directory);
	while ((ent = readdir(dir)) != NULL)
	{
		const std::wstring file_name = ent->d_name;
		const std::wstring full_file_name = directory + "/" + file_name;

		if (file_name[0] == '.')
		{
			continue;
		}

		if (stat(full_file_name.c_str(), &st) == -1)
		{
			continue;
		}

		const bool is_directory = (st.st_mode & S_IFDIR) != 0;

		if (is_directory)
		{
			continue;
		}

		out.push_back(full_file_name);
	}
	closedir(dir);
#endif
}

IOHandler::operator bool()
{
	if (!IFHandler.fail() && !OFHandler.fail())
	{
		return true;
	}

	return false;
}
