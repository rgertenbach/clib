#/usr/bin/bash

cc list_test.c list.c -Wall -Wextra -o list_test && \
  ./list_test && \
  rm list_test
