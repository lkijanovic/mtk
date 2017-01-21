#ifndef MTK_MAIN_H
#define MTK_MAIN_H

#include <xcb/xcb.h>

#include "mtk-type.h"

// contains all MTK internal data
typedef struct mtk_data_t {
	xcb_connection_t *xcb_conn;
	mtk_typetable_t *table;
} mtk_data_t;



int mtk_init();
void mtk_exit();


#endif
