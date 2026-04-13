/** 
 * @brief It declares the tests for the set module
 * @file set_test.h
 * @author Santiago Pita
 * @version 1
 * @date 2026
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test creation of a set
 * @pre Set is successfully created
 * @post Non NULL pointer to set
 */
void test1_set_create();

/**
 * @test Test creation of a set
 * @pre Set is successfully created
 * @post Number of ids is 0
 */
void test2_set_create();

/**
 * @test Test adding an id to a set
 * @pre Pointer to set is valid
 * @post Output == OK
 */
void test1_set_add_value();

/**
 * @test Test adding an id to a set
 * @pre Pointer to set is NULL
 * @post Output == ERROR
 */
void test2_set_add_value();

/**
 * @test Test deleting an id from a set
 * @pre Pointer to set is valid and contains the id
 * @post Output == OK
 */
void test1_set_del_value();

/**
 * @test Test deleting an id from a set
 * @pre Pointer to set is valid but doesn't contain the id
 * @post Output == ERROR
 */
void test2_set_del_value();

/**
 * @test Test finding an id in a set
 * @pre Pointer to set is valid and contains the id
 * @post Output == OK
 */
void test1_set_find_id();

/**
 * @test Test finding an id in a set
 * @pre Pointer to set is valid but doesn't contain the id
 * @post Output == ERROR
 */
void test2_set_find_id();

/**
 * @test Test getting the number of ids in a set
 * @pre Pointer to set is valid and has 1 element
 * @post Output == 1
 */
void test1_set_get_n_ids();

/**
 * @test Test getting the number of ids in a set
 * @pre Pointer to set is NULL
 * @post Output == -1
 */
void test2_set_get_n_ids();

#endif