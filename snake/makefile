compile: main.o queue.o ctl.o
	gcc -Wall -o snake main.o queue.o ctl.o

win: main.o queue.o
	gcc -Wall -o snake.exe main.o queue.o

main.o: main.c snake.h
	gcc -Wall -O -c -o main.o main.c

queue.o: queue.c snake.h
	gcc -Wall -O -c -o queue.o queue.c

ctl.o: ctl.c snake.h
	gcc -Wall -O -c -o ctl.o ctl.c

clean:
	rm ./*.o