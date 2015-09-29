#include "Logic.h"

#include <sstream>
#include <limits>

Logic::Logic(const std::string &rootDirectory) : 
	ExerciseIOHandler(rootDirectory)
{
}

Logic::~Logic()
{
}

void Logic::generateResult(const std::string &exerciseNumberStr)
{
	int exerciseNumber;
	std::istringstream(exerciseNumberStr) >> exerciseNumber;

	ExerciseIOHandler.init(exerciseNumber);

	switch (exerciseNumber)
	{
	case 25:
		while (ExerciseIOHandler.openNext())
		{
			generateResult25();
			ExerciseIOHandler.close();
		}
		
		break;
	case 46:
		while (ExerciseIOHandler.openNext())
		{
			generateResult46();
			ExerciseIOHandler.close();
		}

		break;
	case 52:
		while (ExerciseIOHandler.openNext())
		{
			generateResult52();
			ExerciseIOHandler.close();
		}

		break;
	case 70:
		while (ExerciseIOHandler.openNext())
		{
			generateResult70();
			ExerciseIOHandler.close();
		}

		break;
	default:
		break;
	}
}

void Logic::generateResult25()
{
	int jStart;
	int tStart;
	int sumRooms;

	GraphEdgeWeighted< int, int > graphEdgeWeighted;

	generateResult25_Setup(sumRooms, jStart, tStart, graphEdgeWeighted);

	generateResult25_Calculate(sumRooms, jStart, tStart, graphEdgeWeighted);
}

void Logic::generateResult25_Setup(int &sumRooms, int &jStart, int &tStart, GraphEdgeWeighted< int, int > graphEdgeWeighted)
{
	int fromRoom;
	int toRoom;
	bool isTRooms;

	std::map< int, std::vector< int > > jMap;
	std::map< int, std::vector< int > > tMap;

	ExerciseIOHandler >> sumRooms;
	ExerciseIOHandler >> tStart;
	ExerciseIOHandler >> jStart;

	isTRooms = true;
	while (ExerciseIOHandler >> fromRoom)
	{
		ExerciseIOHandler >> toRoom;
		if (fromRoom == -1)
		{
			isTRooms = false;
		}
		else
		{
			if (isTRooms)
			{
				graphEdgeWeighted.addEdge(fromRoom, toRoom, 0);
			}
			if (!isTRooms)
			{
				graphEdgeWeighted.addEdge(fromRoom, toRoom, 1);
			}
		}
	}
}

void Logic::generateResult25_Calculate(int &sumRooms, int &jStart, int &tStart, GraphEdgeWeighted< int, int > graphEdgeWeighted)
{
	/*graphEdgeWeighted.parallelIngress(tStart, 0, 1);

	if (graphEdgeWeighted.getVertexVisitedAt(tStart) == 1)
	{
		ExerciseIOHandler << std::string("igen");
		ExerciseIOHandler << std::endl;
		ExerciseIOHandler << std::string("nem");
	}
	else
	{
		bool meetPosible = false;
		bool circlePosible = false;
		bool isOver = false;

		waitingForChecing.clear();
		waitingForChecing.push_back(jStart);

		dataVector[jStart] = 2;

		while (!waitingForChecing.empty() && !isOver)
		{
			const int checkingFrom = waitingForChecing.back();
			waitingForChecing.pop_back();
			const std::vector<int> &checkingToVector = jMap[checkingFrom];
			for (auto it = checkingToVector.cbegin(); it != checkingToVector.cend(); ++it)
			{
				if (dataVector[*it] == 1)
				{
					meetPosible = true;
				}
				else if (dataVector[*it] == 0)
				{
					dataVector[*it] = 2;
					waitingForChecing.push_back(*it);
				}
				else if (dataVector[*it] == 2)
				{
					if (*it == jStart)
					{
						circlePosible = true;
					}
				}

				isOver = meetPosible == true && circlePosible == true;
			}
		}

		if (meetPosible)
		{
			ExerciseIOHandler << std::string("igen");
		}
		else
		{
			ExerciseIOHandler << std::string("nem");
		}

		ExerciseIOHandler << std::endl;

		if (circlePosible)
		{
			ExerciseIOHandler << std::string("igen");
		}
		else
		{
			ExerciseIOHandler << std::string("nem");
		}
	}*/
}

void Logic::generateResult46()
{
	std::string startRiver;

	std::map< std::string, std::vector<std::string > > riverMap;
	std::map< std::string, std::vector<std::string > > riverMapReversed;

	generateResult46_Setup(startRiver, riverMap, riverMapReversed);
	
	generateResult46_Calculate(startRiver, riverMap, riverMapReversed);
}

void Logic::generateResult46_Setup(std::string &startRiver, std::map< std::string, std::vector< std::string > > &riverMap, std::map< std::string, std::vector< std::string > > &riverMapReversed)
{
	int riverPairCount;
	std::string riverNameFrom;
	std::string riverNameTo;

	ExerciseIOHandler >> riverPairCount;

	for (int i = 0; i < riverPairCount; ++i)
	{
		ExerciseIOHandler >> riverNameFrom;
		ExerciseIOHandler >> riverNameTo;
		riverMap[riverNameFrom].push_back(riverNameTo);
		riverMapReversed[riverNameTo].push_back(riverNameFrom);
	}

	ExerciseIOHandler >> startRiver;
}

void Logic::generateResult46_Calculate(std::string &startRiver, std::map< std::string, std::vector< std::string > > &riverMap, std::map< std::string, std::vector< std::string > > &riverMapReversed)
{
	std::set< std::string > resultRiversSet;
	std::list< std::string > waitingForChecingRiverList;
	waitingForChecingRiverList.push_back(startRiver);
	while (!waitingForChecingRiverList.empty())
	{
		const std::vector<std::string > &tmpRiverVector = riverMapReversed[waitingForChecingRiverList.back()];
		waitingForChecingRiverList.pop_back();
		for (auto it = tmpRiverVector.cbegin(); it != tmpRiverVector.cend(); ++it)
		{
			std::pair< std::set< std::string >::iterator, bool > tmpInsetReturnPair = resultRiversSet.insert(*it);
			if (tmpInsetReturnPair.second)
			{
				waitingForChecingRiverList.push_back(*it);
			}
		}
	}

	ExerciseIOHandler << resultRiversSet.size();
	ExerciseIOHandler << std::endl;
	for (auto it = resultRiversSet.cbegin(); it != resultRiversSet.cend(); ++it)
	{
		ExerciseIOHandler << *it;
		ExerciseIOHandler << std::endl;
	}

	resultRiversSet.clear();
	waitingForChecingRiverList.clear();
	waitingForChecingRiverList.push_back(startRiver);
	while (!waitingForChecingRiverList.empty())
	{
		const std::vector<std::string > &tmpRiverVector = riverMap[waitingForChecingRiverList.back()];
		waitingForChecingRiverList.pop_back();
		for (auto it = tmpRiverVector.cbegin(); it != tmpRiverVector.cend(); ++it)
		{
			std::pair< std::set< std::string >::iterator, bool > tmpInsetReturnPair = resultRiversSet.insert(*it);
			if (tmpInsetReturnPair.second)
			{
				waitingForChecingRiverList.push_back(*it);
			}
		}
	}
	ExerciseIOHandler << resultRiversSet.size();
	ExerciseIOHandler << std::endl;
	for (auto it = resultRiversSet.cbegin(); it != resultRiversSet.cend(); ++it)
	{
		ExerciseIOHandler << *it;
		ExerciseIOHandler << std::endl;
	}
}

void Logic::generateResult52()
{
	int testDataCount;
	ExerciseIOHandler >> testDataCount;

	for (int i = 0; i < testDataCount; ++i)
	{
		int vertexCount = 0;

		std::map< int, std::vector< std::pair< int, int > > > processData;

		generateResult52_Setup(vertexCount, processData);

		generateResult52_Calculate(vertexCount, processData);
	}
}

void Logic::generateResult52_Setup(int &vertexCount, std::map< int, std::vector< std::pair< int, int > > > &processData)
{
	int edgeCount;

	ExerciseIOHandler >> vertexCount;
	ExerciseIOHandler >> edgeCount;
	

	int fromEdge;
	int toEdge;
	int edgeValue;

	for (int i = 0; i < edgeCount; ++i)
	{
		ExerciseIOHandler >> fromEdge;
		ExerciseIOHandler >> toEdge;
		ExerciseIOHandler >> edgeValue;
		processData[fromEdge].push_back(std::make_pair(toEdge, edgeValue));
	}
}

void Logic::generateResult52_Calculate(int &vertexCount, std::map< int, std::vector< std::pair< int, int > > > &processData)
{
	//DataStruckFunctions dataStruckFunctions;

	int intMaximumValue = std::numeric_limits<int>::max();

	std::vector< int > pathWeightVector(vertexCount, 0);
	std::vector< int > parentVertexVector(vertexCount, -1);
	std::set< std::pair< int, int > > pileVertexesSet;
	//std::vector< std::pair< int, int* > > vertexesPile;
	std::set< int > finishedVertex;

	pathWeightVector[0] = 0;
	pileVertexesSet.insert(std::make_pair(0, 0));
	//vertexesPile.push_back(std::make_pair(0, &pathWeightVector[0]));

	while (!pileVertexesSet.empty())
	//while (!vertexesPile.empty())
	{
		 int pathLastVertex = pileVertexesSet.begin()->first;
		 //int pathLastVertex = vertexesPile.back().first;
		 int pathLastVertexWeight = pileVertexesSet.begin()->second;
		 //int pathLastVertexWeight = *vertexesPile.back().second;
		 pileVertexesSet.erase(pileVertexesSet.begin());
		 //vertexesPile.pop_back();
		 finishedVertex.insert(pathLastVertex);

		 const std::vector< std::pair< int, int > > &tmpVertexWeightPairVector = processData[pathLastVertex];
		 for (auto it = tmpVertexWeightPairVector.cbegin(); it != tmpVertexWeightPairVector.cend(); ++it)
		 {
			 if (finishedVertex.find((*it).first) == finishedVertex.end())
			 {
				 int edge = (*it).first;
				 int weight = (*it).second;
				 int newWeight = pathLastVertexWeight + weight;
				 if (newWeight > pathWeightVector[edge])
				 {
					 pileVertexesSet.erase(std::make_pair(edge, pathWeightVector[edge]));
					 /*if (newWeight != 0 && finishedVertex.find(edge) == finishedVertex.end())
					 {
						 vertexesPile.push_back(std::make_pair(edge, &pathWeightVector[edge]));
					 }*/
					 pathWeightVector[edge] = newWeight;
					 parentVertexVector[edge] = pathLastVertex;
					 //dataStruckFunctions.PileOrdering(vertexesPile);
					 pileVertexesSet.insert(std::make_pair(edge, pathWeightVector[edge]));
				 }
			 }
		 } 
	}

	if (parentVertexVector[vertexCount - 1] == -1)
	{
		ExerciseIOHandler << std::string("Hibas utemterv!") << std::endl;
	}
	else
	{
		ExerciseIOHandler << pathWeightVector[vertexCount - 1];

		std::string pathStr;
		for (int vertex = vertexCount - 1; vertex != 0; vertex = parentVertexVector[vertex])
		{
			pathStr.insert(0, ", " + std::to_string(vertex));
		}

		pathStr.insert(0, " 0");

		ExerciseIOHandler << pathStr << std::endl;
		
	}

	ExerciseIOHandler << std::endl;
}

void Logic::generateResult70()
{
	int startPoint;
	int endPoint;

	Graph< int > tourGraph;

	generateResult70_Setup(startPoint, endPoint, tourGraph);

	generateResult70_Calculate(startPoint, tourGraph);
}

void Logic::generateResult70_Setup(int &startPoint, int &endPoint, Graph< int > &tourGraph)
{
	int pointsCount;
	int pathsCount;
	std::map< int, std::vector< int > > tourMap;

	ExerciseIOHandler >> pointsCount;
	ExerciseIOHandler >> pathsCount;
	ExerciseIOHandler >> startPoint;
	ExerciseIOHandler >> endPoint;

	for (int i = 0; i < pathsCount; ++i)
	{
		int fromPoint;
		int toPoint;

		ExerciseIOHandler >> fromPoint;
		ExerciseIOHandler >> toPoint;

		tourGraph.addEdge(fromPoint, toPoint);
	}
}

void Logic::generateResult70_Calculate(int &startPoint, Graph< int > &tourGraph)
{
	tourGraph.deepIngress(startPoint);

	size_t sumInOutPath = 0;
	std::vector< int > citicalPoints;

	for (size_t i = tourGraph.topologicalSize() - 1; i < -1 ; --i)
	{
		sumInOutPath -= tourGraph.getTopologicalVertexAt(i)->ParentVertexesVector.size();
		if (sumInOutPath == 0)
		{
			citicalPoints.push_back(tourGraph.getTopologicalVertexAt(i)->Id);
		}
		sumInOutPath += tourGraph.getTopologicalVertexAt(i)->ChildVertexesVector.size();
	}

	ExerciseIOHandler << citicalPoints.size();
	ExerciseIOHandler << std::endl;
	for (auto it = citicalPoints.cbegin(); it != citicalPoints.cend(); ++it)
	{
		ExerciseIOHandler << *it;
		ExerciseIOHandler << std::string(" ");
	}
}

