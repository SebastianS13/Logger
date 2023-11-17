#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <chrono>
#include <string>

std::vector<std::string> Logs;

int TotalLogEvents = 0;
int TotalWarnings = 0;
int TotalErrors = 0;

std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point end;

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
			return;
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
	}

	void ExportToFile()
	{
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> duration = end - start;
		double seconds = duration.count();

		std::string FileName = "Log" + std::to_string(seconds) + ".txt";
		std::ofstream file(FileName);

		file << "[INFORMATION]" << std::endl;
		file << std::endl;

		file << "Total log events durring session: " << TotalLogEvents << std::endl;
		file << "Total warnings durring session: " << TotalWarnings << std::endl;
		file << "Total errors durring session: " << TotalErrors << std::endl;
		file << "Runtime in seconds: " << seconds << std::endl;

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

