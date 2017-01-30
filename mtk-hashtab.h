#ifndef MTK_HASHTAB_H
#define MTK_HASHTAB_H

#include "mtk-array.h"

typedef struct mtk_hashtab_t {
	void **buckets;
	unsigned size;
	unsigned elem_size;
	unsigned (*hash)(const char *, unsigned);
	void *(*copy)(void *, const void *);
	void (*destroy)(void *);
} mtk_hashtab_t;

mtk_hashtab_t *mtk_hashtab_create(unsigned elem_size);
mtk_hashtab_t *mtk_hashtab_create_ext(unsigned elem_size, unsigned size
	unsigned (*hash)(const char *, unsigned), 
	void *(*copy)(void *, const void *), void (*destroy)(void *));

#endif