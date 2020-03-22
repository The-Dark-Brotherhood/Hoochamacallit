/*
*  FILE          : DataCreator.h
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel, Michael Gordon
*  FIRST VERSION : 2020-03-5
*  DESCRIPTION   : Contains the include for the common include file, constant define,
*                  and function prototypes
*/
#pragma once
#include "../../Common/inc/Hoochamacallit.h"

// Constants
#define DC_LOG_PATH   "/tmp/dataCreator.log"
#define DC_LOG_LEN    256
#define SLEEP_TIME    10
#define MACHINE_OFF   6
#define MAX_STATUSES  6

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
