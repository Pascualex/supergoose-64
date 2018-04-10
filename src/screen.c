/** 
 * @brief It defines the screen functions
 * @file screen.c
 * @author Profesores PPROG, edited by Alejandro Pascual
 * @version 2.0 
 * @date 
 * @updated 
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Own libraries*/
#include "../include/screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"  /*La trampa...*/

/*We define the maximum rows and columns of the screen we are going o use, and the TOTAL_DATA which is one bigger than the product, for memory allocating purposes*/
#define ROWS 42
#define COLUMNS 80
#define TOTAL_DATA (ROWS * COLUMNS)

#define BORDER_FG_COLOR WHITE
#define BORDER_BG_COLOR BLACK

#define PROMPT " prompt:> "

/*We define the ACCESS to use it in the memset and simplify things*/
#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))

/*We define the area with two coordinates to define the starting point and the width and height of it*/
struct _Area {
    int x, y, width, height;
    char *cursor;
};
/*We globally define the data used*/
char *data;
int *data_fg_color;
int *data_bg_color;

BOOL *borders;
wchar_t *borders_unicode;

/****************************/
/*     Private functions    */
/****************************/
int screen_area_cursor_is_out_of_bounds(Area *);
void screen_area_scroll_up(Area *);
void screen_utils_replaces_special_chars(char *);
const unsigned char* unicode_to_utf8(wchar_t);

/****************************/
/* Functions implementation */

/****************************/
void screen_init(int color) {
    int i, j;

    screen_destroy(); /* Dispose if previously initialized */

    data = (char *) malloc(sizeof (char)*(TOTAL_DATA));
    if (data == NULL) return;

    data_fg_color = (int *) malloc(sizeof (int)*TOTAL_DATA);
    if (data_fg_color == NULL) {
        free(data);
        return;
    }

    data_bg_color = (int *) malloc(sizeof (int)*TOTAL_DATA);
    if (data_bg_color == NULL) {
        free(data_fg_color);
        free(data);
        return;
    }

    borders = (BOOL *) malloc(sizeof (BOOL) * TOTAL_DATA);
    if (borders == NULL) {
        free(data_bg_color);
        free(data_fg_color);
        free(data);
        return;
    }

    borders_unicode = (wchar_t *) malloc(sizeof (wchar_t) * TOTAL_DATA);
    if (borders_unicode == NULL) {
        free(borders);
        free(data_bg_color);
        free(data_fg_color);
        free(data);
        return;
    }

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            data[i * COLUMNS + j] = ' ';
            data_fg_color[i * COLUMNS + j] = color;
            data_bg_color[i * COLUMNS + j] = color;
            borders[i * COLUMNS + j] = FALSE;
            borders_unicode[i * COLUMNS + j] = L'☒';
        }
    }
}

void screen_destroy() {

    if (data != NULL) free(data);
    if (data_fg_color != NULL) free(data_fg_color);
    if (data_bg_color != NULL) free(data_bg_color);
    if (borders != NULL) free(borders);
    if (borders_unicode != NULL) free(borders_unicode);
}

void screen_paint() {
    int i, j;

    if (data != NULL || data_fg_color != NULL || data_bg_color != NULL) {

        puts("\033[2J"); /*Clear the terminal*/

        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLUMNS; j++) {
                if (borders[i * COLUMNS + j] == TRUE) {
                    printf("\033[1;3%d;4%dm%s\033[0m", data_fg_color[i * COLUMNS + j], data_bg_color[i * COLUMNS + j], unicode_to_utf8(borders_unicode[i * COLUMNS + j]));
                } else {
                    printf("\033[1;3%d;4%dm%c\033[0m", data_fg_color[i * COLUMNS + j], data_bg_color[i * COLUMNS + j], data[i * COLUMNS + j]);
                }
            }

            printf("\n");
        }
    }
}

void screen_gets(char *str) {

    fprintf(stdout, PROMPT);
    if (fgets(str, COLUMNS, stdin)) {
        *(str + strlen(str) - 1) = 0; /* Replaces newline character with '\0' */
    }
}

Area *screen_area_init(int x, int y, int width, int height, int fg_color, int bg_color, BOOL has_border) {
    Area* area = NULL;

    area = (Area *) malloc(sizeof (struct _Area));

    if (area == NULL) {
        return NULL;
    }

    *area = (struct _Area){x, y, width, height, ACCESS(data, x, y)};

    screen_color_box(x, y, width, height, fg_color, bg_color);

    if (has_border == TRUE) {
        screen_add_border(x - 1, y - 1, width + 2, height + 2, BORDER_FG_COLOR, BORDER_BG_COLOR);
    }

    return area;
}

void screen_area_destroy(Area *area) {

    if (area == NULL) {
        return;
    }

    free(area);
}

void screen_area_clear(Area *area) {
    int i = 0;

    if (area != NULL) {
        screen_area_reset_cursor(area);

        for (i = 0; i < area->height; i++) {
            memset(ACCESS(area->cursor, 0, i), (int) ' ', (size_t) area->width);
        }
    }
}

void screen_area_reset_cursor(Area *area) {

    if (area != NULL) {
        area->cursor = ACCESS(data, area->x, area->y);
    }
}

void screen_area_puts(Area *area, char *str) {
    int len = 0;
    char *ptr = NULL;

    if (screen_area_cursor_is_out_of_bounds(area)) {
        screen_area_scroll_up(area);
    }

    screen_utils_replaces_special_chars(str);

    for (ptr = str; ptr < (str + strlen(str)); ptr += area->width) {
        memset(area->cursor, ' ', area->width);
        len = (strlen(ptr) < area->width) ? strlen(ptr) : area->width;
        memcpy(area->cursor, ptr, len);
        area->cursor += COLUMNS;
    }
}

int screen_area_cursor_is_out_of_bounds(Area *area) {

    return area->cursor > ACCESS(data, area->x + area->width, area->y + area->height - 1);
}

void screen_area_scroll_up(Area *area) {

    for (area->cursor = ACCESS(data, area->x, area->y); area->cursor < ACCESS(data, area->x + area->width, area->y + area->height - 2); area->cursor += COLUMNS) {
        memcpy(area->cursor, area->cursor + COLUMNS, area->width);
    }
}

void screen_utils_replaces_special_chars(char *str) {
    char *pch = NULL;

    /* Replaces acutes and tilde with '??' */
    while ((pch = strpbrk(str, "ÁÉÍÓÚÑáéíóúñ"))) {
        memcpy(pch, "??", 2);
    }
}

void screen_color_box(int x, int y, int width, int height, int fg_color, int bg_color) {
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            data_fg_color[(y + i) * COLUMNS + x + j] = fg_color;
            data_bg_color[(y + i) * COLUMNS + x + j] = bg_color;
        }
    }
}

void screen_add_border(int x, int y, int width, int height, int fg_color, int bg_color) {
    int i, j;

    for (i = 0; i < height; i++) {
        borders[(y + i) * COLUMNS + x] = TRUE;
        data_fg_color[(y + i) * COLUMNS + x] = fg_color;
        data_bg_color[(y + i) * COLUMNS + x] = bg_color;

        borders[(y + i) * COLUMNS + x + width - 1] = TRUE;
        data_fg_color[(y + i) * COLUMNS + x + width - 1] = fg_color;
        data_bg_color[(y + i) * COLUMNS + x + width - 1] = bg_color;
    }

    for (i = 1; i < width - 1; i++) {
        borders[y * COLUMNS + x + i] = TRUE;
        data_fg_color[y * COLUMNS + x + i] = fg_color;
        data_bg_color[y * COLUMNS + x + i] = bg_color;

        borders[(y + height - 1) * COLUMNS + x + i] = TRUE;
        data_fg_color[(y + height - 1) * COLUMNS + x + i] = fg_color;
        data_bg_color[(y + height - 1) * COLUMNS + x + i] = bg_color;
    }

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            if (borders[i * COLUMNS + j] == TRUE) {
                if (borders[(i - 1) * COLUMNS + j] == TRUE) {
                    if (borders[i * COLUMNS + j - 1] == TRUE) {
                        if (borders[(i + 1) * COLUMNS + j] == TRUE) {
                            if (borders[i * COLUMNS + j + 1] == TRUE) {
                                borders_unicode[i * COLUMNS + j] = L'╋';
                            } else {
                                borders_unicode[i * COLUMNS + j] = L'┫';
                            }
                        } else {
                            if (borders[i * COLUMNS + j + 1] == TRUE) {
                                borders_unicode[i * COLUMNS + j] = L'┻';
                            } else {
                                borders_unicode[i * COLUMNS + j] = L'┛';
                            }
                        }
                    } else {
                        if (borders[(i + 1) * COLUMNS + j] == TRUE) {
                            if (borders[i * COLUMNS + j + 1] == TRUE) {
                                borders_unicode[i * COLUMNS + j] = L'┣';
                            } else {
                                borders_unicode[i * COLUMNS + j] = L'┃';
                            }
                        } else {
                            if (borders[i * COLUMNS + j + 1] == TRUE) {
                                borders_unicode[i * COLUMNS + j] = L'┗';
                            } else {
                                borders_unicode[i * COLUMNS + j] = L'☒';
                            }
                        }
                    }
                } else {
                    if (borders[i * COLUMNS + j - 1] == TRUE) {
                        if (borders[(i + 1) * COLUMNS + j] == TRUE) {
                            if (borders[i * COLUMNS + j + 1] == TRUE) {
                                borders_unicode[i * COLUMNS + j] = L'┳';
                            } else {
                                borders_unicode[i * COLUMNS + j] = L'┓';
                            }
                        } else {
                            if (borders[i * COLUMNS + j + 1] == TRUE) {
                                borders_unicode[i * COLUMNS + j] = L'━';
                            } else {
                                borders_unicode[i * COLUMNS + j] = L'☒';
                            }
                        }
                    } else {
                        if (borders[(i + 1) * COLUMNS + j] == TRUE) {
                            if (borders[i * COLUMNS + j + 1] == TRUE) {
                                borders_unicode[i * COLUMNS + j] = L'┏';
                            } else {
                                borders_unicode[i * COLUMNS + j] = L'☒';
                            }
                        } else {
                            if (borders[i * COLUMNS + j + 1] == TRUE) {
                                borders_unicode[i * COLUMNS + j] = L'☒';
                            } else {
                                borders_unicode[i * COLUMNS + j] = L'☒';
                            }
                        }
                    }
                }
            } else {
                borders_unicode[i * COLUMNS + j] = L'☒';
            }
        }
    }
}

const unsigned char* unicode_to_utf8(wchar_t c) {
    static unsigned char b_static[5];
    unsigned char* b = b_static;

    if (c < (1 << 7)) {
        *b++ = (unsigned char) (c);
    } else if (c < (1 << 11)) {
        *b++ = (unsigned char) ((c >> 6) | 0xC0);
        *b++ = (unsigned char) ((c & 0x3F) | 0x80);
    } else if (c < (1 << 16)) {
        *b++ = (unsigned char) (((c >> 12)) | 0xE0);
        *b++ = (unsigned char) (((c >> 6)&0x3F) | 0x80);
        *b++ = (unsigned char) ((c & 0x3F) | 0x80);
    } else if (c < (1 << 21)) {
        *b++ = (unsigned char) (((c >> 18)) | 0xF0);
        *b++ = (unsigned char) (((c >> 12)&0x3F) | 0x80);
        *b++ = (unsigned char) (((c >> 6)&0x3F) | 0x80);
        *b++ = (unsigned char) ((c & 0x3F) | 0x80);
    }
    *b = '\0';

    return b_static;
}
