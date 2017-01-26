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

	return type;

outB:
	free(type);
outA:
	return NULL;

}

/* 
 * Frees previously created type and its resources.
 * Performs no operation if NULL pointer is passed.
 */
void mtk_type_destroy(mtk_type_t *type) {

	if(type == NULL)
		return;
	free(type->name);
	free(type);

}


mtk_type_t *mtk_type_copy(mtk_type_t *dest, const mtk_type_t *src)
{
	char *name;
	
	name = strdup(src->name);
	if(name == NULL)
		goto out;

	memcpy(dest, src, sizeof(mtk_type_t));
	dest->name = name;


	return dest;
	

out:
	return NULL;
	
}