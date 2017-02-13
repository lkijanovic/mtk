#include "mtk.h"

xcb_visualtype_t *mtk_xcb_get_visual(xcb_connection_t *conn, 
	xcb_visualid_t visual_id) {

	xcb_screen_iterator_t scr_iter;
	xcb_depth_iterator_t dpt_iter;
	xcb_visualtype_iterator_t vis_iter;

	for (; scr_iter.rem; xcb_screen_next(&scr_iter)) {
		dpt_iter = xcb_screen_allowed_depths_iterator(scr_iter.data);
		for (; dpt_iter.rem; xcb_depth_next(&dpt_iter)) {
			vis_iter = xcb_depth_visuals_iterator(dpt_iter.data);
			for (; vis_iter.rem; xcb_visualtype_next(&vis_iter)) {
				if (visual == vis_iter.data->visual_id)
					return vis_iter.data;
			}
		}
	}

}
