/**
 * @brief               It defines the game interface for each command and rest of needed functions
 * @file                game.h
 * @author              Profesores PPROG, edited by Victor Yrazustra, Eric Morales & Alejandro Pascual
 * @version             1.0
 * @date                13-01-2015
 * @copyright           GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "die.h"
#include "link.h"

/**
 * @brief               It holds the necessary data to manage a game.
 */
typedef struct _Game Game;

/**
 * @name 		game_create
 * @author 		Victor Yrazusta edited by Eric Morales
 * @version             2.0
 * @date		27-02-2018
 * @brief               It allocates memory for a game.
 * @return		A game*, which could be NULL if the function failed.
 */
Game *game_create();

/**
 * @name 		game_create_from_file
 * @author 		Victor Yrazusta edited by Eric Morales
 * @version             3.0
 * @date		27-02-2018
 * @brief               It loads into a game (with already allocated memory) the data inside a file.
 * @param               Game* -> a game in which the function will store the obtained data, creating all the needed things on it.
 * @param               char* -> a string which will be the file (allready opened) that contains the information of the game.
 * @return		A STATUS, which will tell if the function failed.
 */
STATUS game_create_from_file(Game *, char *file_name);

/**
 * @name 		game_update
 * @author 		Victor Yrazusta edited by Eric Morales
 * @version             3.0
 * @date		27-02-2018
 * @brief               It updates the game to the last command that was input.
 * @param               Game* -> a game which will be updated depending on the last introduced command.
 * @param               Command* -> a command which will be the last given command from the user.
 * @return		A STATUS, which will tell if the function failed.
 */
STATUS game_update(Game *, Command *);

/**
 * @name 		game_destroy
 * @author 		Victor Yrazusta edited by Eric Morales
 * @version             2.0
 * @date		27-02-2018
 * @brief               It finds an object, a player, a die or a space in the passed game* whose Id is passed as an argument.
 * @param               Game* -> a game in which the function will search for the Id.
 * @param               Id -> an id which will be the Id of the struct found (if any).
 * @return		A STATUS, which will tell if the function failed.
 */
STATUS game_destroy(Game *);

/**
 * @name 		game_is over
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		13-01-2015
 * @brief               It checks if the game is over or not (right now there are no conditions yet).
 * @param               Game* -> the game which we will check if its over or not.
 * @return		A BOOL telling if its ended or not.
 */
BOOL game_is_over(Game *);

/**
 * @name 		game_print_data
 * @author 		Profesores PPROG edited by Victor Yrazusta
 * @version             2.0
 * @date		13-01-2015 (Creation) 07-04-2018 (Edited)
 * @brief               It prints all the game data, for debugging purposes.
 * @param               Game* -> which information will be printed (not graphic engine).
 * @return		A void without any relevant information.
 */
void game_print_data(Game *);

/**
 * @name 		game_add_space
 * @author 		Profesores PPROG edited by Javier Lougedo
 * @version             1.0
 * @date		13-01-2015 
 * @brief               It adds a new space to the game.
 * @param               Game* -> a game where the space will be added.
 * @param               Space* -> carrying the space to be loaded.
 * @return		A STATUS, which will tell if the function failed.
 */
STATUS game_add_space(Game *, Space *);

/**
 * @name 		game_add_object
 * @author 		Alejandro Pascual edited by Javier Lougedo
 * @version             1.0
 * @date		11-03-2018
 * @brief               It adds a new object to the game.
 * @param               Game* -> a game where the object will be added.
 * @param               Object* -> carrying the object to be loaded.
 * @return		A STATUS, which will tell if the function failed.
 */
STATUS game_add_object(Game *, Object *, Id location_id);

/**
 * @name 		game_get_spaces_number
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		16-03-2018
 * @brief               It returns the number of spaces there are in the game.
 * @param               Game* -> a game to check for the number of spaces in it.            
 * @return		An int with the number of spaces. 
 */
int game_get_spaces_number(Game *);

/**
 * @name 		game_get_players_number
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		16-03-2018
 * @brief               It returns the number of players there are in the game.
 * @param               Game* -> a game to check for the number of players in it.             
 * @return		An int with the number of players. 
 */
int game_get_players_number(Game *);

/**
 * @name 		game_get_objects_number
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		16-03-2018
 * @brief               It returns the number of objects there are in the game.
 * @param               Game* -> a game to check for the number of objects in it.            
 * @return		An int with the number of objects. 
 */
int game_get_objects_number(Game *);

/**
 * @name 		game_get_dies_number
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		16-03-2018
 * @brief               It returns the number of dies there are in the game.
 * @param               Game* -> a game to check for the number of dies in it.              
 * @return		An int with the number of dies. 
 */
int game_get_dies_number(Game *);

/**
 * @name 		game_find
 * @author 		Victor Yrazusta
 * @version             2.0
 * @date		27-02-2018
 * @brief               It finds an object, a player, a die or a space in the passed game* whose Id is passed as an argument.
 * @param               Game* -> a game in which the function will search for the Id.
 * @param               Id -> an id which will be the Id of the struct found (if any).
 * @return		A void*, which could be NULL if the function fails to find an object, a player, a die or a space with the specified Id, or the object, player, die or space found otherwise.
 */
void *game_find(Game *, Id id);

/**
 * @name 		game_find_name
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		28-02-2018
 * @brief               It finds an object, a player, a die or a space in the passed game* whose name is passed as an argument.
 * @param               Game* -> a game in which the function will search for the name.
 * @param               char* -> a string which will be the name of the struct found (if any).
 * @return		A void*, which could be NULL if the function fails to find an object, a player, a die or a space with the specified Id, or the object, player, die or space found otherwise.
 */
void *game_find_name(Game *, char *name);

/**
 * @name 		game_set_object_location
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		28-02-2018
 * @brief               It changes the location of the passed object and the location id passed to register the new position of the object.
 * @param               Game* -> a game in which the function will search for the name.
 * @param               Id -> the id of the location which will start holding the passed object Id.
 * @param               Id -> an id with the Id of the object which will be registered by the locations. 
 * @return		A STATUS, which indicates if the process was executed successfully or not. 
 */
STATUS game_set_object_location(Game *game, Id location_id, Id object_id);

/**
 * @name 		game_get_last_command
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		13-01-2015
 * @brief               It gets the last command that the user input, to print it.
 * @param               Game* -> a game where we will get the command from.
 * @return		A T_Command (text) with the actual command.
 */
T_Command game_get_last_command(Game *);

/**
 * @name 		game_get_status_last_command
 * @author 		Eric Morales
 * @version             1.0
 * @date		26-03-2018
 * @brief               It give us the status of the last command printed on the screen
 * @param               Game* -> a game to get the last command status from.
 * @return		A STATUS, the status of the command.
 */
STATUS game_get_status_last_command(Game* game);

/**
 * @name 		game_get_last_text_description
 * @author 		Eric Morales
 * @version             1.0
 * @date		26-03-2018
 * @brief               It gives us the last text description ordered by the user.
 * @param               Game* -> a game  which will give us the text description we are asking for.
 * @return		A const char* with the text description.
 */
char **game_get_last_text_description(Game* game);

/**
 * @name 		game_add_link
 * @author 		Eric Morales edited by Javier Lougedo
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It adds a link to the game.
 * @param 		Game* -> a game where we are playing.
 * @param		Link -> a link with the added link.
 * @return		A STATUS, OK if we can add the link or ERROR if we have problems.
 */
STATUS game_add_link(Game *game, Link *link);

/**
 * @name 		game_add_player
 * @author 		Eric Morales edited by Javier Lougedo
 * @version             1.0
 * @date		03-04-2018
 * @brief 		It adds a player to the game.
 * @param 		Game* -> a game where we are playing.
 * @param		Player* -> a player with the added player.
 * @return		A STATUS, OK if we can add the player or ERROR if we have problems.
 */
STATUS game_add_player(Game *game, Player *player, Id location_id);

#endif
