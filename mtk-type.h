#ifndef MTK_TYPE_H
#define MTK_TYPE_H

typedef struct mtk_type_t {
	char *name;
	int id;
	struct mtk_type_t *next;
} mtk_type_t;

typedef struct mtk_type_list_t {
	mtk_type_t *first;
	mtk_type_t *last;
	int next_id;
} mtk_type_list_t;



mtk_type_t *mtk_type_create(const char *name, int id);
void mtk_type_destroy(mtk_type_t *type);

mtk_type_list_t *mtk_type_list_create();
void mtk_type_list_destroy(mtk_type_list_t *list);
int mtk_type_list_insert(mtk_type_list_t *list, const char *name);
int mtk_type_list_search_name(mtk_type_list_t *list, const char *name);
const char *mtk_type_list_search_id(mtk_type_list_t *list, int id);

#endif
