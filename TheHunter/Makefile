PROGRAM = theHunter
CC      = gcc
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lm -lglut -lGLU -lGL

$(PROGRAM): theHunter.o image.o drawWithTex.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) image.o drawWithTex.o theHunter.o $(LDLIBS)

.PHONY: beauty clean dist

beauty:
	-indent -kr -nut $(PROGRAM).c
	-rm *~ *BAK

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
