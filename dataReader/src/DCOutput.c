#include "../inc/dataReader.h"

void debugLog(const char* logMessage)
{
  writeToLog((char*)logMessage, DR_LOG_PATH);
}

void createLogMessage(DCInfo node, int logType, int index, int msgStatus)
{
  char logMessage[DR_LOG_LEN] = "";

  switch (logType)
  {
		case NEW_CLIENT:
			sprintf(logMessage,"DC-%02d [%d] added to the master list – NEW DC – Status 0 (Everything is OKAY)", index, node.dcProcessID);
			break;
    case MESSAGE:
      sprintf(logMessage, "DC-%02d [%d] updated in the master list – MSG RECEIVED – Status %d (AAAAA)\n", index, node.dcProcessID, msgStatus);
      break;
    case NON_RESPONSIVE:
      sprintf(logMessage, "DC-%02d [%d] removed from master list – NON-RESPONSIVE\n", index, node.dcProcessID);
      break;
    case GO_OFFLINE:
      sprintf(logMessage, "DC-%02d [%d] has gone OFFLINE – removing from master-list\n", index, node.dcProcessID);
      break;
  }
  writeToLog(logMessage, DR_LOG_PATH);
}
