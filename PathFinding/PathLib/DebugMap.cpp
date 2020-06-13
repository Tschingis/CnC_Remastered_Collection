#include "DebugMap.h"
#include <cstring>
#include "stb_image_write.h"

#define IRED(i)		(i*3)
#define IGREEN(i)	(i*3+1)
#define IBLUE(i)	(i*3+2)


DebugMap::DebugMap(const char * debugFileName, const GraphMap * graph)
	: mDebugFileName(debugFileName)
	, mGraph(graph)
{
	mBuffer = new unsigned char[mGraph->getNumNodes() * 3];
	clear();
}

DebugMap::~DebugMap()
{
	delete[] mBuffer;
}

void DebugMap::clear()
{
	memset(mBuffer, 0, mGraph->getNumNodes() * 3);
}

void DebugMap::writeCosts(const int * costs)
{
	int numNodes = mGraph->getNumNodes();
	for (int i = 0; i < numNodes; ++i) {
		unsigned char v = costs[i] > 255 ? 255 : costs[i];
		writeGrey(i, v);
	}
}

void DebugMap::writeCostsScaled(const int * costs)
{
	int max = -1;
	int numNodes = mGraph->getNumNodes();
	for (int i = 0; i < numNodes; ++i) {
		if (costs[i] < 0x3F3F3F3F && costs[i] > max)
			max = costs[i];
	}

	float scale = 255.0f / (float)max;
	for (int i = 0; i < numNodes; ++i) {
		unsigned char v = (unsigned char)((float)costs[i] * scale);
		writeGrey(i, v);
	}
}

void DebugMap::writePath(const int * pathNodes, int numPathNodes)
{
	for (int i = 0; i < numPathNodes; ++i) {
		mBuffer[IBLUE(pathNodes[i])] = 255;
	}
}

void DebugMap::writeRGB(int nodeId, unsigned char r, unsigned char g, unsigned char b)
{
	mBuffer[nodeId * 3 + 0] = r;
	mBuffer[nodeId * 3 + 1] = g;
	mBuffer[nodeId * 3 + 2] = b;
}

void DebugMap::writeGrey(int nodeId, unsigned char v)
{
	writeRGB(nodeId, v, v, v);
}

void DebugMap::writeToFile()
{
	int width = mGraph->getWidth();
	stbi_write_png(mDebugFileName, width, mGraph->getHeight(), 3, mBuffer, width*3);
}
