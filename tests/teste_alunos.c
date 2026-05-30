#include <stdio.h>
#include <string.h>

#include "alunos.h"
#include "teste_utils.h"

void testar_cadastrar_aluno() {
    excluir_aluno(101); // limpa estado 
    int caso_1 = cadastrar_aluno(101, "Joao Silva", "Engenharia"); // matricula valida, dados validos
    checar(caso_1 == 1, "cadastrar_aluno: cadastro valido");
    int caso_2 = cadastrar_aluno(101, "Maria Souza", "Computacao"); // matricula ja existe
    checar(caso_2 == 0, "cadastrar_aluno: aluno ja cadastrado");
    int caso_3 = cadastrar_aluno(-5, "Carlos", "Fisica"); // matricula invalida
    checar(caso_3 == -1, "cadastrar_aluno: matricula invalida");
    int caso_4 = cadastrar_aluno(102, NULL, "Quimica"); // ponteiro nulo no nome
    checar(caso_4 == -3, "cadastrar_aluno: ponteiros invalidos");
}

void testar_buscar_aluno() {
    excluir_aluno(202); // limpa estado
    cadastrar_aluno(202, "Ana Lima", "Matematica"); // setup
    int caso_1 = buscar_aluno(202); // aluno existe
    checar(caso_1 == 1, "buscar_aluno: aluno encontrado");
    int caso_2 = buscar_aluno(999); // aluno nao existe
    checar(caso_2 == 0, "buscar_aluno: aluno nao encontrado");
    int caso_3 = buscar_aluno(-10); // matricula invalida
    checar(caso_3 == -1, "buscar_aluno: matricula invalida");
}

void testar_obter_nome_aluno() {
    excluir_aluno(303); // limpa estado
    cadastrar_aluno(303, "Pedro Santos", "Direito"); // setup
    char nome[100];
    int caso_1 = obter_nome_aluno(303, nome); // aluno existe e ponteiro ok
    checar(caso_1 == 1, "obter_nome_aluno: nome obtido com sucesso");
    int caso_2 = obter_nome_aluno(999, nome); // aluno nao existe
    checar(caso_2 == 0, "obter_nome_aluno: aluno nao encontrado");
    int caso_3 = obter_nome_aluno(-1, nome); // matricula invalida
    checar(caso_3 == -1, "obter_nome_aluno: matricula invalida");
    int caso_4 = obter_nome_aluno(303, NULL); // ponteiro invalido
    checar(caso_4 == -1, "obter_nome_aluno: ponteiro invalido");
}

void testar_listar_alunos() {
    cadastrar_aluno(404, "Lucas", "Historia");
    int caso_1 = listar_alunos(); // listagem normal
    checar(caso_1 == 1, "listar_alunos: lista impressa com sucesso");
}

void testar_excluir_aluno() {
    excluir_aluno(505); // limpa estado
    cadastrar_aluno(505, "Julia", "Medicina"); // setup
    int caso_1 = excluir_aluno(505); // aluno existe
    checar(caso_1 == 1, "excluir_aluno: exclusao valida");
    int caso_2 = excluir_aluno(505); // aluno ja foi excluido (nao existe mais)
    checar(caso_2 == 0, "excluir_aluno: aluno nao encontrado");
    int caso_3 = excluir_aluno(-5); // matricula invalida
    checar(caso_3 == -1, "excluir_aluno: matricula invalida");
}

int main() {
    printf("\n--- TESTES DE: cadastrar_aluno ---\n");
    testar_cadastrar_aluno();

    printf("\n--- TESTES DE: buscar_aluno ---\n");
    testar_buscar_aluno();

    printf("\n--- TESTES DE: obter_nome_aluno ---\n");
    testar_obter_nome_aluno();

    printf("\n--- TESTES DE: listar_alunos ---\n");
    testar_listar_alunos();

    printf("\n--- TESTES DE: excluir_aluno ---\n");
    testar_excluir_aluno();
    
    return 0;
}