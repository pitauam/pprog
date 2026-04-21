/**
 * @brief It implements the interface data strucutre
 *
 * @file interface_data.c
 * @author Profesores PPROG, Samuel Manzorro and Marta López
 * @version 0
 * @date 12-04-2026
 * @copyright GNU Public License
 */

#include "interface_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _InterfaceData {
    Command *last_command; /*!< The last command typed by the user */
    Status last_status;    /*!< The last status of the last command typed by the user */
    char msg[WORD_SIZE];   /*!< The message printed by the game*/
};


InterfaceData *interface_data_create() {

InterfaceData *new_intDat;

  new_intDat = (InterfaceData*)calloc(1,sizeof(InterfaceData));
  if (new_intDat == NULL)
  {
    return NULL;
  }

    new_intDat->last_command = command_create();

    new_intDat->last_status = OK;

    new_intDat->msg[0] = '\0';

    return new_intDat;
}


Status interface_data_destroy(InterfaceData *intData) {
    if (!intData)
    {
        return ERROR;
    }

    command_destroy(intData->last_command);

    free(intData);
    intData = NULL;

    return OK;
}

Command* interface_data_get_last_command(InterfaceData *intDat) {
    if (!intDat)
    {
        return NULL;
    }
    
    return intDat->last_command;
}

Status interface_data_set_last_command(InterfaceData *intDat, Command *command) {
    if (!intDat || !command)
    {
        return ERROR;
    }

    intDat->last_command = command;
    return OK;
}

Status interface_data_get_last_status(InterfaceData *intDat) {
    if (!intDat)
    {
        return ERROR;
    }
    
    return intDat->last_status;
}

Status interface_data_set_last_status(InterfaceData *intDat, Status status) {
    if (!intDat)
    {
        return ERROR;
    }

    intDat->last_status = status;
    return OK;
}

char *interface_data_get_message(InterfaceData *intDat) {
  if (!intDat)
  {
    return NULL;
  }

  return intDat->msg;
}

Status interface_data_set_message(InterfaceData *intDat, const char *msg) {

  if (!intDat || msg == NULL)
  {
    return ERROR;
  }

  strcpy(intDat->msg, msg);
  return OK;
}

Status interface_data_print(InterfaceData *intData) {

    Command *aux = NULL;
    char *last_cmd = NULL;
    char *last_st = NULL;

    if (!intData)
    {
        return ERROR;
    }

    aux = intData->last_command;
    last_cmd = command_to_string(command_get_code(aux));

    if (intData->last_status == OK){
        last_st = "OK";
    } else {
        last_st = "ERROR";
    }

    fprintf(stdout, "Last command: %s, last command status: %s, message: %s", last_cmd, last_st, intData->msg);
    return OK;
}