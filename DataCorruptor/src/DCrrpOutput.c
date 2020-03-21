#include "../inc/DataCorruptor.h"


// FUNCTION      : writeDCKillToLog
// DESCRIPTION   : writes to the log file - when deleting a data creator
//
// PARAMETERS    :
//    int wodAction -> wheel of destruction action
//    int success   -> if the DX was successful in deleting the DC process
//    int id        -> Process ID of the data creator
//
// RETURNS       : none
void writeDCKillToLog(int wodAction, int success, int id, int DCNum)
{
  char logMessage[DCRRP_LOG_LEN] = "";

  if(success)
  {
    sprintf(logMessage, "WOD Action %d - DC-%02d [%d] TERMINATED\n", wodAction, DCNum, id);
  }
  else
  {
    sprintf(logMessage, "WOD Action %d - DC-%02d [%d] FAILED - Data Creator with that PID does not exist\n", wodAction, DCNum, id);
  }

  // Write to log file
  writeToLog(logMessage, DCRRP_LOG_PATH);
}

// FUNCTION      : writeMsgQueueDeleteToLog
// DESCRIPTION   : writes to the log file - when deleting the message queue
//
// PARAMETERS    :
//    int wodAction -> wheel of destruction action
//    int success   -> if the DX was successful in deleting the DC process
//
// RETURNS       : none
void writeMsgQueueDeleteToLog(int wodAction, int success)
{
  char logMessage[DCRRP_LOG_LEN] = "";

  sprintf(logMessage, "WOD Action %d - Delete the Message Queue\n", wodAction);
  if(success)
  {
    strcat(logMessage, "DX deleted the msgQ – the DR/DCs can’t talk anymore - exiting\n");
  }
  else
  {
    strcat(logMessage, "DX unable to delete the msgQ – assuming doesn't exist any more - exiting\n");
  }

  // Write to log file
  writeToLog(logMessage, DCRRP_LOG_PATH);
}

// FUNCTION      : writeDidNothingToLog
// DESCRIPTION   : writes to the log file - when doing nothing
//
// PARAMETERS    :
//    int wodAction -> wheel of destruction action
//
// RETURNS       : none
void writeDidNothingToLog(int wodAction)
{
  char logMessage[DCRRP_LOG_LEN] = "";
  sprintf(logMessage, "WOD Action %d - Did Nothing\n", wodAction);

  // Write to log file
  writeToLog(logMessage, DCRRP_LOG_PATH);
}

// FUNCTION      : writeMsgQueueGoneToLog
// DESCRIPTION   : writes to the log file - when DX detected that message queue is gone
//
// PARAMETERS    : none
//
// RETURNS       : none
void writeMsgQueueGoneToLog(void)
{
  char logMessage[DCRRP_LOG_LEN] = "";
  sprintf(logMessage, "DX detected that msQ is gone - assuming DR/DCs done\n");

  // Write to log file
  writeToLog(logMessage, DCRRP_LOG_PATH);
}
