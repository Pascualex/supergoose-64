/** 
 * @brief It defines the final functions
 * @file final.c
 * @author Eric Morales
 * @version 1.0 
 * @date 23-04-2018
 * @updated 23-04-2018
 * @copyright GNU Public License
 */

#undef __STRICT_ANSI__

/*C libraries*/
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
/*Own libraries*/
#include "../include/screen.h"
#include "../include/final.h"

/*Final structure, which includes the seven areas (options).*/
struct _Final {
    Area *title, *text, *art;
};

/*This function is used to allocate the memory the final is going to use.*/
Final *final_create() {
    Final *final = NULL;

    screen_init(BLACK);
    final = (Final *) malloc(sizeof (Final));

    final->title =  screen_area_init(25,  7, 78, 6,  GREEN, BLACK, FALSE);
    final->text =   screen_area_init(25, 19, 78, 11,  BLUE, BLACK, FALSE);
    final->art =    screen_area_init(25, 35, 78, 22,  BLUE, BLACK, FALSE);

    return final;
}

/*This function is used to free all the memory used by the final*/
void final_destroy(Final *final) {

    if (final == NULL) return;

    screen_area_destroy(final->title);
    screen_area_destroy(final->text);
    screen_area_destroy(final->art);
    free(final);
}

/*This function is the one responsible of painting the final*/
void final_paint(Final *final, RULES_STATUS rule) {
    wchar_t unicode_str[COLUMNS];

    /* Paint the in the title area */
    screen_area_clear(final->title);
    swprintf(unicode_str, COLUMNS, L"    _____                        ______                         _____ __ __");
    screen_area_puts(final->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"   / ___/ __  ______  ___  _____/ ____/___  ____  ________     / ___// // /");
    screen_area_puts(final->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"   \\__  \\/ / / / __ \\/ _ \\/ ___/ / __/ __ \\/ __ \\/  ___/_ \\   / __ \\/ // /_");
    screen_area_puts(final->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"   ___/ / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ (__  )  __/  / /_/ /__  __/");
    screen_area_puts(final->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"  /____/\\____/ ____/\\___/_/   \\____/\\____/\\____/____/\\__/____\\____/  /_/");
    screen_area_puts(final->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"            /_/                                         /___/");
    screen_area_puts(final->title, unicode_str);




    if (rule == END1) {

        screen_area_clear(final->text);
        swprintf(unicode_str, COLUMNS, L"YOU SCAPED THROUGH THE HALL:");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"Somehow, you managed to get the needed key to open the principal door and ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"scape the lab. The scientists who had the guts to go back to the lab didn't ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"even know how you survived or how did you escape. Even though, as a Goose you");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"are going to have a hard life. Things aren't easy in the geese world, so take");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"care of yourself and try to find a goose princess to make your life easier ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"and hit a “braguetazo”.");
        screen_area_puts(final->text, unicode_str);

    } else if (rule == END2) {

        screen_area_clear(final->text);
        swprintf(unicode_str, COLUMNS, L"YOU DIVIDED YOURSELF INTO THE GOOSE AND THE MAN:");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"You managed to find a way to divide yourself from your Goose body and now you");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"are split again. You decide to adopt the Goose and take care of it. Now it is");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"your life partner. Scientists were surprised when they came back to the laboratory");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"and saw you there, sitting on the reception, waiting for them to appear. You might");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"become rich for suing them for what they did to you!");
        screen_area_puts(final->text, unicode_str);

    } else if (rule == END3) {

        screen_area_clear(final->text);
        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"YOU BECAME THE REAL SUPERGOOSE:");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"You went a bit crazy and decided you would try to rule the world.");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"You have become a vital part for the Geesengers and the world loves you.");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"You use a goose wing as your shield and now you are getting in problems with ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"justice due to some Goose called Iron Goose, but it’s all going to be OK.");
        screen_area_puts(final->text, unicode_str);

    } else {

        swprintf(unicode_str, COLUMNS, L"  ▄████  ▄▄▄       ███▄ ▄███▓▓█████     ▒█████   ██▒   █▓▓█████  ██▀███  ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██▒  ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ▒██░  ██▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    ▒██   ██░  ▒██ █░░▒▓█  ▄ ▒██▀▀█▄  ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ░ ████▓▒░   ▒▀█░  ░▒████▒░██▓ ▒██▒");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L" ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ░ ▒░▒░▒░    ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"  ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░     ░ ▒ ▒░    ░ ░░   ░ ░  ░  ░▒ ░ ▒░");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"░ ░   ░   ░   ▒   ░      ░      ░      ░ ░ ░ ▒       ░░     ░     ░░   ░ ");
        screen_area_puts(final->text, unicode_str);

        swprintf(unicode_str, COLUMNS, L"                                                     ░                 ");
        screen_area_puts(final->text, unicode_str);
    }



    screen_area_clear(final->art);
    swprintf(unicode_str, COLUMNS, L"                            _________-----_____");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                 _____------           __      ----_");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"           ___----             ___------             \\");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"             ----________        ----                 \\");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                         -----__    |             _____)");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                              __-                /     \\");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                  _______-----    ___--          \\    /)\\");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"            ------_______      ---____            \\__/  /");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                         -----__    \\ --    _          /\\");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                     ----|   /          |");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         |  |___________|");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         |  | ((_(_)| )_)");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         |  \\_((_(_)|/(_)");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         \\             (");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                          \\_____________)");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                               /  (");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                      ((____.-'    )");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                       \\         /");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                        \\'-.-.-'`/");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         \\______/");
    screen_area_puts(final->art, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                           _|_\\_");
    screen_area_puts(final->art, unicode_str);
    /* Dump to the terminal */
    screen_paint();
}
