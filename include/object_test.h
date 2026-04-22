/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author Marta López
 * @version 1.0
 * @date 22-04-2026
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Test object creation
 * @pre Object ID 
 * @post Non NULL pointer to object 
 */
void test1_object_create();

/**
 * @test Test object creation
 * @pre   NO_ID 
 * @post Output == NULL
 */
void test2_object_create();

/**
 * @test Test function for object_name setting
 * @pre String with object name
 * @post Output == OK 
 */
void test1_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre Pointer to object = NULL 
 * @post Output == ERROR
 */
void test2_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre Pointer to object_name = NULL (pointer to object = NON NULL) 
 * @post Output == ERROR
 */
void test3_object_set_name();

/**
 * @test Test function for object_name getting
 * @pre Valid pointer to object
 * @post Output == String with object name
 */
void test1_object_get_name();

/**
 * @test Test function for object_name getting
 * @pre Pointer to object = NULL
 * @post Output == NULL
 */
void test2_object_get_name();

/**
 * @test Test function for object_id getting
 * @pre Valid pointer to object
 * @post Output == Supplied Object Id
 */
void test1_object_get_id();

/**
 * @test Test function for object_id getting
 * @pre Pointer to object = NULL
 * @post Output == NO_ID
 */
void test2_object_get_id();

/**
 * @test Test function for object health setting
 * @pre Valid pointer to object and positive health value
 * @post Output == OK
 */
void test1_set_health();

/**
 * @test Test function for object health setting
 * @pre NULL object pointer
 * @post Output == ERROR
 */
void test2_set_health();

/**
 * @test Test function  for getting object health
 * @pre Object with initialized health
 * @post Output == set health value
 */
void test1_get_health();

/**
 * @test Test function for getting object health
 * @pre NULL object pointer
 * @post Output == ERROR value
 */
void test2_get_health();

/**
 * @test Test function for object movable setting
 * @pre Valid pointer to object and movable value
 * @post Output == OK
 */
void test1_set_movable();

/**
 * @test Test function for object movable setting
 * @pre NULL object pointer
 * @post Output == ERROR
 */
void test2_set_movable();

/**
 * @test Test function for getting object movable
 * @pre Object with initialized movable
 * @post Output == set movable value
 */
void test1_get_movable();

/**
 * @test Test function for getting object movable
 * @pre NULL object pointer
 * @post Output == FALSE
 */
void test2_get_movable();

/**
 * @test Test function for object dependency setting
 * @pre Valid pointer to object and dependency id
 * @post Output == OK
 */
void test1_set_dependency();

/**
 * @test Test function for object dependency setting
 * @pre NULL object pointer

 * @post Output == ERROR
 */
void test2_set_dependency();

/**
 * @test Test function for getting object dependency
 * @pre Object with initialized dependency
 * @post Output == set dependency id
 */
void test1_get_dependency();

/**
 * @test Test function for getting object dependency
 * @pre NULL object pointer
 * @post Output ==  NO_ID
 */
void test2_get_dependency();

/**
 * @test Test object set open
 * @pre object open
 * @post Output == open
 */
void test1_object_set_open();

/**
 * @test Test object set open
 * @pre object open
 * @post Output == ERROR
 */
void test2_object_set_open();

/**
 * @test Test object get open
 * @pre object open
 * @post Output == open
 */
void test1_object_get_open();

/**
 * @test Test object get open
 * @pre object closed
 * @post Output == closed
 */
void test2_object_get_open();

/**
 * @test Test object get open
 * @pre object NULL
 * @post Output == closed
 */
void test3_object_get_open();

#endif