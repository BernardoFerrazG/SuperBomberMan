SRC := main.c bomb.c telas.c hero.c map.c barrier_border.c

jogo: $(SRC) jogo.h
	gcc -o jogo $(SRC) -lraylib

run: jogo
	./jogo