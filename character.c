/**
 * @brief Implements the character module
 *
 * @file character.c
 * @author Mario Rodriguez
 * @version 0
 * @date 022-02-2026
 */

#include "character.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Character{
    Id id;
    char name[WORD_SIZE +1 ];
    char gdesc[7];
    int health;
    Bool friendly;
    char message[WORD_SIZE +1];
};

Character *character_create(Id id){
    Character *new_character = NULL;

    if(!(new_character = (Character*)malloc(1*sizeof(Character)))){
        return NULL;
    }

    new_character->id = id;
    new_character->name[0] = '\0';
    new_character->gdesc[0] = '\0';
    new_character->health = 100;
    new_character->friendly = 1;
    new_character->message[0] = '\0';

    return new_character;
}

Status character_destroy(Character *character){
    if(character == NULL){
        return ERROR;
    }

    free(character);

    return OK;
}

Id character_get_id(Character *character){
    if(character == NULL){
        return NO_ID;
    }

    return character->id;
}

Status character_set_name(Character *character, char *name){
    if(character == NULL || name == NULL){
        return ERROR;
    }

    strcpy(character->name, name);

    return OK;
}

const char* character_get_name(Character *character){
    if(character == NULL){
        return NULL;
    }

    return character->name;
}

Status character_set_description(Character *character, char *descrp){
    if(character == NULL || descrp == NULL || strlen(descrp) > 6){
        return ERROR;
    }

    strcpy(character->gdesc, descrp);

    return OK;
}

const char *character_get_description(Character *character){
    if(character == NULL){
        return NULL;
    }

    return character->gdesc;
}

Status character_set_health(Character *character, int health){
    if(character == NULL || health < 0 || health > 100){
        return ERROR;
    }

    character->health = health;

    return OK;
}

int character_get_health(Character *character){
    if(character == NULL){
        return -1;
    }

    return character->health;
}

Status character_set_friendly(Character *character, Bool *friendly){
    if(character == NULL || friendly == NULL){
        return ERROR;
    }

    character->friendly = *(friendly);

    return OK;   
}

Bool Character_get_friendly(Character *character){
    if(character == NULL){
        return ERROR;
    }

    return character->friendly;
}

Status character_set_message(Character *character, char *message){
    if(character == NULL || message == NULL){
        return ERROR;
    }

    strcpy(character->message, message);

    return OK;
}

const char *character_get_message(Character *character){
    if(character == NULL){
        return NULL;
    }

    return character->message;
}

Status character_print(Character *character){
    /* Error Control */
    if (!character) {
        return ERROR;
    }

    /* 1. Prints the character's id, name and health */
    fprintf(stdout, "--> character (Id: %ld; Name: %s; Health: %d)\n", character->id, character->name, character->health);

    /* 3. Prints if the character has a description */
    if (character_get_description(character)) {
      fprintf(stdout, "---> Description: %s.\n", character->gdesc);
    }

    if (character_get_message(character)) {
        fprintf(stdout, "---> Message: %s.\n", character->message);
    }
   /* 3. Prints if the player has an object */
  if (Character_get_friendly(character)) {
    fprintf(stdout, "---> Character is friendly.\n");
  } else {
    fprintf(stdout, "---> Character is not friendly.\n");
  }

  return OK;
}