CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = src/principal.c src/alunos.c src/livros.c src/emprestimos.c src/reservas.c
OUT = build/acervo

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)