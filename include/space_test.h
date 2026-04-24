/**
 * @brief It declares the tests for the space module
 * @file space_test.h
 * @author Santiago Pita
 * @author Samuel Manzorro
 * @author Paula de la Fuente
 * @version 0.0 
 * @date 17-02-2025
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
 * @post Output == OK 
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
 * @pre pointer to space_name = NULL (pointer to space = NON NULL) 
 * @post Output == ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for space_id getting
 * @pre Valid pointer to space
 * @post Output == Supplied Space Id
 */
void test1_space_get_id();

/**
 * @test Test function for space_id getting
 * @pre Pointer to space = NULL
 * @post Output == NO_ID
 */
void test2_space_get_id();

/**
 * @test Test function for space_name getting
 * @pre Valid pointer to space
 * @post Output == String with space name
 */
void test1_space_get_name();

/**
 * @test Test function for space_name getting
 * @pre Pointer to space = NULL
 * @post Output == NULL
 */
void test2_space_get_name();

/**
 * @test Test function for object adding
 * @pre Valid pointer to space and valid object id
 * @post Output == OK
 */
void test1_space_add_object();

/**
 * @test Test function for object adding
 * @pre Pointer to space = NULL
 * @post Output == ERROR
 */
void test2_space_add_object();

/**
 * @test Test function for object deleting
 * @pre Valid pointer to space and existing object id
 * @post Output == OK
 */
void test1_space_remove_object();

/**
 * @test Test function for object deleting
 * @pre Valid pointer to space and non-existing object id
 * @post Output == ERROR
 */
void test2_space_remove_object();

/**
 * @test Test function for checking object presence
 * @pre Valid pointer to space and existing object id
 * @post Output == TRUE
 */
void test1_space_find_object();

/**
 * @test Test function for checking object presence
 * @pre Valid pointer to space and non-existing object id
 * @post Output == FALSE
 */
void test2_space_find_object();

/**
 * @test Test function for character setting
 * @pre Valid pointer to space
 * @post Output == OK
 */
void test1_space_set_character();

/**
 * @test Test function for character setting
 * @pre Pointer to space = NULL
 * @post Output == ERROR
 */
void test2_space_set_character();

/**
 * @test Test function for character getting
 * @pre Valid pointer to space with a character
 * @post Output == Supplied Character Id
 */
void test1_space_get_character();

/**
 * @test Test function for character getting
 * @pre Pointer to space = NULL
 * @post Output == NO_ID
 */
void test2_space_get_character();

/**
 * @test Test function for gdesc setting
 * @pre Valid pointer to space and valid char
 * @post Output == OK
 */
void test1_space_set_gdesc();

/**
 * @test Test function for gdesc setting
 * @pre Space=NULL and valid char
 * @post Output == ERROR
 */
void test2_space_set_gdesc();

/*new test3*/
/**
 * @test Test function for gdesc setting
 * @pre Valid pointer to space and char =NULL
 * @post Output == ERROR
 */
void test3_space_set_gdesc();

/**
 * @test Test function for graphic description getting
 * @pre Valid pointer to space
 * @post Output == "***" the gdesc of the space in line 0
 */
void test1_space_get_gdesc_line();

/**
 * @test Test function for graphic description getting
 * @pre Valid pointer to space
 * @pre Invalid line<0
 * @post Output == NULL
 */
void test2_space_get_gdesc_line();

/**
 * @test Test function for graphic description getting
 * @pre Space = NULL and valid line
 * @post Output == NULL
 */
void test3_space_get_gdesc_line();

/**
 * @test Test function for graphic description getting
 * @pre Valid pointer to space
 * @pre Invalid line > GDESC_HEIGHT
 * @post Output == NULL
 */
void test4_space_get_gdesc_line();


/**
 * @test Test function for space_discovered setting
 * @pre Valid pointer to space
 * @post Output == OK
 */
void test1_space_set_discovered();

/**
 * @test Test function for space_discovered setting
 * @pre Pointer to space = NULL
 * @post Output == ERROR
 */
void test2_space_set_discovered();

/**
 * @test Test function for checking if space is discovered
 * @pre Valid pointer to space set as discovered
 * @post Output == TRUE
 */
void test1_space_is_discovered();

/**
 * @test Test function for checking if space is discovered
 * @pre Pointer to space = NULL
 * @post Output == FALSE
 */
void test2_space_is_discovered();


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

#endif
