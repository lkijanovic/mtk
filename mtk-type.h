#ifndef MTK_TYPE_H
#define MTK_TYPE_H

typedef struct mtk_type_t {
	char *type_name;
	unsigned type_id;
} mtk_type_t;

typedef struct mtk_type_table_t {
	mtk_type_t **entries;
	unsigned count;
	unsigned size;
	unsigned next_id;
} mtk_type_table_t;



mtk_type_t *mtk_type_create(char *type_name, unsigned type_id);


mtk_type_table_t *mtk_type_table_create();
void mtk_type_table_insert(mtk_type_table_t *table, char *type_name);

#endif