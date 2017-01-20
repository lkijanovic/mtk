#include <stdlib.h>
#include <string.h>


#include "mtk-type.h"

#define MTK_TYPE_TABLE_INIT_SIZE 50

mtk_type_table_t *mtk_type_table_create()
{

	mtk_type_table_t *table;
	
	/* create empty table */
	table = malloc(sizeof(mtk_type_table_t));
	table->size = MTK_TYPE_TABLE_INIT_SIZE;
	table->count = 0;
	table->entries = NULL;
	table->next_id = 0;
	
	return table;
	
}

void mtk_type_table_add_entry(mtk_type_table_t *table, char *type_name)
{
	
	mtk_type_t *entry;
	
	/* do reallocations if necessary */
	if(table->count == table->size) {
		table->size = table->size * 2;
		table->entries = realloc(table->entries, table->size);
	}
	
	/* create new type */
	entry = mtk_type_create(type_name, table->next_id);
	table->next_id += 1;
	
	/* insert type */
	table->entries[table->count] = entry;
	table->count += 1;
	
	/* make sure table is sorted */
	for(int i = table->count - 2; i >= 0; i--) {
		int cmp = strcmp(table->entries[i]->type_name, 
			table->entries[i+1]->type_name);
			
		if(cmp > 0) {
			mtk_type_t *t = table->entries[i];
			table->entries[i] = table->entries[i+1];
			table->entries[i+1] = t;
		} else {
			break;
		}
		
		/* TODO: error-checking for multiple types with same name */
	}
}


mtk_type_t *mtk_type_create(char *type_name, unsigned type_id)
{

	mtk_type_t *entry;
	
	/* create new widget */
	entry = malloc(sizeof(mtk_type_t));
	entry->type_name = type_name;
	entry->type_id = type_id;
	
	return entry;
}
