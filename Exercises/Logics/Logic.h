#ifndef _LOGIC_H_
#define _LOGIC_H_

#include "Persistance\IOHandler.h"
#include "Graph\Vertex.h"

#include <map>
#include <list>
#include <set>
#include <stack>

typedef std::vector< std::vector< std::pair< int, int> > > weightedEdgesVector; // 09, 52
typedef std::vector< std::vector< int > > vertexVector; // 25, 46
typedef std::map< std::string, int > idMap; // 46
typedef std::vector< std::string > reversedIdVector; // 46
typedef std::vector< std::pair< int, int* > > pileArray; // 52

class Logic
{
public:
	Logic(const std::string &rootDirectory = std::string(""));
	~Logic();

	void generateResult(const std::string &exerciseNumberStr, const std::string &specificInputNumberStr = std::string(""));

	void generateResult09();
	void generateResult09_Setup(int &vertexCount, int &edgeCount, weightedEdgesVector &graph);
	void generateResult09_Calculate(int &vertexCount, int &edgeCount, weightedEdgesVector &graph);

	void generateResult25();
	void generateResult25_Setup(int &sumRooms, int &jStart, int &tStart, vertexVector &jGraph, vertexVector &tGraph);
	void generateResult25_Calculate(int &sumRooms, int &jStart, int &tStart, vertexVector &jGraph, vertexVector &tGraph);
	
	void generateResult46();
	void generateResult46_Setup(std::string &startRiver, vertexVector &downStreamGraph, vertexVector &upStreamGraph, idMap &riversIdVector, reversedIdVector &reversedRiversIdVector);
	void generateResult46_Calculate(std::string &startRiver, vertexVector &downStreamGraph, vertexVector &upStreamGraph, idMap &riversIdVector, reversedIdVector &reversedRiversIdVector);

	void generateResult52();
	void generateResult52_Setup(int &stageCount, weightedEdgesVector &stageGraph);
	void generateResult52_Calculate(int &stageCount, weightedEdgesVector &stageGraph);
	/*
	void generateResult70();
	void generateResult70_Setup(int &startPoint, int &endPoint, Graph< int > &tourGraph);
	void generateResult70_Calculate(int &startPoint, Graph< int > &tourGraph);

	void generateResult77();
	void generateResult77_Setup(int &minesCount, std::map< int, std::vector< int > > &mines, std::map< int, std::vector< int > > &reversedMines);
	void generateResult77_Calculate(int &minesCount, std::map< int, std::vector< int > > &mines, std::map< int, std::vector< int > > &reversedMines);

	void generateResult78();
	void generateResult78_Setup(int &starmapSize, std::vector < std::vector< int> > &starmap);
	void generateResult78_Calculate(int &starmapSize, std::vector < std::vector< int> > &starmap);
	*/

private:
	IOHandler ExerciseIOHandler;
};


#endif