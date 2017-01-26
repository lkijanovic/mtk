#include <stdlib.h>
#include <string.h>

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

	if(list->copy != NULL)
		list->copy(res->data, data);
	else
		memcpy(res->data, data, list->data_size);
	
	res->next = NULL;
	return res;

	
outB:
	free(res);
outA:
	return NULL;

}

void mtk_list_elem_destroy(mtk_list_t *list, mtk_list_elem_t *elem)
{

	if(elem == NULL)
		return;

	if(list->destroy != NULL)
		list->destroy(elem->data);
	else
		free(elem->data);

	free(elem);
}

mtk_list_t *mtk_list_create(unsigned data_size)
{

	return mtk_list_create_ext(data_size, NULL, NULL);

}

mtk_list_t *mtk_list_create_ext(unsigned data_size,
	void *(*copy)(void *, const void *),
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

	mtk_list_elem_t *elem, *t;
	
	elem = list->first;
	while(elem != NULL) {
		t = elem;
		elem = elem->next;
		mtk_list_elem_destroy(list, t);
	}
	
	free(list);
	
}


int mtk_list_insert(mtk_list_t *list, const void *data)
{

	mtk_list_elem_t *elem;
	
	elem = mtk_list_elem_create(list, data);
	if(elem == NULL)
		goto out;
		
	if(list->first == NULL)
		list->first = list->last = elem;
	else
		list->last = list->last->next = elem;
		
	return 1;
	
	
out:
	return 0;
	
}


const void *mtk_list_search(mtk_list_t *list, const void *data,
	int (*compare)(const void *, const void *))
{
	
	mtk_list_elem_t *elem;
	int t;
	
	elem = list->first;
	while(elem != NULL) {
		if(compare != NULL)
			t = compare(elem->data, data);
		else
			t = memcmp(elem->data, data, list->data_size);
			
		if(t == 0)
			return elem->data;
	}
	
	return NULL;
	
}