#ifndef MTK_WIDGET_H
#define MTK_WIDGET_H

#include "mtk-list.h"
#include "mtk-property.h"

typedef struct mtk_widget_t {
	unsigned id;
	char *name;
	unsigned type_id;
	mtk_list_t *properties;
	mtk_list_t *events;
	struct mtk_widget_t *parent;
	mtk_list_t *children;
} mtk_widget_t;

mtk_widget_t *mtk_widget_create(const char *name, const char *type_name);
void mtk_widget_destroy(mtk_widget_t *widget);

const mtk_property_t *mtk_widget_get_property(mtk_widget_t *widget, 
	const char *name);

#endif