#ifndef MTK_MAIN_H
#define MTK_MAIN_H

#include <xcb/xcb.h>

#include "mtk-array.h"
#include "mtk-hashtab.h"

// contains all MTK internal data
typedef struct mtk_data_t {
	xcb_connection_t *xcb_conn;
	mtk_array_t *types;
	mtk_hashtab_t *properties;
	mtk_hashtab_t *events;
} mtk_data_t;



int mtk_init();
void mtk_exit();


#endif
