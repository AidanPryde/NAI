#ifndef _GRAPH_EDGE_WEIGHTED_H_
#define _GRAPH_EDGE_WEIGHTED_H_

#include <vector>
#include <map>
#include <stack>

template< typename id_t, typename weight_t >
class Vertex;

template< typename id_t, typename weight_t >
class Edge
{
public:
	Edge() : Weight(weight_t()), Visited(0) { }
	Edge(weight_t weight) : Weight(weight), Visited(0) { }
	Edge(Vertex< id_t, weight_t >* otherVertex, weight_t weight) : OtherVertex(otherVertex), Weight(weight), Visited(0) { }

	Vertex< id_t, weight_t >* OtherVertex;

	int Visited;
	weight_t Weight;
};

template< typename id_t, typename weight_t >
class Vertex
{
public:
	Vertex() : Visited(0), PathWeight(weight_t()) { }
	Vertex(id_t id, size_t index) : Id(id), Index(index), Visited(0), PathWeight(weight_t()) { }

	std::vector< Edge< id_t, weight_t >* > OutEdgesVector;
	std::vector< Vertex< id_t, weight_t >* > ParentVertexesVector;

	int Visited;

	weight_t PathWeight;

	size_t Index;
	id_t Id;
};

template< typename id_t, typename weight_t >
class GraphEdgeWeighted
{
public:
	GraphEdgeWeighted();
	~GraphEdgeWeighted();

	void addEdge(id_t fromVertex, id_t toVertex, weight_t weight);

	void parallelIngress(id_t startVertexId, weight_t useableEdges, int setVisitedTo);
	void deepIngress(id_t startVertexId);

	int getVertexVisitedAt(id_t id) const;

	size_t size();

	void setWeightDefaultValue(weight_t defaultWeightValue);
	void reSet();
	void setStartEndVertexesVectors();

private:

	weight_t DefaultWeightValue;

	std::map< id_t, size_t > IdToIndexMap;
	std::map< size_t, id_t > IndexToIdMap;

	std::vector< Vertex< id_t, weight_t >* > VertexesVector;

	std::vector< Vertex< id_t, weight_t >* > StartVertexesVector;
	std::vector< Vertex< id_t, weight_t >* > EndVertexesVector;
};

template< typename id_t, typename weight_t >
inline GraphEdgeWeighted< id_t, weight_t >::GraphEdgeWeighted()
{
	DefaultWeightValue = weight_t();
}

template< typename id_t, typename weight_t >
inline GraphEdgeWeighted< id_t, weight_t >::~GraphEdgeWeighted()
{
	for (auto it = VertexesVector.begin(); it != VertexesVector.end(); ++it)
	{
		delete (*it);
	}
}

template< typename id_t, typename weight_t >
inline void GraphEdgeWeighted< id_t, weight_t >::addEdge(id_t fromVertex, id_t toVertex, weight_t weight)
{
	if (IdToIndexMap.find(fromVertex) == IdToIndexMap.end())
	{
		IdToIndexMap[fromVertex] = VertexesVector.size();
		IndexToIdMap[VertexesVector.size()] = fromVertex;
		VertexesVector.push_back(new Vertex< id_t, weight_t >(fromVertex, IdToIndexMap[fromVertex]));
	}

	if (IdToIndexMap.find(toVertex) == IdToIndexMap.end())
	{
		IdToIndexMap[toVertex] = VertexesVector.size();
		IndexToIdMap[VertexesVector.size()] = toVertex;
		VertexesVector.push_back(new Vertex< id_t, weight_t >(toVertex, IdToIndexMap[toVertex]));
	}


	VertexesVector[IdToIndexMap[fromVertex]]->OutEdgesVector.push_back(new Edge< id_t, weight_t >(weight, VertexesVector[IdToIndexMap[toVertex]]));
	VertexesVector[IdToIndexMap[toVertex]]->ParentVertexesVector.push_back(VertexesVector[IdToIndexMap[fromVertex]]);
}

template< typename id_t, typename weight_t >
inline void GraphEdgeWeighted< id_t, weight_t >::parallelIngress(id_t startVertexId, weight_t useableEdges, int setVisitedTo)
{
	std::stack< Vertex< id_t >* > needToCheck;

	needToCheck.push(VertexesVector[IdToIndexMap[startVertexId]]);

	while (!needToCheck.empty())
	{
		Vertex< id_t >* vertex = needToCheck.back();
		needToCheck.pop();

		for (auto it = vertex->OutEdgesVector.begin(); it != vertex->OutEdgesVector.end(); ++it)
		{
			if ((*it)->Weight == useableEdges && (*it)->Visited == 0)
			{
				(*it)->Visited = setVisitedTo;
				needToCheck.push((*it)->OtherVertex);
			}
		}
	}
}

template< typename id_t, typename weight_t >
inline void GraphEdgeWeighted< id_t, weight_t >::deepIngress(id_t startVertexId)
{

}

template<typename id_t, typename weight_t>
inline int GraphEdgeWeighted<id_t, weight_t>::getVertexVisitedAt(id_t id) const
{
	return VertexesVector[IdToIndexMap[id]]->Visited;
}

template< typename id_t, typename weight_t >
inline size_t GraphEdgeWeighted< id_t, weight_t >::size()
{
	return VertexesVector.size();
}

template<typename id_t, typename weight_t>
inline void GraphEdgeWeighted<id_t, weight_t>::setWeightDefaultValue(weight_t defaultWeightValue)
{
	DefaultWeightValue = defaultWeightValue;
}

template< typename id_t, typename weight_t >
inline void GraphEdgeWeighted< id_t, weight_t >::reSet()
{
	for (auto it = VertexesVector.begin(); it != VertexesVector.end(); ++it)
	{
		(*it)->Visited = 0;
		(*it)->PathWeight = DefaultWeightValue;
	}
}

template< typename id_t, typename weight_t >
inline void GraphEdgeWeighted< id_t, weight_t >::setStartEndVertexesVectors()
{
	for (auto it = VertexesVector.begin(); it != VertexesVector.end(); ++it)
	{
		if ((*it)->OutEdgesVector.empty())
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