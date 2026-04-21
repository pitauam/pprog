/** 
 * @brief It tests player module
 * 
 * @file player_test.c
 * @author Paula de la Fuente and Marta López
 * @version 0.0 
 * @date 21/04/2026
 * @copyright GNU Public License
 */


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 30


/** 
 * @brief Main function for PLAYER unit tests. 
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
    printf("Running all test for module Player:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }



  if (all || test == 1) test1_player_create();
  if (all || test == 2) test2_player_create();
  if (all || test == 3) test1_player_set_name();
  if (all || test == 4) test2_player_set_name();
  if (all || test == 5) test1_player_get_name();
  if (all || test == 6) test2_player_get_name();
  if (all || test == 7) test1_player_set_description();
  if (all || test == 8) test2_player_set_description();
  if (all || test == 9) test1_player_get_description();
  if (all || test == 10) test2_player_get_description();
  if (all || test == 11) test1_player_set_health();
  if (all || test == 12) test2_player_set_health();
  if (all || test == 13) test1_player_get_health();
  if (all || test == 14) test2_player_get_health();
  if (all || test == 15) test1_player_get_id();
  if (all || test == 16) test2_player_get_id();
  if (all || test == 17) test1_player_set_location();
  if (all || test == 18) test2_player_set_location();
  if (all || test == 19) test1_player_get_location();
  if (all || test == 20) test2_player_get_location();
  if (all || test == 21) test1_player_add_object();
  if (all || test == 22) test2_player_add_object();
  if (all || test == 23) test1_player_remove_object();
  if (all || test == 24) test2_player_remove_object();
  if (all || test == 25) test1_player_find_object();
  if (all || test == 26) test2_player_find_object();
  if (all || test == 27) test1_player_inventory_full();
  if (all || test == 28) test2_player_inventory_full();
  if (all || test == 29) test1_player_get_object_id();
  if (all || test == 30) test2_player_get_object_id();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}



void test1_player_set_location() {
    Player* p = player_create(5);
    PRINT_TEST_RESULT(player_set_location(p, 2)==OK);
    player_destroy(p);
  }

void test2_player_set_location() {
    Player* p = player_create(5);
    PRINT_TEST_RESULT(player_set_location(p, NO_ID)==ERROR);
    player_destroy(p);
  }

void test1_player_get_location() {
    Player* p = player_create(5);
    player_set_location(p,2);
    PRINT_TEST_RESULT(player_get_location(p)==2);
    player_destroy(p);
  }

void test1_player_add_object(){
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_add_object(p, 2)==OK);
  player_destroy(p);
}

void test2_player_add_object(){
  PRINT_TEST_RESULT(player_add_object(NULL, 2)==ERROR);
}

void test1_player_remove_object(){
  Player *p = player_create(5);
  player_add_object(p, 2);
  PRINT_TEST_RESULT(player_remove_object(p, 2)==OK);
  player_destroy(p);
}

void test2_player_remove_object(){
  PRINT_TEST_RESULT(player_remove_object(NULL, 2)==ERROR);
}

void test1_player_find_object(){
  Player *p = player_create(2);
  player_add_object(p, 5);
  PRINT_TEST_RESULT(player_find_object(p, 5)==OK);
  player_destroy(p);
}

void test2_player_find_object(){
  Player *p = player_create(2);
  PRINT_TEST_RESULT(player_find_object(p, 5)==ERROR);
  player_destroy(p);
}

void test1_player_inventory_full(){
  Player *p = player_create(2);
  int i;
  for(i=0; i<max_objects; i++){
    player_add_object(p, i);
  }
  PRINT_TEST_RESULT(player_inventory_full(p)==TRUE);
  player_destroy(p);
}

void test2_player_inventory_full(){
  PRINT_TEST_RESULT(player_inventory_full(NULL)==FALSE);
}

void test1_player_get_object_id(){
  Player *p = player_create(2);
  player_add_object(p, 5);
  PRINT_TEST_RESULT(player_get_object_id(p, 0)==5);
  player_destroy(p);
}

void test2_player_get_object_id(){
  PRINT_TEST_RESULT(player_get_object_id(NULL, 1)==NO_ID);
}

void test1_player_set_description(){
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_set_description(p, "^P*")==OK);
  player_destroy(p);
}

void test2_player_set_description(){
  PRINT_TEST_RESULT(player_set_description(NULL, "^M*")==ERROR);
}

void test1_player_get_description(){
  Player *p = player_create(5);
  player_set_description(p, "^M*");
  PRINT_TEST_RESULT(strcmp(player_get_description(p), "^M*") == 0);
  player_destroy(p);
}

void test2_player_get_description(){
  PRINT_TEST_RESULT(player_get_description(NULL)==NULL);
}

void test1_player_set_health(){
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_set_health(p, 10)==OK);
  player_destroy(p);
}

void test2_player_player_set_health(){
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_set_health(NULL, -5)==ERROR);
  player_destroy(p);
}

void test1_player_get_health(){
  Player *p = player_create(5);
  player_player_set_health(p, 10);
  PRINT_TEST_RESULT(player_get_health(p) == 10);
  player_destroy(p);
}

void test2_player_get_health(){
  PRINT_TEST_RESULT(player_get_health(NULL)==-1);
}

test1_player_create(){
  Player *p = player_create(5);
  PRINT_TEST_RESULT(p!=NULL);
  player_destroy(p);
}

test2_player_create(){
  PRINT_TEST_RESULT(player_create(NO_ID)==NULL);
}

test1_player_set_name(){
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_set_name(p, "Player") == OK);
  player_destroy(p);
}

test2_player_set_name(){
  PRINT_TEST_RESULT(player_set_name(NULL, "Player")==ERROR);
}

test1_player_get_name(){
  Player *p = player_create(5);
  player_set_name(p, "Player");
  PRINT_TEST_RESULT(strcmp(player_get_name(p), "Player")==0);
  player_destroy(p);
}

test2_player_get_name(){
  PRINT_TEST_RESULT(player_get_name(NULL)==NULL);
}

void test1_player_get_id() {
  Player *p = player_create(25);
  PRINT_TEST_RESULT(player_get_id(p) == 25);
  player_destroy(p);

}

void test2_player_get_id() {
  
  PRINT_TEST_RESULT(player_get_id(NULL) == NO_ID);
}