#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../string/split.h"
#include "flags.h"

// Decls

typedef enum FlagsFlagType FlagType;
typedef union FlagsFlagValue FlagValue;
typedef struct FlagsFlag Flag;
typedef struct FlagsFlagPool FlagPool;


static bool flag_has_name(Flag const * const flag,
                          char const * const name);


// Declare optional FLAGS that refers to this via macro (0?)
// static Flag **flags = malloc(FLAGS_MAX_FLAGS * sizeof(Flag *));
// size_t nflags = 0;

// Internal functions

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

static void flags_set(Flag * const flag, void *value)
{
  FlagValue flag_value;
  switch (flag->type) {
    case FLAG_TYPE_STRING: 
      flag_value.string_value = (char *) value; 
      break;
    default: 
      fprintf(stderr, "%s has an unsupported flag type\n", flag->names[0]); 
      break;
  }
  flag->value = flag_value;
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
  flags->sz++;
}

extern char *flags_get_string(FlagPool const * const flags,
                              char const * const name)
{
  Flag const * const flag = flags_get(flags, name);
  // TODO: Validate type?
  return (flag == NULL) ? NULL : flag->value.string_value;
}


void flags_parse_flags(FlagPool *flags,
                       int argc,
                       char **argv)
{
  Flag *flag;
  for (size_t i = 1; i < (size_t) argc; ++i) {  // 0 is program name.
    flag = flags_get(flags, argv[i]);
    if (flag == NULL) {
      if (*argv[i] == '-') fprintf(stderr, "WARNING: %s is a but not a flag", argv[i]);
      continue;
    }
    // Treat bool and non-bool differently.
    // Currently assumes space separated and <flag> <value>
    if (i == (size_t) (argc - 1)) {
      fprintf(stderr, "No value provided for %s\n", argv[i]);
      exit(1);
    }

    flags_set(flag, argv[++i]);
  }
}
