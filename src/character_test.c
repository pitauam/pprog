/**
 * @brief Tests the character module
 *
 * @file character_test.c
 * @author Santiago Pita and Marta López
 * @version 1
 * @date 07-05-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "test.h"

#include "character_test.h"

#define MAX_TESTS 37

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
  if (all || test == 13) test1_character_set_following();
  if (all || test == 14) test2_character_set_following();
  if (all || test == 15) test3_character_set_following();
  if (all || test == 16) test1_character_get_following();
  if (all || test == 17) test2_character_get_following();
  if (all || test == 18) test1_character_set_friendly();
  if (all || test == 19) test2_character_set_friendly();
  if (all || test == 20) test1_character_get_friendly();
  if (all || test == 21) test2_character_get_friendly();
  if (all || test == 22) test1_character_set_message();
  if (all || test == 23) test2_character_set_message();
  if (all || test == 24) test1_character_get_message();
  if (all || test == 25) test2_character_get_message();
  if (all || test == 26) test1_character_set_description();
  if (all || test == 27) test2_character_set_description();
  if (all || test == 28) test1_character_get_description();
  if (all || test == 29) test2_character_get_description();
  if (all || test == 30) test1_character_set_strength();
  if (all || test == 31) test2_character_set_strength();
  if (all || test == 32) test1_character_get_strength();
  if (all || test == 33) test2_character_get_strength();
  if (all || test == 34) test1_character_set_armor();
  if (all || test == 35) test2_character_set_armor();
  if (all || test == 36) test1_character_get_armor();
  if (all || test == 37) test2_character_get_armor();


  PRINT_PASSED_PERCENTAGE;
  return 0;
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
  PRINT_TEST_RESULT(character_set_name(c, "Alberto") == OK);
  character_destroy(c);
}
void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "Pepe") == ERROR);
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
  PRINT_TEST_RESULT(character_set_health(c, 15) == OK);
  character_destroy(c);
}
void test2_character_set_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_health(c, 100) == ERROR);
}

void test1_character_get_health() {
  Character *c = character_create(5);
  character_set_health(c, 15);
  PRINT_TEST_RESULT(character_get_health(c) == 15);
  character_destroy(c);
}
void test2_character_get_health() {
  Character *c = NULL;
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

void test1_character_set_following() {
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_following(c, 3) == OK);
    character_destroy(c);
}

void test2_character_set_following() {
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_following(c, 3) == ERROR);
}

void test3_character_set_following() {
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_following(c, -1) == ERROR); 
    character_destroy(c);
}

void test1_character_get_following() {
    Character *c = character_create(1);
    character_set_following(c, 10);
    PRINT_TEST_RESULT(character_get_following(c) == 10);
    character_destroy(c);
}

void test2_character_get_following() {
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_following(c) == NO_ID);
}

void test1_character_set_friendly() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK);
  character_destroy(c);
}
void test2_character_set_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
}

void test1_character_get_friendly() {
  Character *c = character_create(5);
  character_set_friendly(c, TRUE);
  PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
  character_destroy(c);
}
void test2_character_get_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_friendly(c) == FALSE);
}

void test1_character_set_message() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_message(c, "Hola") == OK);
  character_destroy(c);
}
void test2_character_set_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_message(c, "Hola") == ERROR);
}

void test1_character_get_message() {
  Character *c = character_create(5);
  character_set_message(c, "Hola");
  PRINT_TEST_RESULT(strcmp(character_get_message(c), "Hola") == 0);
  character_destroy(c);
}
void test2_character_get_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}

void test1_character_set_description() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_description(c, "^M*") == OK);
  character_destroy(c);
}
void test2_character_set_description() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_description(c, "^M*") == ERROR);
}

void test1_character_get_description() {
  Character *c = character_create(5);
  character_set_description(c, "^M*");
  PRINT_TEST_RESULT(strcmp(character_get_description(c), "^M*") == 0);
  character_destroy(c);
}
void test2_character_get_description() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_description(c) == NULL);
}

void test1_character_set_strength(){
  Character *p = character_create(5);
  PRINT_TEST_RESULT(character_set_strength(p, 10)==OK);
  character_destroy(p);
}

void test2_character_set_strength(){
  Character *p = character_create(5);
  PRINT_TEST_RESULT(character_set_strength(NULL, -5)==ERROR);
  character_destroy(p);
}

void test1_character_get_strength(){
  Character *p = character_create(5);
  character_set_strength(p, 10);
  PRINT_TEST_RESULT(character_get_strength(p) == 10);
  character_destroy(p);
}

void test2_character_get_strength(){
  PRINT_TEST_RESULT(character_get_strength(NULL)==-1);
}

void test1_character_set_armor(){
  Character *p = character_create(5);
  PRINT_TEST_RESULT(character_set_armor(p, 10)==OK);
  character_destroy(p);
}

void test2_character_set_armor(){
  Character *p = character_create(5);
  PRINT_TEST_RESULT(character_set_armor(NULL, -5)==ERROR);
  character_destroy(p);
}

void test1_character_get_armor(){
  Character *p = character_create(5);
  character_set_armor(p, 10);
  PRINT_TEST_RESULT(character_get_armor(p) == 10);
  character_destroy(p);
}

void test2_character_get_armor(){
  PRINT_TEST_RESULT(character_get_armor(NULL)==-1);
}