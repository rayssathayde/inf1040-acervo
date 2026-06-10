CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = src/principal.c src/alunos.c src/livros.c src/emprestimos.c src/reservas.c
OUT = build/acervo

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

run: all
	./$(OUT)

teste_alunos:
	$(CC) src/alunos.c tests/teste_alunos.c $(CFLAGS) -o build/teste_alunos && ./build/teste_alunos

teste_livros:
	$(CC) src/livros.c tests/teste_livros.c $(CFLAGS) -o build/teste_livros && ./build/teste_livros

teste_emprestimos:
	$(CC) src/emprestimos.c tests/mocks/alunos_mock.c tests/mocks/livros_mock.c tests/teste_emprestimos.c $(CFLAGS) -o build/teste_emprestimos && ./build/teste_emprestimos

teste_reservas:
	$(CC) src/reservas.c tests/mocks/alunos_mock.c tests/mocks/livros_mock.c tests/teste_reservas.c $(CFLAGS) -o build/teste_reservas && ./build/teste_reservas

clean:
	rm -f $(OUT) build/teste_alunos build/teste_livros build/teste_emprestimos build/teste_reservas