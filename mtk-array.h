#ifndef MTK_ARRAY_H
#define MTK_ARRAY_H

typedef struct mtk_array_t {
	void **data;
	unsigned data_size;
	unsigned data_count;
	unsigned data_alloc;
	
} mtk_array_t;

#endif