#pragma once
#include "../../Common/inc/Hoochamacallit.h"

// Constants
#define DC_LOG_PATH   "/tmp/dataCreator.log"
#define DC_LOG_LEN    256

// Function Prototypes
void sendMessage(int status, int machineID, long messageType, int msgQueueID);
void machineProcessingLoop(int msgQueueID);
int setUpLogSemaphore(void);
void closeLogSemaphore(int semId);
int getQueueID(void);

// Data Creator Output
void createLogMessage(int pid, int status);

//the following is defined in DataCreatorLogging.h
extern struct sembuf acquire_operation;
extern struct sembuf release_operation;
