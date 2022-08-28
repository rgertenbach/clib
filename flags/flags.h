#ifndef FLAGS_H
#define FLAGS_H

#define FLAGS_MAX_NAMES 2
#define FLAGS_MAX_NAME_LEN 32
#define FLAGS_MAX_HELP_LEN 1024

enum FlagsFlagType {
  FLAG_TYPE_STRING = 1
  // FLAG_TYPE_INT = 2
};

union FlagsFlagValue {
  char *string_value;
  // int int_value;
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

void flags_add_string(struct FlagsFlagPool * const flags,
                      char const * const names, 
                      char *default_value, 
                      char const * const help);


char *flags_get_string(struct FlagsFlagPool const * const flags,
                       char const * const name);

#endif
