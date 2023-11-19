#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <sstream>

class SebLogger
{
public:
	enum Severity {
		Debug = 1,
		Warning = 2,
		Error = 3,
		CriticalError = 4,
	};

	void Log(std::string Message, Severity severity);
	void ChangeTimeFormat(const char* NewFormat);
	void ExportToFile();

	SebLogger(const char* Format)
	{
		ChangeTimeFormat(Format);
		Log("A new logger instance was initialised", SebLogger::Severity::Warning);
	}
};

