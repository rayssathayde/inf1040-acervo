#include <stdio.h>
#include <stdlib.h>

#include "emprestimos.h"
#include "alunos.h"
#include "livros.h"


struct emprestimo {
    long isbn;
    int matricula;
}; 

struct no_emprestimo {
    Emprestimo dado;
    struct no_emprestimo *proximo;
};

static struct no_emprestimo *lista_emprestimos = NULL;


int carregar_emprestimos(const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) return 0; // arquivo nao existe ou vazio

    long isbn;
    int matricula;
    int encontrou = 0;
    int lidos;

    while ((lidos = fscanf(fp, "%ld;%d\n", &isbn, &matricula)) != EOF) {
        if (lidos != 2) {
            fclose(fp);
            return -1; // arquivo corrompido, erro de leitura
        }
        struct no_emprestimo *novo = malloc(sizeof(struct no_emprestimo));
        if (novo == NULL) {
            fclose(fp);
            return -2; // erro de alocacao, falta memoria
        }
        // insere dados 
        novo->dado.isbn = isbn;
        novo->dado.matricula = matricula;
        novo->proximo = lista_emprestimos;
        lista_emprestimos = novo;
        encontrou = 1;
    }
    fclose(fp);
    if (encontrou) return 1;
    return 0;
}


int salvar_emprestimos(const char *arquivo) {
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) return -1;

    struct no_emprestimo *atual = lista_emprestimos;
    while (atual != NULL) {
        if (fprintf(fp, "%ld;%d\n", atual->dado.isbn, atual->dado.matricula) < 0) {
            fclose(fp);
            return -1;
        }
        atual = atual->proximo;
    }

    fclose(fp);
    return 1;
}


int emprestar_livro(long isbn, int matricula) {
    int livro = buscar_livro(isbn);
    int aluno = buscar_aluno(matricula);
   
    if (!livro) return -1; // livro nao encontrado
    if (!aluno) return -2; // aluno nao encontrado

    // verifica se aluno ja esta com esse livro
    struct no_emprestimo *atual = lista_emprestimos;
    while (atual != NULL) {
        if (atual->dado.isbn == isbn && atual->dado.matricula == matricula)
            return -3;
        atual = atual->proximo;
    }

    int disponivel = verificar_disponibilidade(isbn);
    if (!disponivel) return 0; // livro indisponivel

    // realiza o emprestimo
    struct no_emprestimo *novo = malloc(sizeof(struct no_emprestimo));
    if (novo == NULL) return -4; // erro de alocacao
    novo->dado.isbn = isbn;
    novo->dado.matricula = matricula;
    novo->proximo = lista_emprestimos;
    lista_emprestimos = novo;

    reduzir_disponivel(isbn);
    return 1;
}


int devolver_livro(long isbn, int matricula) {
    int livro = buscar_livro(isbn);
    int aluno = buscar_aluno(matricula);

    if (!livro) return -1; // livro nao encontrado
    if (!aluno) return -2; // aluno nao encontrado

    struct no_emprestimo *atual = lista_emprestimos;
    struct no_emprestimo *anterior = NULL;

    while (atual != NULL) {
        // verifica se emprestimo existe
        if (atual->dado.isbn == isbn && atual->dado.matricula == matricula) {
            if (anterior == NULL) 
                lista_emprestimos = atual->proximo;
            else if (anterior != NULL) 
                anterior->proximo = atual->proximo; 
            // remove emprestimo 
            free(atual);
            aumentar_disponivel(isbn);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}


int listar_emprestimos_livro(long isbn) {
    int livro = buscar_livro(isbn);
    if (!livro) {
        printf("Livro nao encontrado!\n");
        return -1; 
    }

    char titulo[100];
    obter_titulo_livro(isbn, titulo);
    printf("Emprestimos do livro: %s\n", titulo);

    int encontrou = 0;
    struct no_emprestimo *atual = lista_emprestimos;
    while (atual != NULL) {
        if (atual->dado.isbn == isbn) {
            char nome[50];
            obter_nome_aluno(atual->dado.matricula, nome);
            printf("%d - %s\n", atual->dado.matricula, nome);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (encontrou) return 1;
    
    printf("Nenhum emprestimo encontrado!\n");
    return 0;
}


int listar_emprestimos_aluno(int matricula) {
    int aluno = buscar_aluno(matricula);
    if (!aluno) {
        printf("Aluno(a) nao encontrado(a)!\n");
        return -1;
    } 

    char nome[50];
    obter_nome_aluno(matricula, nome);
    printf("Emprestimos do(a) aluno(a): %s\n", nome);

    int encontrou = 0;
    struct no_emprestimo *atual = lista_emprestimos;
    while (atual != NULL) {
        if (atual->dado.matricula == matricula) {
            char titulo[100];
            obter_titulo_livro(atual->dado.isbn, titulo);
            printf("%ld - %s\n", atual->dado.isbn, titulo);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (encontrou) return 1;
    
    printf("Nenhum emprestimo encontrado!\n");
    return 0;
}


int aluno_possui_emprestimo(int matricula) {
    int aluno = buscar_aluno(matricula);
    if (!aluno) return -1; // aluno nao encontrado

    struct no_emprestimo *atual = lista_emprestimos;
    while (atual != NULL) {
        if (atual->dado.matricula == matricula) 
            return 1;
        atual = atual->proximo;
    }
    return 0;
}


int livro_esta_emprestado(long isbn) {
    int livro = buscar_livro(isbn);
    if (!livro) return -1; // livro nao encontrado

    struct no_emprestimo *atual = lista_emprestimos;
    while (atual != NULL) {
        if (atual->dado.isbn == isbn) 
            return 1;
        atual = atual->proximo;
    }
    return 0;
}


int liberar_emprestimos(void) {
    struct no_emprestimo *atual = lista_emprestimos;
    while (atual != NULL) {
        struct no_emprestimo *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista_emprestimos = NULL;
    return 1;
}
    