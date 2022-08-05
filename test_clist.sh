#/usr/bin/bash

cc clist_test.c clist.c -Wall -Wextra -o clist_test && \
  ./clist_test && \
  rm clist_test
