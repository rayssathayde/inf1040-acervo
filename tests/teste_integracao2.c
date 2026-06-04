#include <stdio.h>
#include <string.h>

#include "alunos.h"
#include "livros.h"
#include "emprestimos.h"
#include "reservas.h"
#include "teste_utils.h"

#define MAT_A 2011001
#define MAT_B 2011002
#define MAT_C 2011003
#define ISBN_1 1001
#define ISBN_2 1002

void setup() {
    liberar_alunos();
    liberar_livros();
    liberar_emprestimos();
    liberar_reservas();

    cadastrar_aluno(MAT_A, "Ana Silva", "Computacao");
    cadastrar_aluno(MAT_B, "Bruno Lima", "Engenharia");
    cadastrar_aluno(MAT_C, "Carla Souza", "Direito");

    cadastrar_livro(ISBN_1, "Livro Um", "Autor Um", 2020, 1);
    cadastrar_livro(ISBN_2, "Livro Dois", "Autor Dois", 2021, 2);
}


void testar_persistencia_detalhada() {
    printf("\n--- PERSISTENCIA DETALHADA ---\n");
    setup();

    // cria cenario completo
    emprestar_livro(ISBN_1, MAT_A);
    emprestar_livro(ISBN_2, MAT_A);
    emprestar_livro(ISBN_2, MAT_B);
    criar_reserva(ISBN_1, MAT_B);
    criar_reserva(ISBN_1, MAT_C);
    criar_reserva(ISBN_2, MAT_C);

    // salva tudo
    salvar_alunos("data/det_alunos.txt");
    salvar_livros("data/det_livros.txt");
    salvar_emprestimos("data/det_emprestimos.txt");
    salvar_reservas("data/det_reservas.txt");

    // limpa e recarrega
    liberar_alunos();
    liberar_livros();
    liberar_emprestimos();
    liberar_reservas();

    carregar_alunos("data/det_alunos.txt");
    carregar_livros("data/det_livros.txt");
    carregar_emprestimos("data/det_emprestimos.txt");
    carregar_reservas("data/det_reservas.txt");

    // verifica alunos
    checar(buscar_aluno(MAT_A) == 1, "det: aluno A recuperado");
    checar(buscar_aluno(MAT_B) == 1, "det: aluno B recuperado");
    checar(buscar_aluno(MAT_C) == 1, "det: aluno C recuperado");

    // verifica livros e disponibilidade
    checar(buscar_livro(ISBN_1) == 1, "det: livro 1 recuperado");
    checar(buscar_livro(ISBN_2) == 1, "det: livro 2 recuperado");
    checar(verificar_disponibilidade(ISBN_1) == 0, "det: livro 1 indisponivel");
    checar(verificar_disponibilidade(ISBN_2) == 0, "det: livro 2 indisponivel");

    // verifica emprestimos
    checar(aluno_possui_emprestimo(MAT_A) == 1, "det: aluno A tem emprestimo");
    checar(aluno_possui_emprestimo(MAT_B) == 1, "det: aluno B tem emprestimo");
    checar(aluno_possui_emprestimo(MAT_C) == 0, "det: aluno C sem emprestimo");
    checar(verificar_emprestimo(ISBN_1, MAT_A) == 1, "det: emprestimo ISBN_1/MAT_A");
    checar(verificar_emprestimo(ISBN_2, MAT_A) == 1, "det: emprestimo ISBN_2/MAT_A");
    checar(verificar_emprestimo(ISBN_2, MAT_B) == 1, "det: emprestimo ISBN_2/MAT_B");

    // verifica reservas
    int proxima;
    checar(proxima_reserva(ISBN_1, &proxima) == 1, "det: fila ISBN_1 tem reserva");
    checar(proxima == MAT_B, "det: primeiro da fila ISBN_1 e MAT_B");
    checar(proxima_reserva(ISBN_2, &proxima) == 1, "det: fila ISBN_2 tem reserva");
    checar(proxima == MAT_C, "det: primeiro da fila ISBN_2 e MAT_C");

    liberar_alunos();
    liberar_livros();
    liberar_emprestimos();
    liberar_reservas();

    // nao remove os arquivos — verificar manualmente
    remove("data/det_alunos.txt");
    remove("data/det_livros.txt");
    remove("data/det_emprestimos.txt");
    remove("data/det_reservas.txt");
}

int main() {
    printf("\n--- TESTES DE: persistencia detalhada ---\n");
    testar_persistencia_detalhada();
    return 0;
}