#pragma once
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

#define LOG_FOLDER_PATH "/tmp/"
#define LOG_LEN         256

// Function Prototypes
void getTime(char* output);
void createFilePathIfNotExists();
void writeToLog(char* logMessage, char* path);
