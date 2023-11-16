#include <iostream>
#include <fstream>
#include <vector> 

class Logger
{
public:

	Logger(bool EnablePrints) 
	{
		EnablePrinting = EnablePrints;
	}

	enum Severity {
		DEBUG = 1,
		WARNING = 2,
		ERROR = 3
	};

	void Log(std::string Message, Severity severity)
	{
		TotalLogEvents += 1;

		switch (severity) {
		case Severity::DEBUG:
			std::cout << "[DEBUG]				" << Message << std::endl;
			Logs.push_back("[DEBUG]				" + Message);
			return;
			break;
		case Severity::WARNING:
			std::cout << "[DEBUG - WARNING]		" << Message << std::endl;
			Logs.push_back("[DEBUG - WARNING]		" + Message);
			TotalWarnings += 1;
			break;
		case Severity::ERROR:
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
		std::string FileName = "Log.txt";
		std::ofstream file(FileName);

		file << "Total log events durring session: " << TotalLogEvents << std::endl;
		file << "Total warnings durring session: " << TotalWarnings << std::endl;
		file << "Total errors durring session: " << TotalErrors << std::endl;

		file << std::endl;
		file << std::endl;
		file << std::endl;

		for (std::string Log : Logs)
		{
			file << Log << std::endl;
		}

		file.close();
	}
private:
	int TotalLogEvents = 0;
	int TotalWarnings = 0;
	int TotalErrors = 0;

	bool EnablePrinting;

	std::vector<std::string> Logs;
};

int main()
{
	Logger logger(true);

	logger.Log("Hello!", logger.DEBUG);
	logger.Log("Hello!", logger.WARNING);
	logger.Log("Hello!", logger.ERROR);

	logger.ExportToFile();
}