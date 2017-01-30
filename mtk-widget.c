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
	int type_id;

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
