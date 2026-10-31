CC      ?= gcc
CFLAGS  ?= -Wall -Wextra -O2
CFLAGS  += -std=c11 $(shell pkg-config --cflags raylib 2>/dev/null)
LDLIBS  += $(shell pkg-config --libs raylib 2>/dev/null || echo -lraylib) -lm

SRC := main.c bomb.c telas.c hero.c map.c barrier_border.c

.PHONY: all run clean

all: jogo

jogo: $(SRC) jogo.h
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDLIBS)

# O jogo carrega images/ e musics/ por caminho relativo, então precisa rodar a partir de src/.
run: jogo
	./jogo

clean:
	rm -f jogo placar.txt
