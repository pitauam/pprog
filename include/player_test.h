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
 * @test Test function for player description setting
 * @pre Valid pointer to player and valid string
 * @post Output == OK
 */
void test1_player_set_description();

/**
 * @test Test function for player description setting
 * @pre Pointer to player = NULL
 * @post Output == ERROR
 */
void test2_player_set_description();

/**
 * @test Test function for player description getting
 * @pre Valid pointer to player with a gdesc set
 * @post Output == 0 (strcmp matches the string)
 */
void test1_player_get_description();

/**
 * @test Test function for player description getting
 * @pre Pointer to player = NULL
 * @post Output == NULL
 */
void test2_player_get_description();

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
void test1_player_add_object();

/**
 * @test Test adding an object to the backpack of the player
 * @pre Player == NULL and valid object id
 * @post Output == ERROR
 */
void test2_player_add_object();

/**
 * @test Test removing an object from the backpack's player
 * @pre Valid player and  object id inside the backpack
 * @post Output == OK
 */
void test1_player_remove_object();

/**
 * @test Test removing an object from the backpack's player
 * @pre Player = NULL and  valid object id inside the backpack
 * @post Output == ERROR
 */
void test2_player_remove_object();

/**
 * @test Test checking if a player has a specific object
 * @pre Valid player and object id inside its backpack
 * @post Output == TRUE
 */
void test1_player_find_object();

/**
 * @test Test checking if a player has a specific object
 * @pre Valid player and object id that IS NOT inside its backpack
 * @post Output == FALSE
 */
void test2_player_find_object();

/**
 * @test Test checking if a player's inventory is full or not
 * @pre Valid player with a FULL inventory
 * @post Output == TRUE
 */
void test1_player_inventory_full();

/**
 * @test Test checking if a player's inventory is full or not
 * @pre Valid player with a NOT FULL inventory
 * @post Output == FALSE
 */
void test2_player_inventory_full();


/**
 * @test Test getting the object id from the player's object at a specific position
 * @pre Player= NULL and valid index
 * @post Output == NO_ID
 */
void test1_player_get_object_id();

/**
 * @test Test getting the object id from the player's object at a specific position
 * @pre Player= NULL and valid index
 * @post Output == NO_ID
 */
void test2_player_get_object_id();

#endif