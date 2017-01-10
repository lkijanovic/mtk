#ifndef MTK_MAIN_H
#define MTK_MAIN_H

#include <xcb/xcb.h>


// contains all MTK internal data  
typedef struct mtk_data {
	xcb_connection_t *xcb_conn;
	
} mtk_data;



int mtk_init();
void mtk_exit();


#endif