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
 * @author 		Alejandro Pascual edited by Eric Morales and Victor Yrazusta
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
STATUS object_set_check(Object *, char check[MAX_TDESC_R][MAX_TDESC_C]);

/**
 * @name 		object_set_alt_check
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		17-04-2018
 * @brief               It changes the alternative check of the passed object to the passed char**.
 * @param               Object* -> which must point towards the object that wants to be renamed.
 * @param               char -> a string with the new alternative check for the object.
 * @return		An STATUS, which could be "ERROR" if one of the passed pointers is NULL or if the rename fails, or "OK" otherwise.
 */
STATUS object_set_alt_check(Object *, char check[MAX_TDESC_R][MAX_TDESC_C]);

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
 * @name 		object_get_alt_check
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		17-04-2018
 * @brief               It returns the alternative check of the object passed as an argument.
 * @param               Object* -> an object whose alternative check will be returned.
 * @return		A char**, which could be NULL if the pointer passed as an argument is NULL, or the object's alternative check otherwise.
 */
char **object_get_alt_check(Object *);

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

/**
 * @name 		object_add_tags
 * @author 		Victor Yrazusta edited by Victor Yrazusta
 * @version             2.0
 * @date		10-04-2018 (creation) 11-04-2018 (edition)
 * @brief               It adds the passed tags to the passed object.
 * @param               Object* -> an object which will recieve the tags.
 * @param               num_tags-> the amount of tags that the funcion will add.
 * @return		A STATUS that indicates whether the funcion was executed correctly or not.
 * @details				NOTE: This funcion has a variable number of input parameters.
 */
STATUS object_add_tags(Object *, int num_tags, ...);

/**
 * @name 		object_get_tags
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		10-04-2018
 * @brief               It returns all the tags that an object has.
 * @param               Object* -> an object whose tags will be returned.
 * @return		An TAG* which will point towards the tags hold by the passed object.
 */
TAG *object_get_tags(Object *);

/**
 * @name 		object_get_tags_number
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		10-04-2018
 * @brief               It returns the number of tags an object has.
 * @param               Object* -> an object whose number of tags will be returned.
 * @return		A unsigned int, which is the amount of tags that the passed object has.
 */
int object_get_tags_number(Object *);

/**
 * @name 		object_is
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		10-04-2018
 * @brief               It checks if an object has a specified tag.
 * @param               Object* -> an object which will be checked.
 * @param               TAG 	-> the tag that the function will look for.
 * @return		A BOOL, that indicates wheter or not the object has the passed tag.
 */
BOOL object_is(Object *, TAG);

/**
 * @name 		object_remove_tag
 * @author 		Victor Yrazusta
 * @version             1.0
 * @date		11-04-2018
 * @brief               It removes a specified tag from an object.
 * @param               Object* -> an object who will have one of his tags removed.
 * @param               TAG 	-> the tag to remove from the object.
 * @return		A STATUS that indicates whether the funcion was executed correctly or not.
 */
STATUS object_remove_tag(Object *, TAG);

#endif
