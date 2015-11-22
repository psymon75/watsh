#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"
#include "errors.h"
#include "utils.h"

int builtin_cd(int stdout_fd, int stderr_fd, int argc, char *argv[]) {
  // TODO: implement 'cd -'
  // TODO: implement algorithm as decribed in man cd
  UNUSED(stdout_fd);
  char *path;
  int exit_status;
  if (argc < 2) {
    path = getenv("HOME");
  } else {
    path = argv[1];
  }
  char *old_path = getcwd(NULL, 0);
  int chdir_return = chdir(path);
  if (chdir_return != 0) {
    perror_fd(stderr_fd, "watsh: cd");
    exit_status = 1;
  } else {
    setenv("OLDPWD", old_path, 1);
    setenv("PWD", path, 1);
    exit_status = 0;
  }
  free(old_path);
  return exit_status;
}

int builtin_pwd(int stdout_fd, int stderr_fd, int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);
  int exit_status;
  char *path = getcwd(NULL, 0);
  if (path == NULL) {
    perror_fd(stderr_fd, "watsh: pwd");
    exit_status = 1;
  } else {
    dprintf(stdout_fd, "%s\n", path);
    free(path);
    exit_status = 0;
  }
  return exit_status;
}
