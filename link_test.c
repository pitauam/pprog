/**
 * @brief It tests the link module
 *
 * @file link_test.c
 * @author Santiago Pita
 * @version 1
 * @date 28-03-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 24

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_link_create();
  if (all || test == 2) test2_link_create();
  if (all || test == 3) test1_link_set_name();
  if (all || test == 4) test2_link_set_name();
  if (all || test == 5) test3_link_set_name();
  if (all || test == 6) test1_link_get_name();
  if (all || test == 7) test2_link_get_name();
  if (all || test == 8) test1_link_set_origin();
  if (all || test == 9) test2_link_set_origin();
  if (all || test == 10) test1_link_get_origin();
  if (all || test == 11) test2_link_get_origin();
  if (all || test == 12) test1_link_set_destination();
  if (all || test == 13) test2_link_set_destination();
  if (all || test == 14) test1_link_get_destination();
  if (all || test == 15) test2_link_get_destination();
  if (all || test == 16) test1_link_set_direction();
  if (all || test == 17) test2_link_set_direction();
  if (all || test == 18) test1_link_get_direction();
  if (all || test == 19) test2_link_get_direction();
  if (all || test == 20) test1_link_set_open();
  if (all || test == 21) test2_link_set_open();
  if (all || test == 22) test1_link_get_open();
  if (all || test == 23) test2_link_get_open();
  if (all || test == 24) test3_link_get_open();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_link_create() {
  Link *link;

  link = link_create(1);
  PRINT_TEST_RESULT(link != NULL);
  link_destroy(link);
}

void test2_link_create() {
  Link *link;

  link = link_create(NO_ID);
  PRINT_TEST_RESULT(link == NULL);
}

void test1_link_set_name() {
  Link *link;

  link = link_create(1);
  PRINT_TEST_RESULT(link_set_name(link, "door") == OK);
  link_destroy(link);
}

void test2_link_set_name() {
  PRINT_TEST_RESULT(link_set_name(NULL, "door") == ERROR);
}

void test3_link_set_name() {
  Link *link;

  link = link_create(1);
  PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
  link_destroy(link);
}

void test1_link_get_name() {
  Link *link;

  link = link_create(1);
  link_set_name(link, "door");
  PRINT_TEST_RESULT(strcmp(link_get_name(link), "door") == 0);
  link_destroy(link);
}

void test2_link_get_name() {
  PRINT_TEST_RESULT(link_get_name(NULL) == NULL);
}

void test1_link_set_origin() {
  Link *link;

  link = link_create(1);
  PRINT_TEST_RESULT(link_set_origin(link, 2) == OK);
  link_destroy(link);
}

void test2_link_set_origin() {
  PRINT_TEST_RESULT(link_set_origin(NULL, 2) == ERROR);
}

void test1_link_get_origin() {
  Link *link;

  link = link_create(1);
  link_set_origin(link, 2);
  PRINT_TEST_RESULT(link_get_origin(link) == 2);
  link_destroy(link);
}

void test2_link_get_origin() {
  PRINT_TEST_RESULT(link_get_origin(NULL) == NO_ID);
}

void test1_link_set_destination() {
  Link *link;

  link = link_create(1);
  PRINT_TEST_RESULT(link_set_destination(link, 3) == OK);
  link_destroy(link);
}

void test2_link_set_destination() {
  PRINT_TEST_RESULT(link_set_destination(NULL, 3) == ERROR);
}

void test1_link_get_destination() {
  Link *link;

  link = link_create(1);
  link_set_destination(link, 3);
  PRINT_TEST_RESULT(link_get_destination(link) == 3);
  link_destroy(link);
}

void test2_link_get_destination() {
  PRINT_TEST_RESULT(link_get_destination(NULL) == NO_ID);
}

void test1_link_set_direction() {
  Link *link;

  link = link_create(1);
  PRINT_TEST_RESULT(link_set_direction(link, E) == OK);
  link_destroy(link);
}

void test2_link_set_direction() {
  PRINT_TEST_RESULT(link_set_direction(NULL, E) == ERROR);
}

void test1_link_get_direction() {
  Link *link;

  link = link_create(1);
  link_set_direction(link, W);
  PRINT_TEST_RESULT(link_get_direction(link) == W);
  link_destroy(link);
}

void test2_link_get_direction() {
  PRINT_TEST_RESULT(link_get_direction(NULL) == NO_DIR);
}

void test1_link_set_open() {
  Link *link;

  link = link_create(1);
  PRINT_TEST_RESULT(link_set_open(link, TRUE) == OK);
  link_destroy(link);
}

void test2_link_set_open() {
  PRINT_TEST_RESULT(link_set_open(NULL, TRUE) == ERROR);
}

void test1_link_get_open() {
  Link *link;

  link = link_create(1);
  link_set_open(link, TRUE);
  PRINT_TEST_RESULT(link_get_open(link) == TRUE);
  link_destroy(link);
}

void test2_link_get_open() {
  Link *link;

  link = link_create(1);
  link_set_open(link, FALSE);
  PRINT_TEST_RESULT(link_get_open(link) == FALSE);
  link_destroy(link);
}

void test3_link_get_open() {
  PRINT_TEST_RESULT(link_get_open(NULL) == FALSE);
}
