/**
 * @brief It implements the dialogue module
 * @file dialogue.c
 * @author Javier Lougedo
 * @version 1.0
 * @date 22-04-2018
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

/*Own libraries*/
#include "../include/dialogue.h"

/*We define the size of the arrays of chars we will be using.*/
#define

char* dialogue(Game *g){
  T_Command cmd;
  int ran, errs;
  char str[MAX_DIA];

  cmd = game->last_cmd;
  errs = game->consec_error_num;

  switch (cmd) {
/*FEEDBACK MÁS SENCILLO*/
    case NO_CMD:
      return DIA_ERROR;
    case UNKNOWN:
      return DIA_UNKNOWN[errs][ran%MAX_DIA_UNKNOWN];
    case EXIT:
      return DIA_EXIT[errs][ran%MAX_DIA_EXIT];
    case THROW:
      return DIA_THROW[errs][ran%MAX_DIA_THROW];
    case LOAD:
      return DIA_LOAD[errs][ran%MAX_DIA_LOAD];
    case SAVE:
      return DIA_SAVE[errs][ran%MAX_DIA_SAVE];
/*TIENEN UN FEEDBACK MAS COMPLETO QUE IMPLEMENTAR*/
    case TURNON:
      if (errs > 0) return DIA_TURNON[errs][ran%MAX_DIA_TURNON];
      fprintf(str, "");
    case TURNOFF:
      if (errs > 0) return DIA_TURNOFF[errs][ran%MAX_DIA_TURNOFF];
      fprintf(str, "");
    case OPEN:
      if (errs > 0) return DIA_OPEN[errs][ran%MAX_DIA_OPEN];
      fprintf(str, "");
    case CHECK:
      if (errs > 0) return DIA_CHECK[errs][ran%MAX_DIA_CHECK];
      fprintf(str, "");
    case GRASP:
      if (errs > 0) return DIA_GRASP[errs][ran%MAX_DIA_GRASP];
      fprintf(str, "");
    case DROP:
      if (errs > 0) return DIA_DROP[errs][ran%MAX_DIA_DROP];
      fprintf(str, "");
/*FEEDBACK RELATIVO AL MOVIMIENTO*/
    default:
      return DIA_MOVE[errs][ran%MAX_DIA_MOVE];
  }
}
