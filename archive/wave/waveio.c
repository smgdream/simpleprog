#include <stdio.h>
#include <stdlib.h>
#include "wave.h"
#include "chunkio.h"

int read_audio_data(Wave *wav, FILE *stream);
int write_audio_data(const Wave *wav, FILE *stream);

Wave *wav_read(const char *filename)
{
	Chunk_hdr ckhdr_tmp;
	Wave *wav = NULL;
	FILE *wav_fp = NULL;
	char rbin[4096];

	wav_fp = fopen(filename, "rb");
	if (wav_fp == NULL)
		return 0;
	/* creating and initlizing */
	wav = malloc(sizeof(*wav));
	wav->riffck.header.size = 0;
	wav->fmtck.header.size = 0;
	wav->factck.header.size = 0;
	wav->bextck.header.size = 0;
	wav->junkck.header.size = 0;
	wav->datack.header.size = 0;
	/* reading chunks */
	while (read_ckhdr(&ckhdr_tmp, wav_fp)) {
		switch (ckhdr_tmp.id) {
		case FOURCC_RIFF:
			read_riffck(&wav->riffck, &ckhdr_tmp, wav_fp);
			break;
		case FOURCC_FMT:
			read_fmtck(&wav->fmtck, &ckhdr_tmp, wav_fp);
			break;
		case FOURCC_FACT:
			read_factck(&wav->factck, &ckhdr_tmp, wav_fp);
			break;
		case FOURCC_BEXT:
			read_bextck(&wav->bextck, &ckhdr_tmp, wav_fp);
			break;
		/*
		case FOURCC_JUNK:
			read_junkck(&wav->junkck, &ckhdr_tmp, wav_fp);
			break;
		*/
		case FOURCC_DATA:
			wav->datack.header = ckhdr_tmp;
			read_audio_data(wav, wav_fp);
			fclose(wav_fp);
			return wav;
			break;
		default:
			fprintf(stderr, "Unknow type of chunk: %.4s\n", (char *)&ckhdr_tmp.id);
			fread(rbin, ckhdr_tmp.size, 1, wav_fp);
			break;
		}
	}
	fclose(wav_fp);
	return NULL;
}

int wav_write(const Wave *wav, const char *filename)
{
	FILE *wav_fp = NULL;

	wav_fp = fopen(filename, "wb");
	if (wav_fp == NULL)
		return 0;
	
	write_riffck(&wav->riffck, wav_fp);
	write_fmtck(&wav->fmtck, wav_fp);
	if (wav->bextck.header.size != 0)
		write_bextck(&wav->bextck, wav_fp);
	fwrite(&wav->datack.header, sizeof(wav->datack.header), 1, wav_fp);
	write_audio_data(wav, wav_fp);
	fclose(wav_fp);

	return 1;
}

int read_audio_data(Wave *wav, FILE *stream)
{
	wav->data = malloc(wav->datack.header.size);
	return fread(wav->data, wav->datack.header.size, 1, stream) == 1;
}

int write_audio_data(const Wave *wav, FILE *stream)
{
	return fwrite(wav->data, wav->datack.header.size, 1, stream) == 1;
}