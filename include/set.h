/**
 * @brief               It defines the ADT Set, which manages a list of Ids
 * @file                set.h
 * @author              Victor Yrazusta and Alejandro Pascual
 * @date                23-02-2017
 * @copyright           GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/**
 * @brief               It holds the necessary data to manage a set.
 */
typedef struct _Set Set;

/**
 * @name 		set_create
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It allocates the memory for a Set structure. 		
 * @return		A Set*, with the memory allocated and all the fields initialized.
 */
Set *set_create();

/**
 * @name 		set_destroy
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It frees the memory for a Set structure.
 * @param               Set* -> a set whose memory will be deallocated.
 * @return		A STATUS, which indicates if the process was executed successfully or not. 
 */
STATUS set_destroy(Set *);

/**
 * @name 		set_add
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It adds an Id to the Set
 * @param               Set* -> a set in which the id will be added.	
 * @param		Id -> the id which will be added to the set.
 * @return		A STATUS, which indicates if the process was executed successfully or not. 
 */
STATUS set_add(Set *, Id);

/**
 * @name 		set_del
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It removes an Id of the Set
 * @param       	Set* -> the set from which the id will be removed.	
 * @param		Id -> the id to be removed from the set.
 * @return		A STATUS, which indicates if the process was executed successfully or not. 
 */
STATUS set_del(Set *, Id);

/**
 * @name 		set_get_id
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It returns the id of the indicated position of the Set.
 * @param               Set* -> the set we will get the id from.	
 * @param               int -> an integer which indicates the position of the Id in the Set.
 * @return		The Id of the selected position of the Set.
 */
Id set_get_id(Set *, int id_position);

/**
 * @name 		set_get_id_position
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It returns the position of the specified Id in the Set.
 * @param               Set* -> the set we are going to search in.	
 * @param               Id -> the id whose position in the Set will be returned.
 * @return		The position of the specified Id in the Set.
 */
int set_get_id_position(Set *, Id);

/**
 * @name 		set_get_ids_number
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It returns the number of Ids stored in the Set.
 * @param               Set* -> the set we will get the number of ids from.	
 * @return		The number of Ids stored in the Set.
 */
int set_get_ids_number(Set *);

/**
 * @name 		set_is_empty
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It returns a BOOL, which indicates if the Set is empty.
 * @param               Set* -> the set we are going to check if empty or not.
 * @return		A BOOL, which indicates if the Set is empty.
 */
BOOL set_is_empty(Set *);

/**
 * @name 		set_is_full
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It returns a BOOL, which indicates if the Set is full.
 * @param               Set* -> the set we are going to check if full.
 * @return		A BOOL, which indicates if the Set is full.
 */
BOOL set_is_full(Set *);

/** 
 * @name 		set_print
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		26-02-2018
 * @brief               It prints the info of the passed Set.
 * @param               Set* -> the set to be used.
 * @return		A STATUS, which indicates if the process was executed successfully or not. 
 * @details             NOTE: This function was created for debugging purposes only and it is not used in the normal execution of the game.
 */
STATUS set_print(Set *);

#endif
