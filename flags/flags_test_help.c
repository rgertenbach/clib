#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"

int main(int argc, char **argv)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_string(flags, "--name -n", "default", "help");
  flags_add_string(flags, "-o -other-flag", "default_value", "help2");

  if (argc == 0) {
    flags_print_help(flags);
    return 0;
  }

  flags_parse_flags(flags, argc, argv);
  printf("%s\n", flags_get_string(flags, "--name"));
  return 0;
}
