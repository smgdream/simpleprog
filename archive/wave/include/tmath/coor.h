#ifndef COOR_H
#define COOR_H

#define pos(x, y, wid) ((x) + (y)*(wid))
#define pos_polar(r, t, ox, oy, x_wid) ( pos( (size_t)(r*cos(t))+ox, (size_t)(r*sin(t))+oy, x_wid) )

#define for_each_pt(img ,x_name, y_name) \
	for (uint32_t y_name = 0; y < img->height; ++y) \
		for (uint32_t x_name = 0; x < img->width; ++x)

#endif