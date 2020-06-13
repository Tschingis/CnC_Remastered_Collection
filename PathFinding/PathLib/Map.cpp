#include "Map.h"
#include <cstring>

Map::Map(int width, int height, const unsigned char* data)
	: mWidth(width)
	, mHeight(height)
{
	mData = new unsigned char[mWidth*mHeight];
	if (data) {
		setData(data);
	}
}

Map::~Map()
{
	delete[] mData;
}

void Map::setData(const unsigned char * data)
{
	std::memcpy(mData, data, mWidth*mHeight);
}
