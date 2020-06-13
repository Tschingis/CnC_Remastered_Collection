#pragma once
#include "GraphMap.h"

class ImageGraphMap : public GraphMap
{
	unsigned char* mData;
	bool mSelfLoaded;

public:
	ImageGraphMap(int width, int height, unsigned char* data);
	ImageGraphMap(const char* pngFileName);
	~ImageGraphMap();

	virtual int getEdges(Edge edges[MAX_EDGES], int nodeId) const;
};

