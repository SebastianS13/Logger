#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>

std::vector<std::string> Logs;

int TotalLogEvents = 0;
int TotalWarnings = 0;
int TotalErrors = 0;

class SebLogger
{
public:

	SebLogger()
	{
		Log("A new logger instance was initialised", SebLogger::Severity::Warning);
	}

	enum Severity {
		Debug = 1,
		Warning = 2,
		Error = 3
	};

	void Log(std::string Message, Severity severity)
	{
		TotalLogEvents += 1;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		time_t now = time(0);
		struct tm currentTimeInfo;
		localtime_s(&currentTimeInfo, &now);
		int Hours = currentTimeInfo.tm_hour;
		int Minutes = currentTimeInfo.tm_min;

		std::string Time = Hours + ":" + Minutes;

		switch (severity) {
		case Severity::Debug:
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			std::cout << "[DEBUG]				" << Message << std::endl;
			Logs.push_back("[DEBUG]				" + Message);
			break;
		case Severity::Warning:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << "[DEBUG - WARNING]		" << Message << std::endl;
			Logs.push_back("[DEBUG - WARNING]		" + Message);
			TotalWarnings += 1;
			break;
		case Severity::Error:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::cout << "[DEBUG - ERROR]			" << Message << std::endl;
			Logs.push_back("[DEBUG - ERROR]			" + Message);
			TotalErrors += 1;
			break;
		default:
			std::cout << "[DEBUG - ERROR] Passed serverity is incorrect!" << std::endl;
			TotalErrors += 1;
		}

		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}

	void ExportToFile()
	{
		std::string FileName = "Log.log";
		std::ofstream file(FileName);

		if (!file.is_open())
		{
			SebLogger::Log("couldnt create log output file!", SebLogger::Severity::Error);
		}

		file << "[INFORMATION]" << std::endl;
		file << std::endl;

		file << "Total log events durring session: " << TotalLogEvents << std::endl;
		file << "Total warnings durring session: " << TotalWarnings << std::endl;
		file << "Total errors durring session: " << TotalErrors << std::endl;

		file << std::endl;
		file << std::endl;
		file << std::endl;

		file << "[LOG]" << std::endl;
		file << std::endl;

		for (std::string Log : Logs)
		{
			file << Log << std::endl;
		}

		file.close();
	}
};

