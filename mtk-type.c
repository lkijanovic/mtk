#include <stdlib.h>
#include <string.h>

#include "mtk-type.h"


/* 
 * Creates new type from given name and id and returns pointer to it.
 * Returns NULL on error.
 */
mtk_type_t *mtk_type_create(const char *name, int id)
{

	mtk_type_t *type;

	type = malloc(sizeof(mtk_type_t));
	if(type == NULL)
		goto outA;
	type->name = strdup(name);
	if(type->name == NULL)
		goto outB;
	type->id = id;
	type->next = NULL;

	return type;

outB:
	free(type);
outA:
	return NULL;

}

/* 
 * Frees previously created type and its resources.
 * Performs no operation if NULL pointer is passed.
 * Does not deallocate next or previous mtk_type_t in list.
 */
void mtk_type_destroy(mtk_type_t *type) {

	if(type == NULL)
		return;
	free(type->name);
	free(type);

}

/* 
 * Creates empty type list and returns pointer to it.
 * Returns NULL on error.
 */
mtk_type_list_t *mtk_type_list_create()
{

	mtk_type_list_t *list;

	list = malloc(sizeof(mtk_type_list_t));
	if(list == NULL)
		return NULL;
	
	list->first = list->last = NULL;
	list->next_id = 0;

	return list;

}


/* 
 * Frees previously created type list and its resources.
 * Performs no operation if NULL pointer is passed.
 */
void mtk_type_list_destroy(mtk_type_list_t *list) {

	mtk_type_t *ptr, *t;
	
	if(list == NULL)
		return;

	ptr = list->first;
	while(ptr != NULL) {
		t = ptr;
		ptr = ptr->next;
		free(t);
	}	

	free(list);

}

/*
 * Inserts new type in type list, and returns 1 on success.
 * Returns 0 on failure without modifying list.
 */
int mtk_type_list_insert(mtk_type_list_t *list, const char *name)
{

	mtk_type_t *type;

	if(mtk_type_list_search_name(list, name) != -1)
		goto out;

	type = mtk_type_create(name, list->next_id);
	if(type == NULL)
		goto out;
	list->next_id++;

	if(list->first == NULL)
		list->first = list->last = type;
	else
		list->last = list->last->next = type;

	return 1;


out:
	return 0;

}

/* 
 * Searches type list by type name and returns type id. 
 * Returns -1 if there are no matches.
 */
int mtk_type_list_search_name(mtk_type_list_t *list, const char *name) 
{
	mtk_type_t *ptr;
	
	ptr = list->first;
	while (ptr != NULL) {
		if(strcmp(ptr->name, name) == 0)
			return ptr->id;
		ptr = ptr->next;
	}

	return -1;

}

/* Searches type list by type id and returns type name. 
 * Returns NULL if there are no matches.
 */
const char *mtk_type_list_search_id(mtk_type_list_t *list, int id)
{
	mtk_type_t *ptr;
	
	ptr = list->first;
	while (ptr != NULL) {
		if(ptr->id == id)
			return ptr->name;
		ptr = ptr->next;
	}

	return NULL;
}
