#------------------------------------------------------------------------------
# Makefile for Multi-Threaded Merge Sort
#
#       make                make clean
#------------------------------------------------------------------------------

CC=gcc
CFLAGS=-I.
DEPS = main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sort : main.o sort.o 
	$(CC) -o sort main.o sort.o 

clean :
	rm -f sort main.o sort.o 