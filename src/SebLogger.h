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

	enum TimeFormat {
		HOURS_MINUTES = 1,
		MINUTES_HOURS = 2,
		HOURS = 3,
		MINUTES = 4,
	};


	void Log(std::string Message, Severity severity);
	void ChangeTimeFormat(TimeFormat NewFormat);
	void ExportToFile();

	SebLogger(TimeFormat Format)
	{
		Log("A new logger instance was initialised", SebLogger::Severity::Warning);
		ChangeTimeFormat(Format);
	}
};

