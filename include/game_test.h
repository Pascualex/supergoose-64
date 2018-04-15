/** 
 * @brief It declares the tests for the game module
 * @file game_test.h
 * @author Javier Lougedo
 * @version 2.0 
 * @date 19-01-2016
 * @copyright GNU Public License
 */

#ifndef GAME_TEST_H
#define GAME_TEST_H

/**
 * @test Test to see if game_create works correctly
 * @pre NULL Game 
 * @post Should return a created game (different from NULL)
 */
void test1_game_create();

/**
 * @test Test to check if a game is created correctly from a file.
 * @pre Created Game and a data file
 * @post OUTPUT==OK
 */
void test1_game_create_from_file();

/**
 * @test Test to check if it works with a NULL game
 * @pre NULL Game 
 * @post OUTPUT==ERROR
 */
void test2_game_create_from_file();

/**
 * @test Test to check if it works with a NULL datafile
 * @pre Created Game and NULL datafile.
 * @post OUTPUT==ERROR
 */
void test3_game_create_from_file();

/**
 * @test Test to check if it works with a non existing datafile
 * @pre Created Game and a bad datafile.
 * @post OUTPUT==ERROR
 */
void test4_game_create_from_file();

/**
 * @test Test if game updates with a NULL Game (simple, but is easy to see if game update isnt working)
 * @pre NULL Game and a command
 * @post OUTPUT==ERROR
 */
void test1_game_update();

/**
 * @test Test if game updates without a command (simple, but is easy to see if game update isnt working)
 * @pre Created Game and a NULL command 
 * @post OUTPUT==ERROR
 */
void test2_game_update();

/**
 * @test Test if game destroys a created Game.
 * @pre Created Game
 * @post OUTPUT==OK
 */
void test1_game_destroy();

/**
 * @test Test if game destroys a NULL Game
 * @pre NULL Game
 * @post OUTPUT==ERROR
 */
void test2_game_destroy();

/**
 * @test Test if normally a created Game is over or not
 * @pre Created Game
 * @post OUTPUT==FALSE
 */
void test1_game_is_over();

/**
 * @test Test if a NULL game is over
 * @pre NULL Game
 * @post OUTPUT==TRUE
 */
void test2_game_is_over();

/**
 * @test Test to see if adding spaces works correctly
 * @pre Created Game and Space Id
 * @post OUTPUT==OK
 */
void test1_game_add_space();

/**
 * @test Test to see if adding spaces doesn't work for NULL games
 * @pre NULL Game Space Id
 * @post OUTPUT==ERROR
 */
void test2_game_add_space();

/**
 * @test Test to see if adding a NULL Space doesn't work
 * @pre Created Game NULL SPACE
 * @post OUTPUT==ERROR
 */
void test3_game_add_space();

/**
 * @test Test to see if it allows more ids than it can handle
 * @pre Created Game Max Spaces
 * @post OUTPUT==ERROR
 */
void test4_game_add_space();

/**
 * @test Test with normal conditions
 * @pre Created Game a Player and a location
 * @post OUTPUT==OK
 */
void test1_game_add_player();

/**
 * @test Test with NULL game
 * @pre NULL Game, a Player and a location
 * @post OUTPUT==ERROR
 */
void test2_game_add_player();

/**
 * @test Test with NULL player
 * @pre Created Game a NULL Player and a location
 * @post OUTPUT==ERROR
 */
void test3_game_add_player();

/**
 * @test Test with NO_ID location
 * @pre Created Game a Player and a NO_ID location
 * @post OUTPUT==ERROR
 */
void test4_game_add_player();

/**
 * @test Test with maximum number of players
 * @pre Created Game max Players and a location
 * @post OUTPUT==ERROR
 */
void test5_game_add_player();

/**
 * @test Test to see if adding objects normally works correctly
 * @pre Created Game, an Object and a location Id
 * @post OUTPUT==OK
 */
void test1_game_add_object();

/**
 * @test Test to see if adding objects doesn't work for NULL games
 * @pre NULL Game, an Object and a location Id
 * @post OUTPUT==ERROR
 */
void test2_game_add_object();

/**
 * @test Test to see if adding a NULL Space doesn't work
 * @pre Created Game, a NULL Object and a location Id
 * @post OUTPUT==ERROR
 */
void test3_game_add_object();

/**
 * @test Test to see if adding a NULL Space doesn't work
 * @pre Created Game, an Object and a location Id = NO_ID
 * @post OUTPUT==ERROR
 */
void test4_game_add_object();

/**
 * @test Test to see if respects space limit
 * @pre Created Game, an Object and a location Id
 * @post OUTPUT==ERROR
 */
void test5_game_add_object();

/**
 * @test Test to see if respects the max objects of the game
 * @pre Created Game, an Object and a location Id
 * @post OUTPUT==ERROR
 */
void test6_game_add_object();

/**
 * @test Test to see if the number (1) of returned spaces is correct.
 * @pre Created Game and a Space
 * @post OUTPUT==1
 */
void test1_game_get_spaces_number();

/**
 * @test Test to see if the number (0) of returned spaces is correct.
 * @pre Created Game
 * @post OUTPUT==0
 */
void test2_game_get_spaces_number();

/**
 * @test Test to see the number of spaces in a NULL game.
 * @pre NULL Game
 * @post OUTPUT==0
 */
void test3_game_get_spaces_number();

/**
 * @test Test to see the number of spaces in a NULL game.
 * @pre NULL Game
 * @post OUTPUT==0
 */
void test4_game_get_spaces_number();

/**
 * @test Test to see if the number (1) of returned players is correct.
 * @pre Created Game and a Player
 * @post OUTPUT==1
 */
void test1_game_get_players_number();

/**
 * @test Test to see if the number (0) of returned players is correct.
 * @pre Created Game
 * @post OUTPUT==0
 */
void test2_game_get_players_number();

/**
 * @test Test to see the number of players in a NULL game.
 * @pre NULL Game
 * @post OUTPUT==0
 */
void test3_game_get_players_number();

/**
 * @test Test to see if respects maximum numebr of players
 * @pre Created Game with max players
 * @post OUTPUT==0
 */
void test4_game_get_players_number();

/**
 * @test Test to see if the number (1) of returned objects is correct.
 * @pre Created Game and a object
 * @post OUTPUT==1
 */
void test1_game_get_objects_number();

/**
 * @test Test to see if the number (0) of returned objects is correct.
 * @pre Created Game
 * @post OUTPUT==0
 */
void test2_game_get_objects_number();

/**
 * @test Test to see the number of objects in a NULL game.
 * @pre NULL Game
 * @post OUTPUT==0
 */
void test3_game_get_objects_number();

/**
 * @test Test to see if respects maximum number of objects
 * @pre Created Game with max objects
 * @post OUTPUT==0
 */
void test4_game_get_objects_number();

/**
 * @test Test to see if the number (0) of returned dies is correct.
 * @pre Created Game
 * @post OUTPUT==0
 */
void test1_game_get_dies_number();

/**
 * @test Test to see the number of dies in a NULL game.
 * @pre NULL Game
 * @post OUTPUT==0
 */
void test2_game_get_dies_number();

/**
 * @test Test to see if it works normally
 * @pre Created Game.
 * @post OUTPUT not NULL
 */
void test1_game_find();

/**
 * @test Test to see if it works with a NULL Game
 * @pre NULL Game.
 * @post OUTPUT==NULL
 */
void test2_game_find();

/**
 * @test Test to see if it works with a NO_ID
 * @pre Created Game.
 * @post OUTPUT==NULL
 */
void test3_game_find();

/**
 * @test Test to see if it works normally
 * @pre Created Game.
 * @post OUTPUT not NULL
 */
void test1_game_find_name();

/**
 * @test Test to see if it works with a NULL Game
 * @pre NULL Game.
 * @post OUTPUT==NULL
 */
void test2_game_find_name();

/**
 * @test Test to see if it works with a NULL
 * @pre Created Game.
 * @post OUTPUT==NULL
 */
void test3_game_find_name();

/**
 * @test Test to see if it works normally
 * @pre Created Game, destiny Id and Object Id
 * @post OUTPUT==OK
 */
void test1_game_set_object_location();

/**
 * @test Test to see if it works with NULL games
 * @pre NULL Game, destiny Id and Object Id
 * @post OUTPUT==ERROR
 */
void test2_game_set_object_location();

/**
 * @test Test to see if it works with NO_ID on destiny
 * @pre Created Game, destiny Id = NO_ID and Object Id
 * @post OUTPUT==ERROR
 */
void test3_game_set_object_location();

/**
 * @test Test to see if it works with NO_ID on the Object_Id
 * @pre Created Game, destiny Id and Object Id = NO_ID
 * @post OUTPUT==ERROR
 */
void test4_game_set_object_location();

/**
 * @test Test to see if it lets us move an object normally
 * @pre Created Game, destiny Id and Object Id
 * @post OUTPUT==OK
 */
void test1_game_set_object_location();

/**
 * @test Test to see if works in normal conditions
 * @pre Created Game with grasp command
 * @post OUTPUT==GRASP
 */
void test1_game_get_last_command();

/**
 * @test Test with NULL Game
 * @pre NULL Game 
 * @post OUTPUT==NO_CMD
 */
void test2_game_get_last_command();

/**
 * @test Test to see if works in normal conditions
 * @pre Created Game with grasp command
 * @post OUTPUT==GRASP
 */
void test1_game_get_status_last_command();

/**
 * @test Test to see if works with a NULL Game
 * @pre NULL Game 
 * @post OUTPUT==ERROR
 */
void test2_game_get_status_last_command();

/**
 * @test Test to see if works in normal conditions with an object
 * @pre Created Game
 * @post OUTPUT==OBJ_DESC
 */
void test1_game_get_last_text_description();

/**
 * @test Test to see how it works with a NULL Game
 * @pre NULL Game
 * @post OUTPUT==NULL
 */
void test2_game_get_last_text_description();

/**
 * @test Test to see if works in normal conditions with a space
 * @pre Created Game
 * @post OUTPUT==SPACE_DESC
 */
void test3_game_get_last_text_description();

/**
 * @test Test with normal conditions
 * @pre Created Game and a Link to add
 * @post OUTPUT==OK
 */
void test1_game_add_link();

/**
 * @test Test with NULL game
 * @pre NULL Game and a Link to add
 * @post OUTPUT==ERROR
 */
void test2_game_add_link();

/**
 * @test Test with NULL Link
 * @pre Created Game and a NULL Link to add
 * @post OUTPUT==ERROR
 */
void test3_game_add_link();

/**
 * @test Test with MAX Links
 * @pre Created Game and a maximum Link to add
 * @post OUTPUT==ERROR
 */
void test3_game_add_link();


/*FOLLOWING FUNCTION IS NO LONGER PUBLIC; BUT LEAVING IT IN CASE IT IS IN THE FUTURE*/
/*
 * @test Test to check normal conditions
 * @pre Created Game and two spaces to link
 * @post OUTPUT==LINK (Not NULL)
 *
void test1_game_get_connection();*/

/*
 * @test Test to check how it works with a NULL Game
 * @pre NULL Game and two spaces to link
 * @post OUTPUT==NULL
 *
void test2_game_get_connection();*/

/*
 * @test Test to check abnormal conditions
 * @pre Created Game and two spaces to link, but origin is NULL
 * @post OUTPUT==NULL
 *
void test3_game_get_connection();*/

/*
 * @test Test to check abnormal conditions
 * @pre Created Game and two spaces to link, but destination is NULL
 * @post OUTPUT==NULL
 *
void test4_game_get_connection();*/


#endif
