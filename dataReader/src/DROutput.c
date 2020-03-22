/*
*  FILE          : DCOutput.c
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel & Michael Gordon
*  FIRST VERSION : 2020-03-20
*  DESCRIPTION   : Contains all the log messages for the DataReader
*/

#include "../inc/dataReader.h"

// Message Status -->> Message
char messages[NUM_MSG][MSG_LEN] =
{
  {MSG_0}, {MSG_1}, {MSG_2}, {MSG_3}, {MSG_4}, {MSG_5}, {MSG_6}, {MSG_ERROR}
};

// FUNCTION      : debugLog
// DESCRIPTION   : Writes the string in the log file
//
// PARAMETERS    :
//  const char* logMessage: Log message
//
//  RETURNS      :
//    void
void debugLog(const char* logMessage)
{
  writeToLog((char*)logMessage, DR_LOG_PATH);
}

// FUNCTION      : createLogMessage
// DESCRIPTION   : Writes the log message based with the contents from the parameters
//                 indicated by logType
//
// PARAMETERS    :
//   DCInfo client : Client of the MasterList
//   int logType   : Message that is going to be written
//   int Index     : Index of the client in the MasterList
//   int msgStatus : Message recevied from the client
//
//  RETURNS      :
//   void
void createLogMessage(DCInfo client, int logType, int index, int msgStatus)
{
  char logMessage[DR_LOG_LEN] = "";

  switch (logType)
  {
		case NEW_CLIENT:
			sprintf(logMessage,"DC-%02d [%d] added to the master list – NEW DC – Status 0 (Everything is OKAY)\n", index + 1, client.dcProcessID);
			break;
    case MESSAGE:
      sprintf(logMessage, "DC-%02d [%d] updated in the master list – MSG RECEIVED – Status %d (%s)\n", index + 1, client.dcProcessID, msgStatus, messages[msgStatus]);
      break;
    case NON_RESPONSIVE:
      sprintf(logMessage, "DC-%02d [%d] removed from master list – NON-RESPONSIVE\n", index + 1, client.dcProcessID);
      break;
    case GO_OFFLINE:
      sprintf(logMessage, "DC-%02d [%d] has gone OFFLINE – removing from master-list\n", index + 1, client.dcProcessID);
      break;
  }
  writeToLog(logMessage, DR_LOG_PATH);
}
