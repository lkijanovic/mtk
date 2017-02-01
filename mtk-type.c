#include <stdlib.h>
#include <string.h>

#include "mtk-type.h"


mtk_type_t *mtk_type_create(const char *name)
{

	return mtk_type_create_ext(name, NULL, NULL);

}

mtk_type_t *mtk_type_create_ext(const char *name, const mtk_list_t *properties,
	const mtk_list_t *events)
{

	static int id = 0;
	mtk_type_t *res = NULL;
	char *res_name = NULL;
	mtk_list_t *res_properties = NULL, *res_events = NULL;

	res = malloc(sizeof(mtk_type_t));
	if(res == NULL)
		goto out;
	res_name = strdup(name);
	if(res_name == NULL)
		goto out;
	res_properties = mtk_list_copy(properties);
	if(properties != NULL && res_properties == NULL)
		goto out;
	res_events = mtk_list_copy(events);
	if(events != NULL && res_events == NULL)
		goto out;

	res->name = res_name;
	res->properties = res_properties;
	res->events = res_events;
	res->id = id;
	id++;

	return res;


out:
	mtk_list_destroy(res_properties);
	free(res_name);
	free(res);
	return NULL;

}



void mtk_type_destroy(mtk_type_t *type)
{

	if(type == NULL)
		return;

	mtk_list_destroy(type->properties);
	mtk_list_destroy(type->events);
	free(type->name);
	free(type);

}


mtk_type_t *mtk_type_copy(const mtk_type_t *type)
{

	mtk_type_t *res = NULL;
	char *name = NULL;
	mtk_list_t *properties = NULL, *events = NULL;	

	res = malloc(sizeof(mtk_type_t));
	if(res == NULL)
		goto out;

	name = strdup(type->name);
	if(name == NULL)
		goto out;
	properties = mtk_list_copy(type->properties);
	if(properties == NULL && type->properties != NULL)
		goto out;
	events = mtk_list_copy(type->events);
	if(events == NULL && type->events != NULL)
		goto out;

	res->name = name;
	res->properties = properties;
	res->events = events;
	res->id = type->id;

	return res;


out:
	mtk_list_destroy(properties);
	free(name);
	return NULL;

}

int mtk_type_compare_name(const mtk_type_t *t1, const mtk_type_t *t2)
{

	return strcmp(t1->name, t2->name);

}

int mtk_type_compare_id(const mtk_type_t *t1, const mtk_type_t *t2)
{

	return (t1->id - t2->id);

}
