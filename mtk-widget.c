#include <stdlib.h>
#include <string.h>

#include "mtk-main.h"
#include "mtk-list.h"
#include "mtk-type.h"
#include "mtk-widget.h"

extern mtk_data_t *data;

mtk_widget_t *mtk_widget_create(const char *name, const char *type_name)
{

	mtk_widget_t *res = NULL;
	char *res_name = NULL;
	const mtk_type_t *type;
	mtk_type_t *t = NULL;
	unsigned type_id;

	res = malloc(sizeof(mtk_widget_t));
	if(res == NULL)
		goto out;

	res_name = strdup(name);
	if(res_name == NULL)
		goto out;

	t = mtk_type_create(type_name);
	if(t == NULL)
		goto out;

	type = mtk_list_search(data->types, t, mtk_type_compare_id);
	if(type == NULL)
		goto out;

	mtk_type_destroy(t);
	type_id = type->id;

	res->name = res_name;
	res->type_id = type_id;
	res->id = 0;/* TODO: generate id */
	res->parent = NULL;
	res->children = NULL;
	res->properties = NULL;
	res->events = NULL;

	return res;


out:
	mtk_type_destroy(t);
	free(res_name);
	free(res);
	return NULL;

}

void mtk_widget_destroy(mtk_widget_t *widget)
{

	if(widget == NULL)
		return;

	free(widget->name);
	mtk_list_destroy(widget->properties);
	mtk_list_destroy(widget->events);

}


int mtk_widget_link(mtk_widget_t *widget, mtk_widget_t *child)
{

	if(mtk_list_search(widget->children, child))
		return 0;

	child->parent = NULL;
	if(!mtk_list_insert(widget->children, child))
		return 1;

}


const mtk_property_t *mtk_widget_get_property(const mtk_widget_t *widget, 
	const char *name)
{

	mtk_property_t *t;
	const mtk_property_t *loc_res, *typ_res, *glb_res, *res;
	mtk_type_t *type = NULL;

	t = mtk_property_create(name, "");
	if(t == NULL)
		goto out;

	if(widget->type_id < mtk_array_size(data->types))
		type = mtk_array_fetch(data->types, widget->type_id);
	if(type == NULL)
		goto out;
	
	loc_res = mtk_list_search(widget->properties, t, mtk_property_compare);
	typ_res = mtk_list_search(type->properties, t, mtk_property_compare);
	glb_res = mtk_hashtab_search(data->properties, t, mtk_property_compare);

	if(loc_res != NULL)
		res = loc_res;
	else if(typ_res != NULL)
		res = typ_res;
	else
		res = glb_res;

	mtk_property_destroy(t);
	return res;


out:
	mtk_property_destroy(t);
	return NULL;

}
