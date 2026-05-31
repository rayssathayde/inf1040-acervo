#include <stdio.h>

#include "reservas.h"
#include "alunos.h"
#include "livros.h"
#include "teste_utils.h"


void testar_criar_reserva() {
    liberar_reservas(); // limpa estado
    int caso_1 = criar_reserva(10342, 202410001); // livro indisponivel
    checar(caso_1 == 1, "criar_reserva: reserva valida");
    int caso_2 = criar_reserva(10341, 202410001); // livro disponivel
    checar(caso_2 == 0, "criar_reserva: livro disponivel");
    int caso_3 = criar_reserva(78304, 202410001); // livro nao existe
    checar(caso_3 == -1, "criar_reserva: livro nao encontrado");
    int caso_4 = criar_reserva(10342, 202820001); // aluno nao existe
    checar(caso_4 == -2, "criar_reserva: aluno nao encontrado");
    liberar_reservas();
    criar_reserva(10342, 202410001);
    int caso_5 = criar_reserva(10342, 202410001); // duplicado
    checar(caso_5 == -3, "criar_reserva: reserva duplicada");
}


void testar_cancelar_reserva() {
    liberar_reservas();
    criar_reserva(10342, 202410001);
    int caso_1 = cancelar_reserva(10342, 202410001);
    checar(caso_1 == 1, "cancelar_reserva: cancelamento valido");
    int caso_2 = cancelar_reserva(10342, 202410001);
    checar(caso_2 == 0, "cancelar_reserva: reserva nao encontrada");
    int caso_3 = cancelar_reserva(78304, 202410001);
    checar(caso_3 == -1, "cancelar_reserva: livro nao encontrado");
    int caso_4 = cancelar_reserva(10342, 202820001);
    checar(caso_4 == -2, "cancelar_reserva: aluno nao encontrado");
}


void testar_listar_reservas_livro() {
    liberar_reservas();
    criar_reserva(10342, 202410001);
    int caso_1 = listar_reservas_livro(10342);
    checar(caso_1 == 1, "listar_reservas_livro: lista com reservas");
    liberar_reservas();
    int caso_2 = listar_reservas_livro(10342);
    checar(caso_2 == 0, "listar_reservas_livro: lista vazia");
    int caso_3 = listar_reservas_livro(78304);
    checar(caso_3 == -1, "listar_reservas_livro: livro nao encontrado");
}


void testar_listar_reservas_aluno() {
    liberar_reservas();
    criar_reserva(10342, 202410001);
    int caso_1 = listar_reservas_aluno(202410001);
    checar(caso_1 == 1, "listar_reservas_aluno: lista com reservas");
    liberar_reservas();
    int caso_2 = listar_reservas_aluno(202410001);
    checar(caso_2 == 0, "listar_reservas_aluno: lista vazia");
    int caso_3 = listar_reservas_aluno(202820001);
    checar(caso_3 == -1, "listar_reservas_aluno: aluno nao encontrado");
}


void testar_proxima_reserva() {
    liberar_reservas();
    int matricula;
    criar_reserva(10342, 202410001);
    int caso_1 = proxima_reserva(10342, &matricula);
    checar(caso_1 == 1 && matricula == 202410001,
           "proxima_reserva: retorno correto");
    liberar_reservas();
    int caso_2 = proxima_reserva(10342, &matricula);
    checar(caso_2 == 0, "proxima_reserva: fila vazia");
    int caso_3 = proxima_reserva(78304, &matricula);
    checar(caso_3 == -1, "proxima_reserva: livro nao encontrado");
    int caso_4 = proxima_reserva(10342, NULL);
    checar(caso_4 == -2, "proxima_reserva: ponteiro invalido");
}


void testar_carregar_salvar_reservas() {
    liberar_reservas();
    criar_reserva(10342, 202410001);
    int caso_1 = salvar_reservas("data/teste_reservas.txt");
    checar(caso_1 == 1, "salvar_reservas: dados salvos");
    liberar_reservas();
    int caso_2 = carregar_reservas("data/teste_reservas.txt");
    checar(caso_2 == 1, "carregar_reservas: dados carregados");
    int matricula;
    int caso_3 = proxima_reserva(10342, &matricula);
    checar(caso_3 == 1 && matricula == 202410001,
           "carregar_reservas: dados recuperados");
    int caso_4 = carregar_reservas("data/arquivo_inexistente.txt");
    checar(caso_4 == 0, "carregar_reservas: arquivo inexistente");
    liberar_reservas();
    remove("data/teste_reservas.txt");
}


int main() {
    printf("\n--- TESTES DE: criar_reserva ---\n");
    testar_criar_reserva();

    printf("\n--- TESTES DE: cancelar_reserva ---\n");
    testar_cancelar_reserva();

    printf("\n--- TESTES DE: listar_reservas_livro ---\n");
    testar_listar_reservas_livro();

    printf("\n--- TESTES DE: listar_reservas_aluno ---\n");
    testar_listar_reservas_aluno();

    printf("\n--- TESTES DE: proxima_reserva ---\n");
    testar_proxima_reserva();

    printf("\n--- TESTES DE: carregar_reservas e salvar_reservas ---\n");
    testar_carregar_salvar_reservas();

    return 0;
}