CC=g++
EXT=

IDIR=./includes

DDIR=./deps/
_DEPS=ioutil.c graph.c
DEPS=$(patsubst %.c, $(DDIR)%.c, $(_DEPS))

build: $(DEPS)
	$(CC) -o graph$(EXT) main.c $(DEPS) -I $(IDIR)

all: build
