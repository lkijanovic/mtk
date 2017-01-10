#include "mtk-main.h"
#include "mtk-window.h"

#include <stdlib.h>
#include <xcb/xcb.h>

extern mtk_data *data;

mtk_window *mtk_create_window() {
	
	mtk_window *win;
	xcb_window_t xcb_win;
	xcb_connection_t *xcb_conn;
	xcb_screen_t *xcb_screen;

	/* allocate memory for the new window */
	win = malloc(sizeof(mtk_window));
	if(win == NULL)
		return NULL;

	/* find screen to place window */
	xcb_conn = data->xcb_conn;
	xcb_screen = xcb_setup_roots_iterator(xcb_get_setup(xcb_conn)).data;

	/* create window */
	xcb_win = xcb_generate_id(xcb_conn);
	xcb_create_window(	xcb_conn,
				XCB_COPY_FROM_PARENT,
				xcb_win,
				xcb_screen->root,
				10, 10, 200, 200, 1,
				XCB_COPY_FROM_PARENT,
				xcb_screen->root_visual,
				0, NULL);

	win->xcb_win = xcb_win;
	
}

void mtk_draw_window(mtk_window *win) {
	
	xcb_map_window(data->xcb_conn, win->xcb_win);
	xcb_flush(data->xcb_conn);
}
