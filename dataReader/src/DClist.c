/*
*  FILE          : DClist.c
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel & Michael Gordon
*  FIRST VERSION : 2020-03-20
*  DESCRIPTION   : Contains the function related to managing the client list
*                  in the MasterList
*/
#include "../inc/dataReader.h"

// FUNCTION      : createClient
// DESCRIPTION   : Creates client with its process ID
//
// PARAMETERS    :
//   pid_t  id : Process Id of the client
//
//  RETURNS      :
//   Return the client
DCInfo createClient(pid_t id)
{
  DCInfo client = {.dcProcessID = id, .lastTimeHeardFrom = time(NULL)};
  return client;
}

// FUNCTION      : insertNodeToList
// DESCRIPTION   : Insert a client shared Master List or it resets the lastTimeHeardFrom of
//								 existing client timer
//
// PARAMETERS    :
//	MasterList* list : List containing information about all server clients
//  DCInfo    client : Client that is going to be inserted
//
// RETURNS       :
//	Returns 1 if the client is added, 2 if the client already exists, and
//  -1 if the list is full
int insertNodeToList(MasterList* list, DCInfo client)
{
  // Check if the client is already on the list
  for(int counter = 0; counter < list->numberOfDCs; counter++)
  {
    if(client.dcProcessID == list->dc[counter].dcProcessID)
    {
      list->dc[counter].lastTimeHeardFrom = time(NULL); // Updates timer
      return 2;
    }
  }

  // Check if the server is full
  if(list->numberOfDCs == MAX_DC_ROLES)
  {
    return -1;
  }

  // Else, add new client
  list->dc[list->numberOfDCs] = client;
  createLogMessage(client, NEW_CLIENT, list->numberOfDCs, 0);
  list->numberOfDCs++;

  return 1;
}

// FUNCTION      : findClient
// DESCRIPTION   : Finds the client index based on its pid
//
// PARAMETERS    :
//	MasterList* list : List containing information about all server clients
//  pid_t       id   : Process ID of the client
//
// RETURNS       :
// Return the index of the client in the masterlist
int findClient(MasterList* list, pid_t id)
{
  for(int counter = 0; counter < list->numberOfDCs; counter++)
  {
    if(list->dc[counter].dcProcessID == id)
    {
      return counter;
    }
  }
  return -1;
}

// FUNCTION      : checkInactivity
// DESCRIPTION   : Deletes an innactivity client from the server list
//
// PARAMETERS    :
//	MasterList* list : Pointer to the shared memory master list
//
// RETURNS       :
//	void
void checkInactivity(MasterList* list)
{
  int counter = 0;

	while (counter < list->numberOfDCs)
	{
		if((int)difftime(time(NULL), list->dc[counter].lastTimeHeardFrom) >= EXIT_DELAY)
		{
			// Replace the deleted object with last element
      int lastIndex = list->numberOfDCs - 1;
      if(lastIndex != counter)
      {
        list->dc[counter] = list->dc[lastIndex];
      }

      createLogMessage(list->dc[counter], NON_RESPONSIVE, counter, 0);
      list->numberOfDCs--;
		}
    else
    {
      counter++;
    }
	}
}



// FUNCTION      : deleteNode
// DESCRIPTION   : Deletes a particular client from a list
//
// PARAMETERS    :
//	MasterList* list : Pointer to the shared memory master list
//	int index      : Index of the client that is going to be deleteds
//
// RETURNS       :
//	void
void deleteNode(MasterList* list, int index)
{
  int lastIndex = list->numberOfDCs - 1;
  list->dc[index] = list->dc[lastIndex];
  list->numberOfDCs--;
}
