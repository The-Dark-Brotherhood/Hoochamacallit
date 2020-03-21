#include "../inc/DataCreator.h"

int main(int argc, char* argv)
{

  //set up the semaphore
  int semId = setUpLogSemaphore();
  //get the queue Id
  int qID = getQueueID();
  machineProcessingLoop(qID);

  //release the semaphore once operation is finished
  closeLogSemaphore(semId);
  return 0;
}


// FUNCTION      : getQueueID
// DESCRIPTION   : check for the existance of message queue
//
// PARAMETERS    : none
//
//
//  RETURNS       :   ID of the message queue,
//                    -1 if the queue does not exist
int getQueueID(void)
{
  int qID = -1;
  key_t msgKey = ftok(KEY_PATH, 'G');

  //Loop checking for existance of queue, sleeping 10 seconds if not found,
  //then searching again
  while((qID = msgget(msgKey,0)) < 0)
  {
    sleep(10);
  }

  return qID;
}

// FUNCTION      : sendMessage
// DESCRIPTION   : compile the message into message struct, send to message queue,
//                 call the function to write to log file.
//
// PARAMETERS    :
//	int status       -> the status of the machine
//  int machineID    -> the ID of the machine
//  long messageType -> type of message(always 0)
//  int msgQueueID   -> ID of the message queue where message will be sent
//
//  RETURNS       :   void
void sendMessage(int status, int machineID, long messageType, int msgQueueID)
{
  //put machine info into struct
  msgData message;
  message.msgType = messageType;
  message.clientId = machineID;
  message.msgStatus = status;
  //get size for msgsend()
  int size = sizeof(message) - sizeof(long);

  //send message to queue
  msgsnd(msgQueueID, (void*)&message, size, 0);

  //write to logfile:
  createLogMessage(machineID, status);
}

// FUNCTION      : machineProcessingLoop
// DESCRIPTION   : main processing loop for machine. Send message, write to log
//                 file, then wait 10-30 seconds, repeat. Exits until status 6 is
//                 generated
//
// PARAMETERS    : vint msgKey -> key of message queue
//
//  RETURNS      : void
void machineProcessingLoop(int msgQueueID)
{
  //get the process ID(to include in message and log)
  int pid = getpid();

  //send first message - ALL OKAY
  sendMessage(EVERYTHING_OKAY, pid, 1, msgQueueID);

  //seed the random number generator
  srand(time(0));

  //Loop ends when machine status 6 is generated
  bool running = true;
  while(running)
  {
    //sleep random amount of time
    sleep((rand() % 21)+10); //sleep between 10 & 30 seconds

    //generate random value between 0 & 6
    int machineStatus = ((rand()%7));
    //send the message to the message queue - logging called in sendMessage()
    sendMessage(machineStatus, pid, 1, msgQueueID);

    //Machine status = "Machine is Off-Line"
    if (machineStatus == 6)
    {
      running = false;
    }
  }
}
