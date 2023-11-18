#include "SebLogger.h"

int main()
{
	SebLogger Logger;

	Logger.Log("Example of a normal log!", Logger.Debug);
	Logger.Log("Example of a warning!", Logger.Warning);
	Logger.Log("Example of a big bad error!", Logger.Error);

	Logger.ExportToFile();
}
