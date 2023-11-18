#include "SebLogger.h"

int main()
{
	SebLogger Logger;

	for (int i = 1; i <= 1000000; i++)
	{
		Logger.Log(std::to_string(i), Logger.Debug);
	}

	//Logger.Log("Example of a normal log!", Logger.Debug);
	//Logger.Log("Example of a warning!", Logger.Warning);
	//Logger.Log("Example of a big bad error!", Logger.Error);

	system("pause");

	Logger.ExportToFile();
}