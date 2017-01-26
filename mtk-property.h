#ifndef MTK_PROPERTY_H
#define MTK_PROPERTY_H

typedef enum mtk_property_type_t {
	MTK_PROPERTY_TYPE_STRING,
	MTK_PROPERTY_TYPE_INTEGER,
	MTK_PROPERTY_TYPE_FLOAT,
	MTK_PROPERTY_TYPE_BOOLEAN	
} mtk_property_type_t;


typedef struct mtk_property_t {
	char *name;
	void *value;
	int size;
	mtk_property_type_t type;
} mtk_property_t;

#endif