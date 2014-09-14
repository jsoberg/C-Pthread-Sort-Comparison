/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */
 
#include <stdio.h>
#include <stdlib.h>
#include "Logger.h"

// Name of defualt log file.
static char* LOG_FILE_NAME = "debugLog.log";
// Debug log message.
static char* DEBUG = "Debug";
// Warning log message.
static char* WARNING = "Warning";
// Error log message.
static char* ERROR = "Error";
// Fatal log message.
static char* FATAL = "Fatal";

/* Prints message to a log file. 
 * @param logLevel - The log level of this message (DEBUG, WARNING, ERROR, FATAL)
 * @param sourceFileName - The name of the source file this log is coming from. 
 * @param lineNumber - The line number that this message is being logged from. 
 * @param message - The log message to be printed. */
static void LogMessage(const char* logLevel, char* sourceFileName, int lineNumber, char* message) 
{
	// Opening file to append.
	FILE *logFile = fopen(LOG_FILE_NAME, "a");
	
	if (sourceFileName == NULL && lineNumber == 0) {
		// Only log message.
		fprintf(logFile, "%s, %s - %s : '%s'\n", __DATE__, __TIME__, logLevel, message);
	} else if (sourceFileName != NULL && lineNumber == 0) {
		// Log only file name.
		fprintf(logFile, "%s, %s - %s (File %s): '%s'\n", __DATE__, __TIME__, logLevel, sourceFileName, message);
	} else {
		// Log file name and line number.
		fprintf(logFile, "%s, %s - %s (File %s Line %d): '%s'\n", __DATE__, __TIME__, logLevel, sourceFileName, lineNumber, message);
	}
	
	fclose(logFile);
}

/* Prints debug message to logs. */
void LogDebug(char* sourceFileName, char* debugMessage)
{
	// Line number not necessary for debug logs.
	LogMessage(DEBUG, sourceFileName, 0, debugMessage);
}

/* Prints warning message to logs. */
void LogWarning(char* sourceFileName, int lineNumber, char* warningMessage)
{
	LogMessage(WARNING, sourceFileName, lineNumber, warningMessage);
}

/* Prints error message to stderr and logs. */
void LogError(char* sourceFileName, int lineNumber, char* errorMessage)
{
	// Printing error message to stderr.
	fprintf(stderr, errorMessage);
	fflush( stderr );
	
	// Logging error message to log.
	LogMessage(ERROR, sourceFileName, lineNumber, errorMessage);
}

/* Prints error message to stderr and logs, then stops execution. */
void LogFatal(char* sourceFileName, int lineNumber, char* fatalMessage)
{
	// Printing fatal message to stderr.
	fprintf(stderr, fatalMessage);
	fflush( stderr );
	
	// Logging error message to log.
	LogMessage(FATAL, sourceFileName, lineNumber, fatalMessage);
	
	// Stopping execution with an error return code.
	exit(1);
}
