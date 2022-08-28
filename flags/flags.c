#include <inttypes.h>
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

// Common params for all flags_add_* functions.
//
// @param type The third arguments, must be supprted in FlagsFlagType.
#define add_params(type) struct FlagsFlagPool * const flags, \
                         char const * const names, \
                         type default_value, \
                         char const * const help

// Common params for all flags_get_* functions.
#define get_params struct FlagsFlagPool const * const flags, \
                   char const * const name

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
}

static Flag *flags_get(FlagPool const * const flags,
                       char const * const name)
{
  for (size_t i = 0; i < flags->sz; ++i) {
    Flag *flag = flags->flags + i;
    if (flag_has_name(flag, name)) return flag;
  }
  fprintf(stderr, "Flag \"%s\" not does not exist\n", name);
  abort();
}

static void flags_add(FlagPool *flags, 
                      FlagType type, 
                      char const * const names,
                      FlagValue value,
                      char const * const help)
{
  flag_init(flags->flags + flags->sz++, type, names, value, help);
}

static void flags_set(Flag * const flag, char *value)
{
  FlagValue flag_value;
  switch (flag->type) {
    case FLAG_TYPE_STRING: 
      flag_value.string_value = value; 
      break;
    case FLAG_TYPE_INT64: 
      flag_value.int64_value = strtoll(value, NULL, 10);
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

// Use flags_set?
extern void flags_add_string(add_params(char *))
{
  FlagValue value;
  value.string_value = default_value;
  flags_add(flags, FLAG_TYPE_STRING, names, value, help);
}

extern char *flags_get_string(get_params)
{
  return flags_get(flags, name)->value.string_value;
}

extern void flags_add_int64(add_params(int64_t))
{
  FlagValue value;
  value.int64_value = default_value;
  flags_add(flags, FLAG_TYPE_INT64, names, value, help);
}

extern int64_t flags_get_int64(get_params)
{
  return flags_get(flags, name)->value.int64_value;
}

#undef add_params
#undef get_params

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

// TODO: Validate type?
