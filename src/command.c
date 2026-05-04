/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @version 1
 * @date 22-04-2026
 * @copyright GNU Public License
 */

#include "command.h"
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>



char *cmd_to_str[N_CMD][N_CMDT] = {
  {"", "No command"},
  {"", "Unknown"},
  {"e", "Exit"},
  {"m", "Move"},
  {"t", "Take"},
  {"d", "Drop"},
  {"a", "Attack"},
  {"c", "Chat"},
  {"i", "Inspect"},
  {"r", "Recruit"},
  {"x", "Abandon"},
  {"u", "Use"},
  {"o", "Open"}

};

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command {
  CommandCode code;            /*!< Name of the command */
  char args[MAX_CMD_ARGS][CMD_LENGTH];        /*!<Arguments introduced with the command*/
  Status result;               /*!<result of the command (error or ok)*/
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Command* command_create() {
  Command* newCommand = NULL;

  newCommand = (Command*)calloc(1,sizeof(Command));
  if (newCommand == NULL) {
    return NULL;
  }

  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;
  newCommand->args[0][0] = '\0';
  return newCommand;
}

Status command_destroy(Command* command) {
  if (!command) {
    return ERROR;
  }

  free(command);
  command = NULL;
  return OK;
}

Status command_set_code(Command* command, CommandCode code) {
  if (!command) {
    return ERROR;
  }

  command->code=code;

  return OK;
}

CommandCode command_get_code(Command* command) {
  if (!command) {
    return NO_CMD;
  }
  return command->code;
}

char *command_get_arg(Command* command, int index) {  /*Now, here we need a specific index to return a concrete arg*/
  if (!command || index < 0 || index >= MAX_CMD_ARGS) {
    return NULL;
  }
  return command->args[index];
}


Status command_get_user_input(Command* command) {
  char input[CMD_LENGTH] = "", *token = NULL, *arg = NULL;
  int i = UNKNOWN - NO_CMD + 1;
  int j;
  CommandCode cmd;

  if (!command)
  {
    return ERROR;
  }

  if (fgets(input, CMD_LENGTH, stdin))
  {
    input[strcspn(input, "\n")] = '\0';
    token = strtok(input, " ");
    if (!token)
    {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD)
    {
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;
      } else {
        i++;
      }
    }

    if (command_set_code(command, cmd) == ERROR)
    {
      return ERROR;
    }
  for(j=0 ; j<MAX_CMD_ARGS ; j++){        /*With more than one argument, we need to store all of them*/
    arg = strtok(NULL, " "); 
    if (arg != NULL) {
      command_set_arg(command, arg, j);
    } else {
      command_set_arg(command, "", j);
    }
  }
    return OK;
  }
  else {
    return command_set_code(command, EXIT);
  }
}

Status command_set_arg(Command* command, char* arg, int index) {  /*Now, here we need a specific index to set the arg in a concrete position*/
  if (!command || !arg || index < 0 || index >= MAX_CMD_ARGS) {return ERROR;}

  strcpy(command->args[index], arg);

  return OK;
}

void command_set_return(Command *command, Status s)
{
  if (!command) {return;}

  command->result = s;
}

Status command_get_return(Command *command)
{
  if (!command)
  {
    return ERROR;
  }

  return command->result;
}

/* We use this function for the log to be able to print the command in a file. */
char *command_to_string(CommandCode cmd){
  switch (cmd)
  {
    case TAKE:
      return "take";

    case DROP:
      return "drop";

    case EXIT:
      return "exit";

    case UNKNOWN:
      return "unknown";

    case ATTACK:
      return "attack";

    case MOVE:
      return "move";

    case CHAT:
      return "chat";

    case INSPECT:
      return "inspect";

    case RECRUIT:
      return "recruit";

    case ABANDON:
      return "abandon";

    case USE:
      return "use";

    case OPEN:
      return "open";
  
    default:
      return "unknown";
  }
}