#ifndef ALIAS_H
#define ALIAS_H

struct alias_st {
  char *alias_name;
  char *alias_value;
  struct alias_st *next;
};

typedef struct alias_st *alias_t;

alias_t new_alias_table();
void free_alias_table(alias_t *alias_table);
int register_alias(alias_t *alias_table, char *alias_name, char *alias_value);
char *get_alias_value(alias_t alias_table, char *alias_name);

#endif
