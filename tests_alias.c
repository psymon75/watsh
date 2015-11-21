#include "greatest.h"
#include "alias.h"

TEST get_alias_value_empty_table(void) {
  alias_t alias_table = new_alias_table();
  ASSERT_EQ(NULL, get_alias_value(alias_table, "foo"));
  ASSERT_EQ(NULL, get_alias_value(alias_table, "bar"));
  free_alias_table(&alias_table);
  PASS();
}

TEST get_alias_value_loop_simple(void) {
  alias_t alias_table = new_alias_table();
  register_alias(&alias_table, "test1", "test2");
  register_alias(&alias_table, "test2", "test3");
  register_alias(&alias_table, "test3", "test1");
  ASSERT_EQ(NULL, get_alias_value(alias_table, "test1"));
  ASSERT_EQ(NULL, get_alias_value(alias_table, "test2"));
  ASSERT_EQ(NULL, get_alias_value(alias_table, "test3"));
  free_alias_table(&alias_table);
  PASS();
}
TEST get_alias_value_loop_complex(void) {
  alias_t alias_table = new_alias_table();
  register_alias(&alias_table, "test1", "test2 --foo");
  register_alias(&alias_table, "test2", "test3");
  register_alias(&alias_table, "test3", "test1 --bar");
  ASSERT_EQ(NULL, get_alias_value(alias_table, "test1"));
  ASSERT_EQ(NULL, get_alias_value(alias_table, "test2"));
  ASSERT_EQ(NULL, get_alias_value(alias_table, "test3"));
  free_alias_table(&alias_table);
  PASS();
}

TEST get_alias_value_registered_alias(void) {
  alias_t alias_table = new_alias_table();
  register_alias(&alias_table, "test1", "test2");
  register_alias(&alias_table, "test3", "test4");
  char *value1 = get_alias_value(alias_table, "test1");
  char *value2 = get_alias_value(alias_table, "test2");
  ASSERT(value1 != NULL);
  ASSERT_STR_EQ("test2", value1);
  ASSERT(value2 != NULL);
  ASSERT_STR_EQ("test4", value2);
  free_alias_table(&alias_table);
  PASS();
}

TEST get_alias_value_nonregistered_alias(void) {
  alias_t alias_table = new_alias_table();
  register_alias(&alias_table, "test1", "test2");
  register_alias(&alias_table, "test3", "test4");
  ASSERT_EQ(NULL, get_alias_value(alias_table, "test5"));
  ASSERT_EQ(NULL, get_alias_value(alias_table, "test6"));
  free_alias_table(&alias_table);
  PASS();
}

TEST get_alias_value_recursive_simple(void) {
  alias_t alias_table = new_alias_table();
  register_alias(&alias_table, "test1", "test2");
  register_alias(&alias_table, "test3", "test4");
  register_alias(&alias_table, "test2", "test3");
  char *value1 = get_alias_value(alias_table, "test1");
  char *value2 = get_alias_value(alias_table, "test2");
  char *value3 = get_alias_value(alias_table, "test3");
  ASSERT(value1 != NULL);
  ASSERT_STR_EQ("test4", value1);
  ASSERT(value2 != NULL);
  ASSERT_STR_EQ("test4", value2);
  ASSERT(value3 != NULL);
  ASSERT_STR_EQ("test4", value3);
  free_alias_table(&alias_table);
  PASS();
}

TEST get_alias_value_recursive_complex(void) {
  alias_t alias_table = new_alias_table();
  register_alias(&alias_table, "test1", "test2 --foo");
  register_alias(&alias_table, "test3", "test4 --bar");
  register_alias(&alias_table, "test4", "test5 --foobar");
  register_alias(&alias_table, "test2", "test3");
  char *value1 = get_alias_value(alias_table, "test1");
  char *value2 = get_alias_value(alias_table, "test2");
  char *value3 = get_alias_value(alias_table, "test3");
  char *value4 = get_alias_value(alias_table, "test4");
  ASSERT(value1 != NULL);
  ASSERT_STR_EQ("test5 --foobar --bar --foo", value1);
  ASSERT(value2 != NULL);
  ASSERT_STR_EQ("test5 --foobar --bar", value2);
  ASSERT(value3 != NULL);
  ASSERT_STR_EQ("test5 --foobar --bar", value3);
  ASSERT(value4 != NULL);
  ASSERT_STR_EQ("test5 --foobar", value4);
  free_alias_table(&alias_table);
  PASS();
}

SUITE(alias) {
  RUN_TEST(get_alias_value_empty_table);
  RUN_TEST(get_alias_value_loop_simple);
  RUN_TEST(get_alias_value_loop_complex);
  RUN_TEST(get_alias_value_registered_alias);
  RUN_TEST(get_alias_value_nonregistered_alias);
  RUN_TEST(get_alias_value_recursive_simple);
  RUN_TEST(get_alias_value_recursive_complex);
}
