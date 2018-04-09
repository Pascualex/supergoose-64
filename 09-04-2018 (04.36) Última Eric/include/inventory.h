/**
 * @brief               It implements the inventory interpreter and the different functions needed to use it.
 * @file                inventory.h
 * @author              Alejandro Pascual.
 * @version             1.0 
 * @date                01-04-2018 (creation)
 * @copyright           GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"


/**
 * @brief 		It holds the necessary data to manage an inventory.
 */
typedef struct _Inventory Inventory;


/**
 * @name 		inventory_create
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It creates an Inventory with the passed int as its capacity.
 * @param 		int -> an integer with the capacity of the new inventory.
 * @return		An Inventory*, which points towards the created inventory.
 */
Inventory *inventory_create(int max_ids);


/**
 * @name 		inventory_destroy
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It destroys the Inventory passed.
 * @param 		Inventory* -> the inventory we are willing to destroy.
 * @return		A STATUS, which indicates whether the operation could be executed correctly.
 */
STATUS inventory_destroy(Inventory *);


/**
 * @name 		inventory_add
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It adds the passed Id to the Set of the Inventory.
 * @param 		Inventory* -> the inventory we are willing to add an (object) id in.
 * @param		Id -> the Id of the object (or other).
 * @return		A STATUS, which indicates whether the operation could be executed correctly.
 */
STATUS inventory_add(Inventory *, Id object_id);


/**
 * @name 		inventory_del
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It removes the passed Id from the Set of the Inventory.
 * @param 		Inventory* -> the inventory we want to delete an object in.
 * @param		Id -> the Id of the object to be destroyed of the inventory.
 * @return		A STATUS, which indicates whether the operation could be executed correctly.
 */
STATUS inventory_del(Inventory *, Id object_id);


/**
 * @name 		inventory_set_max_objects
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It sets the capacity of the Inventory.
 * @param 		Inventory* -> the inventory whose max_objects is going to be set.
 * @param		int -> an integer that will define the capacity of the Inventory.
 * @return		A STATUS, which indicates whether the operation could be executed correctly.
 */
STATUS inventory_set_max_objects(Inventory *, int max_objects);


/**
 * @name 		inventory_get_object_id
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It returns the Id of the specified position in the Set of the Inventory.
 * @param 		Inventory* -> the inventory we are going to get the object from.
 * @param		int -> an integer that will specifie the position of the Id in the Set of the Inventory.
 * @return		The Id of the specified position in the Set of the Inventory.
 */
Id inventory_get_object_id(Inventory *, int position);


/**
 * @name 		inventory_get_objects_number
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It returns the current number of Ids in Set of the Inventory.
 * @param 		Inventory* -> the inventory we want to get the quantity of objects in.
 * @return		The current number of Ids in Set of the Inventory.
 */
int inventory_get_objects_number(Inventory *);


/**
 * @name 		inventory_get_max_objects
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It returns the capacity of the Inventory.
 * @param 		Inventory* -> the Inventory we want to get the max objects from.
 * @return		The capacity of the inventory as an int.
 */
int inventory_get_max_objects(Inventory *);


/**
 * @name 		inventory_check_object
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It checks if the passed Id is on the Set of the Inventory.
 * @param 		Inventory* -> the inventory we are going to check in.
 * @param 		Id -> the Id of the object to be checked.
 * @return		A BOOL, which is TRUE if the object is in the Set.
 */
BOOL inventory_check_object(Inventory *, Id object_id);


/**
 * @name 		inventory_is_empty
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It checks if the Set of the Inventory is empty.
 * @param 		Inventory* -> the inventory we will check if empty or not.
 * @return		A BOOL, which is TRUE if the Set of the Inventory is empty or if the Inventory* is NULL.
 */
BOOL inventory_is_empty(Inventory *);


/**
 * @name 		inventory_is_full
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It checks if the Set of the Inventory is full.
 * @param 		Inventory* -> the inventory we will check if full or not.
 * @return		A BOOL, which is TRUE if the Set of the Inventory is full or if the Inventory* is NULL.
 */
BOOL inventory_is_full(Inventory *);


/** 
 * @name 		inventory_print
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		01-04-2018
 * @brief 		It prints the content of the Set of the Inventory.
 * @param 		Inventory* -> the inventory to be printed.
 * @return		A STATUS, which indicates whether the operation could be executed correctly.
 * @details             NOTE: This function was created for debugging purposes only and it is not used in the normal execution of the game.
 */
STATUS inventory_print(Inventory *);

#endif