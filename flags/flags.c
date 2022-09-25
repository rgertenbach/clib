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
  flag->list_sz = 0;
  return flag;
}

static bool is_list_type(Flag const * const flag)
{
  switch (flag->type) {
    case FLAG_TYPE_STRING_LIST:
      return true;
      break;
    default:
      return false;
      break;
  }
}

static void flag_destroy(Flag *flag)
{
  free(flag->help);
  for (size_t i = 0; i < flag->n_names; ++i) free(flag->names[i]);
  if (is_list_type(flag)) {
    if (flag->type == FLAG_TYPE_STRING_LIST) {
      while (flag->list_sz-- > 0) {
        free(flag->value.string_list_value[flag->list_sz]); 
      }
      free(flag->value.string_list_value);
    }
  }
  free(flag->names);
}

extern Flag *flags_get(FlagPool const * const flags,
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

static Flag *flags_add(FlagPool *flags, 
                      FlagType type, 
                      char const * const names,
                      FlagValue value,
                      char const * const help)
{
  Flag *flag = flags->flags + (flags->sz++);
  flag_init(flag, type, names, value, help);
  return flag;
}

static void flags_set(Flag * const flag, char *value)
{
  switch (flag->type) {
    case FLAG_TYPE_STRING: 
      flag->value.string_value = value; 
      break;
    case FLAG_TYPE_INT64: 
      flag->value.int64_value = strtoll(value, NULL, 10);
      break;
    case FLAG_TYPE_INT32: 
      flag->value.int32_value = strtol(value, NULL, 10);
      break;
    case FLAG_TYPE_INT16: 
      flag->value.int16_value = strtol(value, NULL, 10);
      break;
    case FLAG_TYPE_INT8: 
      flag->value.int8_value = strtol(value, NULL, 10);
      break;
    case FLAG_TYPE_BOOL: 
      flag->value.bool_value = parse_bool_flag_value(value);
      break;
    case FLAG_TYPE_FLOAT:
      flag->value.float_value = strtof(value, NULL);
      break;
    case FLAG_TYPE_DOUBLE:
      flag->value.double_value = strtod(value, NULL);
      break;
    case FLAG_TYPE_LONG_DOUBLE:
      flag->value.long_double_value = strtold(value, NULL);
      break;
    case FLAG_TYPE_STRING_LIST:
      flag->list_sz = strnsplit(
          flag->value.string_list_value, 
          value, 
          ",",
          FLAGS_MAX_LIST_LEN, 
          FLAGS_MAX_STRLIST_ELEM_LEN);
      break;
    default: 
      fprintf(stderr, "%s has an unsupported flag type\n", flag->names[0]); 
      break;
  }
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

extern void flags_add_float(add_params(float))
{
  FlagValue value;
  value.float_value = default_value;
  flags_add(flags, FLAG_TYPE_FLOAT, names, value, help);
}

extern float flags_get_float(get_params)
{
  return flags_get(flags, name)->value.float_value;
}

extern void flags_add_double(add_params(double))
{
  FlagValue value;
  value.double_value = default_value;
  flags_add(flags, FLAG_TYPE_DOUBLE, names, value, help);
}

extern double flags_get_double(get_params)
{
  return flags_get(flags, name)->value.double_value;
}

extern void flags_add_long_double(add_params(long double))
{
  FlagValue value;
  value.long_double_value = default_value;
  flags_add(flags, FLAG_TYPE_LONG_DOUBLE, names, value, help);
}

extern long double flags_get_long_double(get_params)
{
  return flags_get(flags, name)->value.long_double_value;
}

extern void flags_add_string_list(add_params(char *))
{
  FlagValue value;
  value.string_list_value = malloc(FLAGS_MAX_LIST_LEN * sizeof(char *));
  for (size_t i = 0; i < FLAGS_MAX_LIST_LEN; ++i) {
    value.string_list_value[i] = malloc(FLAGS_MAX_STRLIST_ELEM_LEN);
  }
  size_t list_sz = strnsplit(
      value.string_list_value, default_value, ",",
      FLAGS_MAX_LIST_LEN, FLAGS_MAX_STRLIST_ELEM_LEN);

  Flag *flag = flags_add(flags, FLAG_TYPE_STRING_LIST, names, value, help);
  flag->list_sz = list_sz;
}

extern char **flags_get_string_list(get_params)
{
  return flags_get(flags, name)->value.string_list_value;
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

extern size_t flags_list_size(struct FlagsFlag const * const flag)
{
  return flag->list_sz;
} 

extern void flags_generate_help(char * dest,
                                FlagPool const * const flags)
{
  dest += sprintf(dest, "Flags:\n");
  for (size_t flagi = 0; flagi < flags->sz; ++flagi) {
    Flag const * const flag = flags->flags + flagi;
    for (size_t namei = 0; namei < flag->n_names; ++namei) {
      if (namei) dest += sprintf(dest, ", ");
      dest += sprintf(dest, "%s", flag->names[namei]);
    }
    if (flag->help != NULL) dest += sprintf(dest, "\n\t%s", flag->help);
    dest += sprintf(dest, "\n");
  }

  *dest = '\0';
}

extern int flags_fprint_help(FILE * restrict stream,
                             FlagPool const * const flags)
{
  (void) stream;
  (void) flags;
  int result = 0;
  char * help = malloc(1e5);
  flags_generate_help(help, flags);
  fprintf(stream, "%s", help);
  free(help);
  return result;
}

extern int flags_print_help(FlagPool const * const flags)
{
  return flags_fprint_help(stdout, flags);
}
