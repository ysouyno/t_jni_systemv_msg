#ifndef DATA_H_
#define DATA_H_

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h> // For definition of offsetof()
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SERVER_KEY 0x1aaaaaa1

struct request_msg // Requests (client to server)
{
  long mtype;              // Unused
  int client_id;           // ID of client's message queue
  char pathname[PATH_MAX]; // File to be returned
};

// REQ_MSG_SIZE computes size of `mtext` part of `request_msg` structure.
// We use offsetof() to handle the possibility that there are padding
// bytes between the `client_id` and `pathname` fields.

#define REQ_MSG_SIZE                                                           \
  (offsetof(struct request_msg, pathname) -                                    \
   offsetof(struct request_msg, client_id) + PATH_MAX)

#define RESP_MSG_SIZE 8192

struct response_msg // Responses (server to client)
{
  long mtype;               // One of RESP_MT_* values below
  char data[RESP_MSG_SIZE]; // File content / response message
};

// Type for response messages sent from server ot client

#define RESP_MT_FAILURE 1 // File couldn't be opened
#define RESP_MT_DATA 2    // Message contains file data
#define RESP_MT_END 3     // File data complete

#endif // DATA_H_
