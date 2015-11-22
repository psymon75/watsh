#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"
#include "utils.h"

void builtin_cd(int argc, char *argv[]) {
  // TODO: implement 'cd -'
  // TODO: implement algorithm as decribed in man cd
  char *path;
  if (argc < 2) {
    path = getenv("HOME");
  } else {
    path = argv[1];
  }
  char *old_path = getcwd(NULL, 0);
  int chdir_return = chdir(path);
  if (chdir_return != 0) {
    perror("watsh: cd");
  } else {
    setenv("OLDPWD", old_path, 1);
    setenv("PWD", path, 1);
  }
  free(old_path);
}

void builtin_pwd(int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);
  char *path = getcwd(NULL, 0);
  if (path == NULL) {
    perror("watsh: pwd");
  } else {
    printf("%s\n", path);
    free(path);
  }
}
