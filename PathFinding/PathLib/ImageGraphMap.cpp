#include "ImageGraphMap.h"
#include "stb_image.h"

ImageGraphMap::ImageGraphMap(int width, int height, unsigned char * data)
	: GraphMap(width,height)
	, mData(data)
	, mSelfLoaded(false)
{
}

ImageGraphMap::ImageGraphMap(const char* pngFileName)
	: GraphMap(0,0)
	, mSelfLoaded(true)
{
	int n;
	// force grey scale image with parameter 1
	mData = stbi_load(pngFileName, &mWidth, &mHeight, &n, 1);
}

ImageGraphMap::~ImageGraphMap()
{
	if (mSelfLoaded)
		stbi_image_free(mData);
}


int ImageGraphMap::getEdges(Edge edges[MAX_EDGES], int nodeId) const
{
	// we use a black and white map, where full white(255) is walkable area with cost 1 and black(0) is non walkable area
	// intermediate grey scale is walkable with cost=(256 - greyvalue)
	int x = nodeId % mWidth;
	int y = nodeId / mHeight;

	const int nbCount = 8;
	int nb[nbCount];
	nb[0] = x > 0 ? nodeId - 1 : -1;	// leftId
	nb[1] = x < (mWidth - 1) ? nodeId + 1 : -1; // rightId
	nb[2] = y > 0 ? nodeId - mHeight : -1; // topId
	nb[3] = y < (mHeight - 1) ? nodeId + mHeight : -1; // bottomId
	nb[4] = (nb[2] >= 0 && nb[0] >= 0) ? nodeId - mHeight - 1 : -1; // topLeftId
	nb[5] = (nb[2] >= 0 && nb[1] >= 0) ? nodeId - mHeight + 1 : -1; // topRightId
	nb[6] = (nb[3] >= 0 && nb[0] >= 0) ? nodeId + mHeight - 1 : -1; // bottomLeftId
	nb[7] = (nb[3] >= 0 && nb[1] >= 0) ? nodeId + mHeight + 1 : -1; // bottomRightId

	int numEdges = 0;
	for (int i = 0; i < nbCount; ++i) {
		if (nb[i] < 0)
			continue;

		int cost = 256 - mData[nb[i]];
		if (cost == 256)
			continue;	// non walkable area

		edges[numEdges].targetNodeId = nb[i];

		if (i < 4)
			edges[numEdges].cost = cost * 2;
		else
			edges[numEdges].cost = cost * 3;

		++numEdges;
	}

	return numEdges;
}
