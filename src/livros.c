#include "livros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct livro {
    long isbn;
    char titulo[101];
    char autor[101];
    int ano;
    int quantidade_total;
    int quantidade_disponivel;
};

struct no_livro {
    Livro dados;
    struct no_livro *proximo;
};

typedef struct no_livro NoLivro;

static NoLivro *inicio_livros = NULL;


static int dados_livro_validos(long isbn, const char *titulo, const char *autor,
                               int quantidade_total) {
    if (isbn <= 0) return 0;
    if (titulo == NULL || titulo[0] == '\0') return 0;
    if (autor == NULL || autor[0] == '\0') return 0;
    if (quantidade_total <= 0) return 0;
    return 1;
}


int carregar_livros(const char *arquivo) {
    if (arquivo == NULL) return -2; // ponteiro nulo

    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) return 0; // arquivo nao existe ou vazio

    liberar_livros();

    long isbn;
    char titulo[101];
    char autor[101];
    int ano, total, disponivel;

    while (fscanf(fp, "%ld;%100[^;];%100[^;];%d;%d;%d",
                  &isbn, titulo, autor, &ano, &total, &disponivel) == 6) {

        if (!dados_livro_validos(isbn, titulo, autor, total)) {
            fclose(fp);
            liberar_livros();
            return -1; // erro de leitura
        }

        NoLivro *novo = malloc(sizeof(NoLivro));
        if (novo == NULL) {
            fclose(fp);
            liberar_livros();
            return -3; // falta memoria
        }

        novo->dados.isbn = isbn;
        strcpy(novo->dados.titulo, titulo);
        strcpy(novo->dados.autor, autor);
        novo->dados.ano = ano;
        novo->dados.quantidade_total = total;
        novo->dados.quantidade_disponivel = disponivel;

        novo->proximo = inicio_livros;
        inicio_livros = novo;
    }

    if (!feof(fp)) {
        fclose(fp);
        liberar_livros();
        return -1; // arquivo corrompido
    }

    fclose(fp);

    return (inicio_livros != NULL) ? 1 : 0; // carregamento com sucesso (1) ou arquivo vazio (0)
}


int salvar_livros(const char *arquivo) {
    if (arquivo == NULL) return -2; // ponteiro nulo

    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) return -1; // erro ao abrir arquivo

    NoLivro *atual = inicio_livros;

    while (atual != NULL) {
        if (fprintf(fp, "%ld;%s;%s;%d;%d;%d\n",
                    atual->dados.isbn,
                    atual->dados.titulo,
                    atual->dados.autor,
                    atual->dados.ano,
                    atual->dados.quantidade_total,
                    atual->dados.quantidade_disponivel) < 0) {
            fclose(fp);
            return -3; // erro de escrita
        }
        atual = atual->proximo;
    }

    fclose(fp);
    return 1; // sucesso
}


int cadastrar_livro(long isbn, char *titulo, char *autor, int ano, int quantidade) {
    if (titulo == NULL || autor == NULL) return -3; // ponteiros inválidos

    if (isbn <= 0 || quantidade <= 0 || titulo[0] == '\0' || autor[0] == '\0')
        return -1; // dados inválidos

    if (buscar_livro(isbn) == 1) return 0; // livro já cadastrado

    NoLivro *novo = malloc(sizeof(NoLivro));
    if (novo == NULL) return -2; // falha de memória

    novo->dados.isbn = isbn;
    strcpy(novo->dados.titulo, titulo);
    strcpy(novo->dados.autor, autor);
    novo->dados.ano = ano;
    novo->dados.quantidade_total = quantidade;
    novo->dados.quantidade_disponivel = quantidade;

    novo->proximo = inicio_livros;
    inicio_livros = novo;

    return 1; // sucesso
}


int buscar_livro(long isbn) {
    if (isbn <= 0) return 0; // livro não encontrado (isbn invalido)

    NoLivro *atual = inicio_livros;

    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {
            return 1; // livro encontrado
        }
        atual = atual->proximo;
    }

    return 0; // livro nao encontrado
}


int obter_titulo_livro(long isbn, char* titulo) {
    if (titulo == NULL) return -1; // ponteiro inválido

    NoLivro *atual = inicio_livros;

    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {
            strcpy(titulo, atual->dados.titulo);
            return 1; // sucesso
        }
        atual = atual->proximo;
    }

    return 0; // livro não encontrado
}


int alterar_quantidade(long isbn, int nova_quantidade) {
    if (nova_quantidade <= 0) return -1; // quantidade inválida

    NoLivro *atual = inicio_livros;

    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {

            int emprestados = atual->dados.quantidade_total - atual->dados.quantidade_disponivel;

            if (nova_quantidade < emprestados)
                return -1; // não pode ser menor que os emprestados

            // ajusta quantidade disponível proporcionalmente
            int diferenca = nova_quantidade - atual->dados.quantidade_total;

            atual->dados.quantidade_total = nova_quantidade;
            atual->dados.quantidade_disponivel += diferenca;

            return 1; // sucesso
        }
        atual = atual->proximo;
    }

    return 0; // livro não encontrado
}


int verificar_disponibilidade(long isbn) {
    NoLivro *atual = inicio_livros;

    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {
            if (atual->dados.quantidade_disponivel > 0)
                return 1; // disponível
            else
                return 0; // indisponível
        }
        atual = atual->proximo;
    }

    return -1; // livro não encontrado
}


int reduzir_disponivel(long isbn) {
    NoLivro *atual = inicio_livros;

    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {

            if (atual->dados.quantidade_disponivel == 0)
                return -1; // nenhum exemplar disponível

            atual->dados.quantidade_disponivel--;
            return 1; // sucesso
        }
        atual = atual->proximo;
    }

    return 0; // livro não encontrado
}


int aumentar_disponivel(long isbn) {
    NoLivro *atual = inicio_livros;

    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {

            if (atual->dados.quantidade_disponivel == atual->dados.quantidade_total)
                return -1; // todos já estão disponíveis

            atual->dados.quantidade_disponivel++;
            return 1; // sucesso
        }
        atual = atual->proximo;
    }

    return 0; // livro não encontrado
}


int listar_livros() {
    NoLivro *atual = inicio_livros;

    if (atual == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return 0;
    }

    printf("\n=== LISTA DE LIVROS ===\n");

    while (atual != NULL) {
        printf("ISBN: %ld | Titulo: %s | Autor: %s | Ano: %d | Total: %d | Disponiveis: %d\n",
               atual->dados.isbn,
               atual->dados.titulo,
               atual->dados.autor,
               atual->dados.ano,
               atual->dados.quantidade_total,
               atual->dados.quantidade_disponivel);

        atual = atual->proximo;
    }

    printf("========================\n");

    return 1;
}


int excluir_livro(long isbn) {
    NoLivro *atual = inicio_livros;
    NoLivro *anterior = NULL;

    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {

            if (atual->dados.quantidade_disponivel != atual->dados.quantidade_total)
                return -2; // possui empréstimos ativos

            if (anterior == NULL) {
                inicio_livros = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            return 1; // sucesso
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return 0; // livro não encontrado
}


int liberar_livros(void) {
    NoLivro *atual = inicio_livros;

    while (atual != NULL) {
        NoLivro *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    inicio_livros = NULL;

    return 1; // memória liberada com sucesso
}
