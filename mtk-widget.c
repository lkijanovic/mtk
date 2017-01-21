#include "mtk-widget.h"


/*
 * Widget property.
 */
typedef struct mtk_widget_property_t {

} mtk_widget_property_t;

/*
 * Widget event.
 */
typedef struct mtk_widget_event_t {

} mtk_widget_event_t;


/*
 * Basic widget structure.
 */
typedef struct mtk_widget_t {
	int id;
	int class_id;
	mtk_widget_property_t *properties;
	mtk_widget_event_t *events;
	struct mtk_widget_t *parent;
	struct mtk_widget_t **children;
	int children_count;
	int children_size;
} mtk_widget_t;
