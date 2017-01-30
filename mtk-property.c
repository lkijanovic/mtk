#include <stdlib.h>
#include <string.h>

#include "mtk-property.h"

mtk_property_t *mtk_property_create(const char *name, const char *value)
{

	mtk_property_t *res = NULL;
	char *res_name = NULL;
	char *res_value = NULL;

	res = malloc(sizeof(mtk_property_t));
	if(res == NULL)
		goto out;

	res_name = strdup(name);
	if(res_name == NULL)
		goto out;

	res_value = strdup(value);
	if(res_value == NULL)
		goto out;

	res->name = res_name;
	res->value = res_value;

out:
	free(res_name);
	free(res);
	return NULL;

}

void mtk_property_destroy(mtk_property_t *property)
{

	if(property == NULL)
		return;

	free(property->name);
	free(property->value);
	free(property);

}

mtk_property_t *mtk_property_copy(mtk_property_t *dest,
	const mtk_property_t *src)
{

	char *name = NULL;
	void *value = NULL;

	name = strdup(src->name);
	if(name == NULL)
		goto out;
	value = strdup(src->value);
	if(value == NULL)
		goto out;

	dest->name = name;
	dest->value = value;

	return dest;


out:
	free(name);
	return NULL;

}

int mtk_property_compare(const mtk_property_t *t1, const mtk_property_t *t2)
{

	return strcmp(t1->name, t2->name);

}
