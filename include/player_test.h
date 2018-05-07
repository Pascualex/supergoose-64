/** 
 * @brief It declares the tests for the player module
 * @file player_test.h
 * @author Eric Morales
 * @version 1.0 
 * @date 08-04-2018
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Test player creation
 * @pre Player Id and inventory size
 * @post Non NULL pointer to player 
 */
void test1_player_create();

/**
 * @test Test player creation
 * @pre Player ID and inventory size
 * @post Player_ID == Supplied Player Id
 */
void test2_player_create();

/**
 * @test Test function for player name setting
 * @pre Created player and string with player name
 * @post Ouput==OK 
 */
void test1_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre NULL Player and string with player name
 * @post Output==ERROR
 */
void test2_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre Player Id and NULL char
 * @post Output==ERROR
 */
void test3_player_set_name();

/**
 * @test Test graphic description of a player setting
 * @pre Created player and a graphic description string
 * @post OUTPUT==OK
 */
void test1_player_set_graphic_description();

/**
 * @test Test graphic description setting on a NULL Player
 * @pre NULL Player and graphic description string
 * @post OUTPUT==ERROR
 */
void test2_player_set_graphic_description();

/**
 * @test Test Player with a NULL graphic description
 * @pre Created player and NULL string
 * @post OUTPUT==ERROR
 */
void test3_player_set_graphic_description();

/**
 * @test Test in normal conditions for the location setting
 * @pre Created player and location Id
 * @post OUTPUT==OK
 */
void test1_player_set_location();

/**
 * @test Test in abnormal conditions for the location setting
 * @pre NULL Player and location Id
 * @post OUTPUT==ERROR
 */
void test2_player_set_location();

/**
 * @test Test in abnormal conditions for the location setting
 * @pre Created Player and NO_ID location
 * @post OUTPUT==ERROR
 */
void test3_player_set_location();

/**
 * @test Test to see if Player has the given name
 * @pre Player ID and a string with a name on it
 * @post OUTPUT==0 (equal strings)
 */
void test1_player_get_name();

/**
 * @test Test if getting a name from a NULL Player works (it shouldn't)
 * @pre NULL Player
 * @post OUTPUT==NULL (error)
 */
void test2_player_get_name();

/**
 * @test Test to see if Player has the given Id
 * @pre Player ID
 * @post OUTPUT==OK
 */
void test1_player_get_id();

/**
 * @test Test to see if a NULL Player Id is NO_ID
 * @pre NULL Player
 * @post OUTPUT==NO_ID
 */
void test2_player_get_id();

/**
 * @test Test to see if the created player with the given graphic description returns the given graphic description
 * @pre Player ID and a string with a graphic description
 * @post OUTPUT==0 (equal strings)
 */
void test1_player_get_graphic_description();

/**
 * @test Test to check if the graphic description of a NULL Player is NULL
 * @pre NULL Player 
 * @post OUTPUT==NULL
 */
void test2_player_get_graphic_description();

/**
 * @test Test to see if a Player has the given Object on its inventory.
 * @pre Player ID and Object Id
 * @post OUTPUT==OK (matching Ids)
 */
void test1_player_get_object_id();

/**
 * @test Test to check if a NULL Player returns a NO_ID when asked for the object Id
 * @pre NULL Player 
 * @post OUTPUT==NO_ID
 */
void test2_player_get_object_id();

/**
 * @test Test to see if player carried objects number is correct
 * @pre Player ID and object
 * @post OUTPUT==1
 */
void test1_player_get_objects_number();

/**
 * @test Test if Player its generated with 0 objects
 * @pre Player ID 
 * @post OUTPUT==0
 */
void test2_player_get_objects_number();

/**
 * @test Test if NULL player is carrying any object
 * @pre NULL Player
 * @post OUTPUT==0
 */
void test3_player_get_objects_number();

/**
 * @test Test if the maximum amount a Player can handle is the sets maximum
 * @pre Player ID and integer
 * @post OUTPUT==SET_MAX_IDS
 */
void test4_player_get_objects_number();

/**
 * @test Test if the location Id of the player is OK
 * @pre Created player and location Id
 * @post OUTPUT==OK (matching Ids)
 */
void test1_player_get_location();

/**
 * @test Test if the location Id of a NULL player is NO_ID
 * @pre Created player
 * @post OUTPUT==NO_ID
 */
void test2_player_get_location();

/**
 * @test Test if objects are added properly onto the player
 * @pre Created player and object Id
 * @post OUTPUT==OK
 */
void test1_player_add_object();

/**
 * @test Test if objects adding onto a NULL Player works
 * @pre NULL Player
 * @post OUTPUT==ERROR
 */
void test2_player_add_object();

/**
 * @test Test if objects are deleted properly into the player
 * @pre Created player and object Id
 * @post OUTPUT==OK
 */
void test1_player_del_object();

/**
 * @test Test if objects deleting into a NULL Player works
 * @pre NULL Player
 * @post OUTPUT==ERROR
 */
void test2_player_del_object();

/**
 * @test Test if objects deleting into a NULL Player works
 * @pre NULL Player
 * @post OUTPUT==ERROR
 */
void test3_player_del_object();

/**
 * @test Test if a created Id is empty
 * @pre Player ID 
 * @post OUTPUT==TRUE
 */
void test1_player_is_empty();

/**
 * @test Test if a NULL Player is empty
 * @pre NULL Player
 * @post OUTPUT==TRUE
 */
void test2_player_is_empty();

/**
 * @test Test if a Player with an object is not empty
 * @pre Player ID and Object Id
 * @post OUTPUT==FALSE
 */
void test3_player_is_empty();

/**
 * @test Test if a player with all the objects possible is or not full
 * @pre Player ID and objects Id
 * @post OUTPUT==TRUE
 */
void test1_player_is_full();

/**
 * @test Test if an empty Player is full
 * @pre Player Id
 * @post OUTPUT==ERROR
 */
void test2_player_is_full();

/**
 * @test Test if a NULL Player is or not full
 * @pre NULL Player 
 * @post OUTPUT==TRUE
 */
void test3_player_is_full();

/**
 * @test Test if a Player with one only object is full
 * @pre Player ID and Object Id
 * @post OUTPUT==FALSE
 */
void test4_player_is_full();

/**
 * @test Test to see if the check object works on a Player with an object
 * @pre Player ID and Object Id
 * @post OUTPUT==TRUE
 */
void test1_player_check_object();

/**
 * @test Test to see if the check object works on a Player without an object
 * @pre Player ID 
 * @post OUTPUT==FALSE
 */
void test2_player_check_object();

/**
 * @test Test to see if the check object works on a NULL Player
 * @pre Player ID 
 * @post OUTPUT==FALSE
 */
void test3_player_check_object();

#endif

