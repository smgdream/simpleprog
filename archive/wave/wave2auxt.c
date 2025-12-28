#include <string.h>
#include "wave.h"
#include "auxt.h"
#include "tmath.h"

static bool wav_wdat2adat(Wave *wav, Auxt *auxt, size_t size, int bit_depth);
static bool wav_adat2wdat(Auxt *auxt, Wave *wav, size_t size);


Auxt *wav2auxt(Wave *wav, Auxt *auxt)
{
	auxt_set_fmt(auxt,
				 PCM_SIGN,
				 wav->fmtck.data.channels,
				 wav->fmtck.data.bit_depth,
				 wav->fmtck.data.samplerate,
				 SS_SIGN,
				 LITTLE_END);
	if (wav->fmtck.data.bit_depth == 24)
		auxt->size = wav->datack.header.size / 3 * 4;
	else
		auxt->size = wav->datack.header.size;
	auxt_set_data(auxt, auxt->size, wav->fmtck.data.bit_depth);
	wav_wdat2adat(wav, auxt, auxt->size, wav->fmtck.data.bit_depth);
	return auxt;
}

Wave *auxt2wav(Auxt *auxt, Wave *wav)
{
	wav_adat2wdat(auxt, wav, auxt->size);
	return wav;
}

static bool wav_wdat2adat(Wave *wav, Auxt *auxt, size_t size, int bit_depth)
{
	if (bit_depth != 24)
		memcpy(auxt->data, wav->data, size);
	else
		for (Byte *src = wav->data, *dest = auxt->data; size; size -= 4) {
			i24toi32(src, dest);
			src += 3;
			dest += 4;
		}
	return 1;
}

static bool wav_adat2wdat(Auxt *auxt, Wave *wav, size_t size)
{
	if (auxt->fmt.bit_depth != 24)
		memcpy(wav->data, auxt->data, auxt->size);
	else
		for (Byte *src = auxt->data, *dest = wav->data; size; size -= 4) {
			i32toi24(src, dest, 1);
			src += 4;
			dest += 3;
		}
	return 1;
}