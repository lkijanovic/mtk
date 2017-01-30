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

mtk_event_t *mtk_event_copy(mtk_event_t *dest, const mtk_event_t *src)
{

	char *name = NULL;

	name = strdup(src->name);
	if(name == NULL)
		return NULL;

	dest->name = name;
	dest->callback = src->callback;
	return dest;

}

int mtk_event_compare(const mtk_event_t *t1, const mtk_event_t *t2)
{

	return strcmp(t1->name, t2->name);

}
