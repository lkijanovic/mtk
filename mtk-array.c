#include "mtk-array.h"
#include "mtk-array.h"

#include <stdlib.h>
#include <string.h>


int mtk_array_grow(mtk_array_t *array);

mtk_array_t *mtk_array_create(unsigned elem_size)
{

	return mtk_array_create_ext(elem_size, 100, 1.5, NULL, NULL);

}

mtk_array_t *mtk_array_create_ext(unsigned elem_size, unsigned alloc_size, 
	double alloc_coeff, void *(*copy)(const void *), 
	void (*destroy)(void *))
{

	mtk_array_t *res = NULL;
	void **res_data = NULL;

	res = malloc(sizeof(mtk_array_t));
	if(res == NULL)
		goto out;

	res_data = calloc(alloc_size, sizeof(void *));
	if(res_data == NULL)
		goto out;


	res->data = res_data;
	res->elem_size = elem_size;
	res->alloc_size = alloc_size;
	res->alloc_coeff = alloc_coeff;
	res->size = 0;
	res->copy = copy;
	res->destroy = destroy;

	return res;


out:
	free(res);
	return NULL;
}

void mtk_array_destroy(mtk_array_t *array)
{

	if(array == NULL)
		return;

	if(array->destroy != NULL) {
		for(int i = 0; i < array->size; i++) {
			array->destroy(mtk_array_fetch(array, i));
		}
	}

	free(array->data);
	free(array);

}

mtk_array_t *mtk_array_copy(mtk_array_t *array)
{

	mtk_array_t *res = NULL;
	void *elem;

	if(array == NULL)
		goto out;

	res = mtk_array_create_ext(array->elem_size, array->alloc_size, 
		array->alloc_coeff, array->copy, array->destroy);
	if(res == NULL)
		goto out;

	for(int i = 0; i < array->size; i++) {
		elem = mtk_array_fetch(array, i);
		if(!mtk_array_insert(res, elem))
			goto out;
	}

	return res;

out:
	mtk_array_destroy(res);
	return NULL;

}

void *mtk_array_fetch(mtk_array_t *array, unsigned index)
{

	return array->data[index];

}

int mtk_array_insert(mtk_array_t *array, const void *data)
{

	void *elem;

	if(array->size >= array->alloc_size) {
		if(!mtk_array_grow(array))
			return 0;
	}

	if(array->copy != NULL) {
		elem = array->copy(data);
		if(elem == NULL)
			return 0;
	} else {
		elem = malloc(array->elem_size);
		if(elem == NULL)
			return 0;
		memcpy(elem, data, array->elem_size);
	}

	array->data[array->size] = elem;
	array->size += 1;

	return 1;

}

const void *mtk_array_search(mtk_array_t *array, const void *data,
	int (*compare)(const void *, const void *))
{

	int t;
	void *elem;

	for(int i = 0; i < array->size; i++) {

		elem = mtk_array_fetch(array, i);

		if(compare != NULL)
			t = compare(elem, data);
		else
			t = memcmp(elem, data, array->elem_size);

		if(t == 0)
			return elem;
	}

	return NULL;

}

int mtk_array_grow(mtk_array_t *array)
{

	unsigned n_alloc_size;
	void **n_data;

	n_alloc_size = (unsigned)(array->alloc_size * array->alloc_coeff);
	if(n_alloc_size == array->alloc_size)
		n_alloc_size = n_alloc_size + 1;

	n_data = realloc(array->data, n_alloc_size * sizeof(void *));
	if(n_data == NULL)
		return 0;

	array->data = n_data;
	array->alloc_size = n_alloc_size;

	return 1;

}