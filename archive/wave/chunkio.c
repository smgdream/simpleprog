#include <stdio.h>
#include <stdbool.h>
#include "chunk_def.h"
#include "chunkio.h"


/* Read chunks */

bool read_ckhdr(Chunk_hdr *ckhdr, FILE *stream)
{
	return fread(ckhdr, sizeof(*ckhdr), 1, stream) == 1;
}

bool read_riffck(Wav_riffck *chunk, const Chunk_hdr *ckhdr, FILE *stream)
{
	chunk->header = *ckhdr;
	return fread(&chunk->data, sizeof(chunk->data), 1, stream) == 1;
}

bool read_fmtck(Wav_fmtck *chunk, const Chunk_hdr *ckhdr, FILE *stream)
{
	chunk->header = *ckhdr;
	return fread(&chunk->data, sizeof(chunk->data), 1, stream) == 1;
}

bool read_factck(Wav_factck *chunk, const Chunk_hdr *ckhdr, FILE *stream)
{
	chunk->header = *ckhdr;
	return fread(&chunk->data, sizeof(chunk->data), 1, stream) == 1;
}

bool read_junkck(Wav_junkck *chunk, const Chunk_hdr *ckhdr, FILE *stream)
{
	chunk->header = *ckhdr;
	return fread(&chunk->data, sizeof(chunk->data), 1, stream) == 1;
}

bool read_bextck(Wav_bextck *chunk, const Chunk_hdr *ckhdr, FILE *stream)
{
	chunk->header = *ckhdr;
	if ( fread(&chunk->data.desc					, sizeof(chunk->data.desc)						, 1, stream) != 1
	  || fread(&chunk->data.originator				, sizeof(chunk->data.originator)				, 1, stream) != 1
	  || fread(&chunk->data.originator_ref			, sizeof(chunk->data.originator_ref)			, 1, stream) != 1
	  || fread(&chunk->data.origination_date		, sizeof(chunk->data.origination_date)			, 1, stream) != 1
	  || fread(&chunk->data.origination_time		, sizeof(chunk->data.origination_time)			, 1, stream) != 1
	  || fread(&chunk->data.time_ref				, sizeof(chunk->data.time_ref)					, 1, stream) != 1
	  || fread(&chunk->data.align					, sizeof(chunk->data.align)						, 1, stream) != 1
	  || fread(&chunk->data.umid					, sizeof(chunk->data.umid)						, 1, stream) != 1
	  || fread(&chunk->data.loudness_val			, sizeof(chunk->data.loudness_val)				, 1, stream) != 1
	  || fread(&chunk->data.loudness_range			, sizeof(chunk->data.loudness_range)			, 1, stream) != 1
	  || fread(&chunk->data.max_true_peak			, sizeof(chunk->data.max_true_peak)				, 1, stream) != 1
	  || fread(&chunk->data.max_momentary_loudness	, sizeof(chunk->data.max_momentary_loudness)	, 1, stream) != 1
	  || fread(&chunk->data.max_short_term_loudness	, sizeof(chunk->data.max_short_term_loudness)	, 1, stream) != 1
	  || fread(&chunk->data.reserved				, sizeof(chunk->data.reserved)					, 1, stream) != 1
	) return 0;
	else
		return 1;
}



/* Write chunks */

bool write_riffck(const Wav_riffck *chunk, FILE *stream)
{
	return fwrite(chunk, sizeof(*chunk), 1, stream) == 1;
}

bool write_fmtck(const Wav_fmtck *chunk, FILE *stream)
{
	return fwrite(chunk, sizeof(*chunk), 1, stream) == 1;
}

bool write_factck(const Wav_factck *chunk, FILE *stream)
{
	return fwrite(chunk, sizeof(*chunk), 1, stream) == 1;
}

bool write_junkck(const Wav_junkck *chunk, FILE *stream)
{
	return fwrite(chunk, sizeof(*chunk), 1, stream) == 1;
}

bool write_bextck(const Wav_bextck *chunk, FILE *stream)
{
	if ( fwrite(&chunk->header						, sizeof(chunk->header)							, 1, stream) != 1
	  || fwrite(&chunk->data.desc					, sizeof(chunk->data.desc)						, 1, stream) != 1
	  || fwrite(&chunk->data.originator				, sizeof(chunk->data.originator)				, 1, stream) != 1
	  || fwrite(&chunk->data.originator_ref			, sizeof(chunk->data.originator_ref)			, 1, stream) != 1
	  || fwrite(&chunk->data.origination_date		, sizeof(chunk->data.origination_date)			, 1, stream) != 1
	  || fwrite(&chunk->data.origination_time		, sizeof(chunk->data.origination_time)			, 1, stream) != 1
	  || fwrite(&chunk->data.time_ref				, sizeof(chunk->data.time_ref)					, 1, stream) != 1
	  || fwrite(&chunk->data.align					, sizeof(chunk->data.align)						, 1, stream) != 1
	  || fwrite(&chunk->data.umid					, sizeof(chunk->data.umid)						, 1, stream) != 1
	  || fwrite(&chunk->data.loudness_val			, sizeof(chunk->data.loudness_val)				, 1, stream) != 1
	  || fwrite(&chunk->data.loudness_range			, sizeof(chunk->data.loudness_range)			, 1, stream) != 1
	  || fwrite(&chunk->data.max_true_peak			, sizeof(chunk->data.max_true_peak)				, 1, stream) != 1
	  || fwrite(&chunk->data.max_momentary_loudness	, sizeof(chunk->data.max_momentary_loudness)	, 1, stream) != 1
	  || fwrite(&chunk->data.max_short_term_loudness, sizeof(chunk->data.max_short_term_loudness)	, 1, stream) != 1
	  || fwrite(&chunk->data.reserved				, sizeof(chunk->data.reserved)					, 1, stream) != 1
	) return 0;
	else
		return 1;
}