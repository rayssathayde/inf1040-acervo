#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alunos.h"
#include "teste_utils.h" // <-- Usando o arquivo oficial do grupo agora!

#define ARQUIVO_TESTE "alunos_teste.dat"

static void resetar_modulo() {
    remove("mudanca_estado_temp.dat");
    carregar_alunos("mudanca_estado_temp.dat");
}

void testar_carregar_salvar_alunos() {
    remove(ARQUIVO_TESTE);
    resetar_modulo();
    int caso_1 = carregar_alunos(ARQUIVO_TESTE);
    checar(caso_1 == 0, "carregar_alunos: arquivo inexistente");
    int caso_2 = carregar_alunos(NULL);
    checar(caso_2 == -1, "carregar_alunos: ponteiro de arquivo nulo");
    int caso_3 = salvar_alunos(NULL);
    checar(caso_3 == -1, "salvar_alunos: ponteiro de arquivo nulo");
}

void testar_cadastrar_aluno() {
    excluir_aluno(202610001); // limpa estado
    int caso_1 = cadastrar_aluno(202610001, "Vinicius", "Computacao");
    checar(caso_1 == 1, "cadastrar_aluno: cadastro valido");
    int caso_2 = cadastrar_aluno(202610001, "Outro Nome", "Outro Curso");
    checar(caso_2 == 0, "cadastrar_aluno: aluno ja cadastrado");
    int caso_3 = cadastrar_aluno(-5, "Aluno Errado", "Computacao");
    checar(caso_3 == -1, "cadastrar_aluno: matricula invalida (negativa)");
    int caso_4 = cadastrar_aluno(202610002, NULL, "Computacao");
    checar(caso_4 == -3, "cadastrar_aluno: ponteiro nome nulo");
    int caso_5 = cadastrar_aluno(202610003, "Vinicius", NULL);
    checar(caso_5 == -3, "cadastrar_aluno: ponteiro curso nulo");
}

void testar_buscar_aluno() {
    excluir_aluno(202610001);
    int caso_1 = buscar_aluno(202610001);
    checar(caso_1 == 0, "buscar_aluno: aluno nao encontrado");
    cadastrar_aluno(202610001, "Vinicius", "Computacao");
    int caso_2 = buscar_aluno(202610001);
    checar(caso_2 == 1, "buscar_aluno: aluno encontrado");
    int caso_3 = buscar_aluno(-10);
    checar(caso_3 == 0, "buscar_aluno: matricula invalida");
}

void testar_obter_nome_aluno() {
    excluir_aluno(202610001);
    char nome_res[100];
    int caso_1 = obter_nome_aluno(202610001, nome_res);
    checar(caso_1 == 0, "obter_nome_aluno: aluno nao encontrado");
    cadastrar_aluno(202610001, "Vinicius", "Computacao");
    int caso_2 = obter_nome_aluno(202610001, nome_res);
    checar(caso_2 == 1, "obter_nome_aluno: nome obtido com sucesso");
    checar(strcmp(nome_res, "Vinicius") == 0, "obter_nome_aluno: string copiada corretamente");
    int caso_3 = obter_nome_aluno(202610001, NULL);
    checar(caso_3 == 0, "obter_nome_aluno: ponteiro destino nulo");
}

void testar_listar_alunos() {
    excluir_aluno(202610001);
    int caso_1 = listar_alunos();
    checar(caso_1 == 0, "listar_alunos: nenhum aluno cadastrado");
    cadastrar_aluno(202610001, "Vinicius", "Computacao");
    int caso_2 = listar_alunos();
    checar(caso_2 == 1, "listar_alunos: listagem realizada com sucesso");
}

void testar_excluir_aluno() {
    excluir_aluno(202610001);
    int caso_1 = excluir_aluno(202610001);
    checar(caso_1 == 0, "excluir_aluno: aluno nao encontrado");
    cadastrar_aluno(202610001, "Vinicius", "Computacao");
    int caso_2 = excluir_aluno(202610001);
    checar(caso_2 == 1, "excluir_aluno: aluno excluido com sucesso");
    int caso_3 = excluir_aluno(-5);
    checar(caso_3 == 0, "excluir_aluno: matricula invalida");
}

void testar_persistencia_real() {
    remove(ARQUIVO_TESTE);
    excluir_aluno(202610001);
    cadastrar_aluno(202610001, "Vinicius", "Computacao");
    salvar_alunos(ARQUIVO_TESTE);
    excluir_aluno(202610001);
    carregar_alunos(ARQUIVO_TESTE);
    int recuperou = buscar_aluno(202610001);
    checar(recuperou == 1, "persistencia: dados gravados e recuperados com sucesso");
    remove(ARQUIVO_TESTE);
}

int main() {
    printf("==================================================\n");
    printf("   EXECUTANDO RELATORIO DE TESTES: MODULO ALUNOS   \n");
    printf("==================================================\n");

    testar_carregar_salvar_alunos();
    testar_cadastrar_aluno();
    testar_buscar_aluno();
    testar_obter_nome_aluno();
    testar_listar_alunos();
    testar_excluir_aluno();
    testar_persistencia_real();

    printf("==================================================\n");
    return 0;
}