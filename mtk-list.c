#include <stdlib.h>

#include "mtk-list.h"

mtk_list_elem_t *mtk_list_elem_create(mtk_list_t *list, const void *data)
{

	mtk_list_elem_t *res;
	
	res = malloc(sizeof(mtk_list_elem_t));
	if(res == NULL)
		goto outA;
	
	res->data = malloc(list->data_size);
	if(res->data == NULL)
		goto outB;

	if(list->copy == NULL)
		memcpy(res->data, data, data_size);
	else
		list->copy(res->data, data, data_size);
	
	res->next = NULL;
	return res;

	
outB:
	free(res);
outA:
	return NULL;

}

void mtk_list_elem_destroy(mtk_list_t *list, void *data)
{

	if(list->destroy == NULL)
		free(data);
	else
		list->destroy(data);

}

mtk_list_t *mtk_list_create(unsigned data_size)
{

	mtk_list_create_ext(data_size, NULL, NULL);

}

mtk_list_t *mtk_list_create_ext(unsigned data_size,
	void *(*copy)(void *, const void *, unsigned),
	void (*destroy)(void *))
{
	
	mtk_list_t *res;

	res = malloc(sizeof(mtk_list_t));
	if(res == NULL)
		return NULL;

	res->data_size = data_size;
	res->copy = copy;
	res->destroy = destroy;
	res->first = res->last = NULL;

	return res;
	
}

void mtk_list_destroy(mtk_list_t *list)
{
	
}
