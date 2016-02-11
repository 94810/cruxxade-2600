CC=gcc
CFLAGS=$(shell sdl-config --cflags) -Wall -g
LIBS=$(shell sdl-config --libs) -lSDL_image -lm

text.o : text.c text.h police.h
	$(CC) $(CFLAGS) -c -o $@ $<

logic.o : logic.c logic.h
	$(CC) $(CFLAGS) -c -o $@ $<

graphics.o : graphics.c graphics.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c
	$(CC) $(CFLAGS) -c -o $@ $<

cruxxade : main.o graphics.o logic.o text.o
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)

clean :
	rm *.o
