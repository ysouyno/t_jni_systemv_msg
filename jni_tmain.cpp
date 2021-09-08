#include "jni_tmain.h"
#include "data.h"
#include <cstring>
#include <iostream>

JNIEXPORT void JNICALL Java_jni_tmain_no_1args_1return(JNIEnv *, jobject) {
  std::cout << "Java_jni_tmain_no_1args_1return\n";

  struct response_msg resp;
  struct request_msg req;
  int server_id;
  ssize_t msg_len;
  pid_t pid;

  // Get server's queue identifier; crate queue for response

  server_id = msgget(SERVER_KEY, S_IWUSR);
  if (server_id == -1) {
    perror("msgget - server message queue");
    return;
  }

  pid = getpid();

  req.mtype = 1;
  req.client_id = pid;
  strncpy(req.pathname, "3", sizeof(req.pathname) - 1);
  req.pathname[sizeof(req.pathname) - 1] = '\0'; // Ensure string is terminated

  if (msgsnd(server_id, &req, REQ_MSG_SIZE, 0) == -1) {
    perror("msgsnd");
    return;
  }

  // Get first response, which may be failure notification

  msg_len = msgrcv(server_id, &resp, RESP_MSG_SIZE, getpid(), 0);
  if (msg_len == -1) {
    perror("msgrcv");
    return;
  }

  printf("Client get response from server: %d\n", atoi(resp.data));
}
