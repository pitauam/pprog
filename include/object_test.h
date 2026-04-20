/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author Alexander
 * @version 1.0
 * @date 07-04-2026
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
 * @pre NO_ID 
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

#endif