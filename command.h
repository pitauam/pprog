/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 7

typedef enum { CMDS, CMDL } CommandType;

typedef enum { NO_CMD = -1, UNKNOWN, EXIT, NEXT, BACK, TAKE, DROP } CommandCode;

typedef struct _Command Command;

/**
 * @brief It creates a new command, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @return a new comand, initialized
 */
Command* command_create();

/**
 * @brief It destroys a command, frees the memory
 * @author Profesores PPROG
 *
 * @param command pointer to the command that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
 
Status command_destroy(Command* command);

/**
 * @brief It sets the code of the command
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @param code a tructure with the code of the command
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief It gets the code of the command
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @return the command code
 */
CommandCode command_get_code(Command* command);

/**
 * @brief It gets the input of the user
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_get_user_input(Command* command);

#endif
