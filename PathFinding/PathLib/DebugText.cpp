#include "DebugText.h"
#include <iostream>
#include <fstream>
#include <stdarg.h>

#define STREAM	((std::ofstream*)mStream)


DebugText::DebugText(const char* debugFile)
	: mDebugFile(debugFile)
{
	mStream = new std::ofstream();
	STREAM->open(debugFile, std::ofstream::out | std::ofstream::app);
	mPrefix[0] = 0;
}

DebugText::~DebugText()
{
	STREAM->close();
	delete STREAM;
}

void DebugText::setPrefix(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf(mPrefix, sizeof(mPrefix), format, args);
	va_end(args);
}

void DebugText::write(int number)
{
	(*STREAM) << number;
}

void DebugText::write(const char* text)
{
	(*STREAM) << text;
}

void DebugText::writeFormat(const char * format, ...)
{
	va_list args;
	char buff[2000];
	va_start(args, format);
	vsnprintf(buff, sizeof(buff), format, args);
	va_end(args);
	
	(*STREAM) << mPrefix << buff << "\n";
}

void DebugText::writeNewLine()
{
	(*STREAM) << "\n";
}
