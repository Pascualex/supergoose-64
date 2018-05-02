/** 
 * @brief It declares the tests for the object module
 * @file object_test.h
 * @author Eric Morales
 * @version 1.0 
 * @date 08-04-2018
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
 * @pre Object ID 
 * @post Object_ID == Supplied Object Id
 */
void test2_object_create();

/**
 * @test Test function for object name setting
 * @pre Object Id and string with object name
 * @post Ouput==OK 
 */
void test1_object_set_name();

/**
 * @test Test function for object name setting
 * @pre NULL Object and string with object name
 * @post Output==ERROR
 */
void test2_object_set_name();

/**
 * @test Test function for object name setting
 * @pre Object Id and NULL char
 * @post Output==ERROR
 */
void test3_object_set_name();

/**
 * @test Test function for object set location in normal conditions
 * @pre Object Id and location Id
 * @post Output==OK
 */
void test1_object_set_location();

/**
 * @test Test function for object set location with NULL objects
 * @pre NULL object and location Id.
 * @post Output==ERROR
 */
void test2_object_set_location();

/**
 * @test Test function for object set location with no location
 * @pre Object Id and NO_ID location
 * @post Output==ERROR
 */
void test3_object_set_location();

/**
 * @test Test function for set check in normal conditions
 * @pre Object Id and strings for description
 * @post Output==OK
 */
void test1_object_set_check();

/**
 * @test Test function for set check in abnormal conditions (NULL OBJECT)
 * @pre NULL object
 * @post Output==ERROR
 */
void test2_object_set_check();

/**
 * @test Test to see if Object has the given name
 * @pre Object ID and a string with a name on it
 * @post OUTPUT==0 (equal strings)
 */
void test1_object_get_name();

/**
 * @test Test if getting a name from a NULL Object works (it shouldn't)
 * @pre NULL Object
 * @post OUTPUT==NULL (error)
 */
void test2_object_get_name();

/**
 * @test Test to see if Object has the given Id
 * @pre Object ID
 * @post OUTPUT==OK
 */
void test1_object_get_id();

/**
 * @test Test to see if a NULL Object Id is NO_ID
 * @pre NULL Object
 * @post OUTPUT==NO_ID
 */
void test2_object_get_id();

/**
 * @test Test to see if the created object returns the correct location
 * @pre Created object and location Id
 * @post OUTPUT==OK (Matching locations)
 */
void test1_object_get_location();

/**
 * @test Test to see if the created object returns the correct location
 * @pre NULL object
 * @post OUTPUT==OK (Matching locations)
 */
void test2_object_get_location();

/**
 * @test Test to see if the created object returns the correct description
 * @pre Created object and check field
 * @post OUTPUT==OK (Matching descriptions)
 */
void test1_object_get_check();

/**
 * @test Test to see if the created object returns the correct description
 * @pre NULL object
 * @post OUTPUT==OK (Matching descriptions)
 */
void test2_object_get_check();

/**
 * @test Test to see if function add_tags works under normal conditions
 * @pre Created object
 * @post OUTPUT==OK
 */
void test1_object_add_tags();

/**
 * @test Test to see if function add_tags works under abnormal conditions
 * @pre NULL object
 * @post OUTPUT==ERROR
 */
void test2_object_add_tags();

/**
 * @test Test to see if function get_tags works under normal conditions
 * @pre Created object with correct tags
 * @post OUTPUT==OK
 */
void test1_object_get_tags();

/**
 * @test Test to see if function get_tags works under abnormal conditions
 * @pre NULL object
 * @post OUTPUT==ERROR
 */
void test2_object_get_tags();

/**
 * @test Test to see if function get_tags_number works under normal conditions
 * @pre Created object with correct tags
 * @post OUTPUT==TAGS_NUMBER
 */
void test1_object_get_tags_number();

/**
 * @test Test to see if function get_tags works under abnormal conditions
 * @pre NULL object
 * @post OUTPUT==0
 */
void test2_object_get_tags_number();

/**
 * @test Test to see if function is works under normal conditions
 * @pre Created object with correct tags
 * @post Object is passed tag
 */
void test1_object_check_tag();

/**
 * @test Test to see if function is works under abnormal conditions
 * @pre Created object with correct tags
 * @post Object isn't passed tag
 */
void test2_object_check_tag();

/**
 * @test Test to see if function is works under normal conditions
 * @pre Created object with correct tags
 * @post OUTPUT==OK
 */
void test1_object_remove_tag();

/**
 * @test Test to see if function is works under abnormal conditions
 * @pre NULL object
 * @post OUTPUT==OK
 */
void test2_object_remove_tag();

/**
 * @test Test to see if function is works under normal conditions
 * @pre Created object and correct alternative check
 * @post OUTPUT==OK
 */
void test1_object_set_alt_check();

/**
 * @test Test to see if function is works under abnormal conditions
 * @pre NULL object and NULL alternative check
 * @post OUTPUT==ERROR
 */
void test2_object_set_alt_check();

/**
 * @test Test to see if function is works under normal conditions
 * @pre Created object and correct alternative check
 * @post Registered alternative check is expected alternative check
 */
void test1_object_get_alt_check();

/**
 * @test Test to see if function is works under normal conditions
 * @pre NULL object and NULL alternative check
 * @post OUTPUT==NULL
 */
void test2_object_get_alt_check();

#endif

