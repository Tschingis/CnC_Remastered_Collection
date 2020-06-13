#pragma once


class DebugText
{
	const char* mDebugFile;
	void* mStream;
public:
	DebugText(const char* debugFile);
	~DebugText();

	void writeDebug(int number);
	void writeDebug(const char* text);
	void writeNewLine();

};

