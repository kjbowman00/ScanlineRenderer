# set options for this machine
# specify which compilers to use for c, C++, and linking
cc	= gcc

# define variables
HDRDIR = ./include

# optimization
OPTIM = -g

# compiler flags to be used (set to compile with debugging on)
CFLAGS = -I$(HDRDIR) $(OPTIM) -lGL -lGLU -lglut -lm

# link flags to be used
LDFLAGS	= $(OPTIM)

# libraries to be linked in
LIBS	=  -lm

# header files to be counted as dependencies
INCLUDES = include/structs.h

# rule for .c files
srender: $(INCLUDES) makefile display.c generate.c
	$(cc) $(CFLAGS) -o srender

# what to do if user types "make clean"
clean:
	rm src/*.o centroids kmeans

