#include <stdlib.h>

#include "mtk-list.h"
#include "mtk-hashtab.h"

unsigned mtk_hashtab_jenkins(const void *data, unsigned data_len);

mtk_hashtab_t *mtk_hashtab_create(unsigned elem_size)
{

	return mtk_hashtab_create_ext(elem_size, 1024, NULL, NULL, NULL);

}

mtk_hashtab_t *mtk_hashtab_create_ext(unsigned elem_size, unsigned bucket_size,
	unsigned (*hash)(const char *, unsigned), void *(*copy)(const void *), 
	void (*destroy)(void *))
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
		bucket = mtk_list_create_ext(elem_size, copy, destroy);
		if(bucket == NULL)
			goto out;
		if(!mtk_array_insert(buckets, bucket))
			goto out;
		mtk_list_destroy(bucket);
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

	if(hashtab == NULL)
		return;

	mtk_array_destroy(hashtab->buckets);
	free(hashtab);

}

mtk_hashtab_t *mtk_hashtab_copy(mtk_hashtab_t *hashtab)
{

	mtk_hashtab_t *res = NULL;
	mtk_list_t *bucket;
	const void *elem;

	res = mtk_hashtab_create_ext(hashtab->elem_size, hashtab->bucket_size,
		hashtab->hash, hashtab->copy, hashtab->destroy);
	if(res == NULL)
		goto out;

	for(int i = 0; i < hashtab->buckets->size; i++) {
		bucket = mtk_array_fetch(hashtab->buckets, i);
		for(int j = 0; j < bucket->size; j++) {
			elem = mtk_list_fetch(bucket, j);
			if(!mtk_hashtab_insert(res, elem))
				goto out;
		}
	}


	return res;

out:
	mtk_hashtab_destroy(res);
	return NULL;
}

int mtk_hashtab_insert(mtk_hashtab_t *hashtab, const void *data)
{

	unsigned hash_value;
	mtk_list_t *bucket;

	if(hashtab->hash != NULL)
		hash_value = hashtab->hash(data, hashtab->elem_size);
	else
		hash_value = mtk_hashtab_jenkins(data, hashtab->elem_size);
	hash_value = hash_value % hashtab->bucket_size;

	bucket = mtk_array_fetch(hashtab->buckets, hash_value);
	if(!mtk_list_insert(bucket, data))
		return 0;

	hashtab->size += 1;

	return 1;

}

unsigned mtk_hashtab_jenkins(const void *data, unsigned data_len)
{

	unsigned hash_value;
	const char *key;

	hash_value = 0;
	key = (const char *)data;

	for(int i = 0; i < data_len; i++) {
		hash_value += key[i];
		hash_value += hash_value << 10;
		hash_value ^= hash_value >> 6;
	}

	hash_value += hash_value << 3;
	hash_value ^= hash_value >> 11;
	hash_value += hash_value << 15;

	return hash_value;

}

const void *mtk_hashtab_search(mtk_hashtab_t *hashtab, const void *data,
	int (*compare)(const void *, const void *))
{

	unsigned hash_value;
	mtk_list_t *bucket;
	const void *res;

	if(hashtab->hash != NULL)
		hash_value = hashtab->hash(data, hashtab->elem_size);
	else
		hash_value = mtk_hashtab_jenkins(data, hashtab->elem_size);
	hash_value = hash_value % hashtab->bucket_size;

	bucket = mtk_array_fetch(hashtab->buckets, hash_value);

	res = mtk_list_search(bucket, data, compare);
	return res;

}