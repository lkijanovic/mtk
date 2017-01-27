#ifndef MTK_LIST_H
#define MTK_LIST_H


typedef struct mtk_list_elem_t {
	void *data;
	struct mtk_list_elem_t *next;
} mtk_list_elem_t;

typedef struct mtk_list_t {
	unsigned data_size;
	void *(*copy)(void *, const void *);
	void (*destroy)(void *);
	mtk_list_elem_t *first;
	mtk_list_elem_t *last;
} mtk_list_t;


mtk_list_elem_t *mtk_list_elem_create(const mtk_list_t *list, const void *data);
void mtk_list_elem_destroy(const mtk_list_t *list, mtk_list_elem_t *elem);

mtk_list_t *mtk_list_create(unsigned data_size);
mtk_list_t *mtk_list_create_ext(unsigned data_size,
	void *(*copy)(void *, const void *),
	void (*destroy)(void *));
void mtk_list_destroy(mtk_list_t *list);
int mtk_list_insert(mtk_list_t *list, const void *data);
const void *mtk_list_search(mtk_list_t *list, const void *data,
	int (*compare)(const void *, const void *));
mtk_list_t *mtk_list_copy(const mtk_list_t *list);

#endif
