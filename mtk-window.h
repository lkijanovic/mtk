#ifndef MTK_WINDOW_H
#define MTK_WINDOW_H

#include <xcb/xcb.h>

typedef struct mtk_window {
	char *name;
	int x,y;
	int width,height;
	xcb_window_t xcb_win;
} mtk_window;

mtk_window *mtk_create_window();
void mtk_draw_window(mtk_window *mtk_win);

#endif