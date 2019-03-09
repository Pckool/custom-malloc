all: memgrind.c mymalloc.o
	gcc -o memgrind.out memgrind.c mymalloc.o

mymalloc.o: mymalloc.c
	gcc -c mymalloc.c

memgrind:
	./memgrind.out

clean:
	rm memgrind.out; rm mymalloc.o
