/**
 * @brief It implements the dialogue module
 * @file dialogue.c
 * @author Javier Lougedo
 * @version 1.0
 * @date 22-04-2018
 * @copyright GNU Public License
 */

#undef __STRICT_ANSI__

/*C libraries*/
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

/*Own libraries*/
#include "../include/dialogue.h"
#include "../include/game.h"
#include "../include/player.h"
#include "../include/space.h"
#include "../include/die.h"
#include "../include/command.h"

/*typedef enum {
    NO_CMD = -1, --
    UNKNOWN,     --
    EXIT,        --
    MOVE,        --
    FOLLOWING,   --
    LEFT,        --
    PREVIOUS,    --
    RIGHT,       --
    GRASP,       --
    DROP,        --
    THROW,       --
    CHECK,       --
    OPEN_L,        
    TURN_ON,       
    TURN_OFF,      
    LOAD,          
    SAVE,          
    PROMODE        
} T_Command;*/

void dialogue_generate(Game *game, wchar_t dialogue[MAX_DIA_R][MAX_DIA_C]) {
    Player *player = NULL;
    Space *space = NULL;
    Object *object = NULL;
    wchar_t **text_description = NULL;
    int current_row, i;

    player = (Player *) game_find(game, PLAYER_BASE_ID+game_get_players_number(game));
    space = (Space *) game_find(game, player_get_location(player));

    current_row = 0;
    switch (game_get_last_command(game)) {
        case NO_CMD :
            text_description = space_get_basic_description(space); 
            swprintf(dialogue[current_row], MAX_DIA_C, L" What a headache! You wake up knackered inside a strange compartment that looks");
            current_row++; 
            swprintf(dialogue[current_row], MAX_DIA_C, L" like a fridge. You can't remember why you are here but you would rather leave as");
            current_row++;
            swprintf(dialogue[current_row], MAX_DIA_C, L" soon as possible.");
            current_row++;
            swprintf(dialogue[current_row], MAX_DIA_C, L" ");
            current_row++;                
            for (i = 0; i < MAX_TDESC_R; i++) {
                swprintf(dialogue[current_row], MAX_DIA_C, L"%S", text_description[i]);
                current_row++;
            } 
            break;
        case MOVE : case PREVIOUS : case LEFT : case FOLLOWING : case RIGHT :
            if (game_get_status_last_command(game) == OK) {                
                text_description = space_get_basic_description(space); 
                swprintf(dialogue[current_row], MAX_DIA_C, L" You moved to %S.", space_get_name(space));
                current_row++;
                swprintf(dialogue[current_row], MAX_DIA_C, L" ");
                current_row++; 
                if (space_check_tag(space, ILLUMINATED)) {
                    for (i = 0; i < MAX_TDESC_R; i++) {
                        swprintf(dialogue[current_row], MAX_DIA_C, L"%S", text_description[i]);
                        current_row++;
                    }   
                } else {
                    swprintf(dialogue[current_row], MAX_DIA_C, L" You can't see anything in the dark.");
                    current_row++;
                }                   
            } else if (game_get_status_last_command(game) == CLOSED_LINK) { 
                swprintf(dialogue[current_row], MAX_DIA_C, L" You can't move through a closed path.");
                current_row++;
            } else {
                swprintf(dialogue[current_row], MAX_DIA_C, L" You can't move in that direction.");
                current_row++;
            }            
            break;
        case GRASP :
            if (game_get_status_last_command(game) == OK) {
                object = (Object *) game_find(game, player_get_object_id(player, player_get_objects_number(player)-1));
                text_description = object_get_check(object);                
                swprintf(dialogue[current_row], MAX_DIA_C, L" You grasped the %S.", object_get_name(object));
                current_row++;
                swprintf(dialogue[current_row], MAX_DIA_C, L" ");
                current_row++;
                for (i = 0; i < MAX_TDESC_R; i++) {
                    swprintf(dialogue[current_row], MAX_DIA_C, L"%S", text_description[i]);
                    current_row++;
                }
            } else if (game_get_status_last_command(game) == UNMOVABLE) {
                swprintf(dialogue[current_row], MAX_DIA_C, L" You won't be able to move this object any time soon.");
                current_row++;
            } else {
                swprintf(dialogue[current_row], MAX_DIA_C, L" You couldn't grasp the object.");
                current_row++;
            }       
            break;
        case DROP :
            if (game_get_status_last_command(game) == OK) {
                object = (Object *) game_find(game, space_get_object_id(space, space_get_objects_number(space)-1));                
                swprintf(dialogue[current_row], MAX_DIA_C, L" You dropped the %S.", object_get_name(object));
                current_row++;
            } else {
                swprintf(dialogue[current_row], MAX_DIA_C, L" You couldn't drop the object.");
                current_row++;
            }
            break;
        case THROW :
            if (game_get_status_last_command(game) == OK) {
                swprintf(dialogue[current_row], MAX_DIA_C, L" Somehow you didn't loose your always reliable lucky dice. For some reason you");
                current_row++;
                swprintf(dialogue[current_row], MAX_DIA_C, L" decide to roll it and you get... A %d! Your lucky number! What a coincidence! This", die_get_value((Die *) game_find(game, DIE_BASE_ID+game_get_dies_number(game))));
                current_row++;
                swprintf(dialogue[current_row], MAX_DIA_C, L" dice will never let you down.");
                current_row++;
            } else {
                swprintf(dialogue[current_row], MAX_DIA_C, L" UNEXPECTED ERROR.");
                current_row++;
            }
            break;
        case CHECK :
            if (game_get_status_last_command(game) == OK) {
                swprintf(dialogue[current_row], MAX_DIA_C, L" You take a closer look at the surroundings.");
                current_row++;
                swprintf(dialogue[current_row], MAX_DIA_C, L" ");
                current_row++;
                text_description = game_get_last_text_description(game); 
                for (i = 0; i < MAX_TDESC_R; i++) {
                    swprintf(dialogue[current_row], MAX_DIA_C, L"%S", text_description[i]);
                    current_row++;
                }
            } else if (game_get_status_last_command(game) == DARK) {
                swprintf(dialogue[current_row], MAX_DIA_C, L" Even if you try... You can't see anything in the dark.");
                current_row++;
            } else if (game_get_status_last_command(game) == FAR) {
                swprintf(dialogue[current_row], MAX_DIA_C, L" You can't check an object that isn't in your room.");
                current_row++;
            } else {
                swprintf(dialogue[current_row], MAX_DIA_C, L" You couldn't check the object.");
                current_row++;
            }
            break;
        default :
            swprintf(dialogue[current_row], MAX_DIA_C, L" That command doesn't exists!");
            current_row++;
    }
    
    for (i = current_row; i < MAX_DIA_R; i++) {
        swprintf(dialogue[i], MAX_DIA_C, L" ");
    }

    return;
}