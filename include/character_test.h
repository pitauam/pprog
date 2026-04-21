/** @brief It declares the tests for the character module
 * @file character_test.h
 * @author Santiago Pita and Marta López
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

/**
 * @test Test function for character_friendly setting
 * @pre Valid pointer to character
 * @post Output == OK
 */
void test1_character_set_friendly();

/**
 * @test Test function for character_friendly setting
 * @pre Pointer to character = NULL
 * @post Output == ERROR
 */
void test2_character_set_friendly();

/**
 * @test Test function for checking if character is friendly
 * @pre Valid pointer to character set as friendly
 * @post Output == TRUE
 */
void test1_character_get_friendly();

/**
 * @test Test function for checking if character is friendly
 * @pre Pointer to character = NULL
 * @post Output == FALSE
 */
void test2_character_get_friendly();

/**
 * @test Test function for character_message setting
 * @pre Valid pointer to character and valid string
 * @post Output == OK
 */
void test1_character_set_message();

/**
 * @test Test function for character_message setting
 * @pre Pointer to character = NULL
 * @post Output == ERROR
 */
void test2_character_set_message();

/**
 * @test Test function for character_message getting
 * @pre Valid pointer to character with a message set
 * @post Output == 0 (strcmp matches the string)
 */
void test1_character_get_message();

/**
 * @test Test function for character_message getting
 * @pre Pointer to character = NULL
 * @post Output == NULL
 */
void test2_character_get_message();

/**
 * @test Test function for character_description setting
 * @pre Valid pointer to character and valid string
 * @post Output == OK
 */
void test1_character_set_description();

/**
 * @test Test function for character_description setting
 * @pre Pointer to character = NULL
 * @post Output == ERROR
 */
void test2_character_set_description();

/**
 * @test Test function for character_description getting
 * @pre Valid pointer to character with a description set
 * @post Output == 0 (strcmp matches the string)
 */
void test1_character_get_description();

/**
 * @test Test function for character_description getting
 * @pre Pointer to character = NULL
 * @post Output == NULL
 */
void test2_character_get_description();

#endif