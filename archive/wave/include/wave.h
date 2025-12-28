#ifndef WAVE_H
#define WAVE_H

#include <stdio.h>
#include "chunk_def.h"
#include "auxt.h"

struct wave_tag {
	Wav_riffck riffck;
	Wav_fmtck fmtck;
	Wav_factck factck;
	Wav_bextck bextck;
	Wav_junkck junkck;
	Wav_datack datack;
	void *data; // pointer to wav data
};
typedef struct wave_tag Wave;

Wave *wav_read(const char *filename);
int wav_write(const Wave *wav, const char *filename);
Auxt *wav2auxt(Wave *wav, Auxt *auxt);
Wave *auxt2wav(Auxt *auxt, Wave *wav);

#define debug(num) fprintf(stderr, "Dot: %d\n", (num))

#endif