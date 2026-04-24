/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Profesores Pprog, Paula de la Fuente, Santiago Pita
 * @version 0.0 
 * @date 24-4-2026
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "space.h"
#include "space_test.h"
#include "set.h"
#include "test.h"

#define MAX_TESTS 37

/** 
 * @brief Main function for SPACE unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }



  if (all || test == 1) test1_space_create();
  if (all || test == 2) test2_space_create();
  if (all || test == 3) test1_space_set_name();
  if (all || test == 4) test2_space_set_name();
  if (all || test == 5) test3_space_set_name();
  if (all || test == 6) test1_space_get_id();
  if (all || test == 7) test2_space_get_id();
  if (all || test == 8) test1_space_get_name();
  if (all || test == 9) test2_space_get_name();
  if (all || test == 10) test1_space_add_object();
  if (all || test == 11) test2_space_add_object();
  if (all || test == 12) test1_space_remove_object();
  if (all || test == 13) test2_space_remove_object();
  if (all || test == 14) test1_space_find_object();
  if (all || test == 15) test2_space_find_object();
  if (all || test == 16) test1_space_set_gdesc();
  if (all || test == 17) test2_space_set_gdesc();
  if (all || test == 18) test1_space_set_discovered();
  if (all || test == 19) test2_space_set_discovered();
  if (all || test == 20) test1_space_is_discovered();
  if (all || test == 21) test2_space_is_discovered();
  if (all || test == 22) test3_space_set_gdesc();
  if (all || test == 23) test1_space_get_gdesc_line();
  if (all || test == 24) test2_space_get_gdesc_line();
  if (all || test == 25) test3_space_get_gdesc_line();
  if (all || test == 26) test4_space_get_gdesc_line();
  if (all || test == 27) test1_space_add_character();
  if (all || test == 28) test2_space_add_character();
  if (all || test == 29) test3_space_add_character();
  if (all || test == 30) test1_space_remove_character();
  if (all || test == 31) test2_space_remove_character();
  if (all || test == 32) test3_space_remove_character();
  if (all || test == 33) test1_space_find_character();
  if (all || test == 34) test2_space_find_character();
  if (all || test == 35) test3_space_find_character();
  if (all || test == 36) test1_space_get_n_characters();
  if (all || test == 37) test2_space_get_n_characters();



  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_space_create() {
  int result;
  Space *s;
  s = space_create(5);
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

void test2_space_create() {
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

void test1_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "espacio") == OK);
  space_destroy(s);
}

void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "espacio") == ERROR);
}

void test3_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_add_object() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_add_object(s, 10) == OK);
  space_destroy(s);
}
void test2_space_add_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_object(s, 10) == ERROR);
}
void test1_space_remove_object() {
  Space *s = space_create(1);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_remove_object(s, 10) == OK);
  space_destroy(s);
}
void test2_space_remove_object() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_remove_object(s, 10) == ERROR); /* Delete what doesn't exist. */
  space_destroy(s);
}
void test1_space_find_object() {
  Space *s = space_create(1);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_find_object(s, 10) == TRUE);
  space_destroy(s);
}
void test2_space_find_object() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_find_object(s, 10) == FALSE);
  space_destroy(s);
}


void test1_space_set_gdesc() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_gdesc(s, "TestDesc") == OK);
  space_destroy(s);
}
void test2_space_set_gdesc() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_gdesc(s, "TestDesc") == ERROR); /* Error because of line out of range. */
  space_destroy(s);
}

/*new test3*/
void test3_space_set_gdesc() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_gdesc(s, NULL) == ERROR); /* Error because of line out of range. */
  space_destroy(s);
}


void test1_space_get_name() {
  Space *s;
  s = space_create(1);
  space_set_name(s, "espacio");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "espacio") == 0);
  space_destroy(s);
}

void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}



void test1_space_get_id() {
  Space *s;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_set_discovered() {
    Space *s = space_create(5);
    PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == OK);
    space_destroy(s);
}

void test2_space_set_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == ERROR);
}

void test1_space_is_discovered() {
  Space *s = space_create(5);
  space_set_discovered(s, TRUE);
  PRINT_TEST_RESULT(space_is_discovered(s) == TRUE);
  space_destroy(s);
}

void test2_space_is_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_is_discovered(s) == FALSE);
}


void test1_space_get_gdesc_line() {
  Space* s = space_create(5);
  space_set_gdesc(s, "***");
  PRINT_TEST_RESULT(strcmp (space_get_gdesc_line(s, 0), "***")==0);
  space_destroy(s);
}


void test2_space_get_gdesc_line() {
  Space* s = space_create(5);
  space_set_gdesc(s, "***");
  PRINT_TEST_RESULT(space_get_gdesc_line(s, -1)==NULL);
  space_destroy(s);
}


void test3_space_get_gdesc_line() {
  Space* s = NULL;
  PRINT_TEST_RESULT(space_get_gdesc_line(s, 1)==NULL);
  space_destroy(s);
}


void test4_space_get_gdesc_line() {
  Space* s = space_create(5);
  space_set_gdesc(s, "***");
  PRINT_TEST_RESULT(space_get_gdesc_line(s, GDESC_HEIGHT )==NULL);
  space_destroy(s);
}


void test1_space_add_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_add_character(s, 5) == OK);
  space_destroy(s);
}

void test2_space_add_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_character(s, 5) == ERROR);
}

void test3_space_add_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_add_character(s, NO_ID) == ERROR);
  space_destroy(s);
}

void test1_space_remove_character() {
  Space *s = space_create(1);
  space_add_character(s, 5);
  PRINT_TEST_RESULT(space_remove_character(s, 5) == OK);
  space_destroy(s);
}

void test2_space_remove_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_remove_character(s, 5) == ERROR);
  space_destroy(s);
}

void test3_space_remove_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_remove_character(s, 5) == ERROR);
}

void test1_space_find_character() {
  Space *s = space_create(1);
  space_add_character(s, 5);
  PRINT_TEST_RESULT(space_find_character(s, 5) == TRUE);
  space_destroy(s);
}

void test2_space_find_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_find_character(s, 5) == FALSE);
  space_destroy(s);
}

void test3_space_find_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_find_character(s, 5) == FALSE);
}

void test1_space_get_n_characters() {
  Space *s = space_create(1);
  space_add_character(s, 5);
  space_add_character(s, 6);
  PRINT_TEST_RESULT(space_get_n_characters(s) == 2);
  space_destroy(s);
}

void test2_space_get_n_characters() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_n_characters(s) == -1);
}


