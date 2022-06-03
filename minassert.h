/* Minimal unit testing framework.
 *
 * Originally from: https://jera.com/techinfo/jtns/jtn002
 * To define a unit test you define a function that returns a char*.
 * If the test fails the name of the failed test is returned via the macro.
 * Otherwise NULL should be returned which indicates a success.
 * 
 * The test .c file should initialize int tests_run = 0; and the main function
 * Stores the results of the tests and can handle the output based on whether
 * it's NULL or a string.
 *
 * Example:
 * #include <stdio.h>
 * #include "minunit.h"
 * 
 * int tests_run = 0;
 * int foo = 7;
 * int bar = 4;
 * 
 * static char * test_foo() {
 *   mu_assert("error, foo != 7", foo == 7);
 *   return NULL;
 * }
 * 
 * static char * test_bar() {
 *   mu_assert("error, bar != 5", bar == 5);
 *   return NULL;
 * }
 * 
 * static char * all_tests() {
 *   mu_run_test(test_foo);
 *   mu_run_test(test_bar);
 *   return NULL;
 * }
 * 
 * int main(int argc, char **argv) {
 *   char *result = all_tests();
 *   if (result != 0) printf("%s\n", result);
 *   else printf("ALL TESTS PASSED\n");
 *   printf("Tests run: %d\n", tests_run);
 *   return result != NULL;
 * }
 */


// Returns the message of the failed tests if any.
//
// @param message The name of the test / message to send when the test fails.
// @param test A c expression to run, falsy values mean a failure.
#define mu_assert(message, test) do { \
  if (!(test)) return message; \
} while (0)

// Calls function which runs a test checking if it was successful.
//
// @param test The test function to run.
#define mu_run_test(test) do { \
  char *message = test(); \
  tests_run++; \
  if (message) return message; \
} while (0)

// Global keeping track of the number of tests run.
extern int tests_run;
