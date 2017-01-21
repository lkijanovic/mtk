#include <stdlib.h>

#include "mtk-main.h"


// contains all MTK internal data
mtk_data_t *data = NULL;

int mtk_init()
{

	xcb_connection_t *conn = NULL;

	/* don't initialize twice */
	if(data != NULL)
		goto outA;

	/* open connection to X server */
	conn = xcb_connect(NULL, NULL);
	if(xcb_connection_has_error(conn))
		goto outA;

	/* allocate mtk_data */
	data = malloc(sizeof(mtk_data_t));
	if(data == NULL)
		goto outB;
		
	data->xcb_conn = conn;

	/* populate type table with basic types */
	data->table = mtk_type_list_create();
	
	if(data->table == NULL)
		goto outC;
	if(mtk_type_list_insert(data->table, "mtk_blank") == 0)
		goto outD;
	if(mtk_type_list_insert(data->table, "mtk_window") == 0)
		goto outD;

	/* return 1 on success */
	return 1;


outD:
	mtk_type_list_destroy(data->table);
outC:
	free(data);
	data = NULL;
outB:
	xcb_disconnect(conn);
outA:
	return 0;
}

void mtk_exit()
{

	/* disconnect from X server and free allocated data */
	xcb_disconnect(data->xcb_conn);
	mtk_type_list_destroy(data->table);
	free(data);
	data = NULL;
}
