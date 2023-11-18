# Seb Logger  
  
This is my attempt at writing a logger class that someone might actually use. I added serveral features that I think people would want and everything is obviously
is customisable. This logger includes colours for different serverites of log. Curerntly there are only 3 and they are listed below:  
  
```
Debug - green  
Warning - yellow  
Error - Red
```
## Current Output
This is what the output will look if you run the example.cpp:  
![image](https://github.com/SebastianS13/Logger/assets/50264212/dccbf6fa-5e58-494d-9027-d25841925d73)


# Usage  
  
To initialise the logger you need to initalise it as every other class you would. Below you can see examples of both:  
```
SebLogger logger;
```
  
It is important to note that all logs passed into the logger with printing disabled or enabled get stored into an array. To log something you need to pass a message and a severity enum. You can see examples for all 3 serveritise there are curerntly.  
```
Logger.Log("Hello!", Logger.Debug); // This prints out "[DEBUG] {message}
logger.Log("Hello!", logger.Warning); // This prints out "[DEBUG - WARNING] {message}
logger.Log("Hello!", logger.Error); // This prints out "[DEBUG - ERROR] {message}
```  

To export all logs to a file you need to call the export to file function at the end of the code. This should be done at the end of all the code not in the middle as if you call it in the middle then at the end because then any logs that were exported will be erased. To export you just need to add to the end of your code: 
```
logger.ExportToFile();
```

You can check out the exmaple.cpp in the src folder to see the code actually in use!

# Future Stuff

Here I just want to note some stuff that I will definatly add to the logger.
- adding time to each log event
- Add extra details to log output file like total runtime, etc.
