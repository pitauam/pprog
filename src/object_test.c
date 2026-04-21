/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author Alexander
 * @version 1.0
 * @date 07-04-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 9

int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_object_create();
  if (all || test == 2) test2_object_create();
  if (all || test == 3) test1_object_set_name();
  if (all || test == 4) test2_object_set_name();
  if (all || test == 5) test3_object_set_name();
  if (all || test == 6) test1_object_get_name();
  if (all || test == 7) test2_object_get_name();
  if (all || test == 8) test1_object_get_id();
  if (all || test == 9) test2_object_get_id();
  /*
  if (all || test == 10) test1_set_health();
  if (all || test == 11) test2_set health();
  if (all || test == 12) test1_get_health();
  if (all || test == 13) test2_get_health();
  if (all || test == 14) test1_set_movable();
  if (all || test == 15) test2_set_movable();
  if (all || test == 16) test1_get_movable();
  if (all || test == 17) test2_get_movable();
  if (all || test == 18) test1_set_dependency();
  if (all || test == 19) test2_set_dependency();
  if (all || test == 20) test1_get_dependency();
  if (all || test == 21) test2_get_dependency();
  if (all || test == 22) test1_set_open();
  if (all || test == 23) test2_set_open();
  if (all || test == 24) test1_get_open();
  if (all || test == 25) test2_get_open();
  */

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_object_create() {
  Object *o = object_create(5);
  PRINT_TEST_RESULT(o != NULL);
  object_destroy(o);
}

void test2_object_create() {
  Object *o = object_create(NO_ID);
  PRINT_TEST_RESULT(o == NULL);
}

void test1_object_set_name() {
  Object *o = object_create(5);
  PRINT_TEST_RESULT(object_set_name(o, "Espada") == OK);
  object_destroy(o);
}

void test2_object_set_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_name(o, "Espada") == ERROR);
}

void test3_object_set_name() {
  Object *o = object_create(5);
  PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
  object_destroy(o);
}

void test1_object_get_name() {
  Object *o = object_create(5);
  object_set_name(o, "Espada");
  PRINT_TEST_RESULT(strcmp(object_get_name(o), "Espada") == 0);
  object_destroy(o);
}

void test2_object_get_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

void test1_object_get_id() {
  Object *o = object_create(25);
  PRINT_TEST_RESULT(object_get_id(o) == 25);
  object_destroy(o);
}

void test2_object_get_id() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}