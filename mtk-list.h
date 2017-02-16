#ifndef MTK_LIST_H
#define MTK_LIST_H


typedef struct mtk_list_node_t {
	void *data;
	struct mtk_list_node_t *next;
} mtk_list_node_t;

typedef struct mtk_list_t {
	unsigned elem_size;
	unsigned size;
	void *(*copy)(const void *);
	void (*destroy)(void *);
	mtk_list_node_t *first;
	mtk_list_node_t *last;
} mtk_list_t;


mtk_list_node_t *mtk_list_node_create(const mtk_list_t *list, const void *data);
void mtk_list_node_destroy(const mtk_list_t *list, mtk_list_node_t *node);

mtk_list_t *mtk_list_create(unsigned elem_size);
mtk_list_t *mtk_list_create_ext(unsigned elem_size, void *(*copy)(const void *),
	void (*destroy)(void *));
void mtk_list_destroy(mtk_list_t *list);
mtk_list_t *mtk_list_copy(const mtk_list_t *list);
unsigned mtk_list_size(mtk_list_t *list);
const void *mtk_list_fetch(mtk_list_t *list, unsigned index);
int mtk_list_insert(mtk_list_t *list, const void *data);
const void *mtk_list_search(mtk_list_t *list, const void *data,
	int (*compare)(const void *, const void *));

#endif
