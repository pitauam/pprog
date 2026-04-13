/**
 * @brief Implements tests for the set module
 *
 * @file set_test.c
 * @author Santiago Pita
 * @version 1
 * @date 13-04-2026
 */

 #include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "test.h"
#include "set_test.h"

#define MAX_TESTS 10

void test1_set_create();
void test2_set_create();
void test1_set_add_value();
void test2_set_add_value();
void test1_set_del_value();
void test2_set_del_value();
void test1_set_find_id();
void test2_set_find_id();
void test1_set_get_n_ids();
void test2_set_get_n_ids();

int main(int argc, char** argv) {
  int test = 0;
  int all = 1;
  if (argc < 2) {
    printf("Running all tests for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    if (test < 1 && test > MAX_TESTS) { exit(EXIT_SUCCESS); }
  }

  if (all || test == 1) test1_set_create();
  if (all || test == 2) test2_set_create();
  if (all || test == 3) test1_set_add_value();
  if (all || test == 4) test2_set_add_value();
  if (all || test == 5) test1_set_del_value();
  if (all || test == 6) test2_set_del_value();
  if (all || test == 7) test1_set_find_id();
  if (all || test == 8) test2_set_find_id();
  if (all || test == 9) test1_set_get_n_ids();
  if (all || test == 10) test2_set_get_n_ids();

  PRINT_PASSED_PERCENTAGE;
  return 0; 
}

void test1_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(s != NULL);
  set_destroy(s);
}
void test2_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_get_n_ids(s) == 0);
  set_destroy(s);
}

void test1_set_add_value() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_add_value(s, 5) == OK);
  set_destroy(s);
}
void test2_set_add_value() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_add_value(s, 5) == ERROR);
}

void test1_set_del_value() {
  Set *s = set_create();
  set_add_value(s, 5);
  PRINT_TEST_RESULT(set_del_value(s, 5) == OK);
  set_destroy(s);
}
void test2_set_del_value() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_del_value(s, 5) == ERROR);
  set_destroy(s);
}

void test1_set_find_id() {
  Set *s = set_create();
  set_add_value(s, 10);
  PRINT_TEST_RESULT(set_find_id(s, 10) == OK);
  set_destroy(s);
}
void test2_set_find_id() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_find_id(s, 10) == ERROR);
  set_destroy(s);
}

void test1_set_get_n_ids() {
  Set *s = set_create();
  set_add_value(s, 10);
  PRINT_TEST_RESULT(set_get_n_ids(s) == 1);
  set_destroy(s);
}
void test2_set_get_n_ids() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_n_ids(s) == -1);
}