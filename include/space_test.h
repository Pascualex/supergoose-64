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
 * @pre Space and string with space name
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
 * @pre Space and NULL char
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for north Id setting
 * @pre Space, NORTH direction and Space Id
 * @post OUTPUT==OK
 */
void test1_space_set_direction();

/**
 * @test Test function for west Id setting
 * @pre Space, WEST direction and Space Id
 * @post OUTPUT==OK
 */
void test2_space_set_direction();

/**
 * @test Test function for south Id setting
 * @pre Space, SOUTH direction and Space Id
 * @post OUTPUT==OK
 */
void test3_space_set_direction();

/**
 * @test Test function for east Id setting
 * @pre Space, EAST direction and Space Id
 * @post OUTPUT==OK
 */
void test4_space_set_direction();

/**
 * @test Test function for a non valid direction
 * @pre NO_DIR Direction
 * @post OUTPUT==ERROR
 */
void test5_space_set_direction();

/**
 * @test Test function for a non valid Id
 * @pre NO_ID Id
 * @post OUTPUT==ERROR
 */
void test6_space_set_direction();

/**
 * @test Test function for a non created space
 * @pre NULL Space
 * @post OUTPUT==ERROR
 */
void test7_space_set_direction();

/**
 * @test Test graphic description of a space setting
 * @pre Space and a graphic description string
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
 * @pre Space and NULL string
 * @post OUTPUT==ERROR
 */
void test3_space_set_graphic_description();

/**
 * @test Test check of a space setting
 * @pre Space and a check string
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
 * @pre Space and NULL string
 * @post OUTPUT==ERROR
 */
void test3_space_set_check();

/**
 * @test Test to see if Space has the given name
 * @pre Space and a string with a name on it
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
 * @pre Space
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
 * @pre Space and NORTH Direction
 * @post OUTPUT==Northern Id
 */
void test1_space_get_direction();

/**
 * @test Test to check if the western Id is set and got properly
 * @pre Space and WEST Direction
 * @post OUTPUT==Western Id
 */
void test2_space_get_direction();

/**
 * @test Test to check if the souther Id is set and got properly
 * @pre Space and SOUTH Direction
 * @post OUTPUT==Southern Id
 */
void test3_space_get_direction();

/**
 * @test Test to check if the eastern Id is set and got properly
 * @pre Space and EAST Direction
 * @post OUTPUT==Eastern Id
 */
void test4_space_get_direction();

/**
 * @test Test to check if a NO_DIR Direction returns NO_ID
 * @pre NO_DIR Direction
 * @post OUTPUT==NO_ID
 */
void test5_space_get_direction();

/**
 * @test Test to check if a NULL Space returns NO_ID
 * @pre NULL Space
 * @post OUTPUT==NO_ID
 */
void test6_space_get_direction();

/**
 * @test Test to see if the created space with the given graphic description returns the given graphic description
 * @pre Space and a string with a graphic description
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
 * @pre Space and a string with a check
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
 * @pre Space and Object Id
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
 * @pre Space and object
 * @post OUTPUT==1
 */
void test1_space_get_objects_number();

/**
 * @test Test if Space its generated with 0 objects
 * @pre Space 
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
 * @pre Space and integer
 * @post OUTPUT==SET_MAX_IDS
 */
void test4_space_get_objects_number();

/**
 * @test Test if objects are added properly onto the space
 * @pre Space and object Id
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
 * @pre Space 
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
 * @pre Space and Object Id
 * @post OUTPUT==FALSE
 */
void test3_space_is_empty();

/**
 * @test Test if a space with all the objects possible is or not full
 * @pre Space and objects Id
 * @post OUTPUT==TRUE
 */
void test1_space_is_full();

/**
 * @test Test if an empty Space is full
 * @pre Space
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
 * @pre Space and Object Id
 * @post OUTPUT==FALSE
 */
void test4_space_is_full();

/**
 * @test Test to see if the check object works on a Space with an object
 * @pre Space and Object Id
 * @post OUTPUT==TRUE
 */
void test1_space_check_object();

/**
 * @test Test to see if the check object works on a Space without an object
 * @pre Space 
 * @post OUTPUT==FALSE
 */
void test2_space_check_object();

/**
 * @test Test to see if the check object works on a NULL Space
 * @pre Space 
 * @post OUTPUT==FALSE
 */
void test3_space_check_object();

#endif