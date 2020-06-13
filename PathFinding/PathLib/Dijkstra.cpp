#include "Dijkstra.h"
#include <queue>
#include <vector>

// queue element
// first = current weight of node
// second = nodeId
typedef std::pair<int, int> QueueElement;


Dijkstra::Dijkstra(const GraphMap * map)
	: mGraph(map)
{
	mNumNodes = map->getNumNodes();
	mNodeDist = new int[mNumNodes];
	mParentNodes = new int[mNumNodes];
}

Dijkstra::~Dijkstra()
{
	delete[] mNodeDist;
	delete[] mParentNodes;
}

void Dijkstra::run(int startNodeId)
{
	// set dist to infinity
	memset(mNodeDist, Infinity, sizeof(int)*mNumNodes);
	// clear parent nodes
	memset(mParentNodes, -1, sizeof(int)*mNumNodes);

	std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> queue;

	// add startNodeId to queue and set distance to 0
	queue.push(QueueElement(0, startNodeId));
	mNodeDist[startNodeId] = 0;

	Edge edges[MAX_EDGES];

	while (!queue.empty()) {
		auto currNode = queue.top();
		auto currNodeId = currNode.second;
		auto currCosts = currNode.first;
		queue.pop();

		// if we found already a cheaper path until this node, we skip this entry
		if (mNodeDist[currNodeId] < currCosts)
			continue;

		int numEdges = mGraph->getEdges(edges, currNodeId);
		for (int i = 0; i < numEdges; ++i) {
			const int targetNodeId = edges[i].targetNodeId;

			// we go only to the target node if we can
			// achieve a cheaper path
			auto targetNodeCosts = mNodeDist[currNodeId] + edges[i].cost;
			if (targetNodeCosts < mNodeDist[targetNodeId]) {
				mNodeDist[targetNodeId] = targetNodeCosts;
				mParentNodes[targetNodeId] = currNodeId;
				queue.push(QueueElement(targetNodeCosts, targetNodeId));
			}
		}
	}

}
