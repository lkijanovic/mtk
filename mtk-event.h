#ifndef MTK_EVENT_H
#define MTK_EVENT_H

typedef struct mtk_event_t {
	char *name;
	void (*callback)(void *data);
} mtk_event_t;

#endif