#include "data.h"

static int server_id;
static int seq_num = 2;

static void grim_reaper(int sig) // SIGCHLD handler
{
  int saved_errno;

  saved_errno = errno;
  while (waitpid(-1, NULL, WNOHANG) > 0) {
    continue;
  }
  errno = saved_errno;
}

static void serve_request(const struct request_msg *req) {
  struct response_msg resp;

  sprintf(resp.data, "%d", seq_num);

  resp.mtype = req->client_id;

  if (msgsnd(server_id, &resp, RESP_MSG_SIZE, 0) == -1) {
    perror("msgsnd");
  }

  seq_num += atoi(req->pathname);
  printf("seq_num: %d\n", seq_num);
}

int main(int argc, char *argv[]) {
  struct request_msg req;
  pid_t pid;
  ssize_t msg_len;
  struct sigaction sa;

  server_id =
      msgget(SERVER_KEY, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IWGRP);
  if (server_id == -1) {
    perror("msgget");
    return -1;
  }

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = grim_reaper;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    return -1;
  }

  // Read requests, handle each in a separate child process

  for (;;) {
    msg_len = msgrcv(server_id, &req, REQ_MSG_SIZE, -1, 0);
    if (msg_len == -1) {
      if (errno == EINTR) { // Interrupted by SIGCHLD handler?
        continue;           // ... then restart msgrcv()
      }

      perror("msgrcv"); // Some other error
      break;            // ... so terminate loop
    }

    pid = fork();
    if (pid == -1) {
      perror("fork");
      break;
    }

    if (pid == 0) { // Child handles request
      serve_request(&req);
      _exit(EXIT_SUCCESS);
    }

    // Parent loops to receive next client request
  }

  // If msgrcv() or fork() fails, remove server MQ and exit

  if (msgctl(server_id, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    return -1;
  }

  exit(EXIT_SUCCESS);
}
