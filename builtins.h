#ifndef BUILTINS_H
#define BUILTINS_H

int builtin_cd(int stdout_fd, int stderr_fd, int argc, char *argv[]);
int builtin_pwd(int stdout_fd, int stderr_fd, int argc, char *argv[]);

#endif
