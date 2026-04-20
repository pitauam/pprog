/** @brief It declares the tests for the character module
 * @file character_test.h
 * @author Santiago Pita
 * @version 1
 * @date 2026
 */

#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

/**
 * @test Test character creation
 * @pre Character ID
 * @post Non NULL pointer to character
 */
void test1_character_create();

/*comentario de prueba*/

/**
 * @test Test character creation
 * @pre Character ID is NO_ID
 * @post NULL pointer to character
 */
void test2_character_create();

/**
 * @test Test setting character name
 * @pre Pointer to character is valid
 * @post Output == OK
 */
void test1_character_set_name();

/**
 * @test Test setting character name
 * @pre Pointer to character is NULL
 * @post Output == ERROR
 */
void test2_character_set_name();

/**
 * @test Test getting character name
 * @pre Pointer to character is valid and name is set
 * @post Output == "Mario"
 */
void test1_character_get_name();

/**
 * @test Test getting character name
 * @pre Pointer to character is NULL
 * @post Output == NULL
 */
void test2_character_get_name();

/**
 * @test Test setting character health
 * @pre Pointer to character is valid
 * @post Output == OK
 */
void test1_character_set_health();

/**
 * @test Test setting character health
 * @pre Pointer to character is NULL
 * @post Output == ERROR
 */
void test2_character_set_health();

/**
 * @test Test getting character health
 * @pre Pointer to character is valid and health is set to 100
 * @post Output == 100
 */
void test1_character_get_health();

/**
 * @test Test getting character health
 * @pre Pointer to character is NULL
 * @post Output is less than or equal to 0
 */
void test2_character_get_health();

/**
 * @test Test getting character ID
 * @pre Pointer to character is valid with ID 25
 * @post Output == 25
 */
void test1_character_get_id();

/**
 * @test Test getting character ID
 * @pre Pointer to character is NULL
 * @post Output == NO_ID
 */
void test2_character_get_id();

/**
 * @test Test setting character following ID
 * @pre Pointer to character is not NULL
 * @post Output == NO_ID
 */
void test1_character_set_following();

/**
 * @test Test setting character following ID
 * @pre Pointer to character is NULL
 * @post Output == NO_ID
 */
void test2_character_set_following();

/**
 * @test Test setting character following ID
 * @pre Pointer to character is not NULL
 * @post Output == NO_ID
 */
void test3_character_set_following();

/**
 * @test Test setting character following ID
 * @pre Pointer to character is not NULL
 * @post Output == NO_ID
 */
void test1_character_get_following();

/**
 * @test Test setting character following ID
 * @pre Pointer to character is NULL
 * @post Output == NO_ID
 */
void test2_character_get_following();

#endif