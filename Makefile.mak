all: zadatak
zadatak: zadatak.c
	gcc -o zadatak zadatak.c
clean:
	rm zadatak