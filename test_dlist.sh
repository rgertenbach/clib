#/usr/bin/bash

cc dlist_test.c dlist.c -Wall -Wextra -o dlist_test && \
  ./dlist_test && \
  rm dlist_test
