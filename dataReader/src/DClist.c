/*
*  FILE          : linkedList.cpp
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel
*  FIRST VERSION : 2019-06-10
*  DESCRIPTION   : Modified version of the Data Structures Assignment #1 linked list code...cool, right?
*                  This file contains the definitions for the functionsto linked list implementations
*/
#include "../inc/dataReader.h"


// FUNCTION      : insertNodeToList
// DESCRIPTION   : Insert a node in a ascending client ID order or Updates there
//								 existing client timer
//
// PARAMETERS    :
//	MasterList* list : List containing information about all server clients
//  DCInfo*  node   : Pointer to the node that is being inserted
//
// RETURNS       :
//	Returns a pointer to the node if it was added or already existed,
//  NULL if the server is full
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
      createLogMessage(list->dc[counter], NON_RESPONSIVE, counter, 0);
			// Replace the deleted object with last element
      int lastIndex = list->numberOfDCs - 1;
      if(lastIndex != counter)
      {
        list->dc[counter] = list->dc[lastIndex];
      }
      deleteNode(list, lastIndex);
		}
    else
    {
      counter++;
    }
	}
}


// FUNCTION      : deleteNode
// DESCRIPTION   : Deletes a particular node from a list
//
// PARAMETERS    :
//	MasterList* list : Pointer to the shared memory master list
//	int index      : Index of the client that is going to be deleteds
//
// RETURNS       :
//	NOTHING
void deleteNode(MasterList* list, int index)
{
  list->dc[index].dcProcessID = 0;
  list->dc[index].lastTimeHeardFrom = 0;
  list->numberOfDCs--;
}
