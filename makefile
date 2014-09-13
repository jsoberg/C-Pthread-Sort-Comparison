# Joshua Soberg 
# Template obtained from: 'http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/'

# include directory (Header files).
INCDIR = ./include
# src directory (Source files).
SRCDIR = ./src
# build directory (Object files)
BUILDDIR = ./build
# Output directory.
OUTDIR = ./output

# Use gcc to build.
CC=gcc
CFLAGS=-I$(INCDIR)

_DEPS = RandomNumberFileGenerator.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

_OBJ = RandomNumberFileGenerator.o Main.o 
OBJ = $(patsubst %,$(BUILDDIR)/%,$(_OBJ))

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	# Make sure build directory exists.
	mkdir -p $(BUILDDIR)
	# Building...
	$(CC) -c -o $@ $< $(CFLAGS)

# Creating executable.
$(OUTDIR)/a.out: $(OBJ)
	# Make sure output directory exists.
	mkdir -p $(OUTDIR)
	# Building output...
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	# Cleaning up object files.
	rm -f $(BUILDDIR)/*.o *~ core $(INCDIR)/*~ 