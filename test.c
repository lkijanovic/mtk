#include <xcb/xcb.h>

#include "mtk-main.h"
#include "mtk-window.h"

int main(int argc, char **argv) {


	/* initialize mtk library */
	mtk_init();
	
	mtk_window *win = mtk_window_create();
	mtk_window_draw(win);
	
	pause();
	
	mtk_exit();

}
