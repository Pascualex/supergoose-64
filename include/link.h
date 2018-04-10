/**
 * @brief               It defines a link and the different functions it needs to be managed.
 * @file                link.h
 * @author              Víctor Yrazusta
 * @version             2.0
 * @date                26-03-2018 (creation) 26-03-2018 (last edit)
 * @copyright           GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

/**
 * @brief 		It holds the necessary data to manage a link.
 */
typedef struct _Link Link;

/**
 * @name 		link_create
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It creates a link with the id passed.
 * @param 		Id -> the id for the new link.
 * @return		A Link*, which points towards the created link.
 */
Link *link_create(Id);

/**
 * @name 		link_destroy
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It destroys the link passed.
 * @param 		Link* -> the link which will be destroyed.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS link_destroy(Link *);

/**
 * @name 		link_set_name
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It changes the name of the passed link.
 * @param 		Link* -> the link whose name will be changed.
 * @param 		char -> a string with the new name for the link.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS link_set_name(Link *, char name[MAX_NAME]);

/**
 * @name 		link_add_space
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It adds a new space in a link.
 * @param 		Link* -> the link in which the space will be inserted.
 * @param 		Id -> the Id of the space to be inserted.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS link_add_space(Link *, Id);

/**
 * @name 		link_set_status
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It changes the status of the link.
 * @param 		Link* -> the link whose status will be changed.
 * @param 		LINK_STATUS -> the new status for the link.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 */
STATUS link_set_status(Link *, LINK_STATUS status);

/**
 * @name 		link_get_id
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It returns the Id of the passed link.
 * @param 		Link* -> the link whose Id will be returned.
 * @return		An Id of the link passed.
 */
Id link_get_id(Link *);

/**
 * @name 		link_get_name
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It returns the name of the passed link.
 * @param 		Link* -> the link whose name will be returned.
 * @return		A char with the name of the link passed.
 */
char *link_get_name(Link *);

/**
 * @name 		link_get_other_side
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It returns the Id of the other side of a link.
 * @param 		Link* -> the link in which the other space will be searched.
 * @param 		Id -> Id of the space of one side of the link.
 * @return		An Id of the space of the side oposing the passed Id.
 */
Id link_get_other_side(Link *, Id);

/**
 * @name 		link_get_status
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It returns the status of the link passed.
 * @param 		Link* -> the link whose status will be returned.
 * @return		A STATUS of the link passed.
 */
LINK_STATUS link_get_status(Link *);

/**
 * @name 		link_print
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		26-03-2018
 * @brief 		It prints on the standard output all the data that hold the link passed.
 * @param 		Link* -> the link whose data will be printed.
 * @return		A STATUS which indicates whether the operation could be executed correctly.
 * @details             NOTE: This function was created for debugging purposes only and it is not used in the normal execution of the game.
 */
STATUS link_print(Link *);

#endif
