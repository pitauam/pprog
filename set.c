/**
 * @brief Set module
 *
 * @file set.c
 * @author Santiago Pita
 * @version 0
 * @date 17-02-2026
 */

#include "set.h"
#include <stdlib.h>

#define SIZE 256 /*64 Ids */



struct _Set
{
    Id ids[SIZE];   /*Array of static Ids*/
    int n_ids;      /*Keeps track of the number of ids in the Set*/
};

Set* set_create()
{
    Set *new_set = NULL;
    int i;
    
    new_set = (Set*)calloc(1,sizeof(Set));
    if (!new_set) {return NULL;}

    new_set->n_ids = 0;
    for (i = 0; i < SIZE; i++)
    {
        new_set->ids[i] = NO_ID;
    }

    return new_set;
}

Status set_destroy(Set* set)
{
    if (!set){
        return ERROR;
    }

    free(set);
    return OK;
}

Status set_add_value(Set* set, Id value)
{
    int i;
    if (!set){
        return ERROR;
    }

    for (i = 0; i < SIZE; i++)
    {
        if (set->ids[i] == NO_ID)
        {
            set->ids[i] = value;
            return OK;
        }
    }
    return ERROR;
}

Status set_del_value(Set* set, Id value) {
    int i;
    if (!set || value == NO_ID) return ERROR;

    for (i = 0; i < SIZE; i++) {
        if (set->ids[i] == value) {
            set->ids[i] = NO_ID;
            set->n_ids--;
            return OK;
        }
    }
    return ERROR;
}

Status set_find_id(Set* set, Id id)
{
    int i;
    if (!set) {
        return ERROR; 
    }

    for (i = 0; i < SIZE; i++) {
        if (set->ids[i] == id) {
            return i;
            return OK;
        }
    }

    return ERROR; 
}

Status set_print(Set *set, FILE *pf);

int set_get_n_ids(Set *set)
{
    if (!set){return -1;}

    return set->n_ids;
}


