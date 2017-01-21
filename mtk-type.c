#include <stdlib.h>
#include <string.h>

#include "mtk-type.h"



#define MTK_TYPETABLE_INIT_SIZE 50



/* 
 * Creates new type from name and id and returns pointer to it.
 * Returns NULL on error.
 */
mtk_type_t *mtk_type_create(const char *name, int id)
{

	mtk_type_t *type = NULL;

	/* create new type */
	type = malloc(sizeof(mtk_type_t));
	if(type == NULL)
		goto out;
	type->name = strdup(name);
	if(type->name == NULL)
		goto out;
	type->id = id;

	return type;

out:
	free(type);
	return NULL;

}

/* 
 * Frees type and its resources.
 */
void mtk_type_destroy(mtk_type_t *type) {

	free(type->name);
	type->name = NULL;

}

/* 
 * Creates empty type table and returns pointer to it.
 * Returns NULL on error.
 */
mtk_typetable_t *mtk_typetable_create()
{

	mtk_typetable_t *table = NULL;

	table = malloc(sizeof(mtk_typetable_t));
	if(table == NULL)
		goto out;

	table->types = malloc(MTK_TYPETABLE_INIT_SIZE * sizeof(mtk_type_t *));
	if(table->types == NULL)
		goto out;
	table->size = MTK_TYPETABLE_INIT_SIZE;
	table->count = 0;
	table->next_id = 0;

	return table;


out:
	free(table);
	return NULL;

}


/* 
 * Frees type table and its resources.
 */
void mtk_typetable_destroy(mtk_typetable_t *table) {
	
	if(table == NULL)
		return;
	if(table->types == NULL)
		return;

	for(int i = 0; i < table->count; i++) {
		mtk_type_destroy(table->types[i]);
		table->types[i] = NULL;
	}

	free(table->types);
	free(table);

}

/*
 * Inserts new type in type table, and returns 1 on success.
 * Returns 0 on failure without modifying table.
 */
int mtk_typetable_insert(mtk_typetable_t *table, const char *name)
{

	mtk_type_t *type = NULL;

	/* check if type already exists */
	if(mtk_typetable_search_name(table, name) != -1)
		goto out;

	/* do reallocations if necessary */
	if(table->count == table->size) {
		mtk_type_t **ntypes;
		int nsize = table->size * 2;

		ntypes = realloc(table->types, nsize * sizeof(mtk_type_t *));
		if(ntypes == NULL)
			goto out;

		table->size = nsize;
		table->types = ntypes;
	}

	/* create new type */
	type = mtk_type_create(name, table->count);
	if(type == NULL)
		goto out;

	/* insert type to the end of the type table */
	table->types[table->count] = type;
	table->count += 1;

	return 1;


out:
	return 0;

}

/* 
 * Searches type table by type name and returns type id. 
 * Returns -1 if there are no matches.
 */
int mtk_typetable_search_name(mtk_typetable_t *table, const char *name) 
{

	for(int i = 0; i < table->count; i++) {
		if(strcmp(table->types[i]->name, name) == 0)
			return i;
	}

	return -1;

}

/* Searches type table by type id and returns type name. 
 * Returns NULL if there are no matches.
 */
const char *mtk_typetable_search_id(mtk_typetable_t *table, int id)
{
	if(id >= table->count)
		return NULL;

	return table->types[id]->name;
}
