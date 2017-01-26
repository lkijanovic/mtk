#include <stdlib.h>

#include "mtk-main.h"
#include "mtk-type.h"

int mtk_init_table();

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
	if(mtk_init_table() == 0)
		goto outC;

	/* return 1 on success */
	return 1;


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

	if(data == NULL)
		return;

	/* disconnect from X server and free allocated data */
	xcb_disconnect(data->xcb_conn);
	mtk_list_destroy(data->table);
	free(data);
	data = NULL;
	
}

int mtk_init_table()
{
	
	mtk_type_t *type;
	
	data->table = mtk_list_create_ext(sizeof(mtk_type_t), mtk_type_copy,
		mtk_type_destroy);
	if(data->table == NULL)
		goto outA;
	
	type = mtk_type_create("mtk_blank", 0);
	if(type == NULL)
		goto outB;
	if(mtk_list_insert(data->table, type) == 0)
		goto outC;
	mtk_type_destroy(type);
	
	type = mtk_type_create("mtk_window", 1);
	if(type == NULL)
		goto outB;
	if(mtk_list_insert(data->table, type) == 0)
		goto outC;
	mtk_type_destroy(type);
		
	return 1;
	

outC:
	mtk_type_destroy(type);
outB:
	mtk_list_destroy(data->table);
	data->table = NULL;
outA:
	return 0;
	
}
