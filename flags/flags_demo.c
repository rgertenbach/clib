#include <stdlib.h>
#include <stdio.h>

#include "flags.h"

#define UNUSED(a) (void) (a)


int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 10);

  flags_add_string(flags, "-i --input_file", "hello", "some help");

  // printf("%s\n", flags_get_string(flags, "--input_file"));

  flags_flag_pool_destroy(flags);
  return 0;
}
