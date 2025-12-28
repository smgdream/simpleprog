/* AUXT: Audio Exchange Type */
#ifndef AUXT_H
#define AUXT_H
#include <stdint.h>
#include <stdbool.h>
#include "auxt_def.h"

Auxt *auxt_new(void);
bool auxt_set_fmt(Auxt *auxt, uint16_t audio_fmt, uint16_t channels, uint16_t bit_depth, 
				 uint32_t samplerate, uint8_t sign, uint8_t byte_order);
bool auxt_set_data(Auxt *auxt, size_t size, int bit_depth);
bool auxt_free(Auxt *auxt);


#endif
