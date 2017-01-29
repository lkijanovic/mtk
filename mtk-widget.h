#ifndef MTK_WIDGET_H
#define MTK_WIDGET_H

#include "mtk-list.h"

typedef struct mtk_widget_t {
	int id;
	char *name;
	int type_id;
	mtk_list_t *properties;
	mtk_list_t *events;
	struct mtk_widget_t *parent;
	mtk_list_t *children;
} mtk_widget_t;

mtk_widget_t *mtk_widget_create(const char *name, const char *type_name);
void mtk_widget_destroy(mtk_widget_t *widget);

#endif