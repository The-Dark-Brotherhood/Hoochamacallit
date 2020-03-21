#pragma once
#include "../../Common/inc/Hoochamacallit.h"

// Constants -- Do you really look at all the files, Sean? 
#define DCRRP_LOG_PATH  "/tmp/dataCorruptor.log"
#define DCRRP_LOG_LEN   256

// Function Prototypes
void writeDCKillToLog(int wodAction, int success, int id, int DCNum);
MasterList* attachToSharedMemory(int shmID);
void corrupterProcessing(MasterList* shList);
int spinTheWheelOfDestruction(void);
int killTheThing(MasterList* list, int index);
int executeAction(MasterList* list, int action);
void writeMsgQueueDeleteToLog(int wodAction, int success);
void writeDidNothingToLog(int wodAction);
void writeMsgQueueGoneToLog(void);
