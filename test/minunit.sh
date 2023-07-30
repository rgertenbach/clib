# Runs mu test
#
# @param $@ targets passed for cc.
function mu_test() {
  cc -Wall -Wextra "$@"
  ./a.out
  rm a.aout
}
