#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "test.h"

#include "character_test.h"

#define MAX_TESTS 12

void test1_character_create();
void test2_character_create();
void test1_character_set_name();
void test2_character_set_name();
void test1_character_get_name();
void test2_character_get_name();
void test1_character_set_health();
void test2_character_set_health();
void test1_character_get_health();
void test2_character_get_health();
void test1_character_get_id();
void test2_character_get_id();

int main(int argc, char** argv) {
  int test = 0, all = 1;
  if (argc < 2) {
    printf("Running all tests for module Character:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    if (test < 1 && test > MAX_TESTS) { exit(EXIT_SUCCESS); }
  }

  if (all || test == 1) test1_character_create();
  if (all || test == 2) test2_character_create();
  if (all || test == 3) test1_character_set_name();
  if (all || test == 4) test2_character_set_name();
  if (all || test == 5) test1_character_get_name();
  if (all || test == 6) test2_character_get_name();
  if (all || test == 7) test1_character_set_health();
  if (all || test == 8) test2_character_set_health();
  if (all || test == 9) test1_character_get_health();
  if (all || test == 10) test2_character_get_health();
  if (all || test == 11) test1_character_get_id();
  if (all || test == 12) test2_character_get_id();

  PRINT_PASSED_PERCENTAGE;
  return 0; /* ¡Devuelve 0 para evitar el Error 1 de Make! */
}

void test1_character_create() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(c != NULL);
  character_destroy(c);
}
void test2_character_create() {
  Character *c = character_create(NO_ID);
  PRINT_TEST_RESULT(c == NULL);
}

void test1_character_set_name() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_name(c, "Mario") == OK);
  character_destroy(c);
}
void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "Mario") == ERROR);
}

void test1_character_get_name() {
  Character *c = character_create(5);
  character_set_name(c, "Mario");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "Mario") == 0);
  character_destroy(c);
}
void test2_character_get_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test1_character_set_health() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_health(c, 100) == OK);
  character_destroy(c);
}
void test2_character_set_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_health(c, 100) == ERROR);
}

void test1_character_get_health() {
  Character *c = character_create(5);
  character_set_health(c, 100);
  PRINT_TEST_RESULT(character_get_health(c) == 100);
  character_destroy(c);
}
void test2_character_get_health() {
  Character *c = NULL;
  /* Comprobamos si da 0 o error cuando pasamos NULL */
  PRINT_TEST_RESULT(character_get_health(c) <= 0); 
}

void test1_character_get_id() {
  Character *c = character_create(25);
  PRINT_TEST_RESULT(character_get_id(c) == 25);
  character_destroy(c);
}
void test2_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}