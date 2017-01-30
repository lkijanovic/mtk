#include "mtk-list.h"
#include "mtk-hashtab.h"

mtk_hashtab_t *mtk_hashtab_create(unsigned elem_size)
{

	return mtk_hashtab_create_ext(elem_size, 1000, NULL, NULL, NULL);

}

mtk_hashtab_t *mtk_hashtab_create_ext(unsigned elem_size, unsigned size
	unsigned (*hash)(const char *, unsigned), 
	void *(*copy)(void *, const void *), void (*destroy)(void *))
{

	mtk_hashtab_t *res;
	void **res_buckets;

	res = malloc(sizeof(mtk_hashtab_t));
	if(res == NULL)
		goto out;

	res_buckets = malloc(size * sizeof(mtk_list_t));
	if(res_buckets == NULL)
		goto out;

	/* TODO: finish this function */	


}