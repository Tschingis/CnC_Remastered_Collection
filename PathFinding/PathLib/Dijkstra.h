#pragma once
#include "GraphMap.h"

// if defined, the algorithm exists directly if path found
#define DIJKSTRA_EARLY_DROPOUT

class Dijkstra
{
	const GraphMap* mGraph;
	int mNumNodes;
	int* mNodeDist;
	int* mParentNodes;

public:
	enum {
		Infinity = 0x3F3F3F3F
	};

	Dijkstra(const GraphMap* map);
	~Dijkstra();

	inline const int* getNodeDist() const { return mNodeDist; }
	inline const int* getParentNodes() const { return mParentNodes; }
	void run(int startNodeId, int endNodeId);
};

