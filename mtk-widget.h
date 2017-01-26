#ifndef MTK_WIDGET_H
#define MTK_WIDGET_H


typedef struct mtk_widget_t {
	int id;
	int type_id;
	mtk_list_t *properties;
	mtk_list_t *events;
	struct mtk_widget_t *parent;
	struct mtk_widget_t **children;
	int children_count;
	int children_size;
} mtk_widget_t;

#endif