#/usr/bin/bash

cc linked_list_test.c linked_list.c -Wall -Wextra -o linked_list_test && \
  ./linked_list_test && \
  rm linked_list_test
