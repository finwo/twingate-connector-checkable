#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "httpd.h"

void spawn(const char *file, char *const argv[]) {
  int pid = fork();
  if (pid < 0) exit(1); // Error
  if (pid > 0) return;  // Parent
  execv(file, argv);    // Child
}

void sig_handler(int signo) {
  if (signo == SIGINT) exit(0);
}

int main(int argc, char *argv[]) {
  if (signal(SIGINT, sig_handler) == SIG_ERR) exit(1);

  char *const cmd_connectord[] = { "/connectord", NULL };
  spawn(cmd_connectord[0], cmd_connectord);

  char *port = getenv("PORT");
  if (!port) port = "80";
  serve_forever(port);

  return 0;
}

void route() {
  ROUTE_START()
  GET("/") {
    printf("HTTP/1.1 200 OK\r\n\r\n");
    printf("OK");
  }
  ROUTE_END()
}
