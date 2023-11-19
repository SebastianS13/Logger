#include "SebLogger.h"

std::vector<std::string> Logs;
int TotalLogEvents = 0;
int TotalWarnings = 0;
int TotalErrors = 0;

const char* CurrentTimeFormat;

std::string getCurrentTime(bool FileName)
{
	std::time_t now = std::time(nullptr);
	std::tm timeInfo = *std::localtime(&now);

	if (FileName)
	{
		std::ostringstream oss;
		oss << std::put_time(&timeInfo, "%H-%M");
		return oss.str();
	}

	std::ostringstream oss;
	oss << std::put_time(&timeInfo, CurrentTimeFormat);
	return oss.str();
}

std::string StartTime = getCurrentTime(false);
std::string EndTime;

void SebLogger::Log(std::string Message, Severity severity)
{
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
		std::cout << "[" + TimeStamp + "][DEBUG] - CRITIAL]			" + Message << std::endl;
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

void SebLogger::ExportToFile()
{
	std::string FileName = getCurrentTime(true) + ".log";
	std::ofstream file(FileName);

	if (!file.is_open())
	{
		SebLogger::Log("couldnt create log output file!", SebLogger::Severity::Error);
	}

	EndTime = getCurrentTime(false);

	file << "[INFORMATION]\n\n";
	file << "Total log events during session: " << TotalLogEvents << '\n';
	file << "Total warnings during session: " << TotalWarnings << '\n';
	file << "Total errors during session: " << TotalErrors << "\n\n";
	file << "Start time: " << StartTime << '\n';
	file << "End time: " << EndTime << "\n\n\n";
	file << "[LOG]\n\n";

	for (const std::string& Log : Logs) {
		file << Log << '\n';
	}

	file.flush();
	file.close();
}

void SebLogger::ChangeTimeFormat(TimeFormat NewFormat)
{
	std::string StringNewFormat = "";

	switch (NewFormat)
	{
	case SebLogger::HOURS_MINUTES:
		StringNewFormat = "%H:%M";
		break;
	case SebLogger::MINUTES_HOURS:
		StringNewFormat = "%M:%H";
		break;
	case SebLogger::HOURS:
		StringNewFormat = "%H";
		break;
	case SebLogger::MINUTES:
		StringNewFormat = "%M";
		break;
	default:
		StringNewFormat = "%H:%M";
		break;
	}

	const char* CharNewFormat = StringNewFormat.c_str();
	CurrentTimeFormat = CharNewFormat;
}