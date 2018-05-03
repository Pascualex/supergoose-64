/**
 * @brief It implements the command interpreter
 * @file command.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
/*Own libraries*/
#include "../include/command.h"

/*We define the command maximum length, the number of commands and the information of the command (north, south, objects, etc) lengths.*/
#define CMD_LENGHT 50
#define N_CMD 18
#define INFO_LENGHT 30

/*We define the command structure with the command itself (the order) and the info it has (objects, directions and else).*/
struct _Command {
    T_Command command;
    char info[INFO_LENGHT];
};

/*We define the different commands we can use, in long and short forms*/
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Move", "Previous", "Left", "Following", "Right", "Grasp", "Drop", "Throw", "Check", "Open", "TurnOn", "TurnOff", "Load", "Save", "ProMode"};
char *short_cmd_to_str[N_CMD] = {"", "", "e", "m", "p", "l", "f", "r", "g", "d", "t", "c", "o", "ton", "toff", "ld", "sv", "k"};

/*The following function creates commands, allocating memory for them and starting the command to No_CMD and the information as it was empty.*/
Command *command_create() {
    Command *command = NULL;

    command = (Command *) malloc(sizeof (Command));
    if (command == NULL) return NULL;

    command->command = NO_CMD;
    strcpy(command->info, "NO_INFO");

    return command;
}

/*The following function frees the allocated memory of a command*/
STATUS command_destroy(Command *command) {

    if (command == NULL) return ERROR;

    free(command);

    return OK;
}

/*This function gets the input directly from the user and gives it to the program.*/
STATUS command_get_user_input(Command *command) {
    T_Command cmd = NO_CMD;
    char input[CMD_LENGHT+INFO_LENGHT+1] = "";
    int i = UNKNOWN-NO_CMD+1;
    char *inputCommand;
    char *inputInfo;

    if (command == NULL) return ERROR;

    if (fgets(input, CMD_LENGHT+INFO_LENGHT+1, stdin) != NULL) {
        cmd = UNKNOWN;
        inputCommand = strtok(input, " \n");
		inputInfo = strtok(NULL, " \n");

        while (cmd == UNKNOWN && i < N_CMD && inputCommand != NULL) {
            if (!strcasecmp(inputCommand, short_cmd_to_str[i]) || !strcasecmp(inputCommand, cmd_to_str[i])) {
                cmd = i+NO_CMD;
            } else {
                i++;
            }
        }

        command->command = cmd;

        if (inputInfo != NULL && strcmp(inputInfo, "-->") != 0) {
			strcpy(command->info, inputInfo);

			if (cmd == 11) {
				inputInfo = strtok(NULL, " \n");
				if (strcasecmp(inputInfo, "with") != 0) {
					strcpy(command->info, "NO_INFO");
					return ERROR;
				}
				inputInfo = strtok(NULL, " \n");

				strcat(command->info, " ");
				strcat(command->info, inputInfo);
			}
        } else {
            strcpy(command->info, "NO_INFO");
        }


    }

    return OK;
}

/*This function gets the input directly from the user and gives it to the program, but only in ProMode .*/
STATUS command_proMode(Command *command) {
    T_Command cmd = NO_CMD;
    char input = '\0';
    int i = UNKNOWN-NO_CMD+1;
    char inputCommand[CMD_LENGHT];

    if (command == NULL) return ERROR;

    system("/bin/stty raw");
    input = getchar();
    /* Este if parece que lo esta ignorando un poco xd*/
    if (input == '^'){
        getchar();
        getchar();
        input = getchar();
    }
    system("/bin/stty cooked");

    cmd = UNKNOWN;

    switch (input) {
        case 'A': 
            cmd = FOLLOWING;
            break;
        case 'B':
            cmd = PREVIOUS;
            break;
        case 'C':
            cmd = RIGHT;
            break;
        case 'D':
            cmd = LEFT;
            break;
    }
        switch (input) {
        case 'w': 
            cmd = FOLLOWING;
            break;
        case 's':
            cmd = PREVIOUS;
            break;
        case 'd':
            cmd = RIGHT;
            break;
        case 'a':
            cmd = LEFT;
            break;
    }

    if (cmd != UNKNOWN){
        command->command = cmd;
        return OK;
    }

    inputCommand[0] = input;
    inputCommand[1] = '\0';

    while (cmd == UNKNOWN && i < N_CMD && inputCommand != NULL) {
        if (!strcasecmp(inputCommand, short_cmd_to_str[i])) {
            cmd = i+NO_CMD;
        } else {
            i++;
        }
    }



    command->command = cmd;


    strcpy(command->info, "NO_INFO");
    return OK;
}

/*This function is used to get the command itself from the users input, to give the program the requested order.*/
T_Command command_get_command(Command *command) {

    if (command == NULL) return NO_CMD;

    return command->command;
}

/*This function is used to get the info the user is giving the program to complement the command, such as objects, directions or else*/
char *command_get_info(Command *command) {

    if (command == NULL) return NULL;

    return command->info;
}

/*This function is used to print the command in case we need it while debugging*/
STATUS command_print(Command *command) {

    if (command == NULL) return ERROR;

    fprintf(stdout, "--> Command (Command: %d; Info: %s)\n", command->command, command->info);

    return OK;
}

/*This function is used to get the command name so that we can use it in the graphic engine*/
const char *command_get_str(T_Command cmd) {

    return cmd_to_str[cmd-NO_CMD];
}
