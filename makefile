# Joshua Soberg 

# include directory (Header files).
INCDIR = ./include
# src directory (Source files).
SRCDIR = ./src
# build directory (Object files)
BUILDDIR = ./build
# Output directory.
OUTDIR = ./output
# Name of executable
EXCNAME = a.out

# Use gcc to build.
CC=gcc
CFLAGS=-I$(INCDIR)

_DEPS = Logger.h RandomNumberFileGenerator.h SorterThread.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

_OBJ = Logger.o RandomNumberFileGenerator.o SorterThread.o Main.o 
OBJ = $(patsubst %,$(BUILDDIR)/%,$(_OBJ))

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	#Make sure build directory exists.
	mkdir -p $(BUILDDIR)
	# Building...
	$(CC) -c -o $@ $< $(CFLAGS) -pthread

# Creating executable.
$(OUTDIR)/$(EXCNAME): $(OBJ)
	# Make sure output directory exists.
	mkdir -p $(OUTDIR)
	# Building output...
	$(CC) -o $@ $^ $(CFLAGS) -pthread

.PHONY: clean

clean:
	# Cleaning up object files and output directory.
	rm -f $(BUILDDIR)/*.o *~ core $(INCDIR)/*~ $(OUTDIR)/*.*
