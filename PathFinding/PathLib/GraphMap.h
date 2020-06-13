#pragma once
#include "Edge.h"

#define MAX_EDGES	8

class GraphMap
{
protected:
	int mWidth;
	int mHeight;

public:
	GraphMap(int width, int height);
	virtual ~GraphMap();

	inline int getWidth() const { return mWidth; }
	inline int getHeight() const { return mHeight; }
	inline int getNumNodes() const { return mWidth * mHeight; }
	inline int getNodeId(int x, int y) const { return y * mWidth + x; }

	// gets edges for a certain nodeId, returns the number of edges for the supplied node
	virtual int getEdges(Edge edges[MAX_EDGES], int nodeId) const = 0;

};

