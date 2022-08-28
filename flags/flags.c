#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../string/split.h"
#include "flags.h"

typedef enum FlagsFlagType FlagType;
typedef union FlagsFlagValue FlagValue;
typedef struct FlagsFlag Flag;
typedef struct FlagsFlagPool FlagPool;


static bool flag_has_name(Flag const * const flag,
                          char const * const name);


// Declare optional FLAGS that refers to this via macro (0?)
// static Flag **flags = malloc(FLAGS_MAX_FLAGS * sizeof(Flag *));
// size_t nflags = 0;

static Flag *flag_init(Flag *flag,
                       FlagType const flag_type,
                       char const * const names,
                       FlagValue const value,
                       char const * const help)
{
  flag->names = malloc(FLAGS_MAX_NAMES * sizeof(char *));
  for (size_t i = 0; i < FLAGS_MAX_NAMES; ++i) 
    flag->names[i] = malloc(FLAGS_MAX_NAME_LEN);
  flag->n_names = strnsplit(flag->names, names, " ", FLAGS_MAX_NAMES, FLAGS_MAX_NAME_LEN);

  flag->help = malloc(FLAGS_MAX_HELP_LEN);
  strncpy(flag->help, help, FLAGS_MAX_HELP_LEN);

  flag->type = flag_type;
  flag->value = value;
  return flag;
}

static void flag_destroy(Flag *flag)
{
  free(flag->help);
  for (size_t i = 0; i < flag->n_names; ++i) free(flag->names[i]);
  free(flag->names);
  free(flag);
}

static Flag *flags_get(FlagPool const * const flags,
    char const * const name)
{
  for (size_t i = 0; i < flags->sz; ++i) {
    Flag * flag = flags->flags + i;
    if (flag_has_name(flag, name)) return flag;
  }
  fprintf(stderr, "Flag \"%s\" not does not exist\n", name);
  return NULL;
}

static bool flag_has_name(Flag const * const flag,
                          char const * const name)
{
  for (size_t i = 0; i < flag->n_names; ++i) {
    if (strcmp(flag->names[i], name) == 0) return true;
  }
  return false;
}

// Implementation of public methods.

extern void flags_flag_pool_init(FlagPool * const flags,
                                 size_t const max_size)
{
  flags->flags = malloc(max_size * sizeof(Flag));
  flags->sz = 0;
}

extern void flags_flag_pool_destroy(FlagPool *flags)
{
  for (size_t i = 0; i < flags->sz; ++i) flag_destroy(flags->flags + i);
  free(flags);
}

extern void flags_add_string(FlagPool * const flags,
                             char const * const names, 
                             char *default_value, 
                             char const * const help)
{
  FlagValue value;
  value.string_value = default_value;
  flag_init(flags->flags + flags->sz, FLAG_TYPE_STRING, names, value, help);
}


extern char * flags_get_string(FlagPool const * const flags,
                               char const * const name)
{
  Flag const * const flag = flags_get(flags, name);
  // TODO: Validate type?
  return (flag == NULL) ? NULL : flag->value.string_value;
}


// CUrrent issue: does flagpool->flag contain Flags or Flag*s?
