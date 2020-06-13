#pragma once

#include "GraphMap.h"

class BFS
{
	const GraphMap* mGraph;
	int mNumNodes;
	int* mNodeDist;

public:
	BFS(const GraphMap* graph);
	~BFS();

	inline const int* getNodeDist() const { return mNodeDist; }
	void run(int startNodeId);

	
};

