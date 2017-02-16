#ifndef MTK_DRAW_H
#define MTK_DRAW_H

#include <cairo/cairo.h>
#include "mtk-widget.h"

cairo_surface_t *mtk_draw_widget(const mtk_widget_t *widget);

#endif