/**
 * @brief               It defines the screen functions.
 * @file                screen.h
 * @author              Profesores PPROG edited by Alejandro Pascual
 * @version             1.0 
 * @date                11-01-2017
 * @copyright           GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

#include "types.h"

#define SCREEN_MAX_STR 80               /*!< The maximum size of an string to print*/

/**
 * @brief               It holds the necessary data to manage areas.
 */
typedef struct _Area Area;

/**
 * @name 		screen_init
 * @author 		Profesores PPROG edited by Alejandro Pascual
 * @version             1.0
 * @date		11-01-2017
 * @brief 		It allocates memory for the scree usage
 * @param		An int with the color of the screen.
 * @return		A void, without any relevant information.
 */
void screen_init(int color);

/**
 * @name 		screen_destroy
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		11-01-2017
 * @brief 		It frees the memory allocated by a screen.
 * @return		A void, without any relevant information.
 */
void screen_destroy();

/**
 * @name 		screen_paint
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		11-01-2017
 * @brief 		It paints the game information on the screen.
 * @return		A void, without any relevant information.
 */
void screen_paint();

/**
 * @name 		screen_gets
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		11-01-2017
 * @brief 		It gets the information to print on the screen from a character string.
 * @param 		char* -> a string with the data to print on the screen.
 * @return		A void, without any information.
 */
void screen_gets(char *);

/**
 * @name 		screen_area_init
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		11-01-2017
 * @brief 		It initializes the area we will be printing in of a screen (the white boxes).
 * @param 		int -> an integer with the X coordinates to start from.
 * @param 		int -> an integer with the Y coordinates to start from.
 * @param 		int -> an integer with the width of the area.
 * @param 		int -> an integer with the height of the area.
 * @param		int -> an integer with the foreground color of the area.
 * @param		int -> an integer with the background color of the area.
 * @param		BOOL -> A BOOL that determines if the area has border or not.
 * @return		An Area, with the area created.
 */
Area *screen_area_init(int x, int y, int width, int height, int fg_color, int bg_color, BOOL has_border);

/**
 * @name 		screen_area_destroy
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		11-01-2017
 * @brief 		It frees the memory allocated by an area of the screen.
 * @param 		Area* -> an area to destroy.
 * @return		A void, without any relevant information.
 */
void screen_area_destroy(Area *);

/**
 * @name 		screen_area_clear
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		11-01-2017
 * @brief 		It empties an area of the screen (like cleaning it).
 * @param 		Area* -> the area to clear
 * @return		A void, without any relevant information.
 */
void screen_area_clear(Area *);

/**
 * @name 		screen_area_puts_char
 * @author 		Profesores PPROG
 * @version             1.0
 * @date		11-01-2017
 * @brief 		It puts on the area the given info.
 * @param 		Area* -> to print in.
 * @param       char* -> a string with the info to print.
 * @return		A void, without any relevant information.
 */
void screen_area_puts_char(Area *, char *);

/**
 * @name 		screen_color_box
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		04-04-2017
 * @brief 		It paints a colored square on the given coordinates.
 * @param 		int -> an integer with the X coordinates to start from.
 * @param 		int -> an integer with the Y coordinates to start from.
 * @param 		int -> an integer with the width of the area.
 * @param 		int -> an integer with the height of the area.
 * @param		int -> an integer with the foreground color of the area.
 * @param		int -> an integer with the background color of the area.
 * @return		A void, without any relevant information.
 */
void screen_color_box(int x, int y, int width, int height, int fg_color, int bg_color);

/**
 * @name 		screen_add_border
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		04-04-2018
 * @brief 		It puts a border on the given area.
 * @param 		int -> an integer with the X coordinates to start from.
 * @param 		int -> an integer with the Y coordinates to start from.
 * @param 		int -> an integer with the width of the area.
 * @param 		int -> an integer with the height of the area.
 * @param		int -> an integer with the foreground color of the area.
 * @param		int -> an integer with the background color of the area.
 * @return		A void, without any relevant information.
 */
void screen_add_border(int x, int y, int width, int height, int fg_color, int bg_color);

#endif
