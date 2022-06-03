#include <stdio.h>

// Runs a test and prints the message if it fails
//
// @param message The name of the test / message to send when the test fails.
// @param test A c expression to run, falsy values mean a failure.
#define mu_test(message, test) do { \
  printf("%s:\t", message); \
  if ((test)) printf("Passed\n"); \
  else { \
    printf("Failed\n"); \
    return 1; \
  } \
  return 0; \
} while (0)

// Calls function which runs a test checking if it was successful.
//
// @param test The test function to run. Must take void.
#define mu_run_test(test) do { \
  char failed = test(); \
  tests_run++; \
  if (failed) tests_failed++; \
} while (0)

// Global keeping track of the number of tests run.
int tests_run = 0;
int tests_failed = 0;

// Run tests.
//
// @param suite A void function taking void running all tests.
#define mu_main(suite) do { \
  suite(); \
  printf("Ran %d tests\n", tests_run); \
  if (!tests_run) printf("No tests run\n"); \
  if (tests_failed) printf("%d tests failed\n", tests_failed); \
  else printf("All tests pass! :)\n"); \
} while (0)
