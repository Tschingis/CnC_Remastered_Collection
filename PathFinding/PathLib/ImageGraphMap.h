#pragma once
#include "GraphMap.h"

class ImageGraphMap : public GraphMap
{
	const unsigned char* mData;

public:
	ImageGraphMap(int width, int height, const unsigned char* data);

	virtual int getEdges(Edge edges[MAX_EDGES], int nodeId) const;
};

