# Compiles all C files in the src directory

CFLAGS= -Wall -Wextra -Werror
LDFLAGS=-I$(LDIR) $(LDIR)/libcrypto.a
CC=clang

ODIR= obj
SDIR= src
EDIR= bin
LDIR= lib

LIBS= libcrypto.a

SRCS := $(wildcard $(SDIR)/*.c)
_PRGS := $(patsubst %.c,%,$(SRCS))
PRGS := $(patsubst $(SDIR)/%,$(EDIR)/%,$(_PRGS))
_OBJS := $(patsubst %,%.o,$(PRGS))
OBJS := $(patsubst $(EDIR)/%,$(ODIR)/%,$(_OBJS))

all : $(LDIR)/$(LIBS) $(PRGS)

# Optimize using clang's -Ofast option
optimize: CFLAGS += -Ofast
optimize: $(PRGS) $(LIB)

# Generate debug info
debug: clean
debug: CFLAGS += -DDEBUG -g
debug: $(PRGS) $(LIB)


## Compile the utility library
$(ODIR)/libcrypto.o: $(SDIR)/libcrypto.c
	@echo $@
	@$(CC) -c $< $(CFLAGS) -o $@
$(LDIR)/$(LIBS): $(ODIR)/libcrypto.o
	@echo $@
	@ar rcs $@ $^

## Compile the object files
$(ODIR)/%.o : $(SDIR)/%.c
	@if [ $@ != $(SDIR)/libcrypto.c ]; \
	then echo $@; \
		$(CC) -c $< $(CFLAGS) -o $@; \
	fi

## Compile the executables. Discludes library object file.
OBJ = $(patsubst $(EDIR)/%,$(ODIR)/%.o,$@)
$(PRGS): $(OBJS)
	@if [ $@ != $(EDIR)/libcrypto ]; \
	then echo $@; \
		$(CC) $(OBJ) $(LDFLAGS) -o $@; \
	fi

.PHONY: clean
clean:
	@echo Build environment cleaned
	@$(RM) $(PRGS) $(ODIR)/*.o $(LDIR)/*.a
