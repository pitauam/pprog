/**
 * @brief It declares the tests for the space module
 * @file player_test.h
 * @author Paula de la Fuente
 * @version 0.0 
 * @date 11-04-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Test player creation
 * @pre Valid player ID 
 * @post Non NULL pointer to player 
 */
void test1_player_create();

/**
 * @test Test player creation
 * @pre player ID = NO_ID
 * @post NULL pointer to player
 */
void test2_player_create();

/**
 * @test Test function for player_name setting
 * @pre Valid pointer to player and valid string
 * @post Output == OK 
 */
void test1_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre Pointer to player = NULL 
 * @post Output == ERROR
 */
void test2_player_set_name();

/**
 * @test Test function for player_name getting
 * @pre Valid pointer to player with a name set
 * @post Output == 0 (strcmp matches the string)
 */
void test1_player_get_name();

/**
 * @test Test function for player_name getting
 * @pre Pointer to player = NULL
 * @post Output == NULL
 */
void test2_player_get_name();

/**
 * @test Test function for player_gdesc setting
 * @pre Valid pointer to player and valid string
 * @post Output == OK
 */
void test1_player_set_gdesc();

/**
 * @test Test function for player_gdesc setting
 * @pre Pointer to player = NULL
 * @post Output == ERROR
 */
void test2_player_set_gdesc();

/**
 * @test Test function for player_gdesc getting
 * @pre Valid pointer to player with a gdesc set
 * @post Output == 0 (strcmp matches the string)
 */
void test1_player_get_gdesc();

/**
 * @test Test function for player_gdesc getting
 * @pre Pointer to player = NULL
 * @post Output == NULL
 */
void test2_player_get_gdesc();

/**
 * @test Test function for player_health setting
 * @pre Valid pointer to player and positive health value
 * @post Output == OK
 */
void test1_player_set_health();

/**
 * @test Test function for player_health setting
 * @pre Valid pointer to player and negative health value
 * @post Output == ERROR
 */
void test2_player_set_health();

/**
 * @test Test function for player_health getting
 * @pre Valid pointer to player with health = 10
 * @post Output == 10
 */
void test1_player_get_health();

/**
 * @test Test function for player_health getting
 * @pre Pointer to player = NULL
 * @post Output == -1
 */
void test2_player_get_health();

/**
 * @test Test function for plaeyr_id getting
 * @pre Valid pointer to player
 * @post Output == Supplied Player Id
 */
void test1_player_get_id();

/**
 * @test Test function for player_id getting
 * @pre Pointer to player = NULL
 * @post Output == NO_ID
 */
void test2_player_get_id();

/**
 * @test Test function for player_location setting
 * @pre Valid pointer to player and valid location
 * @post Output == OK 
 */
void test1_player_set_location();

/**
 * @test Test function for player_location setting
 * @pre Valid pointer to player and invalid location(NO_ID)
 * @post Output == ERROR
 */
void test2_player_set_location();

/**
 * @test Test function for player_location setting
 * @pre Pointer to player = NULL 
 * @post Output == ERROR
 */
void test3_player_set_location();

/**
 * @test Test function for player_location getting
 * @pre Valid pointer to player
 * @post Output == 2 (correct location)
 */
void test1_player_get_location();

/**
 * @test Test function for player_location getting
 * @pre Pointer to player = NULL 
 * @post Output == NO_ID
 */
void test2_player_get_location();

/**
 * @test Test adding an object to the backpack of the player
 * @pre Valid player and valid object id
 * @post Output == OK
 */
void test1_player_add_object_to_backpack();

/**
 * @test Test adding an object to the backpack of the player
 * @pre Player == NULL and valid object id
 * @post Output == ERROR
 */
void test2_player_add_object_to_backpack();

/**
 * @test Test adding an object with NO_ID to the backpack of the player
 * @pre Valid player and  object id = NO_ID
 * @post Output == ERROR
 */
void test3_player_add_object_to_backpack();

/**
 * @test Test adding an object which is already in the bakcpack of the player
 * @pre Valid player and the object id already on its backpack
 * @post Output == ERROR
 */
void test4_player_add_object_to_backpack();

/**
 * @test Test adding an object to a full bakcpack of the player
 * @pre Valid player with its backpack filled to maximum capacity and a valid obj id
 * @post Output == ERROR
 */
void test5_player_add_object_to_backpack();


/**
 * @test Test removing an object from the backpack's player
 * @pre Valid player and  object id inside the backpack
 * @post Output == OK
 */
void test1_player_remove_object_of_backpack();

/**
 * @test Test removing an object from the backpack's player
 * @pre Player = NULL and  valid object id inside the backpack
 * @post Output == ERROR
 */
void test2_player_remove_object_of_backpack();

/**
 * @test Test removing an object from the backpack's player
 * @pre valid player and  valid object id = NO_ID
 * @post Output == ERROR
 */
void test3_player_remove_object_of_backpack();

/**
 * @test Test removing an object from the backpack's player without being that object in the backpack
 * @pre valid player and  id of an object that there's not in the backpack
 * @post Output == ERROR
 */
void test4_player_remove_object_of_backpack();


/**
 * @test Test checking if a player has a specific object
 * @pre Valid player and object id inside its backpack
 * @post Output == TRUE
 */
void test1_player_has_object();

/**
 * @test Test checking if a player has a specific object
 * @pre Valid player and object id that IS NOT inside its backpack
 * @post Output == FALSE
 */
void test2_player_has_object();

/**
 * @test Test checking if a player has a specific object
 * @pre Player=NULL and valid object id 
 * @post Output == FALSE
 */
void test3_player_has_object();

/**
 * @test Test checking if a player has a specific object
 * @pre Valid player and object id = NO_ID
 * @post Output == FALSE
 */
void test4_player_has_object();


/**
 * @test Test function for player_backpack getting
 * @pre Valid pointer to player
 * @post Output == NON NULL
 */
void test1_player_get_backpack();

/**
 * @test Test function for player_backpack getting
 * @pre pointer to Player=NULL
 * @post Output == NULL
 */
void test2_player_get_backpack();

/**
 * @test Test function for player_backpack setting
 * @pre Valid pointer to player and valid backpack
 * @post Output == OK 
 */
void test1_player_set_backpack();

/**
 * @test Test function for player_backpack setting
 * @pre Valid pointer to player and  backpack = NULL
 * @post Output == ERROR 
 */
void test2_player_set_backpack();

/**
 * @test Test function for player_backpack setting
 * @pre Player=NULL and valid backpack
 * @post Output == ERROR 
 */
void test3_player_set_backpack();


/**
 * @test Test checking if a player's backpack is full or not
 * @pre Valid player with a FULL backpack
 * @post Output == TRUE
 */
void test1_player_backpack_is_full();

/**
 * @test Test checking if a player's backpack is full or not
 * @pre Valid player with a NOT FULL backpack
 * @post Output == FALSE
 */
void test2_player_backpack_is_full();

/**
 * @test Test checking if a player's backpack is full or not
 * @pre Player==NULL
 * @post Output == TRUE
 */
void test3_player_backpack_is_full();

/**
 * @test Test getting the object id from the player's backpack at a specific position
 * @pre Valid player with an object at position 0 of its backpack, and valid index
 * @post Output == The ID of the inserted object (5)
 */
void test1_player_get_object_from_backpack();

/**
 * @test Test getting the object id from the player's backpack at a specific position
 * @pre Valid player with an object at position 0 of its backpack, and not valid index (index<0)
 * @post Output == NO_ID
 */
void test2_player_get_object_from_backpack();

/**
 * @test Test getting the object id from the player's backpack at a specific position
 * @pre Player= NULL and valid index
 * @post Output == NO_ID
 */
void test3_player_get_object_from_backpack();

#endif