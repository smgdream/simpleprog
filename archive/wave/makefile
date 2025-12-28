VPATH=include:include/tmath
release: main.o auxt.o waveio.o wave2auxt.o waveinfo.o chunkio.o tmath.o
	gcc -Wall -O -o wav main.o auxt.o waveio.o wave2auxt.o waveinfo.o chunkio.o tmath.o -lm
	# rm ./*.o

main.o: main.c wave.h auxt.h
	gcc -Wall -Iinclude -O -c -o main.o main.c

tmath.o: tinymath.c tmath.h
	gcc -Wall -Iinclude -O -c -o tmath.o tinymath.c

auxt.o: auxt.c auxt.h auxt_def.h
	gcc -Wall -Iinclude -O -c -o auxt.o auxt.c

chunkio.o: chunkio.c chunkio.h chunk_def.h
	gcc -Wall -Iinclude -O -c -o chunkio.o chunkio.c

waveio.o: waveio.c wave.h chunkio.h
	gcc -Wall -Iinclude -O -c -o waveio.o waveio.c

wave2auxt.o: wave2auxt.c wave.h auxt.h tmath.h
	gcc -Wall -Iinclude -O -c -o wave2auxt.o wave2auxt.c

waveinfo.o: waveinfo.c wave.h
	gcc -Wall -Iinclude -O -c -o waveinfo.o waveinfo.c

clean:
	rm ./*.o
