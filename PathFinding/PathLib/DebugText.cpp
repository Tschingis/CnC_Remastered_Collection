#include "DebugText.h"
#include <iostream>
#include <fstream>

#define STREAM	((std::ofstream*)mStream)


DebugText::DebugText(const char* debugFile)
	: mDebugFile(debugFile)
{
	mStream = new std::ofstream();
	STREAM->open(debugFile);
}

DebugText::~DebugText()
{
	STREAM->close();
	delete STREAM;
}

void DebugText::writeDebug(int number)
{
	(*STREAM) << number;
}

void DebugText::writeDebug(const char* text)
{
	(*STREAM) << text;
}

void DebugText::writeNewLine()
{
	(*STREAM) << "\n";
}
