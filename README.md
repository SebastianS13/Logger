# Logger  
  
This is my attempt at writing a logger class that someone might actually use. I added serveral features that I think people would want and everything is obviously
everything is customisable.  
  
# Usage  
  
To initialise the logger you need to initalise it as every other class you would but you also have to pass a boolean which controls if logs are printed. Below you can see examples of both:  
`Logger logger(true);` - Printing is enabled  
`Logger logger(false);` - Printing is disabled so no logs are printed  
  
It is important to note that all logs passed into the logger with printing disabled or enabled get stored into an array. This array cannot be accessed or cleared at the moment but that may be added later.  
  
To log something you need to pass a message and a severity enum. You can see examples for all 3 serveritise there are curerntly.  
`logger.Log("Hello!", logger.DEBUG);` - This prints out "[DEBUG] {message}"  
`logger.Log("Hello!", logger.WARNING);` - This prints out "[DEBUG - WARNING] {message}"  
`logger.Log("Hello!", logger.ERROR);` - This prints out "[DEBUG - ERROR] {message}"  

To export all logs to a file you need to call the export to file function at the end of the code. This should be done at the end of all the code not in the middle as if you call it in the middle then at the end because then any logs that were exported will be erased. To export you just need to add to the end of your code: `logger.ExportToFile();`
