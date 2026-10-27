CC      = gcc
CFLAGS  = -O2 -Wall -Wextra
OBJS    = main.o cube.o coords.o solver.o parser.o

solver: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

main.o:   main.c cube.h parser.h solver.h
cube.o:   cube.c cube.h
coords.o: coords.c coords.h cube.h
solver.o: solver.c solver.h coords.h cube.h
parser.o: parser.c parser.h cube.h

clean:
	rm -f $(OBJS) solver

.PHONY: clean
