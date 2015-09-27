#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <map>
#include <stack>

static int deph = 0;

template< typename T >
class Vertex
{
public:
	Vertex() : Visited(0), ChieldInSearch(0) { }
	Vertex(T id, size_t index) : Id(id), Index(index), Visited(0), ChieldInSearch(0) { }

	int Visited;
	int ChieldInSearch;

	std::vector< Vertex< T >* > ChildsVector;
	std::vector< Vertex< T >* > ParentsVector;

	size_t Index;
	T Id;
};


template< typename T >
class Graph
{
public:
	Graph();
	~Graph();


	void addEdge(T from, T to);

	void parallelIngress(T startVertexId, int setTo = 1, int check = 0);
	
	void deepIngress(T startVertexId);

	Vertex< T >* getTopologicalVertexAt(size_t i);

	size_t size();
	size_t topologicalSize();

	void reSet();

private:

	std::map< T, size_t > IdToIndexMap;
	std::map< size_t, T > IndexToIdMap;

	std::stack< Vertex< T >* > deepIngressStack;

	std::vector< Vertex< T >* > VertexesVector;

	std::vector< Vertex< T >* > StartVertexesVector;
	std::vector< Vertex< T >* > EndVertexesVector;

	std::vector< Vertex< T >* > TopologicalOrderVector;
};



template<typename T>
inline Graph<T>::Graph()
{
}

template< typename T >
inline Graph<T>::~Graph()
{
	for (auto it = VertexesVector.begin(); it != VertexesVector.end(); ++it)
	{
		delete (*it);
	}
}

template<typename T>
inline void Graph< T >::addEdge(T fromVertex, T toVertex)
{
	if (IdToIndexMap.find(fromVertex) == IdToIndexMap.end())
	{
		IdToIndexMap[fromVertex] = VertexesVector.size();
		IndexToIdMap[VertexesVector.size()] = fromVertex;
		VertexesVector.push_back(new Vertex< T >(fromVertex, IdToIndexMap[fromVertex]));
	}
	
	if (IdToIndexMap.find(toVertex) == IdToIndexMap.end())
	{
		IdToIndexMap[toVertex] = VertexesVector.size();
		IndexToIdMap[VertexesVector.size()] = toVertex;
		VertexesVector.push_back(new Vertex< T >(toVertex, IdToIndexMap[toVertex]));
	}

	VertexesVector[IdToIndexMap[fromVertex]]->ChildsVector.push_back(VertexesVector[IdToIndexMap[toVertex]]);
	VertexesVector[IdToIndexMap[toVertex]]->ParentsVector.push_back(VertexesVector[IdToIndexMap[fromVertex]]);

}

template<typename T>
inline void Graph< T >::parallelIngress(T startVertexId, int setTo, int check)
{
	std::vector< Vertex< T >* > needToCheck;

	needToCheck.push_back(VertexesVector[IdToIndexMap[startVertexId]]);

	
	while (!needToCheck.empty())
	{
		Vertex< T >* vertex = needToCheck.back();
		needToCheck.pop_back();

		for (auto it = vertex->ChildsVector.begin(); it != vertex->ChildsVector.end(); ++it)
		{
			if ((*it)->Visited == 0)
			{
				(*it)->Visited = 1;
				needToCheck.push_back(*it);
			}
		}
	}
}

template<typename T>
inline Vertex< T > * Graph< T >::getTopologicalVertexAt(size_t i)
{
	return TopologicalOrderVector[i];
}

template<typename T>
inline size_t Graph<T>::size()
{
	return VertexesVector.size();
}

template<typename T>
inline size_t Graph<T>::topologicalSize()
{
	return TopologicalOrderVector.size();
}

template<typename T>
inline void Graph<T>::reSet()
{
	for (auto it = VertexesVector.begin(); it != VertexesVector.end(); ++it)
	{
		(*it)->Visited = 0;
	}
}

template<typename T>
inline void Graph< T >::deepIngress(T startVertexId)
{
	TopologicalOrderVector.clear();

	while (!deepIngressStack.empty())
	{
		deepIngressStack.pop();
	}

	deepIngressStack.push(VertexesVector[IdToIndexMap[startVertexId]]);

	while (!deepIngressStack.empty())
	{
		Vertex< T >* vertex = deepIngressStack.top();

		if (vertex->Visited == 0)
		{
			vertex->Visited = 1;
			for (auto it = vertex->ChildsVector.begin(); it != vertex->ChildsVector.end(); ++it)
			{
				if ((*it)->Visited == 0)
				{
					deepIngressStack.push(*it);
				}
			}
			
		}
		else
		{
			TopologicalOrderVector.push_back(vertex);
			deepIngressStack.pop();
		}
	}
}

#endif