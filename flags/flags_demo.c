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
  flags_add_int64(flags, "-n --iterations", 69, "some int help");
  flags_parse_flags(flags, argc, argv);
  printf("%s %ld\n", flags_get_string(flags, "--input_file"), flags_get_int64(flags, "-n"));


  flags_flag_pool_destroy(flags);
  return 0;
}
