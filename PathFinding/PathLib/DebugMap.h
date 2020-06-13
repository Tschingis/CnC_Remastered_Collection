#pragma once
#include "GraphMap.h"

class DebugMap
{
	const char* mDebugFileName;
	const GraphMap* mGraph;
	unsigned char* mBuffer;

public:
	DebugMap(const char* debugFileName, const GraphMap* graph);
	~DebugMap();

	void clear();

	void writeCosts(const int* costs);
	void writeCostsScaled(const int* costs);
	void writePath(const int* pathNodes, int numPathNodes);
	void writeRGB(int nodeId, unsigned char r, unsigned char g, unsigned char b);
	void writeGrey(int nodeId, unsigned char v);

	void writeToFile();

private:
};

