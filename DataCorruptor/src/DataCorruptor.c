/*
*  FILE          : DataCorruptor.c
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel, Michael Gordon
*  FIRST VERSION : 2020-03-16
*  DESCRIPTION   : Contains the functionality for the DataCorruptor - the application
*                  responsible for giving the DataReader and DataCreator a really hard time
*                  The DataCorruptor attaches to the shared memory and randomly selects an
*                  action from the WHEEL OF DEATH. Possible actions include -> killing a DC
*                  process, killing the message queue, and doing nothing. When the Data corruptor
*                  detects that the message queue is gone, it will exit.
*/

#include "../inc/DataCorruptor.h"


int main(int argc, char* argv)
{
  //to get the key
  key_t shmKey = ftok(SHMKEY_PATH, SHM_KEYID);
  int shmID = 0;
  for(int i = 0; i < MAX_SHMEM_TRIES; i++)
  {
    // Grabs the shared memory ID
    shmID = shmget(shmKey, sizeof(MasterList), 0);
    if(shmID != -1)
    {
      break;

    }
    sleep(SHMEM_TRY_SLEEP);
  }

  // Share mem not found after number tries
  if(shmID == -1)
  {
    return 1;
  }

  MasterList* shList = NULL;
  if((shList = attachToSharedMemory(shmID)) == NULL)
  {
    //unable to attach to shared memory if null
    return 2;
  }
  corrupterProcessing(shList, shmKey);

  return 0;
}

// FUNCTION      : attachToSharedMemory
// DESCRIPTION   : attach to the shared memory with the passed shared
//                 memory ID
//
// PARAMETERS    :
//    int shmID -> id of the shared memory
//
// RETURNS       :
//    pointer to share memory master list
//    NULL if not found
MasterList* attachToSharedMemory(int shmID)
{
  MasterList* shList = (MasterList*)shmat (shmID, NULL, 0); // Grabs the shared memory

  //returns null if unable to attach to shared memory

  return shList;
}

// FUNCTION      : corrupterProcessing
// DESCRIPTION   : Main processing loop of the Data Corrupter.
//                 Performs 4 actions:
//                   1 -> sleep 10-30 seconds
//                   2 -> check for existance of message queue
//                   3 -> select random action from WOD
//                   4 -> Execute action
//                Function exits once it detects the message queue is deleted;
//
// PARAMETERS    :
//    MasterList* shList : Pointer to the shared memory master list
//    key_t shmKey       : key for shared memory. Used to check existance of shared memory
//
// RETURNS       : none
void corrupterProcessing(MasterList* shList, key_t shmKey)
{
  int running = 1;
  while(running)
  {
    //Step 1: sleep for 10-30 seconds
    srand(time(0));
    sleep((rand() % (MAX_SLEEP - 9))+ MIN_SLEEP);
    //Step 2: Check for existance of message queue
    int shmID = -1;
    //reader closes message queue and shared memory when shutting down
    shmID = shmget(shmKey, sizeof(MasterList), 0);
    if(shmID < 0)
    {
      //write to log
      writeMsgQueueGoneToLog();
      break;
    }
    //Step 3: Select and action from WOD
    int randomAction = spinTheWheelOfDestruction();
    //Step 4: Execute Action

    //get a return value to know if should exit program
    if(executeAction(shList, randomAction))
    {
      running = 0;
    }
  }
}

// FUNCTION      : spinTheWheelOfDestruction
// DESCRIPTION   : generates a random value between 0 and 20.
//                 value used by DX to perform a random action
//
// PARAMETERS    : none
//
// RETURNS       : int -> value from the wheel
int spinTheWheelOfDestruction(void)
{
  //Get a value between 0-20
  int randomAction = ((rand() % (NUM_WOD_ACTIONS + 1)));
  return randomAction;
}

// FUNCTION      : killTheThing
// DESCRIPTION   : Kill the DC process indicated by the index
//
// PARAMETERS    :
//    MasterList* list : Pointer to the shared memory master list
//  int index        : Index of the client in the master list
//
// RETURNS       :
//    Returns the client pid if the process was killed, -1 if the client does not exist in the list
//    0 if the process was not killed (already was closed)
int killTheThing(MasterList* list, int index)
{
  int retCode = 0;
  if(index > (list->numberOfDCs) - 1)
  {
    retCode = -1;
    return retCode;
    //client doesn't exist
  }
  int pidToKill = list->dc[index].dcProcessID;
    retCode = kill(pidToKill, SIGHUP);
    if(retCode == 0)
    {
      retCode = pidToKill;
    }
    else
    {
      retCode = -2;
    }

  return retCode;
}

// FUNCTION      : executeAction
// DESCRIPTION   : Executes action based on the wheel of destruction number
//                 passed in. Logging functions called within this function
//
// PARAMETERS    :
//    MasterList* list : Pointer to the shared memory master list
//    int action        : WOD action to perform
//
// RETURNS       :
//    Returns 1 if corruptor should quit - msg queue deleted
//    Return 0 if corruptor should keep running
int executeAction(MasterList* list, int action)
{
  int actionCode = 0;
  int dcNumber = 0;
  int success = 0;
  if(action == 0 || action == 8 || action == 19)
  {
    //do Nothing
    writeDidNothingToLog(action);
  }
  else if(action == 10 || action == 17)
  {
    //delete message queue, get success to see if successful in deleting queue
    if(msgctl (list->msgQueueID, IPC_RMID, (struct msqid_ds*)NULL) == -1)
    {
      //failed to delete
      success = -1;
    }
    else
    {
      //successfully deleted the message queue
      success = 1;
    }
    writeMsgQueueDeleteToLog(action, success);
    //return 1 to signal to close corrupter
    return 1;
  }
  else
  {
    switch(action)
    {
      case 1: case 4: case 11:
      //kill 1st
        dcNumber = 1;
        break;
      case 2: case 5: case 15:
      //kill 3rd
        dcNumber = 3;
        break;
      case 3:case 6: case 13:
      //kill 2nd
        dcNumber = 2;
        break;
      case 7:
      //kill 4th
        dcNumber = 4;
        break;
      case 9:
      //kill 5th
        dcNumber = 5;
        break;
      case 12:
      //kill 6
        dcNumber = 6;
        break;
      case 14:
      //kill 7
        dcNumber = 7;
        break;
      case 16:
      //kill 8
        dcNumber = 8;
        break;
      case 18:
      //kill 9
        dcNumber = 9;
        break;
      case 20:
      //kill 10
        dcNumber = 10;
        break;
    }
    int retCode = killTheThing(list,dcNumber - 1);//-1 to match zero based index
    int successfulKill = 0;
    if(retCode == -1)
    {
      //failed to delete
      successfulKill = 0;
    }
    else if(retCode == -2)
    {
      successfulKill = -1;
    }
    else
    {
      //succeeded
      successfulKill = 1;
      //retCode holds pid
    }
    //pass wod action #, pid(in retcode), and successfulkill status, dcNumber
    writeDCKillToLog(action, successfulKill, retCode, dcNumber);
  }
  return 0;
}
