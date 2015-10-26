#include "Logic.h"

#include <sstream>
#include <forward_list>
#include <queue>

Logic::Logic(const std::string &rootDirectory) : 
	ExerciseIOHandler(rootDirectory)
{
}

Logic::~Logic()
{
}

void Logic::generateResult(const std::string &exerciseNumberStr, const std::string &specificInputNumberStr)
{
	int exerciseNumber = -1;
	int specificInputNumber = -1;

	if (!(std::istringstream(exerciseNumberStr) >> exerciseNumber))
	{
		throw "ERROR: Wrong first argument. Probably not a number.";
	}

	if (!(specificInputNumberStr.empty()) && !(std::istringstream(specificInputNumberStr) >> specificInputNumber))
	{
		throw "ERROR: Wrong second argument. Probably not a number.";
	}

	ExerciseIOHandler.init(exerciseNumber, specificInputNumber);

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
	case 77:
		while (ExerciseIOHandler.openNext())
		{
			//generateResult77();
			ExerciseIOHandler.close();
		}

		break;
	case 78:
		while (ExerciseIOHandler.openNext())
		{
			//generateResult78();
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
		int computersCount = 0;
		int connectionsCount = 0;

		weightedEdgesVector networkGraph;

		generateResult09_Setup(networkGraph);

		generateResult09_Calculate(networkGraph);
	}
}

void Logic::generateResult09_Setup(weightedEdgesVector &networkGraph)
{
	int computersCount;
	int connectionsCount;

	int fromComputer;
	int toComputer;
	int connectionSpeed;

	ExerciseIOHandler >> computersCount;
	ExerciseIOHandler >> connectionsCount;

	// Indexed from 1. We will not use 0. index.
	networkGraph.resize(computersCount + 1, std::vector< std::pair < int, int > >(0));

	for (int i = 0; i < connectionsCount; ++i)
	{

		ExerciseIOHandler >> fromComputer;
		ExerciseIOHandler >> toComputer;
		ExerciseIOHandler >> connectionSpeed;

		//Non-Directional.
		networkGraph[fromComputer].push_back(std::make_pair(toComputer, connectionSpeed));
		networkGraph[toComputer].push_back(std::make_pair(fromComputer, connectionSpeed));
	}
}

void Logic::generateResult09_Calculate(weightedEdgesVector &networkGraph)
{
	// We will not use 0. index in these vectors.
	std::vector< int > maximumConnectionSpeedOfKnownComputers(networkGraph.size(), -1);
	std::vector< bool > knownComputers(networkGraph.size(), false);

	maximumConnectionSpeedOfKnownComputers[1] = 0;

	bool over = false;
	int notCheckedComputerCount = networkGraph.size() - 1; // We did not use 0. index, thats why the '- 1';

	while (!over)
	{
		// Get maximum copmputer speed and its index. We set to the 1. index, because we do not use the 0. index.
		int max = maximumConnectionSpeedOfKnownComputers[1];
		size_t maxIndex = 1;

		for (size_t i = 1; i < maximumConnectionSpeedOfKnownComputers.size(); ++i)
		{
			if (knownComputers[i] == false && maximumConnectionSpeedOfKnownComputers[i] > max)
			{
				max = maximumConnectionSpeedOfKnownComputers[i];
				maxIndex = i;
			}
		}

		// The computers are not connected.
		if (knownComputers[maxIndex] == 1)
		{
			ExerciseIOHandler << 0;
			ExerciseIOHandler << std::endl;
			return;
		}

		// We know it know.
		knownComputers[maxIndex] = 1;
		--notCheckedComputerCount;

		// Did we check all?
		for (size_t i = 1; i < knownComputers.size(); ++i)
		{
			over |= (notCheckedComputerCount == 0);
		}

		// Check the connections for a the maximum.
		const std::vector< std::pair< int, int > > & connectionsVector = networkGraph[maxIndex];
		for (auto it = connectionsVector.cbegin(); it != connectionsVector.cend(); ++it)
		{
			if (knownComputers[(*it).first] == 0)
			{
				if (maximumConnectionSpeedOfKnownComputers[(*it).first] < (*it).second)
				{
					maximumConnectionSpeedOfKnownComputers[(*it).first] = (*it).second;
				}
			}
		}
	}

	// We checked all of the computers.
	if (over)
	{
		// We seach for the lowest connection speed.
		int min = maximumConnectionSpeedOfKnownComputers[2];
		size_t minIndex = 2;
		for (size_t i = 2; i < maximumConnectionSpeedOfKnownComputers.size(); ++i)
		{
			if (maximumConnectionSpeedOfKnownComputers[i] < min)
			{
				min = maximumConnectionSpeedOfKnownComputers[i];
				minIndex = i;
			}
		}
		ExerciseIOHandler << maximumConnectionSpeedOfKnownComputers[minIndex];
		ExerciseIOHandler << std::endl;
	}
}


void Logic::generateResult25()
{
	int jStart;
	int tStart;

	vertexVector jGraph;
	vertexVector tGraph;

	generateResult25_Setup(jStart, tStart, jGraph, tGraph);

	generateResult25_Calculate(jStart, tStart, jGraph, tGraph);
}

void Logic::generateResult25_Setup(int &jStart, int &tStart, vertexVector &jGraph, vertexVector &tGraph)
{
	int sumRooms;

	int fromRoom;
	int toRoom;
	bool isTRooms;

	ExerciseIOHandler >> sumRooms;
	ExerciseIOHandler >> tStart;
	ExerciseIOHandler >> jStart;

	// Indexed from 1. We will not use 0. index.
	jGraph.resize(sumRooms + 1, std::vector< int >(0));
	tGraph.resize(sumRooms + 1, std::vector< int >(0));

	isTRooms = true;
	while (ExerciseIOHandler >> fromRoom)
	{
		ExerciseIOHandler >> toRoom;
		if (fromRoom == -1 && toRoom == -1)
		{
			isTRooms = false;
		}
		else
		{
			if (isTRooms)
			{
				tGraph[fromRoom].push_back(toRoom);
			}
			if (!isTRooms)
			{
				jGraph[fromRoom].push_back(toRoom);
			}
		}
	}
}

void Logic::generateResult25_Calculate(int &jStart, int &tStart, vertexVector &jGraph, vertexVector &tGraph)
{
	// We will not use the 0. index.
	std::vector< int > roomCheckState(jGraph.size(), 0);

	// Where can we go from tStart in tGraph.
	std::stack< int > needToCheck;
	needToCheck.push(tStart);

	roomCheckState[tStart] = 1;

	while (!needToCheck.empty())
	{
		const int roomIndex = needToCheck.top();
		needToCheck.pop();

		const std::vector< int > &neighbourRooms = tGraph[roomIndex];

		for (size_t i = 0; i < neighbourRooms.size(); ++i)
		{
			if (roomCheckState[neighbourRooms[i]] == 0)
			{
				needToCheck.push(neighbourRooms[i]);
				roomCheckState[neighbourRooms[i]] = 1;
			}
		}
	}

	// If we reached jStart form tStart throuth tGraph.
	if (roomCheckState[jStart] == 1)
	{
		ExerciseIOHandler << std::string("igen");
		ExerciseIOHandler << std::endl;
		ExerciseIOHandler << std::string("nem");
	}
	else
	{
		// Where can we go from jStart throuth jGraph.
		bool meet = false;
		bool circle = false;
		bool over = false;

		// The needToCheck stack is empty.
		needToCheck.push(jStart);

		// The roomCheckState[jStart] is 0.
		roomCheckState[jStart] = 2;

		while (!(needToCheck.empty()) && !over)
		{
			const int roomIndex = needToCheck.top();
			needToCheck.pop();

			const std::vector<int> &neighbourRooms = jGraph[roomIndex];
			for (auto it = neighbourRooms.cbegin(); it != neighbourRooms.cend(); ++it)
			{
				if (roomCheckState[(*it)] == 0) // No one was here before.
				{
					needToCheck.push((*it));
					roomCheckState[(*it)] = 2;					
				}
				else if (roomCheckState[(*it)] == 1) // First search was here before.
				{
					meet = true;
				}
				else if (roomCheckState[(*it)] == 2) // Second search was here before.
				{
					if ((*it) == jStart) // We are at jStart.
					{
						circle = true;
					}
				}

				// Do we need to search more?
				over = (meet == true) && (circle == true);
			}
		}

		if (meet)
		{
			ExerciseIOHandler << std::string("igen");
		}
		else
		{
			ExerciseIOHandler << std::string("nem");
		}

		ExerciseIOHandler << std::endl;

		if (circle)
		{
			ExerciseIOHandler << std::string("igen");
		}
		else
		{
			ExerciseIOHandler << std::string("nem");
		}
	}
}


void Logic::generateResult46()
{
	std::string startRiver;

	vertexVector downStreamGraph;
	vertexVector upStreamGraph;

	idMap riversIdMap;
	reversedIdVector reversedRiversIdVector;

	generateResult46_Setup(startRiver, downStreamGraph, upStreamGraph, riversIdMap, reversedRiversIdVector);
	
	generateResult46_Calculate(startRiver, downStreamGraph, upStreamGraph, riversIdMap, reversedRiversIdVector);
}

void Logic::generateResult46_Setup(std::string &startRiver, vertexVector &downStreamGraph, vertexVector &upStreamGraph, idMap &riversIdMap, reversedIdVector &reversedRiversIdVector)
{
	int riversPairCount;

	std::string riverNameFrom;
	std::string riverNameTo;

	ExerciseIOHandler >> riversPairCount;

	std::forward_list< std::string > riversDownStreams;

	int idIndex = 0;

	// Get all river name and count, while building riversIdMap.
	for (int i = 0; i < riversPairCount; ++i)
	{
		ExerciseIOHandler >> riverNameFrom;
		ExerciseIOHandler >> riverNameTo;

		int& riverIdFrom = riversIdMap[riverNameFrom];
		if (riverIdFrom == 0)
		{
			riverIdFrom = idIndex;
			++idIndex;
		}

		int& riverIdTo = riversIdMap[riverNameTo];
		if (riverIdTo == 0)
		{
			riverIdTo = idIndex;
			++idIndex;
		}

		riversDownStreams.push_front(riverNameTo);
		riversDownStreams.push_front(riverNameFrom);
	}
	
	ExerciseIOHandler >> startRiver;

	// Now put them into the graphs.
	downStreamGraph.resize(riversIdMap.size(), std::vector< int >(0));
	upStreamGraph.resize(riversIdMap.size(), std::vector< int >(0));

	while (!(riversDownStreams.empty()))
	{
		riverNameFrom = riversDownStreams.front();
		riversDownStreams.pop_front();
		riverNameTo = riversDownStreams.front();
		riversDownStreams.pop_front();

		downStreamGraph[riversIdMap[riverNameFrom]].push_back(riversIdMap[riverNameTo]);
		upStreamGraph[riversIdMap[riverNameTo]].push_back(riversIdMap[riverNameFrom]);
	}

	// Build the reversedRiversIdVector.
	reversedRiversIdVector.resize(riversIdMap.size());

	for (auto it = riversIdMap.cbegin(); it != riversIdMap.cend(); ++it)
	{
		reversedRiversIdVector[(*it).second] = (*it).first;
	}
}

void Logic::generateResult46_Calculate(std::string &startRiver, vertexVector &downStreamGraph, vertexVector &upStreamGraph, idMap &riversIdMap, reversedIdVector &reversedRiversIdVector)
{
	// Init.
	std::vector< int > riverCheckState(downStreamGraph.size(), 0);

	std::stack< int > needToCheck;
	needToCheck.push(riversIdMap[startRiver]);

	riverCheckState[riversIdMap[startRiver]] = 1;

	int riversCount = 0;

	// We check the rivers in upStreamGraph from startRiver.
	while (!(needToCheck.empty()))
	{
		const int riverIndex = needToCheck.top();
		needToCheck.pop();

		const std::vector< int > &upStreamRivers = upStreamGraph[riverIndex];
		for (auto it = upStreamRivers.cbegin(); it != upStreamRivers.cend(); ++it)
		{
			if (riverCheckState[(*it)] == 0)
			{
				needToCheck.push((*it));
				riverCheckState[(*it)] = 1;
				++riversCount;
			}
		}
	}

	// Write out what we found.
	ExerciseIOHandler << riversCount;
	ExerciseIOHandler << std::endl;

	for (size_t i = 0; i < riverCheckState.size(); ++i)
	{
		if (riverCheckState[i] == 1)
		{
			ExerciseIOHandler << reversedRiversIdVector[i];
			ExerciseIOHandler << std::endl;
			riverCheckState[i] = 0;
		}
	}

	// The needToCheck stack is empty here.
	needToCheck.push(riversIdMap[startRiver]);
	riversCount = 0;

	// We check the rivers in downStreamGraph from startRiver.
	while (!(needToCheck.empty()))
	{
		const int riverIndex = needToCheck.top();
		needToCheck.pop();

		const std::vector< int > &downStreamRivers = downStreamGraph[riverIndex];
		for (auto it = downStreamRivers.cbegin(); it != downStreamRivers.cend(); ++it)
		{
			if (riverCheckState[(*it)] == 0)
			{
				needToCheck.push((*it));
				riverCheckState[(*it)] = 1;
				++riversCount;
			}
		}
	}

	// Write out what we found.
	ExerciseIOHandler << riversCount;
	ExerciseIOHandler << std::endl;

	for (size_t i = 0; i < riverCheckState.size(); ++i)
	{
		if (riverCheckState[i] == 1)
		{
			ExerciseIOHandler << reversedRiversIdVector[i];
			ExerciseIOHandler << std::endl;
		}
	}
}


void Logic::generateResult52()
{
	int testDataCount;
	ExerciseIOHandler >> testDataCount;

	for (int i = 0; i < testDataCount; ++i)
	{
		weightedEdgesVector stageGraph;

		generateResult52_Setup(stageGraph);

		generateResult52_Calculate(stageGraph);
	}
}

void Logic::generateResult52_Setup(weightedEdgesVector &stageGraph)
{
	int stageCount;
	int processCount;

	ExerciseIOHandler >> stageCount;
	ExerciseIOHandler >> processCount;
	
	// Indexed from 0.
	stageGraph.resize(stageCount, std::vector< std::pair< int,int > >(0));

	int fromStage;
	int toStage;
	int processTime;

	for (int i = 0; i < processCount; ++i)
	{
		ExerciseIOHandler >> fromStage;
		ExerciseIOHandler >> toStage;
		ExerciseIOHandler >> processTime;
		stageGraph[fromStage].push_back(std::make_pair(toStage, processTime));
	}
}

void Logic::generateResult52_Calculate(weightedEdgesVector &stageGraph)
{
	// We build it form 0 indexed stage, leaving out unconnected stages.
	std::stack< int > topologicalOrderingOfStates;
	std::stack< int > depthSearchStack;

	// Indexed from 0.
	std::vector< bool > checkedStates(stageGraph.size(), false);

	depthSearchStack.push(0);

	while (!(depthSearchStack.empty()))
	{
		int index = depthSearchStack.top();

		if (checkedStates[index] == false)
		{
			checkedStates[index] = true;

			const auto &nextStages = stageGraph[index];
			for (auto it = nextStages.cbegin(); it != nextStages.cend(); ++it)
			{
				if (checkedStates[(*it).first] == false)
				{
					depthSearchStack.push((*it).first);
				}
			}
		}
		else
		{
			topologicalOrderingOfStates.push(depthSearchStack.top());
			depthSearchStack.pop();
		}
	}

	// If the last stage was put into the topological stack.
	if (checkedStates[stageGraph.size() - 1] == true)
	{

		std::vector< int > summedProcessTime(stageGraph.size(), 0);
		std::vector< int > parentStageVector(stageGraph.size(), -1);

		while (!(topologicalOrderingOfStates.empty()))
		{
			int index = topologicalOrderingOfStates.top();

			topologicalOrderingOfStates.pop();

			const auto &nextStages = stageGraph[index];
			for (auto it = nextStages.cbegin(); it != nextStages.cend(); ++it)
			{
				// We ignore if it points to itself.
				if ((*it).first != index)
				{
					int newProcessTime = summedProcessTime[index] + (*it).second;
					if (summedProcessTime[(*it).first] < newProcessTime)
					{
						summedProcessTime[(*it).first] = newProcessTime;

						parentStageVector[(*it).first] = index;
					}
				}
			}
		}

		int index = stageGraph.size() - 1;

		ExerciseIOHandler << summedProcessTime[index];
		ExerciseIOHandler << std::string(" ");

		std::stack< int > stagesPath;
		stagesPath.push(index);

		while (index != 0)
		{
			index = parentStageVector[index];
			stagesPath.push(index);
		}

		while (!(stagesPath.empty()))
		{
			ExerciseIOHandler << stagesPath.top();

			if (stagesPath.top() != stageGraph.size() - 1)
			{
				ExerciseIOHandler << std::string(", ");
			}

			stagesPath.pop();
		}
	}
	else
	{
		ExerciseIOHandler << std::string("Hibas utemterv!");
	}

	ExerciseIOHandler << std::endl;
}

void Logic::generateResult70()
{
	int startPoint;
	int endPoint;

	std::vector< int > parendtsCountOfPoints;
	vertexVector pointsGraph;

	generateResult70_Setup(startPoint, parendtsCountOfPoints, pointsGraph);

	generateResult70_Calculate(startPoint, parendtsCountOfPoints, pointsGraph);
}

void Logic::generateResult70_Setup(int &startPoint, std::vector< int > &parendtsCountOfPoints, vertexVector &pointsGraph)
{
	int pointsCount;
	int pathsCount;

	int endPoint;

	ExerciseIOHandler >> pointsCount;
	ExerciseIOHandler >> pathsCount;
	ExerciseIOHandler >> startPoint;
	ExerciseIOHandler >> endPoint;

	// Points are indexed from 1. This graph is connected without any circle.
	parendtsCountOfPoints.resize(pointsCount + 1, int(0));
	pointsGraph.resize(pointsCount + 1, std::vector< int >(0));

	for (int i = 0; i < pathsCount; ++i)
	{
		int fromPoint;
		int toPoint;

		ExerciseIOHandler >> fromPoint;
		ExerciseIOHandler >> toPoint;

		++(parendtsCountOfPoints[toPoint]);
		pointsGraph[fromPoint].push_back(toPoint);
	}
}

void Logic::generateResult70_Calculate(int &startPoint, std::vector< int > &parendtsCountOfPoints, vertexVector &pointsGraph)
{
	// We build it form startPoint point.
	std::stack< int > topologicalOrderingOfPoints;
	std::stack< int > depthSearchStack;

	std::vector< bool > checkedStates(pointsGraph.size(), false);

	depthSearchStack.push(startPoint);

	while (!(depthSearchStack.empty()))
	{
		int index = depthSearchStack.top();

		if (checkedStates[index] == false)
		{
			checkedStates[index] = true;

			const auto &nextStages = pointsGraph[index];
			for (auto it = nextStages.cbegin(); it != nextStages.cend(); ++it)
			{
				if (checkedStates[(*it)] == false)
				{
					depthSearchStack.push((*it));
				}
			}
		}
		else
		{
			topologicalOrderingOfPoints.push(depthSearchStack.top());
			depthSearchStack.pop();
		}
	}

	// Checking the in and out going paths from a point to tell if it is a critical point.
	int sumInOutPath = 0;
	std::vector< int > citicalPoints(0);

	while (!(topologicalOrderingOfPoints.empty()))
	{
		int index = topologicalOrderingOfPoints.top();

		sumInOutPath -= parendtsCountOfPoints[index];
		if (sumInOutPath == 0)
		{
			citicalPoints.push_back(index);
		}
		sumInOutPath += pointsGraph[index].size();

		topologicalOrderingOfPoints.pop();
	}

	ExerciseIOHandler << citicalPoints.size();
	ExerciseIOHandler << std::endl;

	for (auto it = citicalPoints.cbegin(); it != citicalPoints.cend(); ++it)
	{
		ExerciseIOHandler << (*it);
		ExerciseIOHandler << std::string(" ");
	}
}


void Logic::generateResult77()
{
	int minesCount = 0;

	vertexVector minesGraph;
	vertexVector minesReversedGraph;

	generateResult77_Setup(minesGraph, minesReversedGraph);

	generateResult77_Calculate(minesGraph, minesReversedGraph);
}

void Logic::generateResult77_Setup(vertexVector &minesGraph, vertexVector &minesReversedGraph)
{
	int minesCount;

	ExerciseIOHandler >> minesCount;

	// The mines are indexed from 1. We will not use 0. index.
	minesGraph.resize(minesCount + 1, std::vector< int >(0));

	for (int i = 0; i < minesCount; ++i)
	{
		int connectedCount;

		ExerciseIOHandler >> connectedCount;

		for (int j = 0; j < connectedCount; ++j)
		{
			int connectedMine;

			ExerciseIOHandler >> connectedMine;

			minesGraph[i + 1].push_back(connectedMine);
			minesReversedGraph[connectedMine].push_back(i + 1);
		}
	}
}

void Logic::generateResult77_Calculate(vertexVector &minesGraph, vertexVector &minesReversedGraph)
{
	std::vector< bool > checked(minesGraph.size(), false);
	std::stack< int > depthSearchStack;

	std::stack< int > firstDepthSearchResult;

	for (int i = 1; i < minesGraph.size(); ++i)
	{
		if (checked[i] == false)
		{
			depthSearchStack.push(i);

			while (!depthSearchStack.empty())
			{
				int index = depthSearchStack.top();

				if (checked[index] == false)
				{
					checked[index] = true;
					const std::vector< int > &minesChild = minesGraph[index];
					for (auto it = minesChild.begin(); it != minesChild.end(); ++it)
					{
						if (!checked[(*it)])
						{
							depthSearchStack.push(*it);
						}
					}
				}
				else
				{
					firstDepthSearchResult.push(depthSearchStack.top());
					depthSearchStack.pop();
				}
			}
		}
	}

	checked.clear();
	checked.resize(minesGraph.size() + 1, false);

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

/*
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
*/