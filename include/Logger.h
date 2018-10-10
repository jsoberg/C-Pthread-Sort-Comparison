/* Joshua Soberg */
 
#include <stdio.h>
#include <stdlib.h>

#ifndef LOGGER_H
#define LOGGER_H

// ==================== Function Declarations ====================

/* Prints message to a log file. */
static void LogMessage(const char* logLevel, char* sourceFileName, int lineNumber, char* message);

/* Prints debug message to logs. */
void LogDebug(char* sourceFileName, char* debugMessage);

/* Prints warning message to logs. */
void LogWarning(char* sourceFileName, int lineNumber, char* warningMessage);

/* Prints error message to stderr and logs. */
void LogError(char* sourceFileName, int lineNumber, char* errorMessage);

/* Prints error message to stderr and logs, then stops execution. */
void LogFatal(char* sourceFileName, int lineNumber, char* fatalMessage);

#endif
