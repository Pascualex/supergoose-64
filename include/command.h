/**
 * @brief               It implements the command interpreter and the necessary functions to work with it.
 * @file                command.h
 * @author              Profesores PPROG edited by Victor Irazustra, Alejandro Pascual, Eric Morales.
 * @version             3.0 
 * @date                19-12-2014 (creation) 02-04-2018 (last edit).
 * @copyright           GNU Public License.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

/**
 * @brief               It holds the necessary data to manage a command.
 */
typedef struct _Command Command;

/**
 * @name 		command_create
 * @author 		Alejandro Pascual 
 * @version             1.0
 * @date		16-03-2018
 * @brief               It allocates the memory for a Command structure.			
 * @return		A Command*. 
 */
Command *command_create();

/**
 * @name 		command_destroy
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		16-03-2018
 * @brief               It frees the memory of the passed Command*.
 * @param               Command* -> The command to be freed..
 * @return		A STATUS, which indicates if the process was executed successfully or not. 
 */
STATUS command_destroy(Command *);

/**
 * @name 		command_get_user_input
 * @author 		Profesores PPROG, edited by Victor Yrazusta and Alejandro Pascual
 * @version             3.0
 * @date		07-03-2018
 * @brief               It gets an input command from the user.
 * @param               Command* -> a command in which the input from the user will be stored. 
 * @return		A STATUS, which indicates if the process was executed successfully or not. 
 */
STATUS command_get_user_input(Command *);

/**
 * @name 		command_proMode
 * @author 		Eric Morales
 * @version             1.0
 * @date		03-05-2018
 * @brief               It gets an input command from the use, but only one character.
 * @param               Command* -> a command in which the input from the user will be stored. 
 * @return		A STATUS, which indicates if the process was executed successfully or not. 
 */
STATUS command_proMode(Command *command);

/**
 * @name 		command_get_command
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		07-03-2018
 * @brief               It returns the T_Command of the Command* passed as an argument.
 * @param               Command* -> a command whose T_Command will be returned.
 * @return		A T_Command, which could be "NO_CMD" if the passed pointer is NULL, or the command's T_Command otherwise.
 */
T_Command command_get_command(Command *);

/**
 * @name 		command_get_info
 * @author 		Víctor Yrazusta
 * @version         	1.0
 * @date		07-03-2018
 * @brief               It returns the info of the Command* passed as an argument.
 * @param               Command* -> a command whose info will be returned.
 * @return		A char*, which could be NULL if the passed pointer is NULL, or the command's info otherwise.
 */
char *command_get_info(Command *);

/**
 * @name 		command_print
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		07-03-2018
 * @brief               It prints on the standard output the values of the command passed as an argument.
 * @param               Command* -> a command whose data will be printed.
 * @return		An STATUS, which could be "ERROR" if the pointer passed as an argument is NULL, or "OK" otherwise.
 * @details             NOTE: This function was created for debugging purposes only and it is not used in the normal execution of the game.
 */
STATUS command_print(Command *);

/**
 * @name 		command_get_str
 * @author 		Eric Morales edited by Victor Yrazusta
 * @version             2.0
 * @date		19-02-2018
 * @brief               This function gets the Command as a char to be used on the graphic_engine.
 * @param               Command* -> a command we will get the string from.
 * @return		A const char* with the string of the command.
 */
const char *command_get_str(T_Command);

#endif