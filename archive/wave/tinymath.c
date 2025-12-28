#include <stdbool.h>
#include "tmath.h"


void i24toi32(void *num24, void *num32)
{
	int32_t tmp = 0;

	*(int32_t *)num32 = 0;
	*(uint8_t *)(num32 + 0) = *(uint8_t *)(num24 + 0);
	*(uint8_t *)(num32 + 1) = *(uint8_t *)(num24 + 1);
	*(uint8_t *)(num32 + 2) = *(uint8_t *)(num24 + 2);

	tmp = *(int32_t *)num32;
	/* tmp & 0x800000: tmp is 24bit negative number? */
	if (tmp & 0x800000)
		tmp |= 0xFF000000;
	*(int32_t *)num32 = tmp;
	return;
}

void i32toi24(void *num32, void *num24, bool cliping_flag)
{
	int32_t tmp = *(int32_t *)num32;

	if (cliping_flag) {
		if (tmp >= 0)
			tmp = (tmp > 0x7FFFFF) ? (0x7FFFFF) : tmp;
		else
			tmp = (tmp < (-0x800000)) ? (0x800000) : tmp & (0xFFFFFF);
	}
	else
		tmp = (tmp >= 0) ? (tmp & 0x007FFFFF) : ( (~((~tmp + 1) & 0x7FFFFF) + 1) & 0xFFFFFF );

	*(uint8_t *)(num24 + 0) = *((uint8_t *)&tmp + 0);
	*(uint8_t *)(num24 + 1) = *((uint8_t *)&tmp + 1);
	*(uint8_t *)(num24 + 2) = *((uint8_t *)&tmp + 2);
	return;
}


/*
  y = x / x_max * y_max
    = x * y_max / x_max 
 */
/* sign number mapper function */
int64_t mappers(int64_t src, int64_t dest, int64_t num)
{
	return dest * num / src;
}

uint64_t mapperu(uint64_t src, uint64_t dest, uint64_t num)
{
	return dest * num / src;
}

double mapper(double src, double dest, double num)
{
	return dest * num / src;
}