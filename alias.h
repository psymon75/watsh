#ifndef ALIAS_H
#define ALIAS_H

typedef struct alias_st {
  char *alias_name;
  char *alias_value;
  struct alias_st *next;
} alias_t;

int register_alias(alias_t *alias_table, char *alias_name, char *alias_value);
char *get_alias_value(alias_t alias_table, char *alias_name);

#endif
