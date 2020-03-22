/*
*  FILE          : DataCorruptor.h
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel, Michael Gordon
*  FIRST VERSION : 2020-03-16
*  DESCRIPTION   : Contains the include for the common include file, constant defines
*                  and function prototypes
*/

#pragma once
#include "../../Common/inc/Hoochamacallit.h"

// Constants -- Do you really look at all the files, Sean?
#define DCRRP_LOG_PATH  "/tmp/dataCorruptor.log"
#define DCRRP_LOG_LEN   256
#define MAX_SHMEM_TRIES 100
#define SHMEM_TRY_SLEEP 10
#define NUM_WOD_ACTIONS 20

// Function Prototypes
void writeDCKillToLog(int wodAction, int success, int id, int DCNum);
MasterList* attachToSharedMemory(int shmID);
void corrupterProcessing(MasterList* shList, key_t shmKey);
int spinTheWheelOfDestruction(void);
int killTheThing(MasterList* list, int index);
int executeAction(MasterList* list, int action);
void writeMsgQueueDeleteToLog(int wodAction, int success);
void writeDidNothingToLog(int wodAction);
void writeMsgQueueGoneToLog(void);
