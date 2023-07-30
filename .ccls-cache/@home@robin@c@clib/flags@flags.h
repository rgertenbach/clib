#ifndef FLAGS_H
#define FLAGS_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// You can provide a short and/or a long form.
#define FLAGS_MAX_NAMES 2

// Don't make your flag names too long.
#define FLAGS_MAX_NAME_LEN 64

// Keep your help short.
#define FLAGS_MAX_HELP_LEN 1024

#define FLAGS_MAX_LIST_LEN 1024
#define FLAGS_MAX_STRLIST_ELEM_LEN 256

// TODO:
// - vargs
// - lists
enum FlagsFlagType {
  FLAG_TYPE_STRING = 1,
  FLAG_TYPE_INT64 = 2,
  FLAG_TYPE_INT32 = 3,
  FLAG_TYPE_INT16 = 4,
  FLAG_TYPE_INT8 = 5,
  FLAG_TYPE_BOOL = 6,
  FLAG_TYPE_FLOAT = 7,
  FLAG_TYPE_DOUBLE = 8,
  FLAG_TYPE_LONG_DOUBLE = 9,
  FLAG_TYPE_STRING_LIST = 10,
};

union FlagsFlagValue {
  char *string_value;
  int64_t int64_value;
  int32_t int32_value;
  int16_t int16_value;
  int8_t int8_value;
  bool bool_value;
  float float_value;
  double double_value;
  long double long_double_value;
  char **string_list_value;
};

struct FlagsFlag {
  char **names;
  size_t n_names;
  char *help;
  enum FlagsFlagType type;
  union FlagsFlagValue value;
  size_t list_sz;
};

struct FlagsFlagPool {
  struct FlagsFlag *flags;
  size_t sz;
  char **help_names;
  size_t n_help_names;
};

void flags_flag_pool_init(struct FlagsFlagPool * const flags,
                          size_t const max_Size);

void flags_flag_pool_destroy(struct FlagsFlagPool *flags);

void flags_parse_flags(struct FlagsFlagPool *flags,
                       int argc,
                       char **argv);

// Set which passed flag calls the help.
//
// @param flags The flagpool.
// @param names A space separated list of flags that, when passed just opens
//   the help no matter what else what's passed.
//   Defaults to "-h --help". Pass NULL to delete.
void flags_set_help(struct FlagsFlagPool * const flags, 
                    char const * const names);


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



void flags_add_string(add_params(char *));
char *flags_get_string(get_params);

void flags_add_int64(add_params(int64_t));
int64_t flags_get_int64(get_params);

void flags_add_int32(add_params(int32_t));
int32_t flags_get_int32(get_params);

void flags_add_int16(add_params(int16_t));
int16_t flags_get_int16(get_params);

void flags_add_int8(add_params(int8_t));
int8_t flags_get_int8(get_params);

// Passes true with flag-name and false with no-flag-name.
// Boolean flags should be named with the truthy value.
// That means if you have a variable use-stuff add a flag
// use-stuff not no-use-stuff.
// Flags cam be negated multiple times at parsing, e.g.,
// --no-no-no-flag sets it to false.
void flags_add_bool(add_params(bool));
bool flags_get_bool(get_params);

void flags_add_float(add_params(float));
float flags_get_float(get_params);

void flags_add_double(add_params(double));
double flags_get_double(get_params);

void flags_add_long_double(add_params(long double));
long double flags_get_long_double(get_params);

void flags_add_string_list(add_params(char *));
char **flags_get_string_list(get_params);

#undef add_params
#undef get_params

struct FlagsFlag *flags_get(struct FlagsFlagPool const * const flags, 
                            char const * const name);

size_t flags_list_size(struct FlagsFlag const * const flag);

void flags_generate_help(char * dest,
                         struct FlagsFlagPool const * const flags);
int flags_fprint_help(FILE * stream, 
                      struct FlagsFlagPool const * const flags);
int flags_print_help(struct FlagsFlagPool const * const flags);

#endif
