#ifndef MTK_MAIN_H
#define MTK_MAIN_H

#include <xcb/xcb.h>

#include "mtk-list.h"

// contains all MTK internal data
typedef struct mtk_data_t {
	xcb_connection_t *xcb_conn;
	mtk_list_t *types;
	mtk_list_t *properties;
	mtk_list_t *events;
} mtk_data_t;



int mtk_init();
void mtk_exit();


#endif
