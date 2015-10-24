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
	Vertex(id_t id) : Id(id), Visited(0), PathWeight(weight_t()) { }

	std::vector< Edge< id_t, weight_t >* > OutEdgesVector;
	std::vector< Vertex< id_t, weight_t >* > ParentVertexesVector;

	int Visited;

	weight_t PathWeight;

	id_t Id;
};

#endif