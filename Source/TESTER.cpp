#include <iostream>
#include "SebLogger.hpp"

int main()
{
	std::cout << "Test" << std::endl;
	SebLogger::CreateLogger("Test Logger");
}