#ifndef MTK_HASHTAB_H
#define MTK_HASHTAB_H

#include "mtk-array.h"

typedef struct mtk_hashtab_t {
	mtk_array_t *buckets;
	unsigned size;
	unsigned bucket_size;
	unsigned elem_size;
	unsigned (*hash)(const char *, unsigned);
	void *(*copy)(const void *);
	void (*destroy)(void *);
} mtk_hashtab_t;

mtk_hashtab_t *mtk_hashtab_create(unsigned elem_size);
mtk_hashtab_t *mtk_hashtab_create_ext(unsigned elem_size, unsigned bucket_size,
	unsigned (*hash)(const char *, unsigned), void *(*copy)(const void *), 
	void (*destroy)(void *));
void mtk_hashtab_destroy(mtk_hashtab_t *hashtab);
mtk_hashtab_t *mtk_hashtab_copy(mtk_hashtab_t *hashtab);

#endif