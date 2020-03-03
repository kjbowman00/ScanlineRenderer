IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) $(OPTIM) -lGL -lGLU -lglut -Wall

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = structs.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = generate.o display.o triangle.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

srender: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
