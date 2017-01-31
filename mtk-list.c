#include <stdlib.h>
#include <string.h>

#include "mtk-list.h"

mtk_list_node_t *mtk_list_node_create(const mtk_list_t *list, const void *data)
{

	mtk_list_node_t *res = NULL;

	res = malloc(sizeof(mtk_list_node_t));
	if(res == NULL)
		goto out;

	res->data = malloc(list->elem_size);
	if(res->data == NULL)
		goto out;

	if(list->copy != NULL)
		list->copy(res->data, data);
	else
		memcpy(res->data, data, list->elem_size);

	res->next = NULL;
	return res;


out:
	free(res);
	return NULL;

}

void mtk_list_node_destroy(const mtk_list_t *list, mtk_list_node_t *node)
{

	if(node == NULL)
		return;

	if(list->destroy != NULL)
		list->destroy(node->data);
	else
		free(node->data);

	free(node);
}


mtk_list_t *mtk_list_create(unsigned elem_size)
{

	return mtk_list_create_ext(elem_size, NULL, NULL);

}

mtk_list_t *mtk_list_create_ext(unsigned elem_size,
	void *(*copy)(void *, const void *),
	void (*destroy)(void *))
{

	mtk_list_t *res;

	res = malloc(sizeof(mtk_list_t));
	if(res == NULL)
		return NULL;

	res->elem_size = elem_size;
	res->size = 0;
	res->copy = copy;
	res->destroy = destroy;
	res->first = res->last = NULL;

	return res;

}

void mtk_list_destroy(mtk_list_t *list)
{

	mtk_list_node_t *node, *t;

	if(list == NULL)
		return;

	node = list->first;
	while(node != NULL) {
		t = node;
		node = node->next;
		mtk_list_node_destroy(list, t);
	}

	free(list);

}

const void *mtk_list_fetch(mtk_list_t *list, unsigned index)
{

	mtk_list_node_t *node;

	node = list->first;
	for(int i = 0; i < index; i++) {
		node = node->next;
	}

	return node->data;

}

int mtk_list_insert(mtk_list_t *list, const void *data)
{

	mtk_list_node_t *node;

	node = mtk_list_node_create(list, data);
	if(node == NULL)
		return 0;

	if(list->first == NULL)
		list->first = list->last = node;
	else
		list->last = list->last->next = node;

	list->size += 1;

	return 1;


}


const void *mtk_list_search(mtk_list_t *list, const void *data,
	int (*compare)(const void *, const void *))
{

	mtk_list_node_t *node;
	int t;

	node = list->first;
	while(node != NULL) {
		if(compare != NULL)
			t = compare(node->data, data);
		else
			t = memcmp(node->data, data, list->elem_size);

		if(t == 0)
			return node->data;

		node = node->next;
	}

	return NULL;

}

mtk_list_t *mtk_list_copy(const mtk_list_t *list)
{

	mtk_list_t *res = NULL;
	mtk_list_node_t *node;

	if(list == NULL)
		goto out;

	res = mtk_list_create_ext(list->elem_size, list->copy, list->destroy);
	if(res == NULL)
		goto out;

	for(node = list->first; node != NULL; node = node->next) {
		if(!mtk_list_insert(res, node->data))
			goto out;
	}

	return res;


out:
	mtk_list_destroy(res);
	return NULL;
}
