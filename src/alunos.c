#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alunos.h"

#define TAM_STRING 100

struct aluno {
    int matricula;
    char nome[TAM_STRING];
    char curso[TAM_STRING];
};

typedef struct no_aluno NoAluno;
struct no_aluno {
    struct aluno dados;
    NoAluno *proximo;
};

static NoAluno *inicio_alunos = NULL;

int carregar_alunos(const char *arquivo) {
    if (arquivo == NULL) return -2; // ponteiro nulo

    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        liberar_alunos();
        return 0; // arquivo não existe ou está vazio
    }

    liberar_alunos();

    int qtd_alunos = 0;
    if (fscanf(fp, "%d", &qtd_alunos) != 1) {
        fclose(fp);
        return 0; // arquivo corrompido ou vazio
    }
    
    NoAluno *atual = NULL;
    for (int i = 0; i < qtd_alunos; i++) {
        NoAluno *novo = (NoAluno *)malloc(sizeof(NoAluno));
        if (novo == NULL) {
            fclose(fp);
            liberar_alunos();
            return -3; // falha de alocação de memória
        }
        
        if (fscanf(fp, "%d", &(novo->dados.matricula)) != 1) {
            free(novo);
            fclose(fp);
            liberar_alunos();
            return -1; // erro de leitura física
        }

        if (fgets(novo->dados.nome, TAM_STRING, fp) == NULL) {
            free(novo); 
            fclose(fp); 
            liberar_alunos();
            return -1; // erro de leitura física
        }

        novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

        if (fgets(novo->dados.curso, TAM_STRING, fp) == NULL) {
            free(novo); 
            fclose(fp); 
            liberar_alunos(); 
            return -1; // erro de leitura física
        }
        novo->dados.curso[strcspn(novo->dados.curso, "\n")] = '\0';

        novo->proximo = NULL;

        if (inicio_alunos == NULL) {
            inicio_alunos = novo;
        } else {
            atual->proximo = novo;
        }
        atual = novo;
    }

    fclose(fp);
    return 1; // dados carregados
}

int salvar_alunos(const char *arquivo) {
    if (arquivo == NULL) return -2; // ponteiro nulo

    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) return -1; // erro ao criar ou abrir o arquivo
    
    int qtd_alunos = 0;
    NoAluno *atual = inicio_alunos;
    while (atual != NULL) {
        qtd_alunos++;
        atual = atual->proximo;
    }

    if (fprintf(fp, "%d\n", qtd_alunos) < 0) {
        fclose(fp);
        return -3; // erro de escrita no disco
    }

    atual = inicio_alunos;
    while (atual != NULL) {
        if (fprintf(fp, "%d\n%s\n%s\n",
                    atual->dados.matricula,
                    atual->dados.nome,
                    atual->dados.curso) < 0) {
            fclose(fp);
            return -3; // erro de escrita no disco
        }
        atual = atual->proximo;
    }

    fclose(fp);
    return 1; // dados salvos com sucesso
}


static int matricula_valida(int matricula) {
    if (matricula <= 0) return 0; // matricula invalida

    char str[20];
    sprintf(str, "%d", matricula);

    if (strlen(str) != 7) return 0;

    // dois primeiros digitos: 20-26
    int ano = (str[0] - '0') * 10 + (str[1] - '0');
    if (ano < 20 || ano > 26) return 0;

    // terceiro digito: 1 ou 2
    int periodo = str[2] - '0';
    if (periodo != 1 && periodo != 2) return 0; // matricula invalida

    return 1;
}

int cadastrar_aluno(int matricula, char *nome, char *curso) {
    if (!matricula_valida(matricula)) return -1; // matrícula inválida
    if (nome == NULL || curso == NULL) return -3; // ponteiros inválidos

    NoAluno *atual = inicio_alunos;
    while (atual != NULL) {
        if (atual->dados.matricula == matricula) {
            return 0; // aluno já cadastrado
        }
        atual = atual->proximo;
    }

    NoAluno *novo = (NoAluno *)malloc(sizeof(NoAluno));
    if (novo == NULL) return -2; // falha de alocação de memória

    novo->dados.matricula = matricula;
    
    strncpy(novo->dados.nome, nome, TAM_STRING - 1);
    novo->dados.nome[TAM_STRING - 1] = '\0';
    
    strncpy(novo->dados.curso, curso, TAM_STRING - 1);
    novo->dados.curso[TAM_STRING - 1] = '\0';

    novo->proximo = NULL;

    if (inicio_alunos == NULL) {
        inicio_alunos = novo;
    } else {
        atual = inicio_alunos;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    return 1; // cadastro realizado com sucesso
}

int buscar_aluno(int matricula) {
    if (!matricula_valida(matricula)) return -1; // matrícula inválida
    
    NoAluno *atual = inicio_alunos;
    while (atual != NULL) {
        if (atual->dados.matricula == matricula) {
            return 1; // aluno encontrado
        }
        atual = atual->proximo;
    }
    return 0; // aluno não encontrado
}

int obter_nome_aluno(int matricula, char* nome) {
    if (nome == NULL || !matricula_valida(matricula)) return -1; // aluno inválido ou matrícula inválida
    
    NoAluno *atual = inicio_alunos;
    while (atual != NULL) {
        if (atual->dados.matricula == matricula) {
            strcpy(nome, atual->dados.nome);
            return 1; // nome obtido com sucesso
        }
        atual = atual->proximo;
    }
    return 0; // aluno não encontrado
}

int listar_alunos() {
    if (inicio_alunos == NULL) return 0; // nenhum aluno cadastrado

    printf("\n=== LISTA DE ALUNOS ===\n");
    NoAluno *atual = inicio_alunos;
    while (atual != NULL) {
        printf("Matricula: %d | Nome: %s | Curso: %s\n",
               atual->dados.matricula,
               atual->dados.nome,
               atual->dados.curso);
        atual = atual->proximo;
    }
    printf("=======================\n");
    return 1; // listagem com sucesso
}

int excluir_aluno(int matricula) {
    if (!matricula_valida(matricula)) return -1; // matrícula inválida

    NoAluno *atual = inicio_alunos;
    NoAluno *anterior = NULL;

    while (atual != NULL) {
        if (atual->dados.matricula == matricula) {
            if (anterior == NULL) {
                inicio_alunos = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return 1; // aluno excluído
        }
        anterior = atual;
        atual = atual->proximo;
    }

    return 0; // aluno não encontrado
}


int liberar_alunos(void) {
    NoAluno *atual = inicio_alunos;
    while (atual != NULL) {
        NoAluno *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicio_alunos = NULL;
    return 1;
}