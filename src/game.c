/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#undef __STRICT_ANSI__

/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <wchar.h>
/*Own libraries*/
#include "../include/game.h"
#include "../include/game_management.h"
#include "../include/menu.h"

/*We define the number of functions we have related to the different commands.*/
#define N_CALLBACK 20
/*We define the number of possible directions to move for the move command.*/
#define N_DIR 6
/*INI is used to initialize those variable as the starting number of objects when they are 0.*/
#define INI 0
/*Used to define the number of dies. By the moment we can handle different dies, but with no purpose.*/
#define N_DIES 1
/*We define the number of faces we want our dies to have.*/
#define DIE_FACES 6
/*Used to define the Space where the player begins its journey.*/
#define START 1

/*We declare the structure of the game: */
struct _Game {
    Space *spaces[MAX_SPACES];      /*We define the spaces array for the MAX_SPACES we want to have*/
    Player *players[MAX_PLAYERS];   /*We define the players array, in case we want to handle more than one player in the future*/
    Object *objects[MAX_OBJECTS];   /*We define the objects array, to store all the objects of the game*/
    Die *dies[MAX_DIES];            /*We define the dies array to store all the dies we will be using*/
    Link *links[MAX_LINKS];         /*We define the links array for all the links we will be using*/
    int links_number;               /*Used to store the real amount of links being stored in the game*/
    int spaces_number;              /*Used to store the real amount of spaces in the game*/
    int players_number;             /*Used to store the real amount of players being stored in the game*/
    int objects_number;             /*Used to store the amount of objects the game has*/
    int dies_number;                /*Used to store the number of dies the game is using*/
    wchar_t **last_text_description;/*Used to store the last text description printed*/
    STATUS status_last_cmd;         /*Used to store if the last command worked correctly or not*/
    T_Command last_cmd;             /*Used to store the last command used by the user for graphic engine purposes*/
    BOOL proMode;                   /*Used to know whether the command mode is on proMode or not.*/
};

/*Define the function type for the callbacks*/
typedef STATUS(*callback_fn)(Game *, char *);

/*List of callbacks for each command in the game*/
STATUS game_callback_unknown(Game *, char *);
STATUS game_callback_exit(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_move
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        22-03-2018
 * @description It allows the player to move to the introducted direction.
 * @input
 *              game:       A Game*, where we are playing.
 *              string:     A char*, which should contain the direction where we are going.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_move(Game *game, char *string);

/* FUNCTION:
 *
 * @name        game_callback_previous
 *
 * @author      Víctor Yrazusta edited by Eric Morales
 * @version     2.0
 * @date        27-02-2018
 * @description It allows the player to move to the right.
 * @input
 *              game:       A Game*, whose player will try to move facing north.
 *              string:     A char*, which should contain the id of the player who will move.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_previous(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_left
 *
 * @author      Víctor Yrazusta edited by Eric Morales
 * @version     2.0
 * @date        27-02-2018
 * @description It allows the player to move to the left.
 * @input
 *              game:       A Game*, whose player will try to move facing east.
 *              string:     A char*, which should contain the id of the player who will move.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_left(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_following
 *
 * @author      Víctor Yrazusta edited by Eric Morales
 * @version     2.0 
 * @date        27-02-2018
 * @description It allows the player to move to the right.
 * @input
 *              game:       A Game*, whose player will try to move facing south.
 *              string:     A char*, which should contain the id of the player who will move.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_following(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_right
 *
 * @author      Víctor Yrazusta edited by Eric Morales
 * @version     2.0
 * @date        27-02-2018
 * @description It allows the player to move to the right.
 * @input
 *              game:       A Game*, whose player will try to move facing west.
 *              string:     A char*, which should contain the id of the player who will move.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_right(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_up
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        30-04-2018
 * @description It allows the player to move up.
 * @input
 *              game:       A Game*, whose player will try to move facing west.
 *              string:     A char*, which should contain the id of the player who will move.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_up(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_down
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        30-04-2018
 * @description It allows the player to move down.
 * @input
 *              game:       A Game*, whose player will try to move facing west.
 *              string:     A char*, which should contain the id of the player who will move.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_down(Game *, char *);

/* FUNCTION:
 *
 * @name 		game_callback_check
 *
 * @author 		Eric Morales
 * @version 	1.0
 * @date		26-03-2018
 * @description It allows get the graphic description (object or game).
 * @input
 *				game:		A Game*, where we are playing.
 *              string:     A char*, which should contain the direction where we are going.
 * @output		A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_check(Game *game, char *string);

/* FUNCTION:
 *
 * @name 		game_callback_grasp Edited by Eric Morales
 *
 * @author 		Alejandro Pascual
 * @version 	2.0
 * @date		19-02-2018
 * @description It allows the player to pick up an object. In order to pick up the object, the player must be in the same space as the object, and should not be carrying an object.
 * @input
 *		game:		A Game*, whose player will pick up the object if the previous mentioned conditions are met.
 *      string:   A char*, which should contain the id of the object to pick up.
 * @output		A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_grasp(Game *, char *);

/* FUNCTION:
 *
 * @name 		game_callback_drop
 *
 * @author 		Alejandro Pascual Edited by Eric Morales
 * @version 	2.0
 * @date		19-02-2018
 * @description It allows the player to drop an object. In order to drop the object, the player should be carring that object.
 * @input
 *				game:		A Game*, whose player will pick up the object if the previous mentioned conditions are met.
 *              string:     A char*, which should contain the id of the player whose object will de dropped.
 * @output		A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_drop(Game *, char *);

/* FUNCTION:
 *
 * @name 		game_callback_roll
 *
 * @author 		Víctor Yrazusta
 * @version 	1.0
 * @date		26-02-2018
 * @description It allows the player to roll a die.
 * @input
 *				game:		A Game*, whose player will pick up the object if the previous mentioned conditions are met.
 *              string:     A char*, which should contain the id of the die to roll.
 * @output		A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_roll(Game *, char *);

/* FUNCTION:
 *
 * @name 		game_callback_open
 *
 * @author 		Eric Morales
 * @version 	1.0
 * @date		22-04-2018
 * @description It allows you to open a Link using an Object.
 * @input
 *				game:		A Game*, whose player will open the link.
 *              string:     A char*, which should contain "<Link> with <Obj>"
 * @output		A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_open(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_turnon
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        22-04-2018
 * @description It allows you to turn on an object
 * @input
 *              game:       A Game*, where the player turn on an object.
 *              string:     A char*, which should contain object that is going to be turned on.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_turnon(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_turnon
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        22-04-2018
 * @description It allows you to turn off an object
 * @input
 *              game:       A Game*, where the player turn on an object.
 *              string:     A char*, which should contain object that is going to be turned off.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_turnoff(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_load
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        22-04-2018
 * @description It allows you to load a new game.
 * @input
 *              game:       A Game*, whose is going to be loaded
 *              string:     A char*, which should contain the name of the file that you are going to load.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_load(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_promode
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        22-04-2018
 * @description It allows you to activate the ProMode.
 * @input
 *              game:       A Game*, where you are playing.
 *              string:     A char*, nothing important.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_save(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_promode
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        22-04-2018
 * @description It allows you to activate the ProMode.
 * @input
 *              game:       A Game*, where you are playing.
 *              string:     A char*, nothing important.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_promode(Game *, char *);

/* FUNCTION:
 *
 * @name        game_callback_help
 *
 * @author      Eric Morales
 * @version     1.0
 * @date        22-04-2018
 * @description It allows you to open a help guide with all the commands.
 * @input
 *              game:       A Game*, where you are playing.
 *              string:     A char*, nothing important.
 * @output      A STATUS, which indicates whether the command was executed succesfully or not.
 */
STATUS game_callback_help(Game *, char *);

/*We define the callback functions*/
static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_move,
    game_callback_previous,
    game_callback_left,
    game_callback_following,
    game_callback_right,
    game_callback_up,
    game_callback_down,
    game_callback_grasp,
    game_callback_drop,
    game_callback_roll,
    game_callback_check,
	game_callback_open,
	game_callback_turnon,
	game_callback_turnoff,
	game_callback_load,
    game_callback_save,
    game_callback_promode,
    game_callback_help
};

/*Private functions*/
STATUS game_set_player_location(Game *, Id location_id, Id player_id);
STATUS game_set_object_location(Game *, Id location_id, Id object_id);

/*Game interface implementation*/

/*The following function allocates memory for a whole game, in a organised way, starting also all the things to the proper amount*/
Game *game_create() {
    Game *game = NULL;
    int i;

    game = (Game *) malloc(sizeof(Game));
    if (game == NULL) return NULL;

    for (i = 0; i < MAX_SPACES; i++) {
        game->spaces[i] = NULL;
    }
    for (i = 0; i < MAX_PLAYERS; i++) {
        game->players[i] = NULL;
    }
    for (i = 0; i < MAX_OBJECTS; i++) {
        game->objects[i] = NULL;
    }
    for (i = 0; i < MAX_DIES; i++) {
        game->dies[i] = NULL;
    }
    for (i = 0; i < MAX_LINKS; i++) {
        game->links[i] = NULL;
    }

    game->spaces_number = INI;
    game->players_number = INI;
    game->objects_number = INI;
    game->dies_number = N_DIES;
    game->links_number = INI;
    game->last_text_description = NULL;
    game->proMode = FALSE;

    for (i = 0; i < game->dies_number; i++) {
        game->dies[i] = die_create(DIE_BASE_ID+game->dies_number-i, DIE_FACES);
        die_roll(game->dies[i]);
    }

    die_roll((Die *) game_find(game, DIE_BASE_ID+game->dies_number));
    game->last_cmd = NO_CMD;
    game->status_last_cmd = ERROR;
    return game;
}

/*This function is used to create a new game (that already had memory allocated) from a the given fil (it works shoulder to shoulder with game_management.*/
STATUS game_create_from_file(Game *game, char *file_name) {

    if (game == NULL || file_name == NULL) return ERROR;

    if (game_management_load_spaces(game, file_name) == ERROR) return ERROR;
    if (game_management_load_players(game, file_name) == ERROR) return ERROR;
    if (game_management_load_objects(game, file_name) == ERROR) return ERROR;
    if (game_management_load_links(game, file_name) == ERROR) return ERROR;

    if (game->players[0] != NULL) game->last_text_description = space_get_basic_description(game_find(game, player_get_location(game->players[0])));
    if (game->last_text_description == NULL) return ERROR;

    return OK;
}

/*The following function frees ALL the memory used by a game, so that we left nothing non-freed (we leave no prisioners*/
STATUS game_destroy(Game *game) {
    int i = 0;

    if (game == NULL) return ERROR;

    for (i = 0; i < game->spaces_number; i++) {
        space_destroy(game->spaces[i]);
    }
    for (i = 0; i < game->players_number; i++) {
        player_destroy(game->players[i]);
    }
    for (i = 0; i < game->objects_number; i++) {
        object_destroy(game->objects[i]);
    }
    for (i = 0; i < game->dies_number; i++) {
        die_destroy(game->dies[i]);
    }
    for (i = 0; i < game->links_number; i++) {
        link_destroy(game->links[i]);
    }

    free(game);

    return OK;
}

/*This function is used to add spaces, usually used in game_management as its logic*/
STATUS game_add_space(Game *game, Space *space) {

    if (game == NULL || space == NULL || game->spaces_number >= MAX_SPACES || space_get_id(space) <= SPACE_BASE_ID || space_get_id(space) >= SPACE_BASE_ID+ID_RANGE) return ERROR;

    game->spaces[game->spaces_number] = space;
    game->spaces_number++;

    return OK;
}

/*This function is used to add objects on the given location. As usual, its used by game_management*/
STATUS game_add_object(Game *game, Object *object, Id location_id) {

    if (game == NULL || object == NULL || game->objects_number >= MAX_OBJECTS || location_id == NO_ID || object_get_id(object) <= OBJECT_BASE_ID || object_get_id(object) >= OBJECT_BASE_ID+ID_RANGE) return ERROR;

    game->objects[game->objects_number] = object;
    game->objects_number++;

    if (game_set_object_location(game, location_id, object_get_id(object)) == ERROR) {
        game->objects_number--;
        game->objects[game->objects_number] = NULL;
        return ERROR;
    }

    return OK;
}

/*This function is used to add new links. Again, is used by game_management normally*/
STATUS game_add_link(Game *game, Link *link) {

    if (game == NULL || link == NULL || game->links_number >= MAX_LINKS || link_get_id(link) <= LINK_BASE_ID || link_get_id(link) >= LINK_BASE_ID+ID_RANGE) return ERROR;

    game->links[game->links_number] = link;
    game->links_number++;

    return OK;
}

/*This function is used to add players, usually used in game_management as its logic*/
STATUS game_add_player(Game *game, Player *player, Id location_id) {

    if (game == NULL || player == NULL || game->players_number >= MAX_PLAYERS || player_get_id(player) <= PLAYER_BASE_ID || player_get_id(player) >= PLAYER_BASE_ID+ID_RANGE) return ERROR;

    game->players[game->players_number] = player;
    game->players_number++;
    if (game_set_player_location(game, location_id, player_get_id(player)) == ERROR) return ERROR;

    return OK;
}

/*The following function is used to change the object location or to set a new object location to an object, used when players grasp or drop objects
 It has a long error control so that we ensure it works correctly when needed and returns a proper error without messing the program when not*/
STATUS game_set_object_location(Game *game, Id location_id, Id object_id) {
    void *new_holder = NULL;
    void *previous_holder = NULL;
    Object *object = NULL;

    if (game == NULL || location_id == NO_ID || object_id == NO_ID) return ERROR;

    object = (Object *) game_find(game, object_id);
    new_holder = game_find(game, location_id);

    if (object == NULL || new_holder == NULL) return ERROR;

    if (object_get_location(object) == NO_ID) {
        if (location_id > SPACE_BASE_ID && location_id < SPACE_BASE_ID+ID_RANGE) { /* The object is passed from nowhere to a space */
            if (space_add_object((Space *) new_holder, object_id) == OK && object_set_location(object, location_id) == OK) {
                return OK;
            } else {
                return ERROR;
            }
        }

        if (location_id > PLAYER_BASE_ID && location_id < PLAYER_BASE_ID+ID_RANGE) { /* The object is passed from nowhere to a player */
            if (player_add_object((Player *) new_holder, object_id) == OK && object_set_location(object, location_id) == OK) {
                return OK;
            } else {
                return ERROR;
            }
        }

        return ERROR; /* The object can't be passed from nowhere to an object, a die, a link or an unspecified type */
    }

    if (object_get_location(object) > SPACE_BASE_ID && object_get_location(object) < SPACE_BASE_ID+ID_RANGE) {
        previous_holder = game_find(game, object_get_location(object));

        if (previous_holder == NULL) return ERROR;

        if (location_id > SPACE_BASE_ID && location_id < SPACE_BASE_ID+ID_RANGE) { /* The object is passed from a space to a space */
            if (space_add_object((Space *) new_holder, object_id) == OK && object_set_location(object, location_id) == OK && space_del_object((Space *) previous_holder, object_id) == OK && object_set_location(object, location_id) == OK) {
                return OK;
            } else {
                return ERROR;
            }
        }

        if (location_id > PLAYER_BASE_ID && location_id < PLAYER_BASE_ID+ID_RANGE) { /* The object is passed from a space to a player */
            if (player_add_object((Player *) new_holder, object_id) == OK && space_del_object((Space *) previous_holder, object_id) == OK && object_set_location(object, location_id) == OK) {
                return OK;
            } else {

                return ERROR;
            }
        }

        return ERROR; /* The object can't be passed from a space to an object, a die, a link or an unspecified type */
    }

    if (object_get_location(object) > PLAYER_BASE_ID && object_get_location(object) < PLAYER_BASE_ID+ID_RANGE) {
        previous_holder = game_find(game, object_get_location(object));

        if (previous_holder == NULL) return ERROR;

        if (location_id > SPACE_BASE_ID && location_id < SPACE_BASE_ID+ID_RANGE) { /* The object is passed from a player to a space */
            if (space_add_object((Space *) new_holder, object_id) == OK && object_set_location(object, location_id) == OK && player_del_object((Player *) previous_holder, object_id) == OK && object_set_location(object, location_id) == OK) {
                return OK;
            } else {
                return ERROR;
            }
        }

        if (location_id > PLAYER_BASE_ID && location_id < PLAYER_BASE_ID+ID_RANGE) { /* The object is passed from a player to a player */
            if (player_add_object((Player *) new_holder, object_id) == OK && player_del_object((Player *) previous_holder, object_id) == OK && object_set_location(object, location_id) == OK) {
                return OK;
            } else {
                return ERROR;
            }
        }

        return ERROR;
    }

    /* The only way in which the execution of the function could get to this point is if the object comes from another object, a die, a link or an unspecified Id */

    if (location_id > SPACE_BASE_ID && location_id < SPACE_BASE_ID+ID_RANGE) { /* The object is passed from ??? to a space */
        if (space_add_object((Space *) new_holder, object_id) == OK && object_set_location(object, location_id) == OK) {
            return OK;
        } else {
            return ERROR;
        }
    }

    if (location_id > PLAYER_BASE_ID && location_id < PLAYER_BASE_ID+ID_RANGE) { /* The object is passed from ??? to a player */
        if (player_add_object((Player *) new_holder, object_id) == OK && object_set_location(object, location_id) == OK) {
            return OK;
        } else {
            return ERROR;
        }
    }

    return ERROR;
}

/*The following function is used to change the location of a player, so that we can 'move' it*/
STATUS game_set_player_location(Game *game, Id location_id, Id playerId) {
    Player *player = NULL;

    if (game == NULL || location_id == NO_ID || location_id <= SPACE_BASE_ID || location_id >= SPACE_BASE_ID+ID_RANGE || playerId == NO_ID) return ERROR;

    player = (Player *) game_find(game, playerId);
    if (player == NULL) return ERROR;

    player_set_location(player, location_id);

    return OK;
}

/*This function returns the number of spaces that are being used in the game, in case we needed to go through all of them*/
int game_get_spaces_number(Game *game) {

    if (game == NULL) return 0;

    return game->spaces_number;
}

/*This function is used to get the number of Players that are in the game*/
int game_get_players_number(Game *game) {

    if (game == NULL) return 0;

    return game->players_number;
}

/*This function returns the number of objects that are there in the game*/
int game_get_objects_number(Game *game) {

    if (game == NULL) return 0;

    return game->objects_number;
}

/*This function returns the number of dies in the game*/
int game_get_dies_number(Game *game) {

    if (game == NULL) return 0;

    return game->dies_number;
}

/*This function is used to update the command related game fields*/
STATUS game_update(Game *game, Command *command) {
    if (game == NULL || command == NULL) return ERROR;

    game->last_cmd = command_get_command(command);
    game->status_last_cmd = (*game_callback_fn_list[command_get_command(command)])(game, command_get_info(command));

    return game->status_last_cmd;
}

/*This function give us the result of the boolean proMode */
BOOL game_check_mode(Game *game){     /* TRUE = ProMode and FALSE = NormalMode */
    if (game == NULL) return FALSE;
    return game->proMode;
}

/*This function returns the last command used by the player (the command itself, without the info*/
T_Command game_get_last_command(Game *game) {

    if (game == NULL) return NO_CMD;

    return game->last_cmd;
}

/*This function returns the status of the last command used in the game*/
STATUS game_get_status_last_command(Game* game) {

    if (game == NULL) return ERROR;

    return game->status_last_cmd;
}

void game_print_data(FILE *f, Game *game) {
    int i = 0;

    if (game == NULL) return;

    for (i = 0; i < game->spaces_number; i++) {
        space_print(f, game->spaces[i]);
    }
    fwprintf(f, L"\n");
    for (i = 0; i < game->objects_number; i++) {
        object_print(f, game->objects[i]);
    }
    fwprintf(f, L"\n");
    for (i = 0; i < game->links_number; i++) {
        link_print(f, game->links[i]);
    }
    fwprintf(f, L"\n");
    for (i = 0; i < game->players_number; i++) {
        player_print(f, game->players[i]);
    }
}

/*This function checks if the game is over or not. By the moment, its always false (unless it receives wrong arguments) as there are no losing conditions*/
BOOL game_is_over(Game *game) {

    if (game == NULL) return TRUE;

    return FALSE;
}

/*This is the most interesting function we have. It searchs for whatever Id you give it, and then you do a casting to use it*/
void *game_find(Game *game, Id id) {
    int i;

    if (game == NULL || id == NO_ID) return NULL;

    if (game->spaces && id > SPACE_BASE_ID && id < SPACE_BASE_ID+ID_RANGE) {
        for (i = 0; i < MAX_SPACES; i++) {
            if (space_get_id(game->spaces[i]) == id) {
                return (void *) game->spaces[i];
            }
        }
    }

    if (game->players && id > PLAYER_BASE_ID && id < PLAYER_BASE_ID+ID_RANGE) {
        for (i = 0; i < game->players_number; i++) {
            if (player_get_id(game->players[i]) == id) {
                return (void *) game->players[i];
            }
        }
    }

    if (game->objects && id > OBJECT_BASE_ID && id < OBJECT_BASE_ID+ID_RANGE) {
        for (i = 0; i < game->objects_number; i++) {
            if (object_get_id(game->objects[i]) == id) {
                return (void *) game->objects[i];
            }
        }
    }

    if (game->dies && id > DIE_BASE_ID && id < DIE_BASE_ID+ID_RANGE) {
        for (i = 0; i < game->dies_number; i++) {
            if (die_get_id(game->dies[i]) == id) {
                return (void *) game->dies[i];
            }
        }
    }

    if (game->links && id > LINK_BASE_ID && id < LINK_BASE_ID+ID_RANGE) {
        for (i = 0; i < game->links_number; i++) {
            if (link_get_id(game->links[i]) == id) {
                return (void *) game->links[i];
            }
        }
    }

    return NULL;
}

/*This one does the same as the previous one, but with names instead*/
void *game_find_name(Game *game, char *name) {
    int i;
    void *entity = NULL;
    wchar_t unicode_name[WORD_SIZE];

    if (game == NULL || name == NULL) return NULL;

    swprintf(unicode_name, WORD_SIZE, L"%s", name);

    if (wcscmp(unicode_name, L"NO_INFO") == 0) return NULL;

    if (game->spaces) {
        for (i = 0; i < game->spaces_number; i++) {
            if (wcscasecmp(space_get_name(game->spaces[i]), unicode_name) == 0) {
                entity = game->spaces[i];
            }
        }
    }

    if (game->players) {
        for (i = 0; i < game->players_number; i++) {
            if (wcscasecmp(player_get_name(game->players[i]), unicode_name) == 0) {
                if (entity != NULL) {
                    return NULL;
                }
                entity = game->players[i];
            }
        }
    }

    if (game->objects) {
        for (i = 0; i < game->objects_number; i++) {
            if (wcscasecmp(object_get_name(game->objects[i]), unicode_name) == 0) {
                if (entity != NULL) {
                    return NULL;
                }
                entity = game->objects[i];
            }
        }
    }

    if (game->links) {
        for (i = 0; i < game->links_number; i++) {
            if (wcscasecmp(link_get_name(game->links[i]), unicode_name) == 0) {
                if (entity != NULL) {
                    return NULL;
                }
                entity = game->links[i];
            }
        }
    }

    return entity;
}

/*This function returns the last text description for the graphic engine*/
wchar_t **game_get_last_text_description(Game* game) {

    if (game == NULL) return NULL;

    return game->last_text_description;
}

/*This function is used to get connections between spaces*/
Link *game_get_connection(Game *game, Space *origin, Space *destination) {
    Link *link = NULL;
    DIRECTION direction;

    if (game == NULL || origin == NULL || destination == NULL) return NULL;

    for (direction = NORTH; direction <= EAST; direction++) {
        if (space_get_direction(origin, direction) != NO_ID) {
            link = (Link *) game_find(game, space_get_direction(origin, direction));
            if (link == NULL) return NULL;
            if (link_get_other_side(link, space_get_id(origin)) == space_get_id(destination)) return link;
        }
    }

    return NULL;
}

/*This function is used to pass from tag to string*/
wchar_t *game_tag_to_str(TAG tag) {
    wchar_t *name;

    name = (wchar_t *) malloc(WORD_SIZE*sizeof(wchar_t));

    if (tag == NO_TAG) {
        wcscpy(name, L"NO_TAG");
        return name;
    }
    if (tag == MOVABLE) {
        wcscpy(name, L"MOVABLE");
        return name;
    }
    if (tag == MOVED) {
        wcscpy(name, L"MOVED");
        return name;
    }
    if (tag == HIDDEN) {
        wcscpy(name, L"HIDDEN");
        return name;
    }
    if (tag == CAN_GLOW) {
        wcscpy(name, L"CAN_GLOW");
        return name;
    }
    if (tag == GLOWING) {
        wcscpy(name, L"GLOWING");
        return name;
    }
    if (tag == IS_KEY) {
        wcscpy(name, L"IS_KEY");
        return name;
    }
    if (tag == IS_CROWBAR) {
        wcscpy(name, L"IS_CROWBAR");
        return name;
    }
    if (tag == IS_BASE_ID_CARD) {
        wcscpy(name, L"IS_BASE_ID_CARD");
        return name;
    }
    if (tag == IS_FULL_ID_CARD) {
        wcscpy(name, L"IS_FULL_ID_CARD");
        return name;
    }
    if (tag == IS_FUSE_KEY) {
        wcscpy(name, L"IS_FUSE_KEY");
        return name;
    }
    if (tag == IS_TRANS_CORE_KEY) {
        wcscpy(name, L"IS_TRANS_CORE_KEY");
        return name;
    }
    if (tag == ILLUMINATED) {
        wcscpy(name, L"ILLUMINATED");
        return name;
    }
    if (tag == FINAL_ROOM) {
        wcscpy(name, L"FINAL_ROOM");
        return name;
    }

    return NULL;
}

/*This function is used to pass from string to tag*/
TAG game_str_to_tag(wchar_t *name) {

    if (name == NULL) return NO_TAG;

    if (!wcscmp(name, L"NO_TAG"))          return NO_TAG;
    if (!wcscmp(name, L"MOVABLE"))         return MOVABLE;
    if (!wcscmp(name, L"MOVED"))           return MOVED;
    if (!wcscmp(name, L"HIDDEN"))          return HIDDEN;
    if (!wcscmp(name, L"CAN_GLOW"))        return CAN_GLOW;
    if (!wcscmp(name, L"GLOWING"))         return GLOWING;
    if (!wcscmp(name, L"IS_KEY"))          return IS_KEY;
    if (!wcscmp(name, L"IS_CROWBAR"))      return IS_CROWBAR;
    if (!wcscmp(name, L"IS_BASE_ID_CARD")) return IS_BASE_ID_CARD;
    if (!wcscmp(name, L"IS_FULL_ID_CARD")) return IS_FULL_ID_CARD;
    if (!wcscmp(name, L"IS_FUSE_KEY"))     return IS_FUSE_KEY;
    if (!wcscmp(name, L"IS_TRANS_CORE_KEY"))return IS_TRANS_CORE_KEY;
    if (!wcscmp(name, L"ILLUMINATED"))     return ILLUMINATED;
    if (!wcscmp(name, L"FINAL_ROOM"))      return FINAL_ROOM;

    return NO_TAG;
}

/*The following function displays and implements the menu*/
STATUS game_menu(Game *game) {
	Menu *menu = NULL;
	char input;
	int selectedOption;
    int exit = 0;
	menu = menu_create();

    if (menu == NULL) {
        fprintf(stderr, "Error while initializing the menu.\n");
        return ERROR;
    }

	selectedOption = 0;
	do {
		do {
			menu_paint(menu, selectedOption);
			system("/bin/stty raw");
			input = getchar();
			system("/bin/stty cooked");

			switch (input) {
				case 'w': 
					if (selectedOption > 0) selectedOption--;
					break;
				case 's':
					if (selectedOption < 5) selectedOption++;
					break;
			}
		} while (input != ' ');

		switch (selectedOption) {
			case 0:
                if(game_callback_load(game, "./datafiles/data.dat") == OK){
                    exit = 1;
                } 
                break;
			case 1:
				if(game_callback_load(game, "NO_INFO") == OK){
				    exit = 1;
                }
                break;
			case 2:
				system("man lib/guide.1");									
				break;
			case 3:
				system("man lib/termsofuse.1");      						
				break;
            case 4:
                system("google-chrome doc/html/index.html"); 
                break;
			case 5:
				menu_destroy(menu);
                system("killall make");
				return ERROR;
		}
	} while (exit != 1);
	
	menu_destroy(menu);
	return OK;
}

/*Callbacks implementation for each command/action*/

/*The following action is used when the input doesnt coincide with any other one*/
STATUS game_callback_unknown(Game *game, char *string) {
    return ERROR;
}

/*The following action is used when the program is asked to exit*/
STATUS game_callback_exit(Game *game, char *string) {
    return OK;
}

/*This action repalces all the older movement actions by one only action, which moves the player in the asked direction*/
STATUS game_callback_move(Game *game, char *string) {
    char *direction[N_DIR] = {"North", "West", "South", "East", "Above", "Below"};
    char *direction_letter[N_DIR] = {"N", "W", "S", "E", "A", "B"};
    DIRECTION dir;
    Player *player = NULL;
    Link *link = NULL;
    Id space_id = NO_ID;
    int i;

    if (game == NULL || string == NULL) return ERROR;

    dir = NO_DIR;
    i = 0;
    while (dir == NO_DIR && i <= BELOW && string != NULL) {
        if (!strcasecmp(string, direction[i]) || !strcasecmp(string, direction_letter[i])) {
            dir = i;
        } else {
            i++;
        }
    }

    player = (Player *) game_find(game, atoi(string));
    if (player == NULL) {
        player = (Player *) game_find_name(game, string);

        if (player == NULL) {
            player = game->players[0];
        }
    }

    link = (Link*) game_find(game, space_get_direction((Space *) game_find(game, player_get_location(player)), dir));
    if (link == NULL) return ERROR;
    if (link_get_status(link) == CLOSED) return CLOSED_LINK;

    space_id = link_get_other_side(link, player_get_location(player));
    if (space_id == NO_ID) return ERROR;

    player_set_location(player, space_id);

    game->last_text_description = space_get_basic_description(game_find(game, player_get_location(game->players[0])));
    if (game->last_text_description == NULL) return ERROR;

    return OK;
}

/*The following action was used to move to the previous space in older versions*/
STATUS game_callback_previous(Game *game, char *string) {

    return game_callback_move(game, "North");
}

/*This action moves the player to the left in older versions*/
STATUS game_callback_left(Game *game, char *string) {

    return game_callback_move(game, "West");
}

/*The following action is used to move to the next space in older versions*/
STATUS game_callback_following(Game *game, char *string) {

    return game_callback_move(game, "South");
}

/*This action moves the player to the right in older versions*/
STATUS game_callback_right(Game *game, char *string) {

    return game_callback_move(game, "East");
}

STATUS game_callback_up(Game *game, char *string) {

    return game_callback_move(game, "Above");
}

STATUS game_callback_down(Game *game, char *string) {

    return game_callback_move(game, "Below");
}

/*This command is used when grasping objects, copying them to the players inventory and then deleting them if they pass all the error control it has*/
STATUS game_callback_grasp(Game *game, char *string) {
    Object *object = NULL;

    if (game == NULL || game->players == NULL || game->objects == NULL || string == NULL) return ERROR;

    if (atoi(string) > 0 && atoi(string) < ID_RANGE) object = (Object *) game_find(game, atoi(string)+OBJECT_BASE_ID);

    if (object == NULL) {
        object = (Object *) game_find_name(game, string);
        if (object == NULL) {
            return ERROR;
        }
    }

    if (player_get_location(game->players[0]) == NO_ID || space_check_object((Space *) game_find(game, player_get_location(game->players[0])), object_get_id(object)) == FALSE || player_is_full(game->players[0]) == TRUE || player_get_location(game->players[0]) != object_get_location(object)) return ERROR;
    if (object_check_tag(object, MOVABLE) == FALSE) return UNMOVABLE;

    object_add_tags(object, 1, MOVED);

    return game_set_object_location(game, player_get_id(game->players[0]), object_get_id(object));
}

/*The next command is used when players drop their objects. It copies them to the space where they are and then destroys them from the players inventory*/
STATUS game_callback_drop(Game *game, char *string) {
    Object *object = NULL;

    if (game == NULL || game->players == NULL || game->objects == NULL || string == NULL) return ERROR;

    if (atoi(string) > 0 && atoi(string) < ID_RANGE) object = (Object *) game_find(game, atoi(string)+OBJECT_BASE_ID);

    if (object == NULL) {
        object = (Object *) game_find_name(game, string);
        if (object == NULL) {
            return ERROR;
        }
    }

    if (player_get_location(game->players[0]) == NO_ID || space_is_full((Space *) game_find(game, player_get_location(game->players[0]))) == TRUE || player_is_empty(game->players[0]) == TRUE || player_check_object(game->players[0], object_get_id(object)) == FALSE) return ERROR;
    if (game_set_object_location(game, player_get_location(game->players[0]), object_get_id(object)) == ERROR) return ERROR;

    return OK;
}

/*The following action is used when the user asks to roll a die*/
STATUS game_callback_roll(Game *game, char * string) {
    Die *die = NULL;
    int i;

    if (game == NULL) return ERROR;

    if (strcmp(string, "NO_INFO") == 0) {
        for (i = 0; i < game_get_dies_number(game); i++) {
            die = (Die *) game_find(game, DIE_BASE_ID+game_get_dies_number(game)-i);
            die_roll(die);
        }
    } else {
        die = (Die *) game_find(game, atoi(string));
        die_roll(die);
    }

    return OK;
}

/*This action is used to see the description of a space or an object*/
STATUS game_callback_check(Game *game, char *string) {
    Object *object;
    BOOL space_glowing;
    int i;

    if (game == NULL || game->players == NULL || game->objects == NULL || string == NULL || atoi(string) < 0 || atoi(string) > ID_RANGE) return ERROR;

    if (space_check_tag(game_find(game, player_get_location(game->players[0])), ILLUMINATED) == FALSE) {
        space_glowing = FALSE;
        for (i = 0; i < player_get_objects_number(game->players[0]); i++) {
            if (object_check_tag((Object *) game_find(game, player_get_object_id(game->players[0], i)), GLOWING)) {
                space_glowing = TRUE;
                break;
            }
        }
        if (!space_glowing) {
            for (i = 0; i < space_get_objects_number((Space *) game_find(game, player_get_location(game->players[0]))); i++) {
                if (object_check_tag((Object *) game_find(game, space_get_object_id((Space *) game_find(game, player_get_location(game->players[0])), i)), GLOWING)) {
                    space_glowing = TRUE;
                    break;
                }
            }
        }
        if (!space_glowing) return DARK;         
    }
    
    if (strcmp(string, "space") == 0 || strcmp(string, "s") == 0) {
        game->last_text_description = space_get_check_description(game_find(game, player_get_location(game->players[0])));
        if (game->last_text_description == NULL) return ERROR;
        return OK;
    }

    object = (Object *) game_find(game, atoi(string)+OBJECT_BASE_ID);

    if (object == NULL) {
        object = (Object *) game_find_name(game, string);
        if (object == NULL) return ERROR;
    }

	if (player_check_object(game->players[0], object_get_id(object)) == FALSE) {
		if (player_get_location(game->players[0]) != object_get_location(object)) return FAR;		
	}	

    if (!object_check_tag(object, MOVED)){
        game->last_text_description = object_get_check(object);  
    } else {
        game->last_text_description = object_get_alt_check(object);
    }
    if (game->last_text_description == NULL) return ERROR;

    return OK;
}

/*Using this command you can open a link using an object*/
STATUS game_callback_open(Game *game, char *string) {
    Object *obj;
	Link *link;
	char *sobj, *slink, *aux;

    if (game == NULL || game->players == NULL || game->objects == NULL || string == NULL || strcmp(string, "NO_INFO") == 0) return ERROR;

    aux = (char *) malloc(sizeof(char)*(strlen(string)+1));
    strcpy(aux, string);

	slink = strtok(aux, " ");
	sobj = strtok(NULL, " \n");

    if (sobj == NULL || slink == NULL) return ERROR;

	obj = (Object *) game_find(game, atoi(sobj)+OBJECT_BASE_ID);

    if (obj == NULL) {
        obj = (Object *) game_find_name(game, sobj);
        if (obj == NULL) return ERROR;
    }

	link = (Link *) game_find(game, atoi(slink)+LINK_BASE_ID);
    if (link == NULL) {
        link = (Link *) game_find_name(game, slink);
        if (link == NULL) return ERROR;
    }

	if (object_check_tag(obj, link_get_opener(link)) == FALSE) {
		return ERROR;
	}

    if (player_check_object(game->players[0], object_get_id(obj)) == FALSE && player_get_location(game->players[0]) != object_get_location(obj)) {
        return ERROR;
    }

	link_set_status(link, OPEN);

    free(aux);
    return OK;
}

/*This action is used to turn on an object*/
STATUS game_callback_turnon(Game *game, char *string) {
    Object *object;

    if (game == NULL || game->players == NULL || game->objects == NULL || string == NULL || atoi(string) < 0 || atoi(string) > ID_RANGE) return ERROR;

    object = (Object *) game_find(game, atoi(string)+OBJECT_BASE_ID);

    if (object == NULL) {
        object = (Object *) game_find_name(game, string);
        if (object == NULL) return ERROR;
    }

	if (object_check_tag(object, CAN_GLOW) == FALSE) {
		return ERROR;
	}

	if (player_check_object(game->players[0], object_get_id(object)) == FALSE && player_get_location(game->players[0]) != object_get_location(object)) {
		return ERROR;
	}

	return object_add_tags(object, 1, GLOWING);
}

/*This action is used to turn off an object*/
STATUS game_callback_turnoff(Game *game, char *string) {
    Object *object;

    if (game == NULL || game->players == NULL || game->objects == NULL || string == NULL || atoi(string) < 0 || atoi(string) > ID_RANGE) return ERROR;

    object = (Object *) game_find(game, atoi(string)+OBJECT_BASE_ID);

    if (object == NULL) {
        object = (Object *) game_find_name(game, string);
        if (object == NULL) return ERROR;
    }

	if (player_check_object(game->players[0], object_get_id(object)) == FALSE && player_get_location(game->players[0]) != object_get_location(object)) {
		return ERROR;
	}

	return object_remove_tag(object, GLOWING);
}

STATUS game_callback_load(Game *game, char *string) {

	return game_management_load(game, string);
}

STATUS game_callback_save(Game *game, char *string){

    return game_management_save(game, string);
}

STATUS game_callback_promode(Game *game, char *string){

    if (game == NULL) return ERROR;
    
    if (game->proMode == FALSE){
        game->proMode = TRUE;
    } else {
        game->proMode = FALSE;
    }

    return OK;
}

STATUS game_callback_help(Game *game, char *string){
    system("man lib/controls.1"); 
    return OK;
}