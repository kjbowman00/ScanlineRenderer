IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) $(OPTIM) -lGL -lGLU -lglut -Wall -g

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = structs.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = generate.o display.o triangle.o readFromFile.o map.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

srender: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
