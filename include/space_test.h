/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Santiago Pita
 * @version 2
 * @date 28-03-2026
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
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();

void test1_space_get_id();
void test2_space_get_id();
void test1_space_get_name();
void test2_space_get_name();

/*
void test1_space_get_object();
void test2_space_get_object();
void test3_space_get_object();
*/
void test1_space_add_object();
void test2_space_add_object();
void test1_space_remove_object();
void test2_space_remove_object();

/*
void test1_space_set_character();
void test2_space_set_character();
void test1_space_get_character();
void test2_space_get_character();
*/

void test1_space_set_gdesc();
void test2_space_set_gdesc();

/*
void test1_space_get_object();
void test2_space_get_object();
*/

#endif