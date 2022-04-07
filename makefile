programme: ../projet/main.o daemon.o invocateur.o
	gcc -o programme main.o daemon.o invocateur.o

main.o: main.c
	gcc -c main.c

daemon.o: daemon.c
	gcc -c daemon.c

invcateur.o:invocateur.c
	gcc -c invoateur.c
clean:
	rm *.o

build: programme clean

execute: programme clean
	./programme