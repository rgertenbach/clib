#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../string/split.h"
#include "flags.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

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

// Internal functions

// Assumes the names already match.
static bool parse_bool_flag_value(char const * name)
{
  if (strlen(name) < 2) {
    fprintf(stderr, "'%s' too short a name\n", name);
    exit(1);
  }
  bool val = true;
  char const * p = name + 2;  // Skip 2

  while (!strncmp(p, "no-", 3)) {
    val = !val;
    p += 3;
  }
  return val;
}

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
  // We need to make sure a flag with the actual name doesn't exist before
  // overwriting wit no-.
  if (!strncmp(name, "--no-", 5)) {
    char truthy_name[FLAGS_MAX_NAME_LEN] = "--";
    strcpy(truthy_name + 2, name + 5);
    return flags_get(flags, truthy_name);
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
  flag_init(flags->flags + (flags->sz++), type, names, value, help);
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
    case FLAG_TYPE_INT32: 
      flag_value.int32_value = strtol(value, NULL, 10);
      break;
    case FLAG_TYPE_INT16: 
      flag_value.int16_value = strtol(value, NULL, 10);
      break;
    case FLAG_TYPE_INT8: 
      flag_value.int8_value = strtol(value, NULL, 10);
      break;
    case FLAG_TYPE_BOOL: 
      flag_value.bool_value = parse_bool_flag_value(value);
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
    if (flag->type == FLAG_TYPE_BOOL 
        && strncmp(flag->names[i], "no-", 3) 
        && strcmp(flag->names[i] + 3, name) == 0) return true;
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

// Flags setting and getting

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

extern void flags_add_int32(add_params(int32_t))
{
  FlagValue value;
  value.int32_value = default_value;
  flags_add(flags, FLAG_TYPE_INT32, names, value, help);
}

extern int32_t flags_get_int32(get_params)
{
  return flags_get(flags, name)->value.int32_value;
}

extern void flags_add_int16(add_params(int16_t))
{
  FlagValue value;
  value.int16_value = default_value;
  flags_add(flags, FLAG_TYPE_INT16, names, value, help);
}

extern int16_t flags_get_int16(get_params)
{
  return flags_get(flags, name)->value.int16_value;
}

extern void flags_add_int8(add_params(int8_t))
{
  FlagValue value;
  value.int8_value = default_value;
  flags_add(flags, FLAG_TYPE_INT8, names, value, help);
}

extern int8_t flags_get_int8(get_params)
{
  return flags_get(flags, name)->value.int8_value;
}

extern void flags_add_bool(add_params(bool))
{
  if (strstr(names, "--no")) {
    fprintf(
        stderr, 
        "Do not prefix bool flags with 'no-', "
        "give the truthy name and set a default (got '%s').\n",
        names);
    exit(1);
  }
  FlagValue value;
  value.bool_value = default_value;
  flags_add(flags, FLAG_TYPE_BOOL, names, value, help);
}

extern bool flags_get_bool(get_params)
{
  return flags_get(flags, name)->value.bool_value;
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
    switch (flag->type) {
      case FLAG_TYPE_BOOL:
        flags_set(flag, argv[i]);
        break;

      default:
        if (i == (size_t) (argc - 1)) {
          fprintf(stderr, "No value provided for %s\n", argv[i]);
          exit(1);
        }
        flags_set(flag, argv[++i]);
        break;
    }
  }
}
