#include <stdlib.h>

#include "mtk-main.h"
#include "mtk-type.h"
#include "mtk-property.h"
#include "mtk-event.h"

int mtk_init_types();
int mtk_type_register(const char *name);
int mtk_init_properties();
int mtk_property_register(const char *name, const char *value);
int mtk_init_events();
int mtk_event_register(const char *name, void (*callback)(void *));


// contains all MTK internal data
mtk_data_t *data = NULL;

int mtk_init()
{

	xcb_connection_t *conn = NULL;

	/* open connection to X server */
	conn = xcb_connect(NULL, NULL);
	if(xcb_connection_has_error(conn))
		goto out;

	/* allocate mtk_data */
	data = malloc(sizeof(mtk_data_t));
	if(data == NULL)
		goto out;

	/* populate type list with basic types */
	if(!mtk_init_types())
		goto out;
		
	data->xcb_conn = conn;
	data->properties = NULL;
	data->events = NULL;

	/* return 1 on success */
	return 1;


out:
	free(data);
	data = NULL;
	xcb_disconnect(conn);
	return 0;
	
}

void mtk_exit()
{

	if(data == NULL)
		return;

	/* disconnect from X server and free allocated data */
	xcb_disconnect(data->xcb_conn);
	mtk_list_destroy(data->types);
	free(data);
	data = NULL;
	
}

int mtk_init_types()
{
	
	data->types = mtk_list_create_ext(sizeof(mtk_type_t), mtk_type_copy,
		mtk_type_destroy);
	if(data->types == NULL)
		goto out;
	
	if(!mtk_type_register("mtk_blank"))
		goto out;
	if(!mtk_type_register("mtk_window"))
		goto out;
		
	return 1;


out:
	mtk_list_destroy(data->types);
	data->types = NULL;
	return 0;
	
}

int mtk_type_register(const char *name)
{
	mtk_type_t *type = NULL;
	
	type = mtk_type_create(name);
	if(type == NULL)
		goto out;
	if(!mtk_list_insert(data->types, type))
		goto out;
	mtk_type_destroy(type);
	
	return 1;
	
	
out:
	mtk_type_destroy(type);
	return 0;
	
}

int mtk_init_properties()
{
	
	data->properties = mtk_list_create_ext(sizeof(mtk_property_t),
		mtk_property_copy, mtk_property_destroy);
	if(data->properties == NULL)
		goto out;
	
	/* TODO: add other properties */
	if(!mtk_property_register("bg-color", "white"))
		goto out;
	if(!mtk_property_register("fg-color", "black"))
		goto out;

	return 1;


out:
	mtk_list_destroy(data->properties);
	return 0;

}

int mtk_property_register(const char *name, const char *value)
{
	
	mtk_property_t *property = NULL;

	property = mtk_property_create(name, value);
	if(property == NULL)
		goto out;
	if(!mtk_list_insert(data->properties, property))
		goto out;
	mtk_property_destroy(property);
		
out:
	mtk_property_destroy(property);
	return 0;
}


int mtk_init_events()
{
	
	data->events = mtk_list_create_ext(sizeof(mtk_event_t),
		mtk_event_copy, mtk_event_destroy);
	if(data->events == NULL)
		goto out;
	
	/* TODO: add some events later */
	
	return 1;


out:
	mtk_list_destroy(data->events);
	return 0;

}

int mtk_event_register(const char *name, void (*callback)(void *))
{
	
	mtk_event_t *event = NULL;

	event = mtk_event_create(name, callback);
	if(event == NULL)
		goto out;
	if(!mtk_list_insert(data->events, event))
		goto out;
	mtk_event_destroy(event);
		
out:
	mtk_event_destroy(event);
	return 0;
}
