#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

void perror_fd(int fd, const char *s) {
  if (fd != -1) {
    //perror(s);
    char *error_msg = strerror(errno);
    dprintf(fd, "%s: %s", s, error_msg);
  }
}
