#include <stdlib.h>
#include <string.h>

#include "mtk-event.h"

mtk_event_t *mtk_event_create(const char *name, void (*callback)(void *data))
{

	mtk_event_t *res = NULL;
	char *res_name;

	res = malloc(sizeof(mtk_event_t));
	if(res == NULL)
		goto out;

	res_name = strdup(name);
	if(res_name == NULL)
		goto out;

	res->callback = callback;
	res->name = res_name;

	return res;

out:
	free(res);
	return NULL;

}

void mtk_event_destroy(mtk_event_t *event)
{

	if(event == NULL)
		return;

	free(event->name);
	free(event);

}

mtk_event_t *mtk_event_copy(const mtk_event_t *event)
{
	mtk_event_t *res = NULL;
	char *name;

	res = malloc(sizeof(mtk_event_t));
	if(res == NULL)
		goto out;

	name = strdup(event->name);
	if(name == NULL)
		goto out;

	res->name = name;
	res->callback = event->callback;
	return res;


out:
	free(res);
	return NULL;

}

int mtk_event_compare(const mtk_event_t *t1, const mtk_event_t *t2)
{

	return strcmp(t1->name, t2->name);

}
