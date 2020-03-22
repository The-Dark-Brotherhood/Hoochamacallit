/*
*  FILE          : Hoochamacallit.h
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel & Michael Gordon
*  FIRST VERSION : 2020-03-21
*  DESCRIPTION   : Shared constants, includes, and structures for the Hoochamacallit system
*/

#pragma once
#include "../inc/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>

// Constants
#define SHMKEY_PATH     "."
#define KEY_PATH        "/tmp/"
#define ID_ERROR        -1
#define SHM_KEYID       16535
#define EXIT_CODE       6
#define KEY             1337
#define MESSAGE_LENGTH  100
#define MACHINE_ON      1
#define EVERYTHING_OKAY 0
#define MIN_SLEEP       10
#define MAX_SLEEP       30

// Structures
//--> Message QUEUE
typedef struct
{
  long msgType;
  pid_t clientId;
  int msgStatus;
} msgData;

//--> Shared Memory
#define MAX_DC_ROLES    10
typedef struct DCInfo
{
  pid_t dcProcessID;
  time_t lastTimeHeardFrom;
} DCInfo;

typedef struct
{
  int msgQueueID;
  int numberOfDCs;
  DCInfo dc[MAX_DC_ROLES];
} MasterList;

// Messages
#define MSG_LEN   40
#define NUM_MSG   8
#define MSG_ERROR "ERROR READING STATUS"
#define MSG_0     "Everything is OKAY"
#define MSG_1     "Hydraulic Pressure Failure"
#define MSG_2     "Safety Button Failure"
#define MSG_3     "No Raw Material in the Process"
#define MSG_4     "Operating Temperature Out of Range"
#define MSG_5     "Operator Error"
#define MSG_6     "Machine is Off-line"
