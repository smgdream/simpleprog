#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"
#include "auxt.h"

// By Nimoe 
// 0.1.0

int print_wav_info(const Wave *wav);
int16_t sinewave(uint32_t hz, size_t x, uint32_t samplerate);

int main(int argc, char *argv[])
{
	Wave *wav = NULL;
	Auxt *auxt = auxt_new();

	if (argc == 1) {
		fprintf(stderr, "too few arguments\n");
		return 1;
	}

	wav = wav_read(argv[1]);
	print_wav_info(wav);
	wav2auxt(wav, auxt);

	int16_t *tmp = (int16_t *)auxt->data;
	for (size_t cnt = auxt->size/(2 + auxt->fmt.bit_depth / 17 * 2); cnt; --cnt) {
		*tmp++ += 0;
	}

	auxt2wav(auxt, wav);
	wav_write(wav, "out.wav");
	
	auxt_free(auxt);
	free(wav);
	return 0;
}

#define PI 3.14159265358
int16_t sinewave(uint32_t hz, size_t x, uint32_t samplerate)
{
	return (int16_t)(10000 * sin(x/420.0 * 2.0 * PI * (double)x / samplerate));
}
//x / 240 % 20000