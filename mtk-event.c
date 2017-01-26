#include "mtk-event.h"

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