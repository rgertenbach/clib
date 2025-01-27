#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../test/minunit.h"
#include "str.h"

#define MAXLEN 4
#define MAXELEM 4

char *test_starts_with(void)
{
    mu_test("abc a", str_starts_with("abc", "a"), MU_NO_CLEANUP);
    mu_test("abc ab", str_starts_with("abc", "ab"), MU_NO_CLEANUP);
    mu_test("abc abc", str_starts_with("abc", "abc"), MU_NO_CLEANUP);
    mu_test("!abc bc", !str_starts_with("abc", "bc"), MU_NO_CLEANUP);
    mu_test("!a abc", !str_starts_with("a", "abc"), MU_NO_CLEANUP);
    return NULL;
}

char *test_ends_with(void)
{ 
    mu_test("c c", str_ends_with("c", "c"), MU_NO_CLEANUP);
    mu_test("abc c", str_ends_with("abc", "c"), MU_NO_CLEANUP);
    mu_test("abc bc", str_ends_with("abc", "bc"), MU_NO_CLEANUP);
    mu_test("abc abc", str_ends_with("abc", "abc"), MU_NO_CLEANUP);
    mu_test("!abc ab", !str_ends_with("abc", "ab"), MU_NO_CLEANUP);
    mu_test("!c abc", !str_ends_with("c", "abc"), MU_NO_CLEANUP);
    return NULL;
}

char *test_contains(void)
{ 
    mu_test("c c", str_contains("c", "c"), MU_NO_CLEANUP);
    mu_test("ac ab", str_contains("ab", "ab"), MU_NO_CLEANUP);
    mu_test("abc ab", str_contains("abc", "ab"), MU_NO_CLEANUP);
    mu_test("abc bc", str_contains("abc", "bc"), MU_NO_CLEANUP);
    mu_test("abc abc", str_contains("abc", "abc"), MU_NO_CLEANUP);
    mu_test("!abc abcd", !str_contains("abc", "abcd"), MU_NO_CLEANUP);
    mu_test("!abc d", !str_contains("abc", "d"), MU_NO_CLEANUP);
    return NULL;
}

char *test_containc(void)
{ 
    mu_test("c c", str_containc("c", 'c'), MU_NO_CLEANUP);
    mu_test("ac a", str_containc("ab", 'a'), MU_NO_CLEANUP);
    mu_test("ac c", str_containc("ac", 'c'), MU_NO_CLEANUP);
    mu_test("!abc d", !str_containc("abc", 'd'), MU_NO_CLEANUP);
    return NULL;
}

char * test_lstrip(void)
{
    char s[1000];
    size_t removed = 0;

    strcpy(s, "abc"); 
    removed = str_lstrip(s, "a");
    mu_test_equal("abc a removed", 1, removed, MU_NO_CLEANUP);
    mu_test("abc a", strcmp(s, "bc") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc"); 
    removed = str_lstrip(s, "ba");
    mu_test_equal("abc ab removed", 2, removed, MU_NO_CLEANUP);
    mu_test("abc ba", strcmp(s, "c") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc"); 
    removed = str_lstrip(s, "b");
    mu_test_equal("abc b removed", 0, removed, MU_NO_CLEANUP);
    mu_test("abc b", strcmp(s, "abc") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc"); 
    removed = str_lstrip(s, "aa");
    mu_test_equal("abc aa removed", 1, removed, MU_NO_CLEANUP);
    mu_test("abc aa", strcmp(s, "bc") == 0, MU_NO_CLEANUP);

    return NULL;
}

char * test_rstrip(void)
{
    char s[1000];
    size_t removed = 0;

    strcpy(s, "abc"); 
    removed = str_rstrip(s, "c");
    mu_test_equal("abc c removed", 1, removed, MU_NO_CLEANUP);
    mu_test("abc c", strcmp(s, "ab") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc"); 
    removed = str_rstrip(s, "bc");
    mu_test_equal("abc bc removed", 2, removed, MU_NO_CLEANUP);
    mu_test("abc ba", strcmp(s, "a") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc"); 
    removed = str_rstrip(s, "b");
    mu_test_equal("abc b removed", 0, removed, MU_NO_CLEANUP);
    mu_test("abc b", strcmp(s, "abc") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc"); 
    removed = str_rstrip(s, "cc");
    mu_test_equal("abc cc removed", 1, removed, MU_NO_CLEANUP);
    mu_test("abc cc", strcmp(s, "ab") == 0, MU_NO_CLEANUP);

    return NULL;
}

char * test_strip(void)
{
    char s[1000];
    size_t removed = 0;

    strcpy(s, "abc"); 
    removed = str_strip(s, "ca");
    mu_test_equal("abc ca removed", 2, removed, MU_NO_CLEANUP);
    mu_test("abc ca", strcmp(s, "b") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc"); 
    removed = str_strip(s, "b");
    mu_test_equal("abc b removed", 0, removed, MU_NO_CLEANUP);
    mu_test("abc b", strcmp(s, "abc") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc"); 
    removed = str_strip(s, "abc");
    mu_test_equal("abc abc removed", 3, removed, MU_NO_CLEANUP);
    mu_test("abc abc", strcmp(s, "") == 0, MU_NO_CLEANUP);

    return NULL;
}

char * test_remove_suffix(void)
{
    char s[1000];

    strcpy(s, "abc");
    mu_test("abc removes but 0", str_remove_suffix(s, ""), MU_NO_CLEANUP);
    mu_test("abc", strcmp(s, "abc") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc");
    mu_test("abc bc removes", str_remove_suffix(s, "bc"), MU_NO_CLEANUP);
    mu_test("abc bc", strcmp(s, "a") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc");
    mu_test("abc bc removes", str_remove_suffix(s, "abc"), MU_NO_CLEANUP);
    mu_test("abc bc", strcmp(s, "") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc");
    mu_test("abc d", !str_remove_suffix(s, "d"), MU_NO_CLEANUP);
    mu_test("abc d", strcmp(s, "abc") == 0, MU_NO_CLEANUP);

    return NULL;
}

char * test_remove_prefix(void)
{
    char s[1000];

    strcpy(s, "abc");
    mu_test("abc removes but 0", str_remove_prefix(s, ""), MU_NO_CLEANUP);
    mu_test("abc", strcmp(s, "abc") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc");
    mu_test("abc ab removes", str_remove_prefix(s, "ab"), MU_NO_CLEANUP);
    mu_test("abc ab", strcmp(s, "c") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc");
    mu_test("abc abc removes", str_remove_prefix(s, "abc"), MU_NO_CLEANUP);
    mu_test("abc abc", strcmp(s, "") == 0, MU_NO_CLEANUP);

    strcpy(s, "abc");
    mu_test("abc d", !str_remove_prefix(s, "d"), MU_NO_CLEANUP);
    mu_test("abc d", strcmp(s, "abc") == 0, MU_NO_CLEANUP);

    return NULL;
}

void all_tests(void)
{
    mu_run_test(test_starts_with);
    mu_run_test(test_ends_with);
    mu_run_test(test_contains);
    mu_run_test(test_containc);
    mu_run_test(test_lstrip);
    mu_run_test(test_rstrip);
    mu_run_test(test_strip);
    mu_run_test(test_remove_suffix);
    mu_run_test(test_remove_prefix);
}

int main(int argc, char **argv)
{
    (void) argv;
    if (argc > 1) {
	fprintf(stderr, "Too many arguments supplied\n");
	exit(1);
    }
    printf("%s\n", argv[0]);
    mu_main(all_tests);
}
