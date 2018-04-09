/**
 * @brief               It defines a player and the necessary functions to work with it.
 * @file                player.h
 * @author              Alejandro Pascual and Victor Yrazusta
 * @version             1.0
 * @date                13-02-2018
 * @copyright           GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "inventory.h"


/**
 * @brief               It holds the necessary data to manage a player.
 */
typedef struct _Player Player;


/**
 * @name 		player_create
 * @author 		Victor Yrazusta, edited by Alejandro Pascual
 * @version             1.0
 * @date		19-02-2018
 * @brief               It creates a player with the id passed.
 * @param               Id -> the Id of the created player.
 * @param               int -> which will define the size of the inventory of the player.
 * @return		A Player*, which points towards the created player.
 */
Player *player_create(Id, int inventory_size);


/**
 * @name 		player_destroy
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		19-02-2018
 * @brief               It deallocates the memory reserved for the Player* passed.
 * @param               Player* -> a player which will be deallocated.
 * @return		A STATUS, which could be ERROR if the pointer passed as an argument is NULL, or OK otherwise.
 */
STATUS player_destroy(Player *);


/**
 * @name 		player_set_name
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		19-02-2018
 * @brief               It changes the name of the passed player to the passed name.
 * @param               Player* -> a player whose name will be changed.
 * @param       	char* -> a string with the new name for the player.
 * @return		A STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 */
STATUS player_set_name(Player *, char *name);


/**
 * @name 		player_set_graphic_description
 * @author 		Eric Morales
 * @version             1.0
 * @date		04-04-2018
 * @brief               It changes the graphic_description of the passed player to the passed graphic_description.
 * @param               Player* -> the player whose graphic_description will be changed.
 * @param       	char* -> a string with the new graphic_description for the player.
 * @return		A STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 */
STATUS player_set_graphic_description(Player *, char *graphic_description);


/**
 * @name 		object_set_location
 * @author 		V�ctor Yrazusta
 * @version             1.0
 * @date		19-02-2018
 * @brief               It changes the location of the passed player to the passed id of the new location.
 * @param               Player* -> the player whose location will be changed.
 * @param               Id -> the new location for the player.
 * @return		A STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 */
STATUS player_set_location(Player *, Id location);


/**
 * @name 		object_add_object
 * @author 		Alejandro Pascual 
 * @version             2.0
 * @date		19-02-2018
 * @brief               It adds the object id to the set of the inventory of the player.
 * @param               Player* -> the player whose inventory will be modified
 * @param               Id -> the (object) id that will be added to the set.
 * @return		A STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 */
STATUS player_add_object(Player *, Id object_id);


/**
 * @name 		object_del_object
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		19-02-2018
 * @brief               It removes the object id from the set of the inventory of the player.
 * @param               Player* -> a player whose inventory will be modified.
 * @param		Id -> the (object) id that will be removed from the set.
 * @return		A STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 */
STATUS player_del_object(Player *, Id object_id);


/**
 * @name 		player_get_name
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		19-02-2018
 * @brief               It returns the name of the player passed as an argument.
 * @param               Player* -> the player whose name will be returned.
 * @return		A const char*, which could be NULL if the pointer passed as an argument is NULL, or the player's name otherwise.
 */
const char *player_get_name(Player *);


/**
 * @name 		player_get_graphic_description
 * @author 		Eric Morales
 * @version             1.0
 * @date		04-04-2018
 * @brief               It returns the graphic_description of the player passed as an argument.
 * @param               Player*  -> the player whose graphic_description will be returned.
 * @return		A const char*, which could be NULL if the pointer passed as an argument is NULL, or the player's graphic_description otherwise.
 */
const char *player_get_graphic_description(Player *);


/**
 * @name 		object_get_id
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		19-02-2018
 * @brief               It returns the id of the player passed as an argument.
 * @param               Player* -> the player whose id will be returned.
 * @return		An Id, which could be NO_ID if the pointer passed as an argument is NULL, or the player's id otherwise.
 */
Id player_get_id(Player *);


/** 
 * @name 		player_get_location
 * @author 		V�ctor Yrazusta
 * @version             1.0
 * @date		19-02-2018
 * @brief               It returns the id of the location of the player passed as an argument.
 * @param               Player* -> the player whose location id will be returned.
 * @return		The Id, which could be NO_ID if the pointer passed as an argument is NULL, of the player's location id otherwise.
 */
Id player_get_location(Player *);


/** 
 * @name 		player_get_objects_number
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief               It returns the current number of objects in the inventory of the player.
 * @param               Player* -> the player from which we will get the number of objects.
 * @return		An int, which is the current number of objects in the inventory of the player.
 */

int player_get_objects_number(Player *);


/**
 * @name 		player_get_max_objects
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief               It returns the capacity of the Inventory of the Player.
 * @param               Player* -> a player from which we will get the maximum number of objects.
 * @return		An int, which is the capacity of the Inventory of the Player and 0 if the Player or the Inventory are NULL.
 */
int player_get_max_objects(Player *);


/**
 * @name 		player_get_object
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief               It returns the id of the object in the postion specified on the set of the inventory of the player.
 * @param               Player* -> the player which we will get the object from.
 * @param		int -> an integer that specifies the postion in the set.
 * @return		The Id, which could be NO_ID if the pointer passed as an argument is NULL, of the object in the specified position on the set.
 */
Id player_get_object(Player *, int position);


/**
 * @name 		player_check_object
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		03-04-2018
 * @brief               It checks if the passed object_id is in the set of the inventory of the player.
 * @param               Player* -> the player whose inventory will be checked seaching the object.
 * @param               Id -> the id of the object to be checked.
 * @return		A Bool, which is true if passed object id is in the set of the inventory of the player.
 */
BOOL player_check_object(Player *, Id object_id);


/**
 * @name 		player_is_empty
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		31-03-2018
 * @brief               This function is used to check if the inventory of player is empty.
 * @param               Player* -> a player whose inventory will be checked.
 * @return		A Bool, which is true if the inventory of the player is empty or if the player is NULL.
 */
BOOL player_is_empty(Player *);


/**
 * @name 		player_is_full
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		31-03-2018
 * @brief               This function is used to check if the inventory of player is full.
 * @param               Player* -> whose inventory will be checked.
 * @return		A Bool, which is true if the inventory of the player is full or if the player is NULL.
 */
BOOL player_is_full(Player *);


/**
 * @name 		player_print
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		19-02-2018
 * @brief               It prints on the standard output the values of the player passed as an argument.
 * @param               Player* -> whose data will be printed.
 * @return		A STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 * @details             NOTE: This function was created for debugging purposes only and it is not used in the normal execution of the game.
 */
STATUS player_print(Player *);

#endif
