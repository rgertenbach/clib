#ifndef FLAGS_H
#define FLAGS_H

#include <inttypes.h>

#define FLAGS_MAX_NAMES 2
#define FLAGS_MAX_NAME_LEN 32
#define FLAGS_MAX_HELP_LEN 1024

enum FlagsFlagType {
  FLAG_TYPE_STRING = 1,
  FLAG_TYPE_INT64 = 2,
  FLAG_TYPE_INT32 = 3,
  FLAG_TYPE_INT16 = 3,
  FLAG_TYPE_INT8 = 3,
};

union FlagsFlagValue {
  char *string_value;
  int64_t int64_value;
  int32_t int32_value;
  int16_t int16_value;
  int8_t int8_value;
};

struct FlagsFlag {
  char **names;
  size_t n_names;
  char *help;
  enum FlagsFlagType type;
  union FlagsFlagValue value;
};

struct FlagsFlagPool {
  struct FlagsFlag *flags;
  size_t sz;
};

void flags_flag_pool_init(struct FlagsFlagPool * const flags,
                          size_t const max_Size);

void flags_flag_pool_destroy(struct FlagsFlagPool *flags);

void flags_parse_flags(struct FlagsFlagPool *flags,
                       int argc,
                       char **argv);


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

#undef add_params
#undef get_params

#endif
