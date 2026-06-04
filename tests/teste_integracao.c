#include <stdio.h>
#include <string.h>

#include "alunos.h"
#include "livros.h"
#include "emprestimos.h"
#include "reservas.h"
#include "teste_utils.h"

// matriculas validas para teste
#define MAT_A 2011001
#define MAT_B 2011002
#define MAT_C 2011003

// isbns para teste
#define ISBN_1 1001
#define ISBN_2 1002

// ============================================================================
// setup e teardown
// ============================================================================

void setup() {
    liberar_alunos();
    liberar_livros();
    liberar_emprestimos();
    liberar_reservas();

    cadastrar_aluno(MAT_A, "Ana Silva", "Computacao");
    cadastrar_aluno(MAT_B, "Bruno Lima", "Engenharia");
    cadastrar_aluno(MAT_C, "Carla Souza", "Direito");

    cadastrar_livro(ISBN_1, "Livro Um", "Autor Um", 2020, 1); // 1 exemplar
    cadastrar_livro(ISBN_2, "Livro Dois", "Autor Dois", 2021, 2); // 2 exemplares
}

// ============================================================================
// ciclo basico: emprestar e devolver
// ============================================================================

void testar_ciclo_basico() {
    printf("\n--- CICLO BASICO: emprestar e devolver ---\n");
    setup();

    checar(emprestar_livro(ISBN_1, MAT_A) == 1, "ciclo_basico: emprestimo realizado");
    checar(livro_esta_emprestado(ISBN_1) == 1, "ciclo_basico: livro esta emprestado");
    checar(aluno_possui_emprestimo(MAT_A) == 1, "ciclo_basico: aluno possui emprestimo");
    checar(verificar_disponibilidade(ISBN_1) == 0, "ciclo_basico: livro indisponivel apos emprestimo");

    checar(devolver_livro(ISBN_1, MAT_A) == 1, "ciclo_basico: devolucao realizada");
    checar(livro_esta_emprestado(ISBN_1) == 0, "ciclo_basico: livro nao esta emprestado apos devolucao");
    checar(aluno_possui_emprestimo(MAT_A) == 0, "ciclo_basico: aluno nao possui emprestimo apos devolucao");
    checar(verificar_disponibilidade(ISBN_1) == 1, "ciclo_basico: livro disponivel apos devolucao");
}

// ============================================================================
// multiplos exemplares
// ============================================================================

void testar_multiplos_exemplares() {
    printf("\n--- MULTIPLOS EXEMPLARES ---\n");
    setup();

    checar(emprestar_livro(ISBN_2, MAT_A) == 1, "multiplos: primeiro emprestimo");
    checar(emprestar_livro(ISBN_2, MAT_B) == 1, "multiplos: segundo emprestimo");
    checar(verificar_disponibilidade(ISBN_2) == 0, "multiplos: livro indisponivel com 2 emprestados");
    checar(emprestar_livro(ISBN_2, MAT_C) == 0, "multiplos: terceiro emprestimo bloqueado");

    checar(devolver_livro(ISBN_2, MAT_A) == 1, "multiplos: primeira devolucao");
    checar(verificar_disponibilidade(ISBN_2) == 1, "multiplos: livro disponivel apos devolucao");
}

// ============================================================================
// restricoes de emprestimo
// ============================================================================

void testar_restricoes_emprestimo() {
    printf("\n--- RESTRICOES DE EMPRESTIMO ---\n");
    setup();

    checar(emprestar_livro(ISBN_1, MAT_A) == 1, "restricoes: emprestimo inicial");
    checar(emprestar_livro(ISBN_1, MAT_A) == -3, "restricoes: aluno ja esta com esse livro");
    checar(emprestar_livro(9999, MAT_A) == -1, "restricoes: livro nao encontrado");
    checar(emprestar_livro(ISBN_1, 9999999) == -2, "restricoes: aluno nao encontrado");
}

// ============================================================================
// ciclo reserva: emprestar, reservar, devolver, proxima reserva
// ============================================================================

void testar_ciclo_reserva() {
    printf("\n--- CICLO RESERVA ---\n");
    setup();

    // empresta unico exemplar
    checar(emprestar_livro(ISBN_1, MAT_A) == 1, "reserva: emprestimo realizado");

    // livro disponivel nao pode ser reservado
    checar(criar_reserva(ISBN_2, MAT_B) == 0, "reserva: nao reserva livro disponivel");

    // cria reserva para livro indisponivel
    checar(criar_reserva(ISBN_1, MAT_B) == 1, "reserva: reserva criada");
    checar(criar_reserva(ISBN_1, MAT_C) == 1, "reserva: segunda reserva criada");
    checar(criar_reserva(ISBN_1, MAT_B) == -3, "reserva: duplicata bloqueada");

    // verifica proxima da fila
    int proxima;
    checar(proxima_reserva(ISBN_1, &proxima) == 1, "reserva: proxima reserva encontrada");
    checar(proxima == MAT_B, "reserva: proxima reserva e o primeiro da fila");

    // devolucao — principal deveria chamar proxima_reserva e notificar
    checar(devolver_livro(ISBN_1, MAT_A) == 1, "reserva: devolucao realizada");
    checar(verificar_disponibilidade(ISBN_1) == 1, "reserva: livro disponivel apos devolucao");
}

// ============================================================================
// exclusao com restricoes
// ============================================================================

void testar_restricoes_exclusao() {
    printf("\n--- RESTRICOES DE EXCLUSAO ---\n");
    setup();

    // livro com emprestimo ativo nao pode ser excluido
    emprestar_livro(ISBN_1, MAT_A);
    checar(excluir_livro(ISBN_1) == -2, "exclusao: livro com emprestimo ativo bloqueado");

    // aluno com emprestimo — principal deve verificar antes de excluir
    checar(aluno_possui_emprestimo(MAT_A) == 1, "exclusao: aluno possui emprestimo ativo");

    // apos devolucao, livro pode ser excluido
    devolver_livro(ISBN_1, MAT_A);
    checar(excluir_livro(ISBN_1) == 1, "exclusao: livro excluido apos devolucao");

    // aluno sem emprestimo pode ser excluido
    checar(aluno_possui_emprestimo(MAT_A) == 0, "exclusao: aluno sem emprestimo");
    checar(excluir_aluno(MAT_A) == 1, "exclusao: aluno excluido com sucesso");
}


void testar_cancelamento_em_massa() {
    printf("\n--- CANCELAMENTO EM MASSA DE RESERVAS ---\n");
    setup();

    emprestar_livro(ISBN_1, MAT_A);
    criar_reserva(ISBN_1, MAT_B);
    criar_reserva(ISBN_1, MAT_C);

    int caso_1 = cancelar_reservas_livro(ISBN_1);
    checar(caso_1 == 1, "cancelamento_massa: reservas do livro canceladas");

    int proxima;
    checar(proxima_reserva(ISBN_1, &proxima) == 0, "cancelamento_massa: fila vazia apos cancelar livro");

    criar_reserva(ISBN_1, MAT_B);
    int caso_2 = cancelar_reservas_aluno(MAT_B);
    checar(caso_2 == 1, "cancelamento_massa: reservas do aluno canceladas");
    checar(proxima_reserva(ISBN_1, &proxima) == 0, "cancelamento_massa: fila vazia apos cancelar aluno");
}

// ============================================================================
// persistencia completa
// ============================================================================

void testar_persistencia() {
    printf("\n--- PERSISTENCIA COMPLETA ---\n");
    setup();

    emprestar_livro(ISBN_1, MAT_A);
    emprestar_livro(ISBN_2, MAT_A);  // esgota exemplar
    emprestar_livro(ISBN_2, MAT_B);  // esgota segundo exemplar
    criar_reserva(ISBN_2, MAT_C);    // agora ISBN_2 esta indisponivel

    // salva tudo
    checar(salvar_alunos("data/int_alunos.txt") == 1, "persistencia: alunos salvos");
    checar(salvar_livros("data/int_livros.txt") == 1, "persistencia: livros salvos");
    checar(salvar_emprestimos("data/int_emprestimos.txt") == 1, "persistencia: emprestimos salvos");
    checar(salvar_reservas("data/int_reservas.txt") == 1, "persistencia: reservas salvas");

    // limpa tudo
    liberar_alunos();
    liberar_livros();
    liberar_emprestimos();
    liberar_reservas();

    // recarrega
    checar(carregar_alunos("data/int_alunos.txt") == 1, "persistencia: alunos carregados");
    checar(carregar_livros("data/int_livros.txt") == 1, "persistencia: livros carregados");
    checar(carregar_emprestimos("data/int_emprestimos.txt") == 1, "persistencia: emprestimos carregados");
    checar(carregar_reservas("data/int_reservas.txt") == 1, "persistencia: reservas carregadas");

    // verifica dados
    checar(buscar_aluno(MAT_A) == 1, "persistencia: aluno recuperado");
    checar(buscar_livro(ISBN_1) == 1, "persistencia: livro recuperado");
    checar(aluno_possui_emprestimo(MAT_A) == 1, "persistencia: emprestimo recuperado");

    int proxima;
    checar(proxima_reserva(ISBN_2, &proxima) == 1, "persistencia: reserva recuperada");
    checar(proxima == MAT_C, "persistencia: matricula da reserva correta");

    // limpa arquivos temporarios
    remove("data/int_alunos.txt");
    remove("data/int_livros.txt");
    remove("data/int_emprestimos.txt");
    remove("data/int_reservas.txt");
}

// ============================================================================
// main
// ============================================================================

int main() {
    printf("===========================================================\n");
    printf("  TESTES INTEGRADOS\n");
    printf("===========================================================\n");

    testar_ciclo_basico();
    testar_multiplos_exemplares();
    testar_restricoes_emprestimo();
    testar_ciclo_reserva();
    testar_restricoes_exclusao();
    testar_cancelamento_em_massa();
    testar_persistencia();

    printf("\n===========================================================\n");
    printf("  FIM DOS TESTES INTEGRADOS\n");
    printf("===========================================================\n");

    return 0;
}
