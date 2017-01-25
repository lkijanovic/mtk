#ifndef MTK_LIST_H
#define MTK_LIST_H

typedef struct mtk_list_elem_t {
	void *data;
	struct mtk_list_elem_t *next;
}

typedef struct mtk_list_t {
	unsigned data_size;
	void *(*copy)(void *, const void *, unsigned);
	void (*destroy)(void *);
	mtk_list_elem_t *first;
	mtk_list_elem_t *last;
}


mtk_list_elem_t *mtk_list_elem_create(mtk_list_t *list, const void *data);
void mtk_list_elem_destroy(mtk_list_elem_t *elem, void *);

mtk_list_t *mtk_list_create(unsigned data_size);
mtk_list_t *mtk_list_create_ext(unsigned data_size,
	void *(*copy)(void *, const void *, unsigned),
	void (*destroy)(void *));

void mtk_list_destroy(mtk_list_t *list);




#endif
