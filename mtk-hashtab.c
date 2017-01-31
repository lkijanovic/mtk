#include <stdlib.h>

#include "mtk-list.h"
#include "mtk-hashtab.h"

mtk_hashtab_t *mtk_hashtab_create(unsigned elem_size)
{

	return mtk_hashtab_create_ext(elem_size, 1000, NULL, NULL, NULL);

}

mtk_hashtab_t *mtk_hashtab_create_ext(unsigned elem_size, unsigned bucket_size,
	unsigned (*hash)(const char *, unsigned), 
	void *(*copy)(void *, const void *), void (*destroy)(void *))
{

	mtk_hashtab_t *res;
	mtk_array_t *buckets;
	mtk_list_t *bucket;

	res = malloc(sizeof(mtk_hashtab_t));
	if(res == NULL)
		goto out;

	buckets = mtk_array_create_ext(sizeof(mtk_list_t), bucket_size, 1.5, 
		mtk_list_copy, mtk_list_destroy);
	if(buckets == NULL)
		goto out;

	for(int i = 0; i < bucket_size; i++) {
		bucket = mtk_list_create(elem_size);
		if(bucket == NULL)
			goto out;
		if(!mtk_array_insert(buckets, bucket))
			goto out;
		bucket = NULL;
	}

	res->buckets = buckets;
	res->bucket_size = bucket_size;
	res->elem_size = elem_size;
	res->size = 0;
	res->hash = hash;
	res->copy = copy;
	res->destroy = destroy;

	return res;


out:
	mtk_list_destroy(bucket);
	mtk_array_destroy(buckets);
	free(res);
	return NULL;

}

void mtk_hashtab_destroy(mtk_hashtab_t *hashtab)
{

	mtk_array_destroy(buckets);
	free(hashtab);

}

mtk_hashtab_t *mtk_hashtab_copy(mtk_hashtab_t *hashtab)
{

	mtk_hashtab_t *res;
	mtk_list_t **bucket;

	res = mtk_hashtab_create_ext(hashtab->elem_size, hashtab->bucket_size,
		hashtab->hash, hashtab->copy, hashtab->destroy);
	if(res == NULL)
		return NULL;

	/* TODO: finish this up */

}