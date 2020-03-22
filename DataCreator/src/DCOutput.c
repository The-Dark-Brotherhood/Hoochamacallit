/*
*  FILE          : DCOutput.c
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel, Michael Gordon
*  FIRST VERSION : 2020-03-5
*  DESCRIPTION   : Contains the functionality for logging for the dataCreator
*                  Every time a message is sent, the datacreator will write to
*                  log file. Because there may be multiple processes writing to the
*                  file, a semaphore is used for acccess to the file. The semaphore
*                  is created by the dataReader.
*/

#include "../inc/DataCreator.h"

// DEBUG: Should this be here?
struct sembuf acquire_operation = { 0, -1, SEM_UNDO };
struct sembuf release_operation = { 0, 1, SEM_UNDO };

unsigned short init_values[1] = { 1 };

// FUNCTION      : createLogMessage
// DESCRIPTION   : generates output for the logfile, writes to log file
//                 using a semaphore. Calls getTime() in order to get current
//                 time for log file.
//
// PARAMETERS    : int pid -> process ID
//                 int status -> status of machine
//
//  RETURNS      : void
void createLogMessage(int pid, int status)
{
  // Get the semaphore ID -> the dataReader creates the semaphore on startup
  int semid = semget (KEY, 1, IPC_CREAT | 0777);

  // Get the description of the status - values 0-6
  char description[DC_LOG_LEN] = "";
  switch(status)
  {
    case 0:
      strcpy(description, "Everything is OKAY");
      break;
    case 1:
      strcpy(description, "Hydraulic Pressure Failure");
      break;
    case 2:
      strcpy(description, "Safety Button Failure");
      break;
    case 3:
      strcpy(description, "No Raw Material in the Process");
      break;
    case 4:
      strcpy(description, "Operating Temperature Out of Range");
      break;
    case 5:
      strcpy(description, "Operator Error");
      break;
    case 6:
      strcpy(description, "Machine is Off-line");
      break;
    default:
      // There should only be a value between 0-6
      strcpy(description, "ERROR READING STATUS");
      break;
  }

  //Check semaphore to see if can access critical region
  if (semop (semid, &acquire_operation, 1) == -1)
	{
	   //Critical ERROR
	}
  //Start of critical region

  // Write to logfile
  sprintf(description, "DC [%d] - MSG SENT - Status %d (%s)\n", pid, status, description);
  writeToLog(description, DC_LOG_PATH);

  //End of critical region
  if (semop (semid, &release_operation, 1) == -1)
  {
    //Critical ERROR
  }
}

// FUNCTION      : setUpLogSemaphore
// DESCRIPTION   : this function creates a semaphore that is used by the DCs
//                 for accessing the log file.
//
// PARAMETERS    : none
//
//  RETURNS      : int - semaphore Id
int setUpLogSemaphore(void)
{
  int semid = semget (KEY, 1, IPC_CREAT | 0777);
  if (semctl (semid, 0, SETALL, init_values) == -1)
  {
    printf("error\n");
  }
  return semid;
}

// FUNCTION      : closeLogSemaphore
// DESCRIPTION   : this function closes the semaphore being used by the DC
//
// PARAMETERS    : int semId - semaphore Id
//
//  RETURNS      : none
void closeLogSemaphore(int semId)
{
  semctl (semId, 0, IPC_RMID, 0);
}
