#ifndef CHUNKIO_H
#define CHUNKIO_H

#include <stdio.h>
#include <stdbool.h>
#include "chunk_def.h"

bool read_ckhdr(Chunk_hdr *ckhdr, FILE *stream);
bool read_riffck(Wav_riffck *chunk, const Chunk_hdr *ckhdr, FILE *stream);
bool read_fmtck(Wav_fmtck *chunk, const Chunk_hdr *ckhdr, FILE *stream);
bool read_factck(Wav_factck *chunk, const Chunk_hdr *ckhdr, FILE *stream);
bool read_junkck(Wav_junkck *chunk, const Chunk_hdr *ckhdr, FILE *stream);
bool read_bextck(Wav_bextck *chunk, const Chunk_hdr *ckhdr, FILE *stream);

bool write_riffck(const Wav_riffck *chunk, FILE *stream);
bool write_fmtck(const Wav_fmtck *chunk, FILE *stream);
bool write_factck(const Wav_factck *chunk, FILE *stream);
bool write_junkck(const Wav_junkck *chunk, FILE *stream);
bool write_bextck(const Wav_bextck *chunk, FILE *stream);

#endif