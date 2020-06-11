#pragma once
class PathBuilder
{
	const int* mParentNodes;

public:
	PathBuilder(const int* parentNodes);

	int build(int* pathList, int maxLen, int dstNodeId);
};

