#include <stdlib.h>

#include "mtk-main.h"


// contains all MTK internal data  
mtk_data *data = NULL;

int mtk_init() {

	xcb_connection_t *conn;

	/* don't initialize twice */
	if(data != NULL)
		return 0;

	/* open connection to X server */	
	conn = xcb_connect(NULL, NULL);
	if(xcb_connection_has_error(conn))
		return 0;

	/* allocate mtk_data */
	data = malloc(sizeof(mtk_data));
	if(data == NULL) {
		xcb_disconnect(conn);
		return 0;
	}

	/* return 1 on success */
	data->xcb_conn = conn;
	return 1;	
	
}

void mtk_exit() {
	
	/* disconnect from X server and free allocated data */
	xcb_disconnect(data->xcb_conn);
	free(data);
	data = NULL;
}