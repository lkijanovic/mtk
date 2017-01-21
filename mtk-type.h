#ifndef MTK_TYPE_H
#define MTK_TYPE_H

typedef struct mtk_type_t {
	char *name;
	int id;
} mtk_type_t;

typedef struct mtk_typetable_t {
	mtk_type_t **types;
	int count;
	int size;
	int next_id;
} mtk_typetable_t;



mtk_type_t *mtk_type_create(const char *name, int id);
void mtk_type_destroy(mtk_type_t *type);

mtk_typetable_t *mtk_typetable_create();
void mtk_typetable_destroy(mtk_typetable_t *table);
int mtk_typetable_insert(mtk_typetable_t *table, const char *name);
int mtk_typetable_search_name(mtk_typetable_t *table, const char *name);
const char *mtk_typetable_search_id(mtk_typetable_t *table, int id);

#endif
