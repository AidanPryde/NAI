#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <map>

class Vertex
{
public:
	Vertex() { }

	int visited;

	std::vector< Vertex* > ChildsVector;
	std::vector< Vertex* > ParentsVector;
};


template< typename T >
class Graph
{
public:
	Graph();
	Graph(const std::map< T, std::vector< T > > &inDataMap);
	~Graph();

	void Fill(const std::map< T, std::vector< T > > &inDataMap);

private:

	std::map< T, int > IdMap;
	std::vector< Vertex* > VertexesVector;

	std::vector< Vertex* > StartVertexesVector;
	std::vector< Vertex* > EndVertexesVector;

};

template< typename T >
Graph< T >::Graph()
{
}

template <typename T >
Graph< T >::Graph(const std::map< T, std::vector< T > > &inDataMap)
{
	Fill(inDataMap);
}

template< typename T >
Graph<T>::~Graph()
{
	for (auto it = VertexesVector.begin();
	it != VertexesVector.end();
		++it)
	{
		delete (*it);
	}
}

template< typename T >
void Graph< T >::Fill(const std::map< T, std::vector< T > > &inDataMap)
{
	VertexesVector(inDataMap.size());

	for (auto it = inDataMap.cbegin(), int i = 0;
	it != inDataMap.cend();
		++it, ++i)
	{
		IdMap[it->first] = i;
		if (it->Second.Size() == 0)
		{
			EndVertexesVector.push_back(VertexesVector[i]);
		}
	}

	for (auto it = inDataMap.cbegin(), int i = 0;
	it != inDataMap.cend();
		++it, ++i)
	{
		for (auto itit = it->cbegin();
		itit != it->cend();
			++itit)
		{
			VertexesVector[i]->ChildsVector.push_back(VertexesVector[IdMap[*itit]]);
			VertexesVector[IdMap[*itit]]->ParentsVector.push_back(VertexesVector[i]);
		}
	}

	for (auto it = VertexesVector->cbegin();
	it != VertexesVector->cend();
		++it)
	{
		if ((*it)->ParentsVector.size() == 0)
		{
			StartVertexesVector.push_back(it);
		}
	}
}

#endif