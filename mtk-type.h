#ifndef MTK_TYPE_H
#define MTK_TYPE_H

#include "mtk-list.h"

typedef struct mtk_type_t {
	char *name;
	int id;
	mtk_list_t *properties;
	mtk_list_t *events;
} mtk_type_t;

typedef struct mtk_type_list_t {
	mtk_type_t *first;
	mtk_type_t *last;
} mtk_type_list_t;



mtk_type_t *mtk_type_create(const char *name);
mtk_type_t *mtk_type_create_ext(const char *name, const mtk_list_t *properties,
	const mtk_list_t *events);
void mtk_type_destroy(mtk_type_t *type);
mtk_type_t *mtk_type_copy(const mtk_type_t *type);

int mtk_type_compare_name(const mtk_type_t *t1, const mtk_type_t *t2);
int mtk_type_compare_id(const mtk_type_t *t1, const mtk_type_t *t2);

#endif
