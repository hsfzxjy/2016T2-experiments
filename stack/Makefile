CC=g++
EXT=

IDIR=./includes

DDIR=./deps/
_DEPS=stack.c
DEPS=$(patsubst %.c, $(DDIR)%.c, $(_DEPS))

BINDIR=./bin

build: $(DEPS)
	$(CC) -o $(BINDIR)/match$(EXT) $(DEPS) ./main/match.c -I $(IDIR) -include $(IDIR)/elements/match.h
	$(CC) -o $(BINDIR)/evaluation$(EXT) $(DEPS) ./main/evaluation.c -I $(IDIR) -include $(IDIR)/elements/evaluation.h
	$(CC) -o $(BINDIR)/maze$(EXT) ./main/maze.c
	$(CC) -o $(BINDIR)/queens$(EXT) ./main/queens.c
	$(CC) -o $(BINDIR)/power_set$(EXT) ./main/power_set.c

all: build
