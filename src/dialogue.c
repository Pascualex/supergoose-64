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
#include "../include/space.h"
#include "../include/command.h"

/*typedef enum {
    NO_CMD = -1,    
    UNKNOWN,       
    EXIT,          
    MOVE,         
    FOLLOWING,    
    LEFT,           
    PREVIOUS,      
    RIGHT,         
    GRASP,          
    DROP,         
    THROW,        
    CHECK,       
    OPEN_L,         
    TURN_ON,       
    TURN_OFF,    
    LOAD,          
    SAVE,           
    PROMODE        
} T_Command;*/

void dialogue_generate(Game *game, wchar_t dialogue[MAX_DIA_R][MAX_DIA_C]) {
    int current_row, i;

    current_row = 0;

    switch (game_get_last_command(game)) {
        case NO_CMD : 
            swprintf(dialogue[current_row], MAX_DIA_C, L"Welcome to our game!");
            current_row++;
            break;
        case MOVE :
            swprintf(dialogue[current_row], MAX_DIA_C, L"You moved to %S successful",);
        default :
            swprintf(dialogue[current_row], MAX_DIA_C, L"That command doesn't exists!");
            current_row++;
    }
    
    for (i = current_row; i < MAX_DIA_R; i++) {
        swprintf(dialogue[i], MAX_DIA_C, L" ");
    }

    return;
}