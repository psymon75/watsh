#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"
#include "utils.h"

int builtin_cd(int argc, char *argv[]) {
  // TODO: implement 'cd -'
  // TODO: implement algorithm as decribed in man cd
  char *path;
  int return_code;
  if (argc < 2) {
    path = getenv("HOME");
  } else {
    path = argv[1];
  }
  char *old_path = getcwd(NULL, 0);
  int chdir_return = chdir(path);
  if (chdir_return != 0) {
    perror("watsh: cd");
    return_code = 1;
  } else {
    setenv("OLDPWD", old_path, 1);
    setenv("PWD", path, 1);
    return_code = 0;
  }
  free(old_path);
  return return_code;
}

int builtin_pwd(int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);
  int return_code;
  char *path = getcwd(NULL, 0);
  if (path == NULL) {
    perror("watsh: pwd");
    return_code = 1;
  } else {
    printf("%s\n", path);
    free(path);
    return_code = 0;
  }
  return return_code;
}
