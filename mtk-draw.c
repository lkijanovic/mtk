#include "mtk-draw.h"
#include "mtk-property.h"

#include <stdlib.h>

cairo_surface_t *mtk_draw_widget(const mtk_widget_t *widget)
{

	cairo_t *cr;
	cairo_surface_t *res, *t;
	const mtk_property_t *prop;
	unsigned width, height;

	const mtk_widget_t *child;
	unsigned child_x, child_y;

	prop = mtk_widget_get_property(widget, "width");
	if(prop == NULL)
		return NULL;
	width = (unsigned)atoi(prop->value);

	prop = mtk_widget_get_property(widget, "height");
	if(prop == NULL)
		return NULL;
	height = (unsigned)atoi(prop->value);

	res = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, height, width);
	cr = cairo_create(res);


	for(int i = 0; i < mtk_list_size(widget->children); i++) {
		child = mtk_list_fetch(widget->children, i);
		t = mtk_draw_widget(child);

		prop = mtk_widget_get_property(child, "x");
		if(prop == NULL)
			return NULL;
		child_x = (unsigned)atoi(prop->value);

		prop = mtk_widget_get_property(child, "y");
		if(prop == NULL)
			return NULL;
		child_y = (unsigned)atoi(prop->value);

		cairo_set_source_surface(cr, t, child_x, child_y);
		cairo_paint(cr);
	}
	
	cairo_destroy(cr);

	return res;

}
