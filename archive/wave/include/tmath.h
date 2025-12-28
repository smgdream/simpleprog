#ifndef TMATH_H
#define TMATH_H

#include <stdint.h>
#include <stdbool.h>
#include "tmath/coor.h"

static inline bool approx_eq(double src_num, double dest_num, double err)
{
	return  dest_num - err <= src_num && src_num <= dest_num + err;
}
void i24toi32(void *num24, void *num32);
void i32toi24(void *num32, void *num24, bool cliping_flag);

double mapper(double supremum_src, double supremum_dest, double num);
int64_t mappers(int64_t supremum_src, int64_t supremum_dest, int64_t num);
uint64_t mapperu(uint64_t supremum_src, uint64_t supremum_dest, uint64_t num);

#endif