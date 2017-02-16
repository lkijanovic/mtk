#include "mtk-draw.h"
#include "mtk-property.h"

#include <stdlib.h>

cairo_surface_t *mtk_draw_widget(mtk_widget_t *widget)
{

	cairo_t *cr;
	cairo_surface_t *res;
	const mtk_property_t *prop;
	unsigned width, height;

	prop = mtk_widget_get_property(widget, "width");
	if(prop == NULL)
		return NULL;
	width = (unsigned)atoi(prop->value);

	prop = mtk_widget_get_property(widget, "height");
	if(prop == NULL)
		return NULL;
	height = (unsigned)atoi(prop->value);


	res = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, height, width);

	return res;

}