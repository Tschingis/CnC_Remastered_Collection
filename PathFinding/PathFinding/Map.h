#pragma once
class Map
{
	unsigned char* mData;
	int mWidth;
	int mHeight;

public:
	Map(int width, int height, const unsigned char* data= nullptr);
	~Map();

	inline const unsigned char* getData() const { return mData; }
	inline unsigned char* getData() { return mData; }
	inline int getWidth() const { return mWidth; }
	inline int getHeight() const { return mHeight; }

	inline unsigned char getPos(int x, int y) const { return mData[y*mWidth + x]; }

	void setData(const unsigned char* data);

};

