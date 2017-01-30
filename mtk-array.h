#ifndef MTK_ARRAY_H
#define MTK_ARRAY_H

typedef struct mtk_array_t {
	void *data;
	unsigned elem_size;
	unsigned size;
	unsigned alloc_size;
	double alloc_coeff;
	void *(*copy)(void *, const void *);
	void (*destroy)(void *);
} mtk_array_t;


mtk_array_t *mtk_array_create(unsigned elem_size);
mtk_array_t *mtk_array_create_ext(unsigned elem_size, unsigned alloc_size, 
	double alloc_coef, void *(*copy)(void *, const void *), 
	void (*destroy)(void *));
void mtk_array_destroy(mtk_array_t *array);
mtk_array_t *mtk_array_copy(mtk_array_t *array);
void *mtk_array_fetch(mtk_array_t *array, unsigned index);
int mtk_array_insert(mtk_array_t *array, const void *data);
const void *mtk_array_search(mtk_array_t *array, const void *data,
	int (*compare)(const void *, const void *));
#endif