CC=g++
EXT=

IDIR=./includes

DDIR=./deps/
_DEPS=ioutil.c linkedlist.c polyn.c
DEPS=$(patsubst %.c, $(DDIR)%.c, $(_DEPS))


build: $(DEPS)
	$(CC) -o polyn$(EXT) main.c $(DEPS) -I $(IDIR)

all: build
