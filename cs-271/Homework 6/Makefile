all: encoder decoder

encoder: encoder.o
	ld -o encoder encoder.o
	
decoder: decoder.o
	ld -o decoder decoder.o

decoder.o: decoder.asm
	nasm -f elf -g -F stabs decoder.asm

encoder.o: encoder.asm
	nasm -f elf -g -F stabs encoder.asm

clean:
	rm encoder decoder encoder.o decoder.o
