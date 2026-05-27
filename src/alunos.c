#include <stdio.h>
#include <stdlib.h>
#include <string.h> // <-- ADICIONADO: Necessário para strncpy, strcpy e strcmp

#include "alunos.h"

#define TAM_STRING 100
#define MAX_ALUNOS 100

struct aluno {
    int matricula;
    char nome[TAM_STRING];
    char curso[TAM_STRING];
};

static Aluno alunos[MAX_ALUNOS];
static int qtd_alunos = 0;

int carregar_alunos(const char *arquivo) {
    if (arquivo == NULL) return -1;

    FILE *fp = fopen(arquivo, "rb");
    if (fp == NULL) {
        qtd_alunos = 0;
        return 0; // arquivo não existe ou está vazio
    }

    if (fread(&qtd_alunos, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return -1; // erro ao ler arquivo
    }
    
    if (qtd_alunos > 0) {
        fread(alunos, sizeof(struct aluno), qtd_alunos, fp);
    }

    fclose(fp);
    return 1; // dados carregados
}

int salvar_alunos(const char *arquivo) {
    if (arquivo == NULL) return -1;

    FILE *fp = fopen(arquivo, "wb");
    if (fp == NULL) return -1; // erro ao escrever

    fwrite(&qtd_alunos, sizeof(int), 1, fp);
    fwrite(alunos, sizeof(struct aluno), qtd_alunos, fp);

    fclose(fp);
    return 1; // dados salvos
}

// CORRIGIDO: Removido o ';' intruso
int cadastrar_aluno(int matricula, char *nome, char *curso) {
    if (matricula <= 0) return -1;             // CORRIGIDO: alterado para <= 0
    if (qtd_alunos >= MAX_ALUNOS) return -2; // limite máximo
    if (nome == NULL || curso == NULL) return -3; // CORRIGIDO: curso == NULL

    for(int i = 0; i<qtd_alunos; i++){
        if (matricula == alunos[i].matricula)  return 0;
    }
    alunos[qtd_alunos].matricula = matricula;
    
    strncpy(alunos[qtd_alunos].nome, nome, TAM_STRING - 1);
    alunos[qtd_alunos].nome[TAM_STRING - 1] = '\0';
    
    strncpy(alunos[qtd_alunos].curso, curso, TAM_STRING - 1);
    alunos[qtd_alunos].curso[TAM_STRING - 1] = '\0';

    qtd_alunos++;
    return 1;
}

int buscar_aluno(int matricula) {
    if (matricula <= 0) return 0;
    
    for (int i = 0; i < qtd_alunos; i++) {
        if (alunos[i].matricula == matricula) { // CORRIGIDO: banco_alunos alterado para alunos
            return 1; // aluno encontrado
        }
    }
    return 0; // aluno não encontrado
}

int obter_nome_aluno(int matricula, char* nome){
    if (nome == NULL || matricula <= 0) return 0; // aluno não encontrado
    
    for(int i = 0; i < qtd_alunos; i++){
        if(alunos[i].matricula == matricula){
            strcpy(nome,alunos[i].nome);
            return 1; // nome obtido
        }
    }
    return 0;
}

int listar_alunos() {
    if (qtd_alunos == 0) return 0; // nenhum aluno cadastrado

    printf("\n=== LISTA DE ALUNOS ===\n");
    for (int i = 0; i < qtd_alunos; i++) {
        printf("Matricula: %d | Nome: %s | Curso: %s\n", 
               alunos[i].matricula, 
               alunos[i].nome, 
               alunos[i].curso);
    }
    printf("=======================\n");
    return 1; // listagem com sucesso
}

int excluir_aluno(int matricula) {
    if (matricula <= 0) return 0;

    int indice = -1;

    for (int i = 0; i < qtd_alunos; i++) {
        if (alunos[i].matricula == matricula) {
            indice = i;
            break; // achou
        }
    }

    if (indice == -1) return 0; // aluno não encontrou

    for (int i = indice; i < qtd_alunos - 1; i++) {
        alunos[i] = alunos[i + 1];
    }

    qtd_alunos--;
    return 1; // aluno excluido
}