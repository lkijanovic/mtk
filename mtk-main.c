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
		goto outA;

	/* populate type table with basic types */
	data->table = mtk_typetable_create();
	if(data->table == NULL)
		goto outA;
	if(mtk_typetable_insert(data->table, "mtk_blank"))
		goto outB;
	if(mtk_typetable_insert(data->table, "mtk_window"))
		goto outB;

	/* return 1 on success */
	data->xcb_conn = conn;
	return 1;


outB:
	mtk_typetable_destroy(data->table);
outA:
	free(data);
	data = NULL;
	xcb_disconnect(conn);
	return 0;
}

void mtk_exit()
{

	/* disconnect from X server and free allocated data */
	xcb_disconnect(data->xcb_conn);
	mtk_typetable_destroy(data->table);
	free(data);
	data = NULL;
}
