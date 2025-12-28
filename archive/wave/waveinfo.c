#include <stdio.h>
#include <stdint.h>
#include "wave.h"

int print_wav_umid(const char *umid);

int print_wav_info(const Wave *wav)
{
	/*
	printf("  %-16s: %.4s\n", "ID", (char *)&wav->ck.header.id);
	printf("  %-16s: %zu\n", "Size", (size_t)wav->ck.header.size);
	printf("  %-16s: %.4s\n", "", (char *)&wav->ck.data.);
	*/
	
	printf("\n");
	printf("  %-16s: %.4s\n"	, "ID"	, (char *)&wav->riffck.header.id);
	printf("  %-16s: %zu\n"		, "Size", (size_t)wav->riffck.header.size);
	printf("  %-16s: %.4s\n"	, "Type", (char *)&wav->riffck.data.type);

	printf("\n");
	printf("  %-16s: %.4s\n", "ID"				, (char *)&wav->fmtck.header.id);
	printf("  %-16s: %zu\n"	, "Size"			, (size_t)wav->fmtck.header.size);
	printf("  %-16s: %zu\n"	, "Audio format"	, (size_t)wav->fmtck.data.audio_fmt);
	printf("  %-16s: %zu\n"	, "Channels"		, (size_t)wav->fmtck.data.channels);
	printf("  %-16s: %zu\n"	, "Sample rate"		, (size_t)wav->fmtck.data.samplerate);
	printf("  %-16s: %zu\n"	, "Bit rate"		, (size_t)wav->fmtck.data.byterate * 8);
	printf("  %-16s: %zu\n"	, "Sample size"		, (size_t)wav->fmtck.data.block_align);
	printf("  %-16s: %zu\n"	, "Bit depth"		, (size_t)wav->fmtck.data.bit_depth);

	printf("\n");
	printf("  %-16s: %.4s\n"	, "ID"				, (char *)&wav->bextck.header.id);
	printf("  %-16s: %zu\n"		, "Size"			, (size_t)wav->bextck.header.size);
	printf("  %-16s: %.63s~\n"	, "Description"		, (char *)wav->bextck.data.desc);
	printf("  %-16s: %.32s\n"	, "Originator"		, (char *)wav->bextck.data.originator);
	printf("  %-16s: %.32s\n"	, "Originator ref"	, (char *)wav->bextck.data.originator_ref);
	printf("  %-16s: %.10s\n"	, "date"			, (char *)wav->bextck.data.origination_date);
	printf("  %-16s: %.8s\n"	, "time"			, (char *)wav->bextck.data.origination_time);
	printf("  %-16s: %zu\n"		, "Time reference"	, (size_t)wav->bextck.data.time_ref);
	printf("  %-16s: %zu\n"		, "Align"			, (size_t)wav->bextck.data.align);
	printf("  %-16s: "			, "umid"			);	print_wav_umid(wav->bextck.data.umid);
	printf("  %-16s: %zu\n"		, "Loudness value"	, (size_t)wav->bextck.data.loudness_val);
	printf("  %-16s: %zu\n"		, "Loudness range"	, (size_t)wav->bextck.data.loudness_range);
	printf("  %-16s: %zu\n"		, "Max true peak"	, (size_t)wav->bextck.data.max_true_peak);
	printf("  %-16s: %zu\n"		, "Max mom loudness", (size_t)wav->bextck.data.max_momentary_loudness);
	printf("  %-16s: %zu\n"		, "Max st loudness"	, (size_t)wav->bextck.data.max_short_term_loudness);

	printf("\n");
	printf("  %-16s: %.4s\n", "ID"	, (char *)&wav->datack.header.id);
	printf("  %-16s: %zu\n"	, "Size", (size_t)wav->datack.header.size);
	

	return 1;
}

int print_wav_umid(const char *umid)
{
	if (umid == NULL)
		return 0;

	printf("0x");
	for (int i = 0; i < 32; ++i)
		printf("%02hhX", *(uint8_t *)umid++);
	printf("\n");

	return 1;
}