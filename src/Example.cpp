#include <iostream>
#include <fstream>
#include <vector>
#include "SebLogger.h"

int main()
{
	SebLogger Logger(true);

	Logger.Log("Hello!", Logger.DEBUG);
	Logger.Log("Hello!", Logger.WARNING);
	Logger.Log("Hello!", Logger.ERROR);

	Logger.ExportToFile();
}