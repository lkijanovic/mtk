#include <stdlib.h>
#include <string.h>

#include "mtk-widget.h"

mtk_property_t *mtk_property_create(char *name, mtk_property_type_t type, 
					void *value, int size)
{
	mtk_property_t *res;
	
	res = malloc(sizeof(mtk_property_t));
	if(res == NULL)
		goto outA;
		
	res->name = strdup(name);
	if(res->name == NULL)
		goto outB;
		
	res->value = malloc(size);
	if(res->value == NULL)
		goto outC;
	memcpy(res->value, value, size);

	res->type = type;
	res->size = size;
	
outC:
	free(res->name);
outB:
	free(res);
outA:
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

mtk_event_t *mtk_event_create(char *name, void (*callback)(void *data))
{
	mtk_event_t *res;
	
	res = malloc(sizeof(mtk_event_t));
	if(res == NULL)
		goto outA;
		
	res->name = strdup(name);
	if(res->name == NULL)
		goto outB;

	res->callback = callback;
	
	return res;

outB:
	free(res);
outA:
	return NULL;
}

void mtk_event_destroy(mtk_event_t *event)
{
	if(event == NULL)
		return;
	
	free(event->name);
	free(event);
}