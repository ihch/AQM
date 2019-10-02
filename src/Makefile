.PHONY: all
all: example

example: acf.o readfile.o findpeaks.o
	gcc -Wall -o example example.c acf.o readfile.o findpeaks.o

acf.o: acf.c
	gcc -c acf.c

readfile.o: readfile.c
	gcc -c readfile.c

findpeaks.o: findpeaks.c
	gcc -c findpeaks.c

clean:
	rm -f example acf.o readfile.o findpeaks.o
