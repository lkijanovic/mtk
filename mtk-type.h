#ifndef MTK_TYPE_H
#define MTK_TYPE_H

typedef struct mtk_type_t {
	char *name;
	int id;
} mtk_type_t;

typedef struct mtk_type_list_t {
	mtk_type_t *first;
	mtk_type_t *last;
	int next_id;
} mtk_type_list_t;



mtk_type_t *mtk_type_create(const char *name, int id);
void mtk_type_destroy(mtk_type_t *type);
mtk_type_t *mtk_type_copy(mtk_type_t *dest, const mtk_type_t *src);

#endif
