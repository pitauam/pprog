/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @version 0
 * @date 22-02-2026
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define CMD_LENGTH 30 /*!< Maximum lenght of a command input */
#define MAX_CMD_ARGS 3 /*!< Maximum arguments a command can have */
#define N_CMDT 2    /*!< Number of command Types*/
#define N_CMD 13      /*!< Number of commands*/

typedef enum { CMDS, CMDL } CommandType;

typedef enum { NO_CMD = -1, UNKNOWN, EXIT, MOVE, TAKE, DROP, ATTACK, CHAT, INSPECT, RECRUIT, ABANDON, USE, OPEN } CommandCode;

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


/**
 * @brief It sets the argument of the command
 * @author Paula de la Fuente
 *
 * @param command a pointer to the command
 * @param arg a string with the argument to set
 * @param index the index that the argument wanted occupies on the array
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_set_arg(Command* command, char* arg, int index);


/**
 * @brief It gets the argument of the command
 * @author Paula de la Fuente
 *
 * @param command a pointer to the command
 * @param index index of that the argument wanted ocuppies in the array
 * @return the argument code
 */
char *command_get_arg(Command* command, int index);

/**
 * @brief It sets the return result of the command
 * @author Santiago Pita
 *
 * @param command a pointer to the command
 * @param s the return state
 */
void command_set_return(Command *command, Status s);

/**
 * @brief It gets the return result of the command
 * @author Santiago Pita
 *
 * @param command a pointer to the command
 * @return the return state
 */
Status command_get_return(Command *command);

/**
 * @brief It changes the command to string, we use it in game_loop_log.
 * @author Marta López
 *
 * @param code the new CommandCode to be set
 * @return a string
 */
char *command_to_string(CommandCode cmd);

#endif
