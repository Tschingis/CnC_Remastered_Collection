#pragma once


class DebugText
{
	const char* mDebugFile;
	void*		mStream;
	char		mPrefix[1000];

public:
	DebugText(const char* debugFile);
	~DebugText();

	void setPrefix(const char* format, ...);
	void write(int number);
	void write(const char* text);
	void writeFormat(const char* format, ...);
	void writeNewLine();

};

