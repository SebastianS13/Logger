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
		Error = 3,
		CriticalError = 4
	};

	void Log(std::string Message, Severity severity)
	{
		time_t s, val = 1;
		struct tm* curr_time;
		s = time(NULL); //This will store the time in seconds
		curr_time = localtime(&s); //get the current time using localtime()

		std::string TimeStamp = getCurrentTime(false);

		TotalLogEvents += 1;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		std::string Output = "";

		switch (severity) {
		case Severity::Debug:
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			Output = "[" + TimeStamp + "][DEBUG]				" + Message;
			break;
		case Severity::Warning:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			Output = "[" + TimeStamp + "][DEBUG - WARNING]		" + Message;
			TotalWarnings += 1;
			break;
		case Severity::Error:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			Output = "[" + TimeStamp + "][DEBUG - ERROR]			" + Message;
			TotalErrors += 1;
			break;
		case Severity::CriticalError:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			Output = "[" + TimeStamp + "][DEBUG] - CRITIAL]			" + Message;
			TotalErrors += 1;
			Logs.push_back(Output);
			SebLogger::ExportToFile();
			exit(-1);
			break;
		default:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			Output = "[" + TimeStamp + "][DEBUG - ERROR]			Passed serverity is incorrect!";
			TotalErrors += 1;
		}

		std::cout << Output << std::endl;
		Logs.push_back(Output);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}

	void ExportToFile()
	{
		std::string FileName = getCurrentTime(true) + ".log";
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

private:
	std::string getCurrentTime(bool FileName) {
		std::time_t now = std::time(nullptr);
		std::tm timeInfo = *std::localtime(&now);

		if (FileName)
		{
			std::ostringstream oss;
			oss << std::put_time(&timeInfo, "%H-%M");
			return oss.str();
		}

		std::ostringstream oss;
		oss << std::put_time(&timeInfo, "%H:%M");
		return oss.str();
	}
};

