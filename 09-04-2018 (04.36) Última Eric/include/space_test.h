/** 
 * @brief It declares the tests for the space module
 * @file space_test.h
 * @author Profesores Pprog and Eric Morales
 * @version 2.0 
 * @date 19-01-2016
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
 * @pre Space Id and string with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre NULL Space and string with space name
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre Space Id and NULL char
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for north Id setting
 * @pre Space ID
 * @post OUTPUT==OK
 */
void test1_space_set_north();

/**
 * @test Test function for a non created space for north Id setting
 * @pre NULL Space and direction Id
 * @post OUTPUT==ERROR
 */
void test2_space_set_north();

/**
 * @test Test function for south Id setting
 * @pre Space ID and direction Id
 * @post OUTPUT==OK
 */
void test1_space_set_south();

/**
 * @test Test function for a non created space for south Id setting
 * @pre NULL Space and direction Id
 * @post OUTPUT==ERROR
 */
void test2_space_set_south();

/**
 * @test Test function for east Id setting
 * @pre Space ID and direction Id
 * @post OUTPUT==OK
 */
void test1_space_set_east();

/**
 * @test Test function for a non created space for east Id setting
 * @pre NULL Space and direction Id
 * @post OUTPUT==ERROR
 */
void test2_space_set_east();

/**
 * @test Test function for west Id setting
 * @pre Space ID and direction Id
 * @post OUTPUT==OK
 */
void test1_space_set_west();

/**
 * @test Test function for a non created space for west Id setting
 * @pre NULL Space and direction Id
 * @post OUTPUT==ERROR
 */
void test2_space_set_west();

/**
 * @test Test graphic description of a space setting
 * @pre Space ID and a graphic description string
 * @post OUTPUT==OK
 */
void test1_space_set_graphic_description();

/**
 * @test Test graphic description setting on a NULL Space
 * @pre NULL Space and graphic description string
 * @post OUTPUT==ERROR
 */
void test2_space_set_graphic_description();

/**
 * @test Test Space with a NULL graphic description
 * @pre Space ID and NULL string
 * @post OUTPUT==ERROR
 */
void test3_space_set_graphic_description();

/**
 * @test Test check of a space setting
 * @pre Space ID and a check string
 * @post OUTPUT==OK
 */
void test1_space_set_check();

/**
 * @test Test check setting on a NULL Space
 * @pre NULL Space and check string
 * @post OUTPUT==ERROR
 */
void test2_space_set_check();

/**
 * @test Test Space with a NULL check
 * @pre Space ID and NULL string
 * @post OUTPUT==ERROR
 */
void test3_space_set_check();

/**
 * @test Test to see if Space has the given name
 * @pre Space ID and a string with a name on it
 * @post OUTPUT==0 (equal strings)
 */
void test1_space_get_name();

/**
 * @test Test if getting a name from a NULL Space works (it shouldn't)
 * @pre NULL Space
 * @post OUTPUT==NULL (error)
 */
void test2_space_get_name();

/**
 * @test Test to see if Space has the given Id
 * @pre Space ID
 * @post OUTPUT==OK
 */
void test1_space_get_id();

/**
 * @test Test to see if a NULL Space Id is NO_ID
 * @pre NULL Space
 * @post OUTPUT==NO_ID
 */
void test2_space_get_id();

/**
 * @test Test to check if the northern Id is set and got properly
 * @pre Space ID and north Id
 * @post OUTPUT==OK
 */
void test1_space_get_north();

/**
 * @test Test to check if a NULL Space northern Id is 0
 * @pre NULL Id and a north Id
 * @post OUTPUT==NO_ID
 */
void test2_space_get_north();

/**
 * @test Test to check if the southern Id is set and got properly
 * @pre Space ID and south Id
 * @post OUTPUT==OK
 */
void test1_space_get_south();

/**
 * @test Test to check if a NULL Space southern Id is 0
 * @pre NULL Id and a south Id
 * @post OUTPUT==NO_ID
 */
void test2_space_get_south();

/**
 * @test Test to check if the eastern Id is set and got properly
 * @pre Space ID and east Id
 * @post OUTPUT==OK
 */
void test1_space_get_east();

/**
 * @test Test to check if a NULL Space eastern Id is 0
 * @pre NULL Id and a east Id
 * @post OUTPUT==NO_ID
 */
void test2_space_get_east();

/**
 * @test Test to check if the western Id is set and got properly
 * @pre Space ID and west Id
 * @post OUTPUT==OK
 */
void test1_space_get_west();

/**
 * @test Test to check if a NULL Space western Id is 0
 * @pre NULL Id and a west Id
 * @post OUTPUT==NO_ID
 */
void test2_space_get_west();

/**
 * @test Test to see if the created space with the given graphic description returns the given graphic description
 * @pre Space ID and a string with a graphic description
 * @post OUTPUT==OK
 */
void test1_space_get_graphic_description();

/**
 * @test Test to check if the graphic description of a NULL Space is NULL
 * @pre NULL Space 
 * @post OUTPUT==NULL
 */
void test2_space_get_graphic_description();

/**
 * @test Test to see if the created space with the given check returns the given check
 * @pre Space ID and a string with a check
 * @post OUTPUT==OK
 */
void test1_space_get_check();

/**
 * @test Test to check if the check of a NULL Space is NULL
 * @pre NULL Space 
 * @post OUTPUT==NULL
 */
void test2_space_get_check();

/**
 * @test Test to see if the Id of an object on a Space is the one the Space returns.
 * @pre Space ID and Object Id
 * @post OUTPUT==OK
 */
void test1_space_get_object_id();

/**
 * @test Test to check if a NULL Space returns a NO_ID when asked for the object Id
 * @pre NULL Space 
 * @post OUTPUT==NO_ID
 */
void test2_space_get_object_id();

/**
 * @test Test if Space carries one object
 * @pre Space ID and object
 * @post OUTPUT==1
 */
void test1_space_get_objects_number();

/**
 * @test Test if Space its generated with 0 objects
 * @pre Space ID 
 * @post OUTPUT==0
 */
void test2_space_get_objects_number();

/**
 * @test Test if NULL space is carrying any object
 * @pre NULL Space
 * @post OUTPUT==0
 */
void test3_space_get_objects_number();

/**
 * @test Test if the maximum amount a Space can handle is the sets maximum
 * @pre Space ID and integer
 * @post OUTPUT==SET_MAX_IDS
 */
void test4_space_get_objects_number();

/**
 * @test Test if objects are added properly onto the space
 * @pre Space ID and object Id
 * @post OUTPUT==OK
 */
void test1_space_add_object();

/**
 * @test Test if objects adding onto a NULL Space works
 * @pre NULL Space
 * @post OUTPUT==ERROR
 */
void test2_space_add_object();

/**
 * @test Test if a created Id is empty
 * @pre Space ID 
 * @post OUTPUT==TRUE
 */
void test1_space_is_empty();

/**
 * @test Test if a NULL Space is empty
 * @pre NULL Space
 * @post OUTPUT==TRUE
 */
void test2_space_is_empty();

/**
 * @test Test if a Space with an object is not empty
 * @pre Space ID and Object Id
 * @post OUTPUT==FALSE
 */
void test3_space_is_empty();

/**
 * @test Test if a space with all the objects possible is or not full
 * @pre Space ID and objects Id
 * @post OUTPUT==TRUE
 */
void test1_space_is_full();

/**
 * @test Test if an empty Space is full
 * @pre Space Id
 * @post OUTPUT==ERROR
 */
void test2_space_is_full();

/**
 * @test Test if a NULL Space is or not full
 * @pre NULL Space 
 * @post OUTPUT==TRUE
 */
void test3_space_is_full();

/**
 * @test Test if a Space with one only object is full
 * @pre Space ID and Object Id
 * @post OUTPUT==FALSE
 */
void test4_space_is_full();

/**
 * @test Test to see if the check object works on a Space with an object
 * @pre Space ID and Object Id
 * @post OUTPUT==TRUE
 */
void test1_space_check_object();

/**
 * @test Test to see if the check object works on a Space without an object
 * @pre Space ID 
 * @post OUTPUT==FALSE
 */
void test2_space_check_object();

/**
 * @test Test to see if the check object works on a NULL Space
 * @pre Space ID 
 * @post OUTPUT==FALSE
 */
void test3_space_check_object();

#endif

