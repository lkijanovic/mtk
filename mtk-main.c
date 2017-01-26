#include <stdlib.h>

#include "mtk-main.h"
#include "mtk-type.h"

int mtk_init_list();
int mtk_type_register(const char *name);

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

	/* populate type list with basic types */
	if(mtk_init_list() == 0)
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
	mtk_list_destroy(data->list);
	free(data);
	data = NULL;
	
}

int mtk_init_list()
{
	
	data->list = mtk_list_create_ext(sizeof(mtk_type_t), mtk_type_copy,
		mtk_type_destroy);
	if(data->list == NULL)
		goto outA;
	
	if(mtk_type_register("mtk_blank") == 0)
		goto outB;
	if(mtk_type_register("mtk_window") == 0)
		goto outB;
		
	return 1;


outB:
	mtk_list_destroy(data->list);
	data->list = NULL;
outA:
	return 0;
	
}

int mtk_type_register(const char *name)
{
	mtk_type_t *type;
	
	type = mtk_type_create(name);
	if(type == NULL)
		goto outA;
	if(mtk_list_insert(data->list, type) == 0)
		goto outB;
	mtk_type_destroy(type);
	
	return 1;
	
	
outB:
	mtk_type_destroy(type);
outA:
	return 0;
	
}
