/** 
 * @brief It tests player module
 * 
 * @file player_test.c
 * @author Paula de la Fuente
 * @version 0.0 
 * @date 24-03-2025
 * @copyright GNU Public License
 */


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 45


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
  if (all || test == 7) test1_player_set_gdesc();
  if (all || test == 8) test2_player_set_gdesc();
  if (all || test == 9) test1_player_get_gdesc();
  if (all || test == 10) test2_player_get_gdesc();
  if (all || test == 11) test1_player_set_health();
  if (all || test == 12) test2_player_set_health();
  if (all || test == 13) test1_player_get_health();
  if (all || test == 14) test2_player_get_health();
  if (all || test == 15) test1_player_get_id();
  if (all || test == 16) test2_player_get_id();
  if (all || test == 17) test1_player_set_location();
  if (all || test == 18) test2_player_set_location();
  if (all || test == 19) test3_player_set_location();
  if (all || test == 20) test1_player_get_location();
  if (all || test == 21) test2_player_get_location();
  if (all || test == 22) test1_player_add_object_to_backpack();
  if (all || test == 23) test2_player_add_object_to_backpack();
  if (all || test == 24) test3_player_add_object_to_backpack();
  if (all || test == 25) test4_player_add_object_to_backpack();
  if (all || test == 26) test5_player_add_object_to_backpack();
  if (all || test == 27) test1_player_remove_object_of_backpack();
  if (all || test == 28) test2_player_remove_object_of_backpack();
  if (all || test == 29) test3_player_remove_object_of_backpack();
  if (all || test == 30) test4_player_remove_object_of_backpack();
  if (all || test == 31) test1_player_has_object();
  if (all || test == 32) test2_player_has_object();
  if (all || test == 33) test3_player_has_object();
  if (all || test == 34) test4_player_has_object();
  if (all || test == 35) test1_player_get_backpack();
  if (all || test == 36) test2_player_get_backpack();
  if (all || test == 37) test1_player_set_backpack();
  if (all || test == 38) test2_player_set_backpack();
  if (all || test == 39) test3_player_set_backpack();
  if (all || test == 40) test1_player_backpack_is_full();
  if (all || test == 41) test2_player_backpack_is_full();
  if (all || test == 42) test3_player_backpack_is_full();
  if (all || test == 43) test1_player_get_object_from_backpack();
  if (all || test == 44) test2_player_get_object_from_backpack();
  if (all || test == 45) test3_player_get_object_from_backpack();

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

void test3_player_set_location() {
    Player* p = NULL;
    PRINT_TEST_RESULT(player_set_location(p, 2)==ERROR);
  }


void test1_player_get_location() {
  Player* p = player_create(5);
  player_set_location(p, 2);
  PRINT_TEST_RESULT(player_get_location(p)==2);
  player_destroy(p);  
}

void test2_player_get_location() {
  Player* p = NULL;
  PRINT_TEST_RESULT(player_get_location(p)==NO_ID);
}

void test1_player_add_object_to_backpack() {
  Player* p = player_create(5);
  PRINT_TEST_RESULT(player_add_object_to_backpack(p, 2)==OK);
  player_destroy(p);
}

void test2_player_add_object_to_backpack() {
  Player* p = NULL;
  PRINT_TEST_RESULT(player_add_object_to_backpack(p, 2)==ERROR);
}

void test3_player_add_object_to_backpack() {
  Player* p = player_create(5);
  PRINT_TEST_RESULT(player_add_object_to_backpack(p, NO_ID)==ERROR);
  player_destroy(p);
}

void test4_player_add_object_to_backpack() { /* Object repetition. */
  Player* p = player_create(5);
  player_add_object_to_backpack(p, 2);
  PRINT_TEST_RESULT(player_add_object_to_backpack(p, 2)==ERROR);
  player_destroy(p);
}

void test5_player_add_object_to_backpack() { /*Without space. */
  Player* p = player_create(5);
  int i;
  for(i=0 ; i<MAX_OBJS ; i++){
    player_add_object_to_backpack(p, i);
  }
  PRINT_TEST_RESULT(player_add_object_to_backpack(p, MAX_OBJS)==ERROR);
  player_destroy(p);
}

void test1_player_remove_object_of_backpack() {
  Player* p = player_create(5);
  player_add_object_to_backpack(p, 2);
  PRINT_TEST_RESULT(player_remove_object_from_backpack(p, 2)==OK);
  player_destroy(p);
}

void test2_player_remove_object_of_backpack() {
  Player* p = NULL;
  PRINT_TEST_RESULT(player_remove_object_from_backpack(p, 2)==ERROR);
}

void test3_player_remove_object_of_backpack() {
  Player* p = player_create(5);
  PRINT_TEST_RESULT(player_remove_object_from_backpack(p, NO_ID)==ERROR);
  player_destroy(p);
}

void test4_player_remove_object_of_backpack() { /*no that obj*/
  Player* p = player_create(5);
  player_add_object_to_backpack(p, 2);
  PRINT_TEST_RESULT(player_remove_object_from_backpack(p, 1)==ERROR);
  player_destroy(p);
}



void test1_player_has_object() {
  Player *p = player_create(2);
  player_add_object_to_backpack(p, 5);
  PRINT_TEST_RESULT(player_has_object(p, 5) == TRUE);
  player_destroy(p);
}

void test2_player_has_object() {
  Player *p = player_create(2);
  PRINT_TEST_RESULT(player_has_object(p, 5) == FALSE);
  player_destroy(p);
}

void test3_player_has_object() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_has_object(p, 5) == FALSE);
}

void test4_player_has_object() {
  Player *p = player_create(2);
  PRINT_TEST_RESULT(player_has_object(p, NO_ID) == FALSE);
  player_destroy(p);
}

void test1_player_get_backpack() {
  Player *p = player_create(2);
  PRINT_TEST_RESULT(player_get_backpack(p)!=NULL);
  player_destroy(p);
}


void test2_player_get_backpack() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_backpack(p)==NULL);
}


void test1_player_set_backpack() {
  Inventory* inv=NULL;
  Player *p = player_create(2);
  inv = inventory_create();
  PRINT_TEST_RESULT(player_set_backpack(p, inv)==OK);
}

void test2_player_set_backpack() {
  Inventory* inv=NULL;
  Player *p = NULL;
  inv = inventory_create();
  PRINT_TEST_RESULT(player_set_backpack(p, inv)==ERROR);
}

void test3_player_set_backpack() {
  Inventory* inv=NULL;
  Player *p = player_create(2);
  PRINT_TEST_RESULT(player_set_backpack(p, inv)==ERROR);
}


void test1_player_backpack_is_full() {
  int i;
  Player *p = player_create(2);
  for(i=0; i<MAX_OBJS ; i++){
    player_add_object_to_backpack(p, i);
  }
  PRINT_TEST_RESULT(player_backpack_is_full(p)==TRUE);
  player_destroy(p);

}

void test2_player_backpack_is_full() {
  Player *p = player_create(2);
  player_add_object_to_backpack(p, 5);
  PRINT_TEST_RESULT(player_backpack_is_full(p)==FALSE);
  player_destroy(p);

}

void test3_player_backpack_is_full() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_backpack_is_full(p)==TRUE);
  player_destroy(p);

}




void test1_player_get_object_from_backpack() {
  Player *p = player_create(2);
  player_add_object_to_backpack(p, 5);  
  PRINT_TEST_RESULT(player_get_object_from_backpack(p, 0)==5);
  player_destroy(p);
}

void test2_player_get_object_from_backpack() {
  Player *p = player_create(2);
  player_add_object_to_backpack(p, 5);  
  PRINT_TEST_RESULT(player_get_object_from_backpack(p, -1)==NO_ID);
  player_destroy(p);
}


void test3_player_get_object_from_backpack() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_object_from_backpack(p, 1)==NO_ID);
  player_destroy(p);
}




void test1_player_create() {
  Player* p = player_create(5);
  PRINT_TEST_RESULT(p != NULL);
  player_destroy(p);
}

void test2_player_create() {
  Player* p = player_create(NO_ID);
  PRINT_TEST_RESULT(p == NULL);
}


void test1_player_set_name() {
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_set_name(p, "Player") == OK);
  player_destroy(p);
}

void test2_player_set_name() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_name(p, "Player") == ERROR);
}


void test1_player_get_name() {
  Player *p = player_create(5);
  player_set_name(p, "Player");
  PRINT_TEST_RESULT(strcmp(player_get_name(p), "Player") == 0);
  player_destroy(p);
}

void test2_player_get_name() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_name(p) == NULL);
}


void test1_player_set_gdesc() {
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_set_gdesc(p, "^P*") == OK);
  player_destroy(p);
}

void test2_player_set_gdesc() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_gdesc(p, "^M*") == ERROR);
}


void test1_player_get_gdesc() {
  Player *p = player_create(5);
  player_set_gdesc(p, "^M*");
  PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), "^M*") == 0);
  player_destroy(p);
}

void test2_player_get_gdesc() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_gdesc(p) == NULL);
}


void test1_player_set_health() {
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_set_health(p, 10) == OK);
  player_destroy(p);
}

void test2_player_set_health() {
  Player *p = player_create(5);
  PRINT_TEST_RESULT(player_set_health(p, -5) == ERROR); /* Negative life */
  player_destroy(p);
}


void test1_player_get_health() {
  Player *p = player_create(5);
  player_set_health(p, 10);
  PRINT_TEST_RESULT(player_get_health(p) == 10);
  player_destroy(p);
}

void test2_player_get_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_health(p) == -1);
}


void test1_player_get_id() {
  Player *p;
  p = player_create(25);
  PRINT_TEST_RESULT(player_get_id(p) == 25);
  player_destroy(p);
}

void test2_player_get_id() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
}