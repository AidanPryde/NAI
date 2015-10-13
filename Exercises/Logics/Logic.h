#ifndef _LOGIC_H_
#define _LOGIC_H_

#include "Persistance\IOHandler.h"
#include "Graph\Graph.h"
//#include "Graph\GraphEdgeWeighted.h"

#include <map>
#include <list>
#include <set>
#include <stack>

class Logic
{
public:
	Logic(const std::string &rootDirectory);
	~Logic();

	void generateResult(const std::string &exerciseNumberStr);

	void generateResult09();
	void generateResult09_Setup(int &vertexCount, int &edgeCount, std::map< int, std::vector< std::pair< int, int > > > &processData);
	void generateResult09_Calculate(int &vertexCount, int &edgeCount, std::map< int, std::vector< std::pair< int, int > > > &processData);

	/*void generateResult25();
	void generateResult25_Setup(int &sumRooms, int &jStart, int &tStart, GraphEdgeWeighted< int, int > graphEdgeWeighted);
	void generateResult25_Calculate(int &sumRooms, int &jStart, int &tStart, GraphEdgeWeighted< int, int > graphEdgeWeighted);*/

	void generateResult46();
	void generateResult46_Setup(std::string &startRiver, std::map< std::string, std::vector< std::string > > &riverMap, std::map< std::string, std::vector< std::string > > &riverMapReversed);
	void generateResult46_Calculate(std::string &startRiver, std::map< std::string, std::vector< std::string > > &riverMap, std::map< std::string, std::vector< std::string > > &riverMapReversed);

	void generateResult52();
	void generateResult52_Setup(int &vertexCount, std::map< int, std::vector< std::pair< int, int > > > &processData);
	void generateResult52_Calculate(int &vertexCount, std::map< int, std::vector< std::pair< int, int > > > &processData);

	void generateResult70();
	void generateResult70_Setup(int &startPoint, int &endPoint, Graph< int > &tourGraph);
	void generateResult70_Calculate(int &startPoint, Graph< int > &tourGraph);

	void generateResult77();
	void generateResult77_Setup(int &minesCount, std::map< int, std::vector< int > > &mines, std::map< int, std::vector< int > > &reversedMines);
	void generateResult77_Calculate(int &minesCount, std::map< int, std::vector< int > > &mines, std::map< int, std::vector< int > > &reversedMines);

	void generateResult78();
	void generateResult78_Setup(int &starmapSize, std::vector < std::vector< int> > &starmap);
	void generateResult78_Calculate(int &starmapSize, std::vector < std::vector< int> > &starmap);


private:
	IOHandler ExerciseIOHandler;
};


#endif