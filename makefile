PROGRAM_NAME=juliaSet
SOURCES=./src
ASM=nasm
AFLAGS=-f elf64
GCC=gcc
CFLAGS=-m64 -fPIC
ALLEGRO5=`pkg-config --cflags --libs allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5 `


all: juliaSet

main.o: $(SOURCES)/main.c
	$(GCC) $(CFLAGS) -c $(SOURCES)/main.c 

julia.o: $(SOURCES)/julia.s
	$(ASM) $(AFLAGS)  $(SOURCES)/julia.s 
	
juliaSet: 	main.o julia.o $(SOURCES)/julia.h
	$(GCC) $(CFLAGS) main.o $(SOURCES)/julia.o -o $(PROGRAM_NAME)  $(ALLEGRO5)
	rm main.o
	rm $(SOURCES)/julia.o

run: 	juliaSet
	./$(PROGRAM_NAME)

clean:
	rm *.o
	rm juliaSet
