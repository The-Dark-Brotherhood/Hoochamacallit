/*
*  FILE          : dataReader.c
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel & Michael Gordon
*  FIRST VERSION : 2020-03-21
*  DESCRIPTION   : DataReader Application, The Server of the Hoochamacallit system
*                  Creates the semaphores to the client apps, creates the message queue
*                  and the shared memory section
*/

#include "../inc/dataReader.h"


struct sembuf acquire_operation = { 0, -1, SEM_UNDO };
struct sembuf release_operation = { 0, 1, SEM_UNDO };
unsigned short init_values[1] = { 1 };

int main(int argc, char const *argv[])
{
  int semId = setUpLogSemaphore();

  // MESSAGE QUEUE;
  // Generate key
  key_t msgKey = ftok(KEY_PATH, 'G');
  int msgID = 0;

  if(msgKey == ID_ERROR)
  {
    debugLog("ERROR: Unable to generate a key for message queue\n");
    return ID_ERROR;
  }

  // Creates or Grab message queue
  msgID = msgget(msgKey, 0);
  if(msgID == -1)
  {
    msgID = msgget(msgKey, (IPC_CREAT | 0660));
    if(msgID == -1)
    {
      debugLog(strerror(errno));
      return errno;
    }
  }

  // MASTER LIST;
  // Generattes key
  key_t shmKey = ftok(SHMKEY_PATH, SHM_KEYID);
  int shmID = 0;
  if(shmKey == ID_ERROR)
  {
    debugLog("ERROR: Unable to generate a key for shared memory\n");
    return ID_ERROR;
  }

  // Creates or Grabs shared memory
  MasterList* shList = NULL;
  shmID = shmget(shmKey, sizeof(MasterList), 0);
  if(shmID == -1)
  {
    shmID = shmget(shmKey, sizeof(MasterList), (IPC_CREAT | 0660));
    if(shmID == -1)
    {
      debugLog(strerror(errno));
      return errno;
    }
  }

  //--> Listening loop
  shList = (MasterList*)shmat (shmID, NULL, 0);       // Grabs the shared memory and
  shList->msgQueueID = msgID;                         // Assign the message queue ID

  // Wait for clients to start
  sleep(TIMEOUT);

  msgData msg;
  int msgSize = sizeof(msgData) - sizeof(long);
  int retcode = 0;

  time_t startTime = time(NULL); // Listen for messages loop
  while((int)difftime(time(NULL), startTime) < CLOSE_DELAY)
  {
    // Process messages if received AND if it is able to add client or it already exists in shList
    if(msgrcv(msgID, &msg, msgSize, 0, IPC_NOWAIT) != -1 &&
      (retcode = insertNodeToList(shList, createClient(msg.clientId))))
    {
      // I dont error check findClient because the check above already guarantees
      // that a client with that Id exists
      checkInactivity(shList);
      int currentClient = findClient(shList, msg.clientId);

      if(msg.msgStatus == EXIT_CODE)        // Remove client
      {
        createLogMessage(shList->dc[currentClient], GO_OFFLINE, currentClient, 0);
        deleteNode(shList, currentClient);
      }
      else if(retcode == 2)               // Log message
      {
        createLogMessage(shList->dc[currentClient], MESSAGE, currentClient, msg.msgStatus);
      }

      // Delay and reset time since last message
      sleep(MSG_DELAY);
      startTime = time(NULL);
    }
  }

  // Clean up and exit
  debugLog("All DCs have gone offline or terminated – DR TERMINATING\n");
  msgctl (msgID, IPC_RMID, (struct msqid_ds*)NULL);
  shmdt(shList);
  shmctl(shmID, IPC_RMID, 0);
  closeLogSemaphore(semId);

  return 0;
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
    debugLog("Error setting up the Semephore\n");
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
  semctl(semId, 0, IPC_RMID, 0);
}
