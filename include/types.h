/**
 * @brief It defines common types
 * @file types.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define MAX_CHECK_C 75              /*!< Maximum columns of the check field*/
#define MAX_CHECK_R 3               /*!< Maximum rows of the check field*/

#define MAX_GDESC_C 8               /*!< Maximum columns of the graphic description field*/
#define MAX_GDESC_R 3               /*!< Maximum rows of the graphic description field*/

#define MAX_NAME 128                /*!< Maximum characters of a link name*/
#define WORD_SIZE 1000              /*!< Maximum size of some of the names (players, objects and else)*/

#define NO_ID -1                    /*!< Default Id used when there is no Id or something works as it shouldn't*/
#define NOT_FOUND -1                /*!< Used when a set doesnt found the given Id position*/

#define SET_MAX_IDS 5               /*!< Maximum number of Ids a set can store*/
#define MAX_SPACES 100              /*!< Maximum number of spaces a game is prepared to store*/
#define MAX_PLAYERS 10              /*!< Maximum number of players a game is prepared to store*/
#define MAX_OBJECTS 10              /*!< Maximum number of objects a game is prepared to store*/
#define MAX_DIES 10                 /*!< Maximum number of dies a game is prepared to store*/
#define MAX_LINKS 50                /*!< Maximum number of links a game is prepared to store*/
#define MAX_TAGS 10					/*!< Maximun number of tags an object can have*/

#define ID_RANGE 1000               /*!< Used to define the maximum amount of elements from each type we can manage*/
#define SPACE_BASE_ID 0000          /*!< Marks where the Spaces Ids start*/
#define PLAYER_BASE_ID 1000         /*!< Marks where the Players Ids start*/
#define OBJECT_BASE_ID 2000         /*!< Marks where the Objects Ids start*/
#define DIE_BASE_ID 3000            /*!< Marks where the Dies Ids start*/
#define LINK_BASE_ID 4000           /*!< Marks where the Links Ids start*/

/** 
 * @brief Id (to store Ids of objects, players, etc)
 */
typedef long Id;

/** 
 * @brief Boolean (to store boolean values that are or not)
 */
typedef enum {
    FALSE, /*!< If the condition is not fullfilled*/
    TRUE /*!< If the condition is correct and real*/
} BOOL;

/** 
 * @brief Status (to store all the executions, if correct or not)
 */
typedef enum {
    ERROR, /*!< If something went wrong*/
    OK /*!< If all worked correctly*/
} STATUS;

/**
 * @brief Command enumeration (to be used on command.c
 */
typedef enum {
    NO_CMD = -1, /*!< No command */
    UNKNOWN, /*!< Unknown command (beginning)*/
    EXIT, /*!< Exit game */
    FOLLOWING, /*!< Following space (old)*/
    PREVIOUS, /*!< Previous space (old) */
    GRASP, /*!< Grasp an object */
    DROP, /*!< Drop an object */
    THROW, /*!< Roll the die */
    RIGHT, /*!< Right space (old) */
    LEFT, /*!< Left space (old) */
    MOVE, /*!< Move to a direction */
    CHECK
} T_Command;

/** 
 * @brief Direction (to be used when moving through the board)
 */
typedef enum {
    ERR = -1, /*!< If something went wrong*/
    N, /*!< When going North*/
    W, /*!< When going West*/
    S, /*!< When going South*/
    E /*!< When going East*/
} DIRECTION;

/**
 * @brief LINK_STATUS enumeration (to be used on links)
 */
typedef enum {
    OPEN = 0, /*!< Open link*/
    CLOSED = 1 /*!< Closed link*/
} LINK_STATUS;

/**
 * @brief COLOR enumeration (to be used when painting the graphic engine)
 */
typedef enum {
    BLACK, /*!< BLACK COLOR*/
    RED, /*!< RED COLOR*/
    GREEN, /*!< GREEN COLOR*/
    YELLOW, /*!< YELLOW COLOR*/
    BLUE, /*!< BLUE COLOR*/
    PURPLE, /*!< PURPLE COLOR*/
    CYAN, /*!< CYAN COLOR*/
    WHITE /*!< WHITE COLOR*/
} COLOR;

/**
 * @brief TAG enumeration (to be used when asigning propierties to objects)
 */
typedef enum {
	NO_TAG = 0,		/*!< Tag not specified*/
	VISIBLE, 		/*!< The object is visible*/
	MOVABLE,		/*!< The object can be moved*/
	MOVED,			/*!< The object has been moved*/
	HIDDEN,			/*!< The object is hidden*/
	CAN_GLOW,		/*!< The object is able to glow*/
	GLOWING,		/*!< The object is glowing*/
	IS_KEY			/*!< The object is a key*/
} TAG;

#endif

/*DOXYGEN MAINPAGE*/
/**
 * @mainpage Main Page
 *
 * @section intro_sec SuperGoose_64
 *
 * Welcome to our incredible game! Please, have fun while playing it and remember to ask the creators if you have any doubts. Cheers :)
 *
 * @section install_sec The creators
 *
 * @subsection step1 Eric Morales:
 *  
 * 	eric.morales@estudiante.uam.es
 *
 * @subsection step2 Victor Yrazusta:
 *  
 * 	victor.yrazusta@estudiante.uam.es
 *
 * @subsection step3 Alejandro Pascual:
 *  
 * 	alejandro.pascualp@estudiante.uam.es
 *
 * @subsection step4 Javier Lougedo:
 *  
 * 	javier.lougedo@estudiante.uam.es
 *
 */