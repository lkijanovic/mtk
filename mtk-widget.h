#ifndef MTK_WIDGET_H
#define MTK_WIDGET_H

typedef enum mtk_property_type_t {
	MTK_PROPERTY_TYPE_STRING,
	MTK_PROPERTY_TYPE_INTEGER,
	MTK_PROPERTY_TYPE_FLOAT,
	MTK_PROPERTY_TYPE_BOOLEAN	
} mtk_property_type_t;


/*
 * Widget property.
 */
typedef struct mtk_property_t {
	char *name;
	void *value;
	int size;
	mtk_property_type_t type;
	struct mtk_property_t *next;
} mtk_property_t;

typedef struct mtk_property_list_t {
	mtk_property_t *first;
	mtk_property_t *last;
} mtk_property_list_t;

/*
 * Widget event.
 */
typedef struct mtk_event_t {
	char *name;
	void (*callback)(void *data);
	struct mtk_event_t *next;
} mtk_event_t;

typedef struct mtk_event_list_t {
	mtk_event_t *first;
	mtk_event_t *last;
} mtk_event_list_t;

/*
 * Basic widget structure.
 */
typedef struct mtk_widget_t {
	int id;
	int class_id;
	mtk_property_list_t *properties;
	mtk_event_list_t *events;
	struct mtk_widget_t *parent;
	struct mtk_widget_t **children;
	int children_count;
	int children_size;
} mtk_widget_t;

#endif