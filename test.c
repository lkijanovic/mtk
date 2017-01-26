#include <stdlib.h>
#include <stdio.h>
#include <xcb/xcb.h>

#include "mtk-main.h"
#include "mtk-type.h"
#include "mtk-window.h"

extern mtk_data_t *data;

int main(int argc, char **argv)
{


	/* initialize mtk library */
	if(mtk_init() == 0)
		exit(1);

	/*mtk_window *win = mtk_window_create();
	if(win == NULL)
		exit(1);

	mtk_window_draw(win);*/

	mtk_list_elem_t *elem;
	for(elem = data->list->first; elem != NULL; elem = elem->next) {
		mtk_type_t *type = (mtk_type_t *)elem->data;
		printf("%s:%i\n", type->name, type->id);
	}

	mtk_exit();

}
