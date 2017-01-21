#include <stdlib.h>
#include <xcb/xcb.h>

#include "mtk-main.h"
#include "mtk-window.h"

int main(int argc, char **argv)
{


	/* initialize mtk library */
	if(mtk_init() == 0)
		exit(1);

	mtk_window *win = mtk_window_create();
	if(win == 0)
		exit(1);
	mtk_window_draw(win);

	pause();

	mtk_exit();

}
