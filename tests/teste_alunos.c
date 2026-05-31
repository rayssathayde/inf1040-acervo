#include <stdio.h>
#include <string.h>

#include "alunos.h"
#include "teste_utils.h"

void testar_cadastrar_aluno() {
    liberar_alunos(); // limpa estado 
    int caso_1 = cadastrar_aluno(2011001, "Joao Silva", "Engenharia"); // matricula valida, dados validos
    checar(caso_1 == 1, "cadastrar_aluno: cadastro valido");
    int caso_2 = cadastrar_aluno(2011001, "Maria Souza", "Computacao"); // matricula ja existe
    checar(caso_2 == 0, "cadastrar_aluno: aluno ja cadastrado");
    int caso_3 = cadastrar_aluno(1931001, "Carlos", "Fisica"); // matricula invalida
    checar(caso_3 == -1, "cadastrar_aluno: matricula invalida");
    int caso_4 = cadastrar_aluno(2220879, NULL, "Quimica"); // ponteiro nulo no nome
    checar(caso_4 == -3, "cadastrar_aluno: ponteiros invalidos");
    int caso_5 = cadastrar_aluno(2220879, "Teste", NULL);
    checar(caso_5 == -3, "cadastrar_aluno: curso nulo");
}

void testar_buscar_aluno() {
    liberar_alunos(); // limpa estado
    cadastrar_aluno(2516230, "Ana Lima", "Matematica"); // setup
    int caso_1 = buscar_aluno(2516230); // aluno existe
    checar(caso_1 == 1, "buscar_aluno: aluno encontrado");
    int caso_2 = buscar_aluno(2320879); // aluno nao existe
    checar(caso_2 == 0, "buscar_aluno: aluno nao encontrado");
    int caso_3 = buscar_aluno(1931001); // matricula invalida
    checar(caso_3 == -1, "buscar_aluno: matricula invalida");
}

void testar_obter_nome_aluno() {
    liberar_alunos(); // limpa estado
    cadastrar_aluno(2611234, "Pedro Santos", "Direito"); // setup
    char nome[100];
    int caso_1 = obter_nome_aluno(2611234, nome); // aluno existe e ponteiro ok
    checar(caso_1 == 1, "obter_nome_aluno: nome obtido com sucesso");
    int caso_2 = obter_nome_aluno(2320879, nome); // aluno nao existe
    checar(caso_2 == 0, "obter_nome_aluno: aluno nao encontrado");
    int caso_3 = obter_nome_aluno(1931001, nome); // matricula invalida
    checar(caso_3 == -1, "obter_nome_aluno: matricula invalida");
    int caso_4 = obter_nome_aluno(2611234, NULL); // ponteiro invalido
    checar(caso_4 == -1, "obter_nome_aluno: ponteiro invalido");
}

void testar_listar_alunos() {
    liberar_alunos(); // limpa estado
    cadastrar_aluno(2423574, "Lucas", "Historia");
    int caso_1 = listar_alunos(); // listagem normal
    checar(caso_1 == 1, "listar_alunos: lista impressa com sucesso");
}

void testar_excluir_aluno() {
    liberar_alunos(); // limpa estado
    cadastrar_aluno(2525698, "Julia", "Medicina"); // setup
    int caso_1 = excluir_aluno(2525698); // aluno existe
    checar(caso_1 == 1, "excluir_aluno: exclusao valida");
    int caso_2 = excluir_aluno(2525698); // aluno ja foi excluido (nao existe mais)
    checar(caso_2 == 0, "excluir_aluno: aluno nao encontrado");
    int caso_3 = excluir_aluno(1824563); // matricula invalida
    checar(caso_3 == -1, "excluir_aluno: matricula invalida");
}


void testar_carregar_salvar_alunos() {
    liberar_alunos(); // limpa estado
    cadastrar_aluno(2124587, "Teste Aluno", "Computacao"); // setup
    int caso_1 = salvar_alunos("data/teste_alunos.txt");
    checar(caso_1 == 1, "salvar_alunos: dados salvos com sucesso");
    liberar_alunos(); // limpa lista para testar o carregamento
    int caso_2 = carregar_alunos("data/teste_alunos.txt");
    checar(caso_2 == 1, "carregar_alunos: dados carregados com sucesso");
    int caso_3 = buscar_aluno(2124587); // verifica se o dado voltou
    checar(caso_3 == 1, "carregar_alunos: dados recuperados corretamente");
    int caso_4 = carregar_alunos("data/arquivo_inexistente.txt");
    checar(caso_4 == 0, "carregar_alunos: arquivo inexistente");
    liberar_alunos();
    remove("data/teste_alunos.txt");
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

    printf("\n--- TESTES DE: carregar_alunos e salvar_alunos ---\n");
    testar_carregar_salvar_alunos();
    
    return 0;
}