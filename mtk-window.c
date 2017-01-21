#include "mtk-main.h"
#include "mtk-window.h"

#include <stdlib.h>
#include <xcb/xcb.h>

extern mtk_data *data;

mtk_window *mtk_window_create()
{

	mtk_window *mtk_win;

	xcb_connection_t *conn;
	xcb_screen_t *screen;
	xcb_screen_iterator_t screen_iter;
	xcb_window_t win;
	unsigned win_mask;
	unsigned win_values[1];

	/* allocate memory for the new window */
	mtk_win = malloc(sizeof(mtk_window));
	if(mtk_win == NULL)
		return NULL;

	/* get screen for window */
	conn = data->xcb_conn;
	screen = xcb_setup_roots_iterator(xcb_get_setup(conn)).data;

	/* create default window, 200x200 pixels with black background */
	win = xcb_generate_id(conn);
	win_mask = XCB_CW_BACK_PIXEL;
	win_values[0] = screen->black_pixel;
	xcb_create_window(	conn,
				XCB_COPY_FROM_PARENT,
				win,
				screen->root,
				100, 100, 200, 200, 1,
				XCB_COPY_FROM_PARENT,
				screen->root_visual,
				win_mask,
				win_values);

	mtk_win->xcb_win = win;

}


void mtk_window_draw(mtk_window *mtk_win)
{

	xcb_map_window(data->xcb_conn, mtk_win->xcb_win);
	xcb_flush(data->xcb_conn);
}
