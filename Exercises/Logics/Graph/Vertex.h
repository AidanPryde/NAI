#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>

template< typename id_t >
class Vertex
{
public:
	Vertex() : Visited(0), ChieldInSearch(0) { }
	Vertex(id_t id) : Id(id), Visited(0) { }

	std::vector< Vertex< id_t >* > ChildVertexesVector;
	std::vector< Vertex< id_t >* > ParentVertexesVector;

	int Visited;

	id_t Id;
};

#endif