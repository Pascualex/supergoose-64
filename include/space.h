/**
 * @brief               It defines the space and the needed functions
 * @file                space.h
 * @author              Profesores PPROG and Eric Morales
 * @version             1.0 
 * @date                13-01-2015
 * @copyright           GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"

/**
 * @brief               It holds the necessary data to manage a space.
 */
typedef struct _Space Space;

/** 
 * @name 		space_create
 * @author 		Profesores PPROG edited by Eric Morales
 * @version             2.0
 * @date		18-03-2018
 * @brief 		It creates a space with the id passed.
 * @param 		Id with the id for the new space.
 * @return		A Link*, which points towards the created space.
 */
Space *space_create(Id);

/** 
 * @name 		space_destroy
 * @author 		Profesores PPROG edited by Eric Morales
 * @version             2.0
 * @date		13-01-2015
 * @brief 		It destroys the space passed.
 * @param 		Space* with the space which will be destroyed.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS space_destroy(Space *);

/** 
 * @name 		space_set_name
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		13-01-2015
 * @brief 		It changes the name of the passed space.
 * @param 		Space* with the space whose name will be changed.
 * @param 		schar with the new name for the space.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS space_set_name(Space *, char *name);

/** 
 * @name 		space_set_direction
 * @author 		Alejandro Pascual
 * @version             3.0
 * @date		11-04-2018
 * @brief 		It changes the Link of the passed DIRECTION of the passed Space.
 * @param 		Space* with the space whose Link will be changed.
 * @param		DIRECTION wich specifies which Link will be changed.
 * @param 		Id with the new Link for the Space.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS space_set_direction(Space *, DIRECTION, Id);

/** 
 * @name 		space_add_object
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It adds an object to the passed space.
 * @param 		Space* with the space in which the object will be inserted.
 * @param 		Id, with the Id of the object to be inserted.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS space_add_object(Space *, Id object_id);

/** 
 * @name 		space_del_object
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It deletes an object from the passed space.
 * @param 		Space* with the space in which the object will be deleted.
 * @param 		Id with the Id of the object to be deleted.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS space_del_object(Space *, Id object_id);

/** 
 * @name 		space_set_graphic_description
 * @author 		Alejandro Pascual edited by Eric Morales
 * @version             2.0
 * @date		05-03-2018
 * @brief 		It changes the graphic description of the passed space.
 * @param 		Space* with the space whose graphic description will be changed.
 * @param 		char with the new graphich description for the space.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS space_set_graphic_description(Space *, char graphic_description[3][8]);

/** 
 * @name 		object_set_check
 * @author 		Eric Morales
 * @version             1.0
 * @date		26-03-2018
 * @brief               It changes the check description of the passed object to the passed char**.
 * @param               Object*, which must point towards the object that wants to be renamed.
 * @param		check, with the new description for the object.
 * @return		An STATUS, which could be "ERROR" if one of the passed pointers is NULL or if the rename fails, or "OK" otherwise.
 */
STATUS space_set_check(Space *, char check[MAX_CHECK_R][MAX_CHECK_C]);

/** 
 * @name 		space_get_id
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		13-01-2015
 * @brief 		It returns the Id of the passed space.
 * @param 		Space* with the space whose Id will be returned.
 * @return		An Id with the Id of the space passed.
 */
Id space_get_id(Space *);

/** 
 * @name 		space_get_name
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		13-01-2015
 * @brief 		It returns the name of the passed space.
 * @param 		Space* with the space whose name will be returned.
 * @return		The name of the space passed.
 */
const char *space_get_name(Space *);

/** 
 * @name 		space_get_check
 * @author 		Eric Morales
 * @version             1.0
 * @date		26-03-2018
 * @brief               It returns the check of the space passed as an argument.
 * @param               Space*, whose name will be returned.
 * @return		A char**, which could be NULL if the pointer passed as an argument is NULL, or the object's check otherwise.
 */
char **space_get_check(Space *);

/** 
 * @name 		space_get_direction
 * @author 		Alejandro Pascual 
 * @version             3.0
 * @date		26-04-2018
 * @brief 		It returns the Link of the passed DIRECTION of the passed Space.
 * @param 		Space* with the Space whose Link will be returned.
 * @param		DIRECTION wich specifies which Link will be returned.
 * @return		The Link of passed DIRECTION of the space passed.
 */
Id space_get_direction(Space *, DIRECTION);

/**
 * @name 		space_get_object_id
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It returns the id of the object that is in a certain position in the space.
 * @param 		Space* with the space in which the object will be searched.
 * @param 		int with the position in which the object is located.
 * @return		An id of the object that is in the position passed of the space passed.
 */
Id space_get_object_id(Space *, int position);

/**
 * @name 		space_get_objects_number
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It returns the number of objects that the passed space holds.
 * @param 		Space* with the space whose number of objects will be returned.
 * @return		The number of objects that the passed space holds.
 */
int space_get_objects_number(Space *);

/**
 * @name 		space_get_graphic_description
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It returns the graphic description that the passed space holds.
 * @param 		Space* with the space whose graphic description will be returned.
 * @return		A char**, with the graphic description of the space passed.
 */
char **space_get_graphic_description(Space *);

/**
 * @name 		space_check_object
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It checks if the passed space contains the id passed.
 * @param 		Space* with the space in which the passed object_id will be searched.
 * @param 		Id with the id of the object to search.
 * @return		A BOOL that indicates whether the object is in the passed space.
 */
BOOL space_check_object(Space *, Id object_id);

/**
 * @name 		space_is_empty
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It checks if the passed space is empty.
 * @param               Space* with the space which will be checked.
 * @return		A BOOL that indicates whether the passed space is empty or not.
 */
BOOL space_is_empty(Space *);

/**
 * @name 		space_is_full
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It checks if the passed space is full.
 * @param 		Space* with the space which will be checked.
 * @return		A BOOL that indicates whether the passed space is full or not.
 */
BOOL space_is_full(Space *);

/**
 * @name 		space_print
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		05-03-2018
 * @brief 		It prints on the standard output all the data that hold the space passed.
 * @param 		Space* with the space whose data will be printed.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS space_print(Space *);

#endif
