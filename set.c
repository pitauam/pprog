/**
 * @brief Set module
 *
 * @file set.c
 * @author Santiago Pita
 * @version 0
 * @date 17-02-2026
 */

#include "set.h"
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

Status set_destroy(Set* set);

Status set_add_value(Set* set, Id value);

Status set_del_value(Set* set, Id value);

Status set_find_id(Set* set, Id id);

Status set_print(Set *set, FILE *pf);



