#pragma once
#include "../../Common/inc/Hoochamacallit.h"

// Constants
#define DR_LOG_PATH     "/tmp/dataReader.log"
#define DR_LOG_LEN      256
#define TIMEOUT         5                   // DEBUG: CHANGE LATER
#define EXIT_DELAY      35                  // DEBUG: Check if this is right for closing the server
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
extern struct sembuf acquire_operation;
extern struct sembuf release_operation;
