#ifndef CHUNK_DEF_H
#define CHUNK_DEF_H

#include <stdint.h>
/* 
 * As the defined of RIFF some chunk is nest. But I want to make simple.
 * So I seem the file as the combine of segment.
 */
/*
	+----------------------+
	|      RIFF chunk      |
	+----------------------+
	|    Format chunk      |
	+----------------------+
	|      Fact chunk opt  |
	+----------------------+
	|      Bext chunk opt  |
	+----------------------+
	|      Junk chunk opt  |
	+----------------------+
	|  Wav data chunk      |
	+----------------------+
*/

#define PCM_SIGN 0x1
enum chunk_id { FOURCC_RIFF = 0x46464952, FOURCC_FMT = 0x20746D66, FOURCC_FACT = 0x74636166,
	FOURCC_BEXT = 0x74786562, FOURCC_JUNK = 0x6B6E756A, FOURCC_DATA = 0x61746164 };

typedef uint8_t Byte;

struct chunk_hdr {
	uint32_t id;
	uint32_t size;
};
typedef struct chunk_hdr Chunk_hdr;

struct wav_riff_chunk_tag {// RIFF
	Chunk_hdr header;
	struct {
		uint32_t type;
	} data;
};
typedef struct wav_riff_chunk_tag Wav_riffck;

struct wav_fmt_chunk_tag {
	Chunk_hdr header;
	struct {
		uint16_t audio_fmt;		// Format of audio(PCM, ADPCM)
		uint16_t channels;		// Sound channels
		uint32_t samplerate;	// Sample Rate
		uint32_t byterate;		// Byte rate (byte per sec)
		uint16_t block_align;	// size of a sample 
		uint16_t bit_depth;		// Bit depth of audio
	} data;
};
typedef struct wav_fmt_chunk_tag Wav_fmtck;

struct wav_fact_chunk_tag {
	Chunk_hdr header;
	struct {
		uint32_t sample_len;
	} data;
};
typedef struct wav_fact_chunk_tag Wav_factck;

struct wav_bext_chunk_tag {
	Chunk_hdr header;
	struct {
		char desc[256]; // Description
		char originator[32];
		char originator_ref[32];
		char origination_date[10];
		char origination_time[8];
		uint64_t time_ref;
		uint16_t align; // use as align the memory adderss(set 1)
		char umid[64];
		int16_t loudness_val;
		int16_t loudness_range;
		int16_t max_true_peak;
		int16_t max_momentary_loudness;
		int16_t max_short_term_loudness;
		char reserved[180];
	} data;
};
typedef struct wav_bext_chunk_tag Wav_bextck;


struct wav_junk_chunk_tag {
	Chunk_hdr header;
	void *data;
};
typedef struct wav_junk_chunk_tag Wav_junkck;

struct wav_data_chunk_tag {
	Chunk_hdr header;
};
typedef struct wav_data_chunk_tag Wav_datack;

#endif