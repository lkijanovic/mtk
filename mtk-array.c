#include "mtk-array.h"
#include "mtk-array.h"

#include <stdlib.h>
#include <string.h>

mtk_array_t *mtk_array_create(unsigned elem_size)
{

	return mtk_array_create_ext(elem_size, 100, 1.5, NULL, NULL);

}

mtk_array_t *mtk_array_create_ext(unsigned elem_size, unsigned alloc_size, 
	double alloc_coeff, void *(*copy)(void *, const void *), 
	void (*destroy)(void *))
{

	mtk_array_t *res;

	res = malloc(alloc_size * sizeof(elem_size));
	if(res == NULL)
		return NULL;

	res->elem_size = elem_size;
	res->alloc_size = alloc_size;
	res->alloc_coeff = alloc_coeff;
	res->size = 0;
	res->copy = copy;
	res->destroy = destroy;

	return res;

}

void mtk_array_destroy(mtk_array_t *array)
{

	if(array->destroy != NULL)
		for(int i = 0; i < array->size; i++) {
			array->destroy(mtk_array_fetch(array, i));
		}

	free(array->data);
	free(array);

}

void *mtk_array_fetch(mtk_array_t *array, unsigned index)
{

	return array->data + array->elem_size * index;

}

int mtk_array_insert(mtk_array_t *array, const void *data)
{

	void *n_data, *elem;
	int n_alloc_size;

	if(array->size >= array->alloc_size) {
		n_alloc_size = array->alloc_size * array->elem_size;
		n_alloc_size = (int)(n_alloc_size * array->alloc_coeff);

		n_data = realloc(array->data, n_alloc_size);
		if(n_data == NULL)
			return 0;

		array->data = n_data;
		array->alloc_size = n_alloc_size;
	}

	elem = mtk_array_fetch(array, array->size);
	if(array->copy != NULL)
		array->copy(elem, data);
	else
		memcpy(elem, data, array->elem_size);

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

mtk_array_t *mtk_array_copy(mtk_array_t *array)
{

	mtk_array_t *res;
	void *elem;

	res = mtk_array_create_ext(array->elem_size, array->alloc_size, 
		array->alloc_coeff, array->copy, array->destroy);
	if(res == NULL)
		return NULL;

	if(array->copy != NULL) {
		for(int i = 0; i < array->size; i++) {
			elem = mtk_array_fetch(array, i);
			array->copy(res->data + array->elem_size * i, elem);
		}
	} else {
		memcpy(res->data, array->data, array->elem_size * array->size);
	}

	return res;

}