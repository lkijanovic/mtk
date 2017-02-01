#ifndef MTK_EVENT_H
#define MTK_EVENT_H

typedef struct mtk_event_t {
	char *name;
	void (*callback)(void *data);
} mtk_event_t;


mtk_event_t *mtk_event_create(const char *name, void (*callback)(void *data));
void mtk_event_destroy(mtk_event_t *event);
mtk_event_t *mtk_event_copy(const mtk_event_t *event);

int mtk_event_compare(const mtk_event_t *t1, const mtk_event_t *t2);

#endif