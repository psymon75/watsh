#include <unistd.h>

#include "greatest.h"
#include "builtins.h"

TEST builtin_cd_permission_denied(void) {
  char *argv[] = {"cd", "/root"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  char *old_path = getcwd(NULL, 0);
  int cd_exit_status = builtin_cd(-1, -1, argc, argv);
  char *new_path = getcwd(NULL, 0);
  ASSERT_EQ(1, cd_exit_status);
  ASSERT_STR_EQ(old_path, new_path);
  free(old_path);
  free(new_path);
  PASS();
}

TEST builtin_cd_no_such_directory(void) {
  char *argv[] = {"cd", "non_existing_direcotry"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  char *old_path = getcwd(NULL, 0);
  int cd_exit_status = builtin_cd(-1, -1, argc, argv);
  char *new_path = getcwd(NULL, 0);
  ASSERT_EQ(1, cd_exit_status);
  ASSERT_STR_EQ(old_path, new_path);
  free(old_path);
  free(new_path);
  PASS();
}

TEST builtin_cd_dot(void) {
  char *argv[] = {"cd", "."};
  int argc = sizeof(argv) / sizeof(argv[0]);
  char *old_path = getcwd(NULL, 0);
  int cd_exit_status = builtin_cd(-1, -1, argc, argv);
  char *new_path = getcwd(NULL, 0);
  ASSERT_EQ(0, cd_exit_status);
  ASSERT_STR_EQ(old_path, new_path);
  free(old_path);
  free(new_path);
  PASS();
}

TEST builtin_cd_existing_directory(void) {
  char *argv[] = {"cd", ".git"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  char *old_path = getcwd(NULL, 0);
  int cd_exit_status = builtin_cd(-1, -1, argc, argv);
  char *new_path = getcwd(NULL, 0);
  ASSERT_EQ(0, cd_exit_status);
  ASSERT(strcmp(old_path, new_path) < 0);
  free(old_path);
  free(new_path);
  PASS();
}

TEST builtin_cd_dotdot(void) {
  char *argv[] = {"cd", ".."};
  int argc = sizeof(argv) / sizeof(argv[0]);
  char *old_path = getcwd(NULL, 0);
  int cd_exit_status = builtin_cd(-1, -1, argc, argv);
  char *new_path = getcwd(NULL, 0);
  ASSERT_EQ(0, cd_exit_status);
  ASSERT(strcmp(old_path, new_path) > 0);
  free(old_path);
  free(new_path);
  PASS();
}

SUITE(builtins) {
  RUN_TEST(builtin_cd_permission_denied);
  RUN_TEST(builtin_cd_no_such_directory);
  RUN_TEST(builtin_cd_dot);
  RUN_TEST(builtin_cd_existing_directory);
  RUN_TEST(builtin_cd_dotdot);
}
