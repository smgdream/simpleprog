#ifndef AUXT_DEF_H
#define AUXT_DEF_H

#include <stdint.h>

enum auxt_endian { UNK_END, LITTLE_END, BIG_END };
enum auxt_sample_sig { SS_UNSIGN, SS_SIGN };
enum auxt_aufmt { PCM_FMT = 0x1 };

typedef uint8_t Byte;

struct auxt_fmt_tag {
	uint16_t audio_fmt;
	uint16_t channels;
	uint16_t bit_depth;
	uint8_t byte_order;
	uint8_t sample_sign;
	uint32_t samplerate;
};
typedef struct auxt_fmt_tag Auxt_fmt;

struct auxt_metadata_tag {
	char desc[256]; // Description
	char creator[32];
	char date[10];
	char time[8];
	void *cover;
	char reserved[128];
};
typedef struct auxt_metadata_tag Auxt_metadata;

struct auxt_tag {
	Auxt_fmt fmt;
	Auxt_metadata metadata;
	size_t size;
	Byte *data;
};
typedef struct auxt_tag Auxt;

#endif