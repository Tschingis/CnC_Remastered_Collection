#pragma once
#include "Edge.h"

#define MAX_EDGES	4

class GraphMap
{
	const unsigned char* mData;
	int mWidth;
	int mHeight;

public:
	GraphMap(int width, int height, const unsigned char* data);

	inline int getNumNodes() const { return mWidth * mHeight; }
	inline int getNodeId(int x, int y) const { return y * mWidth + x; }

	// gets edges for a certain nodeId, returns the number of edges for the supplied node
	int getEdges(Edge edges[MAX_EDGES], int nodeId) const;

};

