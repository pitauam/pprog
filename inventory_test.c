/**
 * @brief It tests the inventory module
 *
 * @file inventory_test.c
 * @author Santiago Pita
 * @version 1
 * @date 28-03-2026
 */

#include <stdio.h>
#include <stdlib.h>

#include "inventory.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 19

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Inventory:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_inventory_create();
  if (all || test == 2) test2_inventory_create();
  if (all || test == 3) test1_inventory_set_max_obj();
  if (all || test == 4) test2_inventory_set_max_obj();
  if (all || test == 5) test1_inventory_get_max_obj();
  if (all || test == 6) test2_inventory_get_max_obj();
  if (all || test == 7) test1_inventory_add_object();
  if (all || test == 8) test2_inventory_add_object();
  if (all || test == 9) test3_inventory_add_object();
  if (all || test == 10) test4_inventory_add_object();
  if (all || test == 11) test1_inventory_remove_object();
  if (all || test == 12) test2_inventory_remove_object();
  if (all || test == 13) test1_inventory_is_empty();
  if (all || test == 14) test2_inventory_is_empty();
  if (all || test == 15) test1_inventory_get_object_id();
  if (all || test == 16) test1_inventory_find_object();
  if (all || test == 17) test2_inventory_find_object();
  if (all || test == 18) test1_inventory_get_n_objects();
  if (all || test == 19) test2_inventory_get_n_objects();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_inventory_create() {
  Inventory *inventory;

  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory != NULL);
  inventory_destroy(inventory);
}

void test2_inventory_create() {
  Inventory *inventory;

  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory_get_max_obj(inventory) == MAX_OBJ);
  inventory_destroy(inventory);
}

void test1_inventory_set_max_obj() {
  Inventory *inventory;

  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory_set_max_obj(inventory, 4) == OK);
  inventory_destroy(inventory);
}

void test2_inventory_set_max_obj() {
  PRINT_TEST_RESULT(inventory_set_max_obj(NULL, 4) == ERROR);
}

void test1_inventory_get_max_obj() {
  Inventory *inventory;

  inventory = inventory_create();
  inventory_set_max_obj(inventory, 4);
  PRINT_TEST_RESULT(inventory_get_max_obj(inventory) == 4);
  inventory_destroy(inventory);
}

void test2_inventory_get_max_obj() {
  PRINT_TEST_RESULT(inventory_get_max_obj(NULL) == -1);
}

void test1_inventory_add_object() {
  Inventory *inventory;

  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory_add_object(inventory, 10) == OK);
  inventory_destroy(inventory);
}

void test2_inventory_add_object() {
  PRINT_TEST_RESULT(inventory_add_object(NULL, 10) == ERROR);
}

void test3_inventory_add_object() {
  Inventory *inventory;

  inventory = inventory_create();
  inventory_add_object(inventory, 10);
  PRINT_TEST_RESULT(inventory_add_object(inventory, 10) == ERROR);
  inventory_destroy(inventory);
}

void test4_inventory_add_object() {
  Inventory *inventory;

  inventory = inventory_create();
  inventory_add_object(inventory, 10);
  inventory_add_object(inventory, 20);
  PRINT_TEST_RESULT(inventory_add_object(inventory, 30) == ERROR);
  inventory_destroy(inventory);
}

void test1_inventory_remove_object() {
  Inventory *inventory;

  inventory = inventory_create();
  inventory_add_object(inventory, 10);
  PRINT_TEST_RESULT(inventory_remove_object(inventory, 10) == OK);
  inventory_destroy(inventory);
}

void test2_inventory_remove_object() {
  Inventory *inventory;

  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory_remove_object(inventory, 10) == ERROR);
  inventory_destroy(inventory);
}

void test1_inventory_is_empty() {
  Inventory *inventory;

  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory_is_empty(inventory) == TRUE);
  inventory_destroy(inventory);
}

void test2_inventory_is_empty() {
  Inventory *inventory;

  inventory = inventory_create();
  inventory_add_object(inventory, 10);
  PRINT_TEST_RESULT(inventory_is_empty(inventory) == FALSE);
  inventory_destroy(inventory);
}

void test1_inventory_get_object_id() {
  Inventory *inventory;

  inventory = inventory_create();
  inventory_add_object(inventory, 10);
  PRINT_TEST_RESULT(inventory_get_object_id(inventory, 0) == 10);
  inventory_destroy(inventory);
}

void test1_inventory_find_object() {
  Inventory *inventory;

  inventory = inventory_create();
  inventory_add_object(inventory, 10);
  PRINT_TEST_RESULT(inventory_find_object(inventory, 10) == TRUE);
  inventory_destroy(inventory);
}

void test2_inventory_find_object() {
  Inventory *inventory;

  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory_find_object(inventory, 10) == FALSE);
  inventory_destroy(inventory);
}

void test1_inventory_get_n_objects() {
  Inventory *inventory;

  inventory = inventory_create();
  inventory_add_object(inventory, 10);
  inventory_add_object(inventory, 20);
  PRINT_TEST_RESULT(inventory_get_n_objects(inventory) == 2);
  inventory_destroy(inventory);
}

void test2_inventory_get_n_objects() {
  PRINT_TEST_RESULT(inventory_get_n_objects(NULL) == -1);
}
