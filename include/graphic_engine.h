/**
 * @brief               It defines a textual graphic engine
 * @file                graphic_engine.h
 * @author              Profesores PPROG edited by Javier Lougedo, Victor Yrazusta, Eric Morales & Alejandro Pascual
 * @version             4.0 
 * @date                18-01-2017 
 * @copyright           GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

/**
 * @brief               It holds the necessary data to manage a Graphic Engine.
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @name 		graphic_engine_create
 * @author 		Profesores PPROG edited by Eric Morales
 * @version             2.0
 * @date		02-03-2018
 * @brief               It allocates memory for a Graphic Engine we will be using to print.
 * @return		A Graphic Engine.
 */
Graphic_engine* graphic_engine_create();

/**
 * @name 		graphic_engine_destroy
 * @author 		Profesores PPROG edited by Eric Morales
 * @version             1.0
 * @date		02-03-2018
 * @brief               It frees the memory a Graphic Engine was allocating.
 * @param               Graphic_engine* -> a graphic engine to be freed.
 * @return		A void, with nothing important.
 */
void graphic_engine_destroy(Graphic_engine *ge);

/** 
 * @name 		graphic_engine_paint_game
 * @author 		Profesores PPROG edited by Alejandro Pascual, Eric Morales & Javier Lougedo.
 * @version             3.0
 * @date		02-03-2018
 * @brief               It paints the game on the screen with all its info.
 * @param               Graphic_engine* -> a graphic engine that will define where to print.
 * @param               Game* -> a game with the information to print on the screen.
 * @return		A void.
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/** 
 * @name 		graphic_engine_write_command
 * @author 		Eric Morales.
 * @version             3.0
 * @date		02-03-2018
 * @brief               It writes the last command and if it worked on the screen.
 * @param               Graphic_engine* -> a graphic engine that will define where to print.
 * @param               char* -> a string with the command text to print on the screen.
 * @return		A void.
 */
void graphic_engine_write_command(Graphic_engine *ge, char *str);

/**
 * @name 		graphic_engine_write_command
 * @author 		Alejandro Pascual.
 * @version             3.0
 * @date		02-03-2018
 * @brief               It writes the last command and if it worked on the screen.
 * @param               Game* -> a game to get the objects from.
 * @param               Space* -> a space where we will 'extract' the objects to print.
 * @return		A wchar_t with the symbol of the object (its initial).
 */
wchar_t *graphic_engine_get_objects_symbols(Game *, Space *);

#endif
