#include "BFS.h"
#include <queue>

BFS::BFS(const GraphMap * graph)
	: mGraph(graph)
{
	mNumNodes = graph->getNumNodes();
	mNodeDist = new int[mNumNodes];
}

BFS::~BFS()
{
	delete[] mNodeDist;
}

void BFS::run(int startNodeId)
{
	// clear dist
	memset(mNodeDist, 0, sizeof(int) * mNumNodes);

	mNodeDist[startNodeId] = 1;

	std::queue<int> queue;

	// push start node
	queue.push(startNodeId);
	Edge edges[MAX_EDGES];

	while (!queue.empty()) {
		const int currNodeId = queue.front();
		queue.pop();

		int numEdges = mGraph->getEdges(edges, currNodeId);

		for (int i = 0; i < numEdges; ++i) {
			const int targetNodeId = edges[i].targetNodeId;
			// check if we where already on this node
			if (mNodeDist[targetNodeId])
				continue;

			mNodeDist[targetNodeId] = mNodeDist[currNodeId] + 1;
			queue.push(targetNodeId);
		}
	}
}
