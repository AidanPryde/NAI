#ifndef _GRAPH_EDGE_WEIGHTED_H_
#define _GRAPH_EDGE_WEIGHTED_H_

#include <vector>
#include <map>

class Vertex;

class Edge
{
public:
	Edge(int weight = 0) : Weight(weight) { }
	Edge(Vertex* otherVertex, int weight = 0) : OtherVertex(otherVertex), Weight(weight) { }
	Vertex* OtherVertex;
	int Weight;
	int Checked;
};

class Vertex
{
public:
	Vertex(int pathWeight = 0) : PathWeight(pathWeight) { }

	std::vector< Edge* > OutEdgesVector;
	std::vector< Edge* > InEdgesVector;

	int PathWeight;
};

template< typename T >
class GraphEdgeWeighted
{
public:
	GraphEdgeWeighted();
	~GraphEdgeWeighted();

private:

	std::map< T, int > IdMap;
	std::vector< Vertex* > VertexesVector;

	std::vector< Vertex* > StartVertexesVector;
	std::vector< Vertex* > EndVertexesVector;
};

template<typename T>
inline GraphEdgeWeighted<T>::GraphEdgeWeighted()
{
}

template<typename T>
inline GraphEdgeWeighted<T>::~GraphEdgeWeighted()
{
}

#endif