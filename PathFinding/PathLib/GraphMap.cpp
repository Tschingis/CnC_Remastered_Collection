#include "GraphMap.h"

GraphMap::GraphMap(int width, int height, const unsigned char * data)
	: mData(data)
	, mWidth(width)
	, mHeight(height)
{
}

int GraphMap::getEdges(Edge edges[MAX_EDGES], int nodeId) const
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
