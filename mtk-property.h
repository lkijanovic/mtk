#ifndef MTK_PROPERTY_H
#define MTK_PROPERTY_H


typedef struct mtk_property_t {
	char *name;
	char *value;
} mtk_property_t;

mtk_property_t *mtk_property_create(const char *name, const char *value);
void mtk_property_destroy(mtk_property_t *property);
mtk_property_t *mtk_property_copy(mtk_property_t *dest,
	const mtk_property_t *src);
int mtk_property_compare(const mtk_property_t *t1, const mtk_property_t *t2);
#endif