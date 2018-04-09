/**
 * @brief It defines the game loop 
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */
/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Own libraries*/
#include "../include/graphic_engine.h"

/*This is the main program of the game, where the aaction takes place. It is responsible of calling all the other function and advises if anythin is going wrong*/
int main(int argc, char *argv[]) {
    Game *game = NULL;
    Command *command = NULL;
    Graphic_engine *gengine;
    FILE *log = NULL;

    if (argc < 2 || argc == 3) { /* Check if we have data file. */
        fprintf(stderr, "Use: %s <game_data_file> (normal use) or %s <game_data_file> -l <game_log_file> (using log file)\n", argv[0], argv[0]);
        return 1;
    }
    if (argc == 4) {
        if (strcmp(argv[2], "-l") == 0) {
            log = fopen(argv[3], "w");
            if (log == NULL) {
                fprintf(stderr, "Error while opening the file.\n");
                return 1;
            }
        } else {
            fprintf(stderr, "Use: %s <game_data_file> (normal use) or %s <game_data_file> -l <game_log_file> (using log file)\n", argv[0], argv[0]);
            return 1;
        }
    }

    game = game_create();
    if (game == NULL) {
        fprintf(stderr, "Error while initializing game.\n");
        return 1;
    }

    if (game_create_from_file(game, argv[1]) == ERROR) {
        fprintf(stderr, "Error while loading the game.\n");
        game_destroy(game);
        return 1;
    }

    gengine = graphic_engine_create();
    if (gengine == NULL) {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return 1;
    }

    command = command_create();
    if (command == NULL) {
        fprintf(stderr, "Error while initializing the command.\n");
        graphic_engine_destroy(gengine);
        game_destroy(game);
        return 1;
    }

    while ((command_get_command(command) != EXIT) && !game_is_over(game)) {
        graphic_engine_paint_game(gengine, game);
        command_get_user_input(command);
        game_update(game, command);

        if (log != NULL) {
            if (strcmp(command_get_info(command), "NO_INFO") == 0) {
                fprintf(log, "%s", command_get_str(game_get_last_command(game)));
            } else {
                fprintf(log, "%s %s", command_get_str(game_get_last_command(game)), command_get_info(command));
            }
            if (game_get_status_last_command(game) == OK) {
                fprintf(log, " --> OK\n");
            } else {
                fprintf(log, " --> ERROR\n");
            }
        }
    }

    command_destroy(command);
    graphic_engine_destroy(gengine);
    game_destroy(game);

    if (log) {
        fclose(log);
    }

    return 0;
}
