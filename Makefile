exe: fonction.o main.o
	gcc -Wall fonction.o main.o -o exe

fonction.o: fonction.c main.h
	gcc -Wall -c fonction.c

main.o: main.c main.h
	gcc -Wall -c main.c

clean:
	rm *.o exe