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

SUITE(alias) {
  RUN_TEST(get_alias_value_empty_table);
  RUN_TEST(get_alias_value_loop_simple);
}
