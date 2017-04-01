CC=g++
EXT=

IDIR=./includes

DDIR=./deps/
_DEPS=ioutil.c bitree.c
DEPS=$(patsubst %.c, $(DDIR)%.c, $(_DEPS))

build: $(DEPS)
	$(CC) -o bitree$(EXT) main.c $(DEPS) -I $(IDIR)

all: build
