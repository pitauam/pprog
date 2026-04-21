/**
 * @brief It declares the tests for the link module
 *
 * @file link_test.h
 * @author Santiago Pita
 * @version 1
 * @date 28-03-2026
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test link creation
 * @pre Link ID 
 * @post Non NULL pointer to link 
 */
void test1_link_create();

/**
 * @test Test link creation with NO_ID
 * @pre NO_ID
 * @post NULL pointer to link 
 */
void test2_link_create();

/**
 * @test Test link set name
 * @pre Link and name
 * @post Output == OK 
 */
void test1_link_set_name();

/**
 * @test Test link set name
 * @pre Link and name
 * @post Output == OK 
 */
void test2_link_set_name();

/**
 * @test Test link set name
 * @pre Link and name
 * @post Output == OK 
 */
void test3_link_set_name();

/**
 * @test Test link get name
 * @pre Link name 
 * @post Output == name
 */
void test1_link_get_name();

/**
 * @test Test link get name
 * @pre Link name 
 * @post Output == name
 */
void test2_link_get_name();

/**
 * @test Test link set origin
 * @pre Link and origin 
 * @post Output == OK
 */
void test1_link_set_origin();

/**
 * @test Test link set origin
 * @pre Link and origin 
 * @post Output == OK
 */
void test2_link_set_origin();

/**
 * @test Test link get origin
 * @pre Link and origin
 * @post Output == ID
 */
void test1_link_get_origin();

/**
 * @test Test link get origin
 * @pre Link and origin
 * @post Output == ID
 */
void test2_link_get_origin();
void test1_link_set_destination();
void test2_link_set_destination();
void test1_link_get_destination();
void test2_link_get_destination();

/**
 * @test Test link set direction
 * @pre Link and direction
 * @post Output == OK
 */
void test1_link_set_direction();

/**
 * @test Test link set direction
 * @pre Link and direction
 * @post Output == OK
 */
void test2_link_set_direction();

/**
 * @test Test link get direction
 * @pre Link direction
 * @post Output == direction
 */
void test1_link_get_direction();

/**
 * @test Test link get direction
 * @pre Link direction
 * @post Output == direction
 */
void test2_link_get_direction();
void test1_link_set_open();
void test2_link_set_open();
void test1_link_get_open();
void test2_link_get_open();
void test3_link_get_open();

#endif
