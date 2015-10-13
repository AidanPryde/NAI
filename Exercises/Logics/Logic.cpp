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
	case 9:
		while (ExerciseIOHandler.openNext())
		{
			generateResult09();
			ExerciseIOHandler.close();
		}

		break;
	case 25:
		while (ExerciseIOHandler.openNext())
		{
			//generateResult25();
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
	case 77:
		while (ExerciseIOHandler.openNext())
		{
			generateResult77();
			ExerciseIOHandler.close();
		}

		break;
	case 78:
		while (ExerciseIOHandler.openNext())
		{
			generateResult78();
			ExerciseIOHandler.close();
		}

		break;
	default:
		break;
	}
}

void Logic::generateResult09()
{
	int testDataCount;
	ExerciseIOHandler >> testDataCount;

	for (int i = 0; i < testDataCount; ++i)
	{
		int vertexCount = 0;
		int edgeCount = 0;

		std::map< int, std::vector< std::pair< int, int > > > processData;

		generateResult09_Setup(vertexCount, edgeCount, processData);

		generateResult09_Calculate(vertexCount, edgeCount, processData);
	}
}

void Logic::generateResult09_Setup(int &vertexCount, int &edgeCount, std::map< int, std::vector< std::pair< int, int > > > &processData)
{
	int fromVertex;
	int toVertex;
	int weight;

	ExerciseIOHandler >> vertexCount;
	ExerciseIOHandler >> edgeCount;

	for (int i = 0; i < edgeCount; ++i)
	{
		ExerciseIOHandler >> fromVertex;
		ExerciseIOHandler >> toVertex;
		ExerciseIOHandler >> weight;
		processData[fromVertex].push_back(std::make_pair(toVertex, weight));
		processData[toVertex].push_back(std::make_pair(fromVertex, weight));
	}
}

void Logic::generateResult09_Calculate(int &vertexCount, int &edgeCount, std::map< int, std::vector< std::pair< int, int > > > &processData)
{
	std::vector< int > d(vertexCount + 1, -1);
	std::vector< int > szin(vertexCount + 1, 0);

	d[1] = 0;

	bool vege = false;

	while (!vege)
	{
		int max = d[1];
		size_t maxIndex = 1;
		for (size_t i = 1; i < d.size(); ++i)
		{
			if (szin[i] == 0 && d[i] > max)
			{
				max = d[i];
				maxIndex = i;
			}
		}

		if (szin[maxIndex] == 1)
		{
			ExerciseIOHandler << 0;
			ExerciseIOHandler << std::endl;
			return;
		}

		szin[maxIndex] = 1;

		bool a = true;
		for (size_t i = 1; i < szin.size(); i++)
		{
			if (szin[i] == 0)
			{
				a = false;
			}
		}
		vege = a;

		const std::vector< std::pair< int, int > > & weightedEdgesVector = processData[maxIndex];

		for (auto it = weightedEdgesVector.begin(); it != weightedEdgesVector.end(); ++it)
		{
			if (szin[(*it).first] == 0)
			{
				if (d[(*it).first] < (*it).second)
				{
					d[(*it).first] = (*it).second;
				}
			}
		}

	}

	if (vege)
	{
		int min = d[2];
		size_t minIndex = 2;
		for (size_t i = 2; i < d.size(); ++i)
		{
			if (d[i] < min)
			{
				min = d[i];
				minIndex = i;
			}
		}
		ExerciseIOHandler << d[minIndex];
		ExerciseIOHandler << std::endl;
	}

}

/*
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
	graphEdgeWeighted.parallelIngress(tStart, 0, 1);

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
	}
}*/

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

void Logic::generateResult77()
{
	int minesCount = 0;

	std::map< int, std::vector< int > > mines;
	std::map< int, std::vector< int > > reversedMines;

	generateResult77_Setup(minesCount, mines, reversedMines);

	generateResult77_Calculate(minesCount, mines, reversedMines);

}

void Logic::generateResult77_Setup(int &minesCount, std::map< int, std::vector< int > > &mines, std::map< int, std::vector< int > > &reversedMines)
{
	ExerciseIOHandler >> minesCount;

	for (int i = 0; i < minesCount; ++i)
	{
		int connectedCount;

		ExerciseIOHandler >> connectedCount;

		for (int j = 0; j < connectedCount; ++j)
		{
			int connectedMine;

			ExerciseIOHandler >> connectedMine;

			mines[i + 1].push_back(connectedMine);
			reversedMines[connectedMine].push_back(i + 1);
		}
	}
}

void Logic::generateResult77_Calculate(int &minesCount, std::map< int, std::vector< int > > &mines, std::map< int, std::vector< int > > &reversedMines)
{
	std::vector< bool > checked(minesCount + 1, false);
	std::stack< int > deepIngressStack;

	std::stack< int > firstDeepIngressStackResult;

	

	for (auto i = 1; i < checked.size(); ++i)
	{
		if (!checked[i])
		{
			deepIngressStack.push(i);

			while (!deepIngressStack.empty())
			{
				int index = deepIngressStack.top();

				if (!checked[index])
				{
					checked[index] = true;
					const std::vector< int > &minesChild = mines[index];
					for (auto it = minesChild.begin(); it != minesChild.end(); ++it)
					{
						if (!checked[(*it)])
						{
							deepIngressStack.push(*it);
						}
					}
				}
				else
				{
					int tmp = deepIngressStack.top();
					firstDeepIngressStackResult.push(tmp);
					deepIngressStack.pop();
				}
			}
		}
	}

	checked.clear();
	checked.resize(minesCount + 1, false);

	while (!deepIngressStack.empty())
	{
		deepIngressStack.pop();
	}

	std::vector< int > strongChildCounts(minesCount + 1, 0);
	int strongChildCount = 0;

	while (!firstDeepIngressStackResult.empty())
	{
		int vertex = firstDeepIngressStackResult.top();
		firstDeepIngressStackResult.pop();
		if (strongChildCounts[vertex] == 0)
		{
			++strongChildCount;

			deepIngressStack.push(vertex);

			while (!deepIngressStack.empty())
			{
				int index = deepIngressStack.top();

				if (!checked[index])
				{
					checked[index] = true;
					strongChildCounts[index] = strongChildCount;
					const std::vector< int > &minesChild = reversedMines[index];
					for (auto it = minesChild.begin(); it != minesChild.end(); ++it)
					{
						if (strongChildCounts[(*it)] == 0)
						{
							deepIngressStack.push(*it);
						}
					}
				}
				else
				{
					deepIngressStack.pop();
				}
			}
		}
	}

	std::vector< int > resultVector(strongChildCount + 1, 0);

	for (int i = 1; i < mines.size(); ++i)
	{
		const std::vector< int > &minesChild = mines[i];
		for (auto it = minesChild.begin(); it != minesChild.end(); ++it)
		{
			if (strongChildCounts[i] != strongChildCounts[(*it)])
			{
				++(resultVector[strongChildCounts[(*it)]]);
			}
		}
	}

	int count = 0;

	for (int i = 1; i < resultVector.size(); ++i)
	{
		if (resultVector[i] == 0)
		{
			++count;
		}
	}

	ExerciseIOHandler << count;
}

void Logic::generateResult78()
{
	int starmapSize;
	std::vector < std::vector< int> > starmap;

	generateResult78_Setup(starmapSize, starmap);

	generateResult78_Calculate(starmapSize, starmap);
}

void Logic::generateResult78_Setup(int &starmapSize, std::vector < std::vector< int> > &starmap)
{
	int starsCount;
	ExerciseIOHandler >> starsCount;
	ExerciseIOHandler >> starmapSize;

	starmap.resize(starmapSize, std::vector< int >(starmapSize, 0));

	for (int i = 0; i < starsCount; ++i)
	{
		int x;
		int y;

		ExerciseIOHandler >> x;
		ExerciseIOHandler >> y;
		starmap[x - 1][y - 1] = -1;
	}
}

void Logic::generateResult78_Calculate(int &starmapSize, std::vector < std::vector< int> > &starmap)
{
	for (int x = 0; x < starmapSize; ++x)
	{
		int possibleMaximumWidth = 1;
		for (int y = 0; y < starmapSize; ++y)
		{
			if (starmap[x][y] != -1)
			{
				starmap[x][y] = possibleMaximumWidth;
				++possibleMaximumWidth;
			}
			else
			{
				possibleMaximumWidth = 1;
			}
		}
	}

	std::vector< std::vector <int> > maximumRectangle;

	int possibleMaximumWidth = 0;
	int maximumSize = 0;

	for (int y = starmapSize - 1; y > -1; --y)
	{
		for (int x = starmapSize - 1; x > -1; --x)
		{
			possibleMaximumWidth = 0;

			for (int k = x; k > -1; --k)
			{
				if (starmap[k][y] != -1)
				{
					if (possibleMaximumWidth > starmap[k][y] - 1 || possibleMaximumWidth == 0)
					{
						possibleMaximumWidth = starmap[k][y] - 1;
					}

					int currentSize = possibleMaximumWidth * (x - k + 1);

					if (currentSize > maximumSize)
					{
						maximumRectangle.clear();

						maximumRectangle.push_back(std::vector< int >(4, 0));
						maximumRectangle.back()[0] = x;
						maximumRectangle.back()[1] = y;
						maximumRectangle.back()[2] = k;
						maximumRectangle.back()[3] = y - possibleMaximumWidth + 1;
						maximumSize = (abs(x - k) + 1) * (abs(possibleMaximumWidth - 1) + 1);
					}
					else if (currentSize == maximumSize)
					{
						maximumRectangle.push_back(std::vector< int >(4, 0));
						maximumRectangle.back()[0] = x;
						maximumRectangle.back()[1] = y;
						maximumRectangle.back()[2] = k;
						maximumRectangle.back()[3] = y - possibleMaximumWidth + 1;
					}
				}
				else
				{
					possibleMaximumWidth = 0;
				}
			}
		}
	}
	
	ExerciseIOHandler << maximumSize;
	ExerciseIOHandler << std::string("\n");

	for (size_t i = 0; i < maximumRectangle.size(); ++i)
	{
		ExerciseIOHandler << maximumRectangle[i][0] + 1;
		ExerciseIOHandler << std::string(" ");
		ExerciseIOHandler << maximumRectangle[i][1] + 1;
		ExerciseIOHandler << std::string(" ");
		ExerciseIOHandler << maximumRectangle[i][2] + 1;
		ExerciseIOHandler << std::string(" ");
		ExerciseIOHandler << abs(maximumRectangle[i][3]) + 1;
		ExerciseIOHandler << std::string("\n");
	}
	 
}
