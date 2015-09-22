#ifndef _LOGIC_H_
#define _LOGIC_H_

#include "Persistance\IOHandler.h"
//#include "DataStruckFunctions.h"

#include <map>
#include <list>
#include <set>
#include <stack>

/*class CompareDist
{
public:
	bool operator()(std::pair< int, int > firstPair, std::pair< int, int > secundPair)
	{
		return firstPair.first > secundPair.first;
	}
};*/

class Logic
{
public:
	Logic(const std::string &rootDirectory);
	~Logic();

	void generateResult(const std::string &exerciseNumberStr);

	void generateResult25();
	void generateResult25_Setup(int &sumRooms, int &jStart, int &tStart, std::map< int, std::vector< int > > &jMap, std::map< int, std::vector< int > > &tMap);
	void generateResult25_Calculate(int &sumRooms, int &jStart, int &tStart, std::map< int, std::vector< int > > &jMap, std::map< int, std::vector< int > > &tMap);

	void generateResult46();
	void generateResult46_Setup(std::string &startRiver, std::map< std::string, std::vector< std::string > > &riverMap, std::map< std::string, std::vector< std::string > > &riverMapReversed);
	void generateResult46_Calculate(std::string &startRiver, std::map< std::string, std::vector< std::string > > &riverMap, std::map< std::string, std::vector< std::string > > &riverMapReversed);

	void generateResult52();
	void generateResult52_Setup(int &vertexCount, std::map< int, std::vector< std::pair< int, int > > > &processData);
	void generateResult52_Calculate(int &vertexCount, std::map< int, std::vector< std::pair< int, int > > > &processData);

	void generateResult70();
	void generateResult70_Setup(int &startPoint, int &endPoint, std::vector< std::pair< int, int > > &inOutPathOfPoints, std::map< int, std::vector< int > > &tourMap);
	void generateResult70_Calculate(int &startPoint, int &endPoint, std::vector< std::pair< int, int > > &inOutPathOfPoints, std::map< int, std::vector< int > > &tourMap);

	void MB(std::stack< int> &topologiclyOrderedPoints, std::map< int, std::vector< int > > &tourMap, std::vector< bool > &finishedPoint, const int& point);
private:
	IOHandler ExerciseIOHandler;
};


#endif