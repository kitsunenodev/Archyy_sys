programme: main.o daemon.o invocateur.o
	gcc -o programme main.o daemon.o invocateur.o

main.o: main.c
	gcc -c main.c

daemon.o: daemon.c
	gcc -c daemon.c

invocateur.o: invocateur.c
	gcc -c invocateur.c

clean:
	rm *.o

build: programme clean

execute: programme clean
	./programme