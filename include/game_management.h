/**
 * @brief               It defines the functions to read games from files, used to initialize the game  
 * @file                game_management.h
 * @author              Alejandro Pascual and Víctor Yrazusta, edited by Eric Morales
 * @version             1.0 
 * @date                08-02-2018
 * @copyright           GNU Public License
 */

#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "space.h"
#include "types.h"
#include "game.h"
#include "link.h"
#include "player.h"

/**
 * @name 		game_management_load_spaces
 * @author 		Alejandro Pascual edited by Eric Morales
 * @version             2.0
 * @date		10-03-2018
 * @brief 		It loads the data of the spaces from the passed filename to the passed game.
 * @param 		char* -> a string with the name of the file containing the data of the spaces.
 * @param 		Game* -> a game in which the data of the spaces will be loaded.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS game_management_load_spaces(Game *, char *filename);

/**
 * @name 		game_management_load_players
 * @author 		Eric Morales
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It loads the data of the players from the passed filename to the passed game.
 * @param 		char* -> a string with the name of the file containing the data of the players.
 * @param 		Game* -> a game in which the data of the players will be loaded.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS game_management_load_players(Game *game, char *filename);

/**
 * @name 		game_management_load_objects
 * @author 		Alejandro Pascual edited by Eric Morales
 * @version             2.0
 * @date		13-03-2018
 * @brief 		It loads the data of the objects from the passed filename to the passed game.
 * @param 		char* -> a string with the name of the file containing the data of the objects.
 * @param 		Game* -> a game in which the data of the objects will be loaded.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS game_management_load_objects(Game *game, char *filename);

/**
 * @name 		game_management_load_links
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It loads the data of the links from the passed filename to the passed game.
 * @param 		char* -> a string with the name of the file containing the data of the links.
 * @param 		Game* -> a game in which the data of the links will be loaded.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS game_management_load_links(Game *game, char *filename);

/**
 * @name 		game_management_load
 * @author 		Eric Morales
 * @version             1.0
 * @date		03-05-2018
 * @brief 		It loads the data of the game from the passed filename to the passed game.
 * @param 		char* -> a string with the name of the file containing the data of the game (data.dat)
 * @param 		Game* -> a game in which the data of the game will be loaded.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS game_management_load(Game *game, char *filename);

/**
 * @name 		game_management_save
 * @author 		Eric Morales
 * @version             1.0
 * @date		03-05-2018
 * @brief 		It saves the data from the passed game to the passed filename.
 * @param 		char* -> a string where the name of the file that is going to be saved.
 * @param 		Game* -> a game that we are going to save. 
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS game_management_save(Game *game, char *filename);

#endif