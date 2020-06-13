#include "PathBuilder.h"
#include <vector>

PathBuilder::PathBuilder(const int * parentNodes)
	: mParentNodes(parentNodes)
{
}

int PathBuilder::build(int * pathList, int maxLen, int dstNodeId)
{
	if (mParentNodes[dstNodeId] < 0)
		return 0;

	int currNodeId = dstNodeId;
	int pathLen = 0;
	while (currNodeId >= 0 && pathLen < maxLen) {
		pathList[pathLen] = currNodeId;
		++pathLen;
		currNodeId = mParentNodes[currNodeId];
	}

	std::reverse(pathList, pathList + pathLen);

	return pathLen;
}
