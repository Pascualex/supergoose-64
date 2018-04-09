/** 
 * @brief It defines the die functions
 * @file die.c
 * @author Victor Yrazusta
 * @version 1.0 
 * @date 
 * @updated 
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/*Own libraries*/
#include "../include/die.h"

/*We define the die as an structure with three parameters:*/
struct _Die {
	Id id;                  /*The dies Id to distinguish it from other dies.*/
	int last_roll;          /*The last_roll value, to use it in modules as graphic_engine.*/
	int faces_number;       /*The number of faces, to define special dices in case of need.*/
};

/*The following function allocates memory for a die of the given size, with the given Id, rolling it for a first time so that it has a random last roll value.*/
Die *die_create(Id id, int faces_number) {
	Die *die = NULL;
	
	if (faces_number <= 0) {
		return NULL;
	}
	
	die = (Die *) malloc(sizeof(Die));
	srand(time(NULL));

	if(die == NULL) {
		return NULL;
	}
	
	die->id = id;
	die->faces_number = faces_number;
	die_roll(die);

	return die;
}

/*The following function frees the memory the given die is allocating.*/
STATUS die_destroy(Die *die) {
	
	if (die == NULL) {
		return ERROR;
	}
	
	free(die);
	return OK;
}

/*The next function returns the Id of the given die.*/
Id die_get_id(Die *die) {

	if (die == NULL) {
		return NO_ID;
	}

	return die->id;
}

/*This function rolls the die, giving it a random value between 1 and the number of maximum faces defined by the game. Then, returns the new value.*/
int die_roll(Die *die) {
	
	if (die == NULL || die->faces_number == 0) {
		return -1;
	}

	die->last_roll = rand()%die->faces_number + 1;
	return die->last_roll;
}

/*The following function returns the value of the last roll, without modifying it, for the graphic engine functions.*/
int die_get_value(Die* die){
    if (!die){
		return -1;
	}

    return die->last_roll;
}

/*The next function sets the number of faces of a die.*/
STATUS die_set_faces_number(Die *die, int faces_number) {
	
	if (die == NULL) {
		return ERROR;
	}
	
	die->faces_number = faces_number;
	return OK;
}

/*The following function prints the die info for debugging and testing purposes.*/
STATUS die_print(Die* die) {

	if (die == NULL) {
		return ERROR;
	}

	fprintf(stdout, "--> Die (Id: %ld; Last roll: %d; N. of Faces: %d)\n", die->id, die->last_roll, die->faces_number);

	return OK;
}
