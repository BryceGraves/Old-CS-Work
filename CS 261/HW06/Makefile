all: concordance 

hashMap.o: hashMap.c hashMap.h 
	gcc -g -Wall -std=c99 -c hashMap.c
	
main.o: main.c hashMap.h
	gcc -g -Wall -std=c99 -c main.c
		
concordance: hashMap.o main.o
	gcc -g -Wall -std=c99 -o concordance hashMap.o  main.o

clean:
	rm concordance
	rm hashMap.o
	rm main.o
