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

#define CMD_LENGHT 30

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
  {"u", "Use"}
};

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command {
  CommandCode code;            /*!< Name of the command */
  char arg[CMD_LENGHT];        /*!<Argument introduced with the command*/
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
  newCommand->arg[0] = '\0';
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

char *command_get_arg(Command* command) {
  if (!command) {
    return NULL;
  }
  return command->arg;
}


Status command_get_user_input(Command* command) {
  char input[CMD_LENGTH] = "", *token = NULL, *arg = NULL;
  int i = UNKNOWN - NO_CMD + 1;
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

    arg = strtok(NULL, " "); 
    if (arg != NULL) {
      command_set_arg(command, arg);
    } else {
      command_set_arg(command, "");
    }

    return OK;
  }
  else {
    return command_set_code(command, EXIT);
  }
}

Status command_set_arg(Command* command, char* arg) {
  if (!command || !arg) {return ERROR;}
  strcpy(command->arg, arg);
  return OK;
}

void command_set_return(Command *command, Status s)
{
  if (!command) {return;}

  command->result = s;
}

Status command_get_return(Command *command)
{
  if (!command) {return ERROR;}

  if (command->result == OK)
  {
    return OK;
  }
  return ERROR;
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
  
    default:
      return "unknown";
  }
}