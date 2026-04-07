#include <stdio.h>
#include <stdlib.h>

#include "inventory.h"



struct _Inventory
{
    Set *obj;
    int max_obj;
};


Inventory *inventory_create(){

    Inventory *new_inventory = NULL;

    if(!(new_inventory = (Inventory*)malloc(sizeof(Inventory)))){
        return NULL;
    }

    new_inventory->obj = set_create();
    new_inventory->max_obj = 0;

    return new_inventory;
}

Status inventory_destroy(Inventory *inventory){

    if(!inventory){
        return ERROR;
    }

    if(set_destroy(inventory->obj) == ERROR){
        return ERROR;
    }

    free(inventory);

    return OK;
}

Status inventory_set_max_obj(Inventory* inventory, int max){

    if(!inventory || max < 1){
        return ERROR;
    }

    inventory->max_obj = max;

    return OK;
}

int inventory_get_max_obj(Inventory* inventory){
    
    if(!inventory){
        return -1;
    }

    return inventory->max_obj;
}

Status inventory_add_object(Inventory* inventory, Id id){

    if(!inventory || !inventory->obj || id < 0 || inventory_get_n_objects(inventory)==inventory_get_max_obj(inventory)){
        return ERROR;
    }

    if(set_find_id(inventory->obj, id)){
        return ERROR;
    }
    set_add_value(inventory->obj, id);

    return OK;
}

Status inventory_remove_object(Inventory* inventory, Id id){
    if(!inventory || !inventory->obj || id < 0 || id == NO_ID ){                                  /*falta compribar si esta vacio*/
        return ERROR;
    }

    if(set_find_id(inventory->obj, id)){
        set_del_value(inventory->obj, id);
    return OK;
    }

    return ERROR;
}

Id inventory_get_object_id(Inventory* inventory, int pos){

    if (inventory == NULL || inventory->obj == NULL || pos < 0) {
        return FALSE;
    }

    return set_get_id(inventory->obj, pos);
}

Bool inventory_is_empty(Inventory* inventory){

    if (inventory == NULL || inventory->obj == NULL) {
        return TRUE;
    }

    if (set_get_n_ids(inventory->obj) > 0){
        return FALSE;
    } 

    return TRUE;
}

Bool inventory_is_full(Inventory* inventory){
     if (inventory == NULL || inventory->obj == NULL) {
        return FALSE;
    }

    if (set_get_n_ids(inventory->obj) == inventory_get_max_obj(inventory)){
        return TRUE;
    } 

    return FALSE;
}


Bool inventory_find_object(Inventory* inventory, Id id){

    if (inventory == NULL || inventory->obj == NULL || id == NO_ID) {
        return FALSE;
    }

    if(set_find_id(inventory->obj, id) == ERROR){
        return FALSE;
    }

    return TRUE;
}

int inventory_get_n_objects(Inventory* inventory){

    if(inventory == NULL){
        return -1;
    }

    return set_get_n_ids(inventory->obj);
}

Status inventory_print(Inventory* inventory){

    if(!inventory || !inventory->obj){
        return ERROR;
    }
    if (inventory_is_empty(inventory) == FALSE) {
        fprintf(stdout, "---> There's %d objects in the inventory.\n", set_get_n_ids(inventory->obj));
    } else {
        fprintf(stdout, "---> No object in the inventory.\n");
    }

    fprintf(stdout, "Max objects of the inventory: %d", inventory->max_obj);

    return OK;
}