#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <xcb/xcb.h>

#include "mtk-main.h"
#include "mtk-type.h"
#include "mtk-window.h"

#include "mtk-array.h"
#include "mtk-hashtab.h"

extern mtk_data_t *data;


int main(int argc, char **argv)
{


	/* initialize mtk library */
	if(!mtk_init())
		exit(1);

	/*mtk_window *win = mtk_window_create();
	if(win == NULL)
		exit(1);

	mtk_window_draw(win);*/




	mtk_exit();

}
