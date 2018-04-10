/**
 * @brief               It defines an object and the necessary functions to use it
 * @file                object.h
 * @author              Alejandro Pascual, Victor Yrazusta edited by Eric Morales
 * @version             2.0
 * @date                13-02-2018
 * @copyright           GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/** 
 * @brief               It holds the necessary data to manage an object.
 */
typedef struct _Object Object;

/**
 * @name 		object_create
 * @author 		Alejandro Pascual edited by Eric Morales
 * @version             2.0
 * @date		19-02-2018
 * @brief               It creates an object with the id passed.
 * @param               Id -> the Id of the created object.
 * @return		An Object*, which points towards the created object.
 */
Object *object_create(Id);

/**
 * @name 		object_destroy
 * @author 		Victor Yrazusta edited by Eric Morales
 * @version             2.0
 * @date		19-02-2018
 * @brief               It deallocates the memory reserved for the Object* passed.
 * @param               Object* -> the object which will be deallocated.
 * @return		An STATUS, which could be ERROR if the pointer passed as an argument is NULL, or OK otherwise.
 */
STATUS object_destroy(Object *);

/**
 * @name 		object_set_check
 * @author 		Eric Morales
 * @version             1.0
 * @date		26-03-2018
 * @brief               It changes the check of the passed object to the passed char**.
 * @param               Object* -> which must point towards the object that wants to be renamed.
 * @param               char -> a string with the new check for the object.
 * @return		An STATUS, which could be "ERROR" if one of the passed pointers is NULL or if the rename fails, or "OK" otherwise.
 */
STATUS object_set_check(Object *, char check[MAX_CHECK_R][MAX_CHECK_C]);

/**
 * @name 		object_set_name
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		19-02-2018
 * @brief               It changes the name of the passed object to the passed char*.
 * @param               Object* -> which must point towards the object that wants to be renamed.
 * @param               char -> a string with the new name for the object.
 * @return		An STATUS, which could be "ERROR" if one of the passed pointers is NULL or if the rename fails, or "OK" otherwise.
 */
STATUS object_set_name(Object *, char *name);

/**
 * @name 		object_set_location
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		19-02-2018
 * @brief               It changes the location of the passed object to the passed id of the new location.
 * @param               Object* -> an object whose location will be changed.
 * @param               Id -> an id with the new location for the object.
 * @return		An STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 */
STATUS object_set_location(Object *, Id location);

/**
 * @name 		object_get_name
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		19-02-2018
 * @brief               It returns the name of the object passed as an argument.
 * @param               Object* -> an object whose name will be returned.
 * @return		A const char*, which could be NULL if the pointer passed as an argument is NULL, or the object's name otherwise.
 */
const char *object_get_name(Object *);

/**
 * @name 		object_get_check
 * @author 		Eric Morales
 * @version             1.0
 * @date		26-03-2018
 * @brief               It returns the check of the object passed as an argument.
 * @param               Object* -> an object whose check will be returned.
 * @return		A char**, which could be NULL if the pointer passed as an argument is NULL, or the object's check otherwise.
 */
char **object_get_check(Object *);

/**
 * @name 		object_get_id
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		19-02-2018
 * @brief               It returns the id of the object passed as an argument.
 * @param               Object* -> an object whose id will be returned.
 * @return		A const char*, which could be NO_ID if the pointer passed as an argument is NULL, or the object's id otherwise.
 */
Id object_get_id(Object *);

/**
 * @name 		object_get_location
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		19-02-2018
 * @brief               It returns the id of the location of the object passed as an argument.
 * @param               Object* -> an object whose location id will be returned.
 * @return		An Id, which could be NO_ID if the pointer passed as an argument is NULL, or the object's location id otherwise.
 */
Id object_get_location(Object *);

/**
 * @name 		object_print
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		19-02-2018
 * @brief               It prints on the standard output the values of the object passed as an argument.
 * @param               Object* -> an object whose data will be printed.
 * @return		An STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 * @details             NOTE: This function was created for debugging purposes only and it is not used in the normal execution of the game.
 */
STATUS object_print(Object *);

#endif
