# Seb Logger  
  
This is my attempt at writing a logger class that someone might actually use. I added serveral features that I think people would want and everything is obviously
is customisable. This logger includes colours for different serverites of log. They are listed below and what they do:
  
```
Debug - Greem colour
Warning - Yellow colour
Error - Red Colour
CriticalError - Red Colour, Extra Indent, Stops execution, Exports logs to file
```
## Current Output
This is what the output will look if you run the example.cpp:  
![image](https://github.com/SebastianS13/Logger/assets/50264212/0e272380-2685-483a-8d17-08fc7491af8f)


# Usage  
  
To initialise the logger you need to initalise it as every other class you would but you also have to pass a TimeFormat which is a string. Below you can see an example where I use the %H:%M which means it will use HOURS : MINUTES as the format:  
```
SebLogger logger("%H:%M");
```
  
It is important to note that all logs passed into the logger get stored into an array, there is 1 array that all logger instances pass their logs to. To log something you need to pass a message and a severity. You can see examples for all 3 serveritise there are curerntly.  
```
Logger.Log("Hello!", Logger.Debug); // This prints out "[DEBUG] {message}"
logger.Log("Hello!", logger.Warning); // This prints out "[DEBUG - WARNING] {message}"
logger.Log("Hello!", logger.Error); // This prints out "[DEBUG - ERROR] {message}"
```  

To export all logs to a file you need to call the export to file function at the end of the code. This should be done at the end of all the code not in the middle as if you call it in the middle then at the end, any logs that were exported will be erased. To export you just need to add to the end of your code: 
```
logger.ExportToFile();
```
The exporting to file function can save at about 1 million logs per second, although this is amazing I am planning on splitting output files into a maximum of 100,000 logs to make smaller files and make the potetially even faster!

You can check out the exmaple.cpp in the src folder to see the code actually in use!
