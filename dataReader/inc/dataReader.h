/*
*  FILE          : dataReader.h
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel & Michael Gordon
*  FIRST VERSION : 2020-03-21
*  DESCRIPTION   : Shared constants, includes, and structures for the DataReader program
*/

#pragma once
#include "../../Common/inc/Hoochamacallit.h"

// Constants
#define DR_LOG_PATH     "/tmp/dataReader.log"
#define DR_LOG_LEN      256
#define TIMEOUT         15
#define EXIT_DELAY      35
#define CLOSE_DELAY     EXIT_DELAY + 1      // Adds an extra second for accomodate process time
#define MSG_DELAY       1.5

// For Data Reader Output
#define NEW_CLIENT        0
#define NON_RESPONSIVE    1
#define MESSAGE           2
#define GO_OFFLINE        3

// Function Prototypes
void checkInactivity(MasterList* list);
void deleteNode(MasterList* list, int index);
int insertNodeToList(MasterList* list, DCInfo client);
int findClient(MasterList* list, pid_t id);

// Data Reader Output
void createLogMessage(DCInfo node, int logType, int index, int msgStatus);
void debugLog(const char* logMessage);

// Semaphores
DCInfo createClient(pid_t id);
int setUpLogSemaphore(void);
void closeLogSemaphore(int semId);

extern struct sembuf acquire_operation;
extern struct sembuf release_operation;
