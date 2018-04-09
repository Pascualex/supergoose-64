/**
 * @brief               It defines a die and the different functions it needs to be managed.
 * @file                die.h
 * @author              Víctor Yrazusta
 * @version             2.0
 * @date                13-02-2018 (creation) 22-03-2018 (last edit)
 * @copyright           GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include "types.h"


/**
 * @brief               It holds the necessary data to manage a die.
 */
typedef struct _Die Die;


/**
 * @name 		die_create
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		23-02-2018
 * @brief               It creates a die with the id and number of faces passed.
 * @param               Id -> an id which will be the Id of the die created.
 * @param               int -> an integer, which will be the number of faces of the die created.
 * @return		A Die*, which points towards the created die.
 */
Die *die_create(Id, int nFaces);


/**
 * @name 		die_destroy
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		23-02-2018
 * @brief               It deallocates the memory reserved for the Die* passed.
 * @param               Die* -> the die which will be deallocated.
 * @return		A STATUS, which could be ERROR if the pointer passed as an argument is NULL, or OK otherwise.
 */
STATUS die_destroy(Die *);


/**
 * @name 		die_get_id
 * @author 		Eric Morales
 * @version             1.0
 * @date		20-03-2018
 * @brief               It gets the Id of the given Die (as an argument).
 * @param               Die* -> a die which we will get the Id from.
 * @return		An Id, with the given Dies Id.
 */
Id die_get_id(Die *);


/**
 * @name 		die_get_value 
 * @author 		Eric Morales
 * @version             1.0
 * @date		20-03-2018
 * @brief               It gets the value of the last roll from the given Die (as an argument).
 * @param               Die* -> a die which will give us its last roll value.
 * @return		An integer, with the last value of the die (might be 0 if never rolled before).
 */
int die_get_value(Die* die);


/**
 * @name 		die_roll
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		23-02-2018
 * @brief               It rolls the die passed as an argument.
 * @param               Die* -> a die which will be rolled.
 * @return		An integer, which could be "-1" if the pointer passed as an argument is NULL or if it refers to a die that has no faces, or the result of rolling the die otherwise.
 */
int die_roll(Die *);


/**
 * @name 		die_set_nFaces
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		23-02-2018
 * @brief               It changes the number of faces of the die to a new value.
 * @param               Die* -> a die whose number of faces will be changed.
 * @param               int -> an integer which will indicate the new number of faces for the die.
 * @return		A STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 */
STATUS die_set_nFaces(Die *, int nFaces);


/**
 * @name 		die_print
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		23-02-2018
 * @brief               It prints on the standard output the values of the die passed as an argument.
 * @param               Die* -> a die whose data will be printed.
 * @return		A STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 * @details             NOTE: This function was created for debugging purposes only and it is not used in the normal execution of the game.
 */
STATUS die_print(Die *);

#endif
