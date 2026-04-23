/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Santiago Pita
 * @version 3
 * @date 23-04-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput == OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output == ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output == ERROR
 */
void test3_space_set_name();

/**
 * @test Test space id getter
 * @pre Space created with valid ID
 * @post Output == ID of the space
 */
void test1_space_get_id();

/**
 * @test Test space id getter
 * @pre Pointer to space = NULL
 * @post Output == NO_ID
 */
void test2_space_get_id();

/**
 * @test Test space name getter
 * @pre Space created and name set
 * @post Output == 0 (string comparison matches)
 */
void test1_space_get_name();

/**
 * @test Test space name getter
 * @pre Pointer to space = NULL
 * @post Output == NULL
 */
void test2_space_get_name();

/**
 * @test Test function to add an object to space
 * @pre Space created, valid object ID
 * @post Output == OK
 */
void test1_space_add_object();

/**
 * @test Test function to add an object to space
 * @pre Pointer to space = NULL
 * @post Output == ERROR
 */
void test2_space_add_object();

/**
 * @test Test function to remove an object from space
 * @pre Space created and object previously added
 * @post Output == OK
 */
void test1_space_remove_object();

/**
 * @test Test function to remove an object from space
 * @pre Space created, but object not in space
 * @post Output == ERROR
 */
void test2_space_remove_object();

/**
 * @test Test setting the graphic description of space
 * @pre Space created, valid gdesc string
 * @post Output == OK
 */
void test1_space_set_gdesc();

/**
 * @test Test setting the graphic description of space
 * @pre Pointer to space = NULL
 * @post Output == ERROR
 */
void test2_space_set_gdesc();

/**
 * @test Test function to add a character to space
 * @pre Space created, valid character ID
 * @post Output == OK
 */
void test1_space_add_character();

/**
 * @test Test function to add a character to space
 * @pre Pointer to space = NULL
 * @post Output == ERROR
 */
void test2_space_add_character();

/**
 * @test Test function to add a character to space
 * @pre Space created, invalid character ID (NO_ID)
 * @post Output == ERROR
 */
void test3_space_add_character();

/**
 * @test Test function to remove a character from space
 * @pre Space created and character previously added
 * @post Output == OK
 */
void test1_space_remove_character();

/**
 * @test Test function to remove a character from space
 * @pre Space created, but character not in space
 * @post Output == ERROR
 */
void test2_space_remove_character();

/**
 * @test Test function to remove a character from space
 * @pre Pointer to space = NULL
 * @post Output == ERROR
 */
void test3_space_remove_character();

/**
 * @test Test function to find a character in space
 * @pre Space created and character previously added
 * @post Output == TRUE
 */
void test1_space_find_character();

/**
 * @test Test function to find a character in space
 * @pre Space created, but character not in space
 * @post Output == FALSE
 */
void test2_space_find_character();

/**
 * @test Test function to find a character in space
 * @pre Pointer to space = NULL
 * @post Output == FALSE
 */
void test3_space_find_character();

/**
 * @test Test getting the number of characters in a space
 * @pre Space created with 2 characters added
 * @post Output == 2
 */
void test1_space_get_n_characters();

/**
 * @test Test getting the number of characters in a space
 * @pre Pointer to space = NULL
 * @post Output == -1
 */
void test2_space_get_n_characters();

/**
 * @test Test function to find an object in space
 * @pre Space created and object previously added
 * @post Output == TRUE
 */
void test1_space_find_object();

/**
 * @test Test function to find an object in space
 * @pre Space created, but object not in space
 * @post Output == FALSE
 */
void test2_space_find_object();

/**
 * @test Test getting the number of objects in a space
 * @pre Space created with 2 objects added
 * @post Output == 2
 */
void test1_space_get_n_objects();

/**
 * @test Test getting the number of objects in a space
 * @pre Pointer to space = NULL
 * @post Output == -1
 */
void test2_space_get_n_objects();

#endif