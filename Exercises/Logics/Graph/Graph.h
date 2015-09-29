#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <map>
#include <stack>

static int deph = 0;

template< typename id_t >
class Vertex
{
public:
	Vertex() : Visited(0), ChieldInSearch(0) { }
	Vertex(id_t id, size_t index) : Id(id), Index(index), Visited(0) { }

	std::vector< Vertex< id_t >* > ChildVertexesVector;
	std::vector< Vertex< id_t >* > ParentVertexesVector;

	int Visited;

	size_t Index;
	id_t Id;
};


template< typename id_t >
class Graph
{
public:
	Graph();
	~Graph();


	void addEdge(id_t from, id_t to);

	void parallelIngress(id_t startVertexId);
	void deepIngress(id_t startVertexId);

	Vertex< id_t >* getTopologicalVertexAt(size_t i);

	size_t size();
	size_t topologicalSize();

	void reSet();
	void setStartEndVertexesVectors();

private:

	std::map< id_t, size_t > IdToIndexMap;
	std::map< size_t, id_t > IndexToIdMap;

	std::vector< Vertex< id_t >* > VertexesVector;

	std::vector< Vertex< id_t >* > StartVertexesVector;
	std::vector< Vertex< id_t >* > EndVertexesVector;

	std::vector< Vertex< id_t >* > TopologicalOrderVector;
};



template< typename id_t >
inline Graph< id_t >::Graph()
{
}

template< typename id_t >
inline Graph< id_t >::~Graph()
{
	for (auto it = VertexesVector.begin(); it != VertexesVector.end(); ++it)
	{
		delete (*it);
	}
}

template< typename id_t >
inline void Graph< id_t >::addEdge(id_t fromVertex, id_t toVertex)
{
	if (IdToIndexMap.find(fromVertex) == IdToIndexMap.end())
	{
		IdToIndexMap[fromVertex] = VertexesVector.size();
		IndexToIdMap[VertexesVector.size()] = fromVertex;
		VertexesVector.push_back(new Vertex< id_t >(fromVertex, IdToIndexMap[fromVertex]));
	}
	
	if (IdToIndexMap.find(toVertex) == IdToIndexMap.end())
	{
		IdToIndexMap[toVertex] = VertexesVector.size();
		IndexToIdMap[VertexesVector.size()] = toVertex;
		VertexesVector.push_back(new Vertex< id_t >(toVertex, IdToIndexMap[toVertex]));
	}

	VertexesVector[IdToIndexMap[fromVertex]]->ChildVertexesVector.push_back(VertexesVector[IdToIndexMap[toVertex]]);
	VertexesVector[IdToIndexMap[toVertex]]->ParentVertexesVector.push_back(VertexesVector[IdToIndexMap[fromVertex]]);

}

template< typename id_t >
inline void Graph< id_t >::parallelIngress(id_t startVertexId)
{
	std::stack< Vertex< id_t >* > needToCheck;

	needToCheck.push(VertexesVector[IdToIndexMap[startVertexId]]);
	
	while (!needToCheck.empty())
	{
		Vertex< id_t >* vertex = needToCheck.back();
		needToCheck.pop();

		for (auto it = vertex->ChildVertexesVector.begin(); it != vertex->ChildVertexesVector.end(); ++it)
		{
			if ((*it)->Visited == 0)
			{
				(*it)->Visited = 1;
				needToCheck.push(*it);
			}
		}
	}
}

template< typename id_t >
inline void Graph< id_t >::deepIngress(id_t startVertexId)
{
	TopologicalOrderVector.clear();

	std::stack< Vertex< id_t >* > deepIngressStack;

	deepIngressStack.push(VertexesVector[IdToIndexMap[startVertexId]]);

	while (!deepIngressStack.empty())
	{
		Vertex< id_t >* vertex = deepIngressStack.top();

		if (vertex->Visited == 0)
		{
			vertex->Visited = 1;
			for (auto it = vertex->ChildVertexesVector.begin(); it != vertex->ChildVertexesVector.end(); ++it)
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

template< typename id_t >
inline Vertex< id_t > * Graph< id_t >::getTopologicalVertexAt(size_t i)
{
	return TopologicalOrderVector[i];
}

template< typename id_t >
inline size_t Graph< id_t >::size()
{
	return VertexesVector.size();
}

template< typename id_t >
inline size_t Graph< id_t >::topologicalSize()
{
	return TopologicalOrderVector.size();
}

template< typename id_t >
inline void Graph< id_t >::reSet()
{
	for (auto it = VertexesVector.begin(); it != VertexesVector.end(); ++it)
	{
		(*it)->Visited = 0;
	}
}

template< typename id_t >
inline void Graph< id_t >::setStartEndVertexesVectors()
{
	for (auto it = VertexesVector.begin(); it != VertexesVector.end(); ++it)
	{
		if ((*it)->ChildVertexesVector.empty())
		{
			EndVertexesVector.push_back(*it);
		}

		if ((*it)->ParentVertexesVector.empty())
		{
			StartVertexesVector.push_back(*it);
		}
	}
}

#endif