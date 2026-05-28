#include "livros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define TAM_TITULO 101
#define TAM_AUTOR 101
#define CAPACIDADE_INICIAL 10

struct livro {
    long isbn;
    char titulo[TAM_TITULO];
    char autor[TAM_AUTOR];
    int ano;
    int quantidade_total;
    int quantidade_disponivel;
};

static Livro *livros = NULL;
static int quantidade_livros = 0;
static int capacidade_livros = 0;

static void copiar_string(char *destino, const char *origem, size_t tamanho_destino) {
    if (tamanho_destino == 0) {
        return;
    }

    if (origem == NULL) {
        destino[0] = '\0';
        return;
    }

    strncpy(destino, origem, tamanho_destino - 1);
    destino[tamanho_destino - 1] = '\0';
}

static int linha_em_branco(const char *linha) {
    int i;

    if (linha == NULL) {
        return 1;
    }

    for (i = 0; linha[i] != '\0'; i++) {
        if (linha[i] != ' ' && linha[i] != '\t' && linha[i] != '\n' && linha[i] != '\r') {
            return 0;
        }
    }

    return 1;
}

static int encontrar_indice_livro(long isbn) {
    int i;

    for (i = 0; i < quantidade_livros; i++) {
        if (livros[i].isbn == isbn) {
            return i;
        }
    }

    return -1;
}

static int encontrar_indice_no_vetor(Livro *vetor, int tamanho, long isbn) {
    int i;

    for (i = 0; i < tamanho; i++) {
        if (vetor[i].isbn == isbn) {
            return i;
        }
    }

    return -1;
}

static int garantir_capacidade(int nova_quantidade) {
    Livro *novo_vetor;
    int nova_capacidade;

    if (nova_quantidade <= capacidade_livros) {
        return 1;
    }

    nova_capacidade = capacidade_livros == 0 ? CAPACIDADE_INICIAL : capacidade_livros;

    while (nova_capacidade < nova_quantidade) {
        nova_capacidade *= 2;
    }

    novo_vetor = (Livro *) realloc(livros, nova_capacidade * sizeof(Livro));
    if (novo_vetor == NULL) {
        return 0;
    }

    livros = novo_vetor;
    capacidade_livros = nova_capacidade;

    return 1;
}

static int garantir_capacidade_temporaria(Livro **vetor, int *capacidade, int nova_quantidade) {
    Livro *novo_vetor;
    int nova_capacidade;

    if (nova_quantidade <= *capacidade) {
        return 1;
    }

    nova_capacidade = *capacidade == 0 ? CAPACIDADE_INICIAL : *capacidade;

    while (nova_capacidade < nova_quantidade) {
        nova_capacidade *= 2;
    }

    novo_vetor = (Livro *) realloc(*vetor, nova_capacidade * sizeof(Livro));
    if (novo_vetor == NULL) {
        return 0;
    }

    *vetor = novo_vetor;
    *capacidade = nova_capacidade;

    return 1;
}

static int dados_livro_validos(long isbn, const char *titulo, const char *autor,
                               int quantidade_total, int quantidade_disponivel) {
    if (isbn <= 0) {
        return 0;
    }

    if (titulo == NULL || titulo[0] == '\0') {
        return 0;
    }

    if (autor == NULL || autor[0] == '\0') {
        return 0;
    }

    if (quantidade_total <= 0) {
        return 0;
    }

    if (quantidade_disponivel < 0 || quantidade_disponivel > quantidade_total) {
        return 0;
    }

    return 1;
}

int carregar_livros(const char *arquivo) {
    FILE *fp;
    Livro *livros_temporarios = NULL;
    int qtd_temporaria = 0;
    int capacidade_temporaria = 0;
    char linha[512];
    int encontrou_dados = 0;

    if (arquivo == NULL) {
        return -1;
    }

    errno = 0;
    fp = fopen(arquivo, "r");
    if (fp == NULL) {
        if (errno == ENOENT) {
            return 0;
        }
        return -1;
    }

    while (fgets(linha, sizeof(linha), fp) != NULL) {
        Livro livro_lido;
        char titulo[TAM_TITULO];
        char autor[TAM_AUTOR];
        char extra;
        int lidos;

        if (linha_em_branco(linha)) {
            continue;
        }

        encontrou_dados = 1;

        lidos = sscanf(linha, "%ld;%100[^;];%100[^;];%d;%d;%d %c",
                       &livro_lido.isbn,
                       titulo,
                       autor,
                       &livro_lido.ano,
                       &livro_lido.quantidade_total,
                       &livro_lido.quantidade_disponivel,
                       &extra);

        if (lidos != 6) {
            fclose(fp);
            free(livros_temporarios);
            return -1;
        }

        copiar_string(livro_lido.titulo, titulo, TAM_TITULO);
        copiar_string(livro_lido.autor, autor, TAM_AUTOR);

        if (!dados_livro_validos(livro_lido.isbn,
                                 livro_lido.titulo,
                                 livro_lido.autor,
                                 livro_lido.quantidade_total,
                                 livro_lido.quantidade_disponivel)) {
            fclose(fp);
            free(livros_temporarios);
            return -1;
        }

        if (encontrar_indice_no_vetor(livros_temporarios, qtd_temporaria, livro_lido.isbn) != -1) {
            fclose(fp);
            free(livros_temporarios);
            return -1;
        }

        if (!garantir_capacidade_temporaria(&livros_temporarios, &capacidade_temporaria, qtd_temporaria + 1)) {
            fclose(fp);
            free(livros_temporarios);
            return -1;
        }

        livros_temporarios[qtd_temporaria] = livro_lido;
        qtd_temporaria++;
    }

    if (ferror(fp)) {
        fclose(fp);
        free(livros_temporarios);
        return -1;
    }

    if (fclose(fp) != 0) {
        free(livros_temporarios);
        return -1;
    }

    free(livros);
    livros = livros_temporarios;
    quantidade_livros = qtd_temporaria;
    capacidade_livros = capacidade_temporaria;

    if (!encontrou_dados) {
        return 0;
    }

    return 1;
}

int salvar_livros(const char *arquivo) {
    FILE *fp;
    int i;

    if (arquivo == NULL) {
        return -1;
    }

    fp = fopen(arquivo, "w");
    if (fp == NULL) {
        return -1;
    }

    for (i = 0; i < quantidade_livros; i++) {
        if (fprintf(fp, "%ld;%s;%s;%d;%d;%d\n",
                    livros[i].isbn,
                    livros[i].titulo,
                    livros[i].autor,
                    livros[i].ano,
                    livros[i].quantidade_total,
                    livros[i].quantidade_disponivel) < 0) {
            fclose(fp);
            return -1;
        }
    }

    if (fclose(fp) != 0) {
        return -1;
    }

    return 1;
}

int cadastrar_livro(long isbn, char *titulo, char *autor, int ano, int quantidade) {
    Livro novo_livro;

    if (quantidade <= 0) {
        return -1;
    }

    if (isbn <= 0 || titulo == NULL || titulo[0] == '\0' || autor == NULL || autor[0] == '\0') {
        return -1;
    }

    if (buscar_livro(isbn)) {
        return 0;
    }

    if (!garantir_capacidade(quantidade_livros + 1)) {
        return -1;
    }

    novo_livro.isbn = isbn;
    copiar_string(novo_livro.titulo, titulo, TAM_TITULO);
    copiar_string(novo_livro.autor, autor, TAM_AUTOR);
    novo_livro.ano = ano;
    novo_livro.quantidade_total = quantidade;
    novo_livro.quantidade_disponivel = quantidade;

    livros[quantidade_livros] = novo_livro;
    quantidade_livros++;

    return 1;
}

int buscar_livro(long isbn) {
    return encontrar_indice_livro(isbn) != -1 ? 1 : 0;
}

int obter_titulo_livro(long isbn, char *titulo) {
    int indice;

    if (titulo == NULL) {
        return 0;
    }

    indice = encontrar_indice_livro(isbn);
    if (indice == -1) {
        return 0;
    }

    strcpy(titulo, livros[indice].titulo);
    return 1;
}

int alterar_quantidade(long isbn, int nova_quantidade) {
    int indice;
    int quantidade_emprestada;

    indice = encontrar_indice_livro(isbn);
    if (indice == -1) {
        return 0;
    }

    quantidade_emprestada = livros[indice].quantidade_total - livros[indice].quantidade_disponivel;

    if (nova_quantidade <= 0 || nova_quantidade < quantidade_emprestada) {
        return -1;
    }

    livros[indice].quantidade_total = nova_quantidade;
    livros[indice].quantidade_disponivel = nova_quantidade - quantidade_emprestada;

    return 1;
}

int verificar_disponibilidade(long isbn) {
    int indice;

    indice = encontrar_indice_livro(isbn);
    if (indice == -1) {
        return -1;
    }

    return livros[indice].quantidade_disponivel > 0 ? 1 : 0;
}

int reduzir_disponivel(long isbn) {
    int indice;

    indice = encontrar_indice_livro(isbn);
    if (indice == -1) {
        return 0;
    }

    if (livros[indice].quantidade_disponivel <= 0) {
        return -1;
    }

    livros[indice].quantidade_disponivel--;
    return 1;
}

int aumentar_disponivel(long isbn) {
    int indice;

    indice = encontrar_indice_livro(isbn);
    if (indice == -1) {
        return 0;
    }

    if (livros[indice].quantidade_disponivel >= livros[indice].quantidade_total) {
        return -1;
    }

    livros[indice].quantidade_disponivel++;
    return 1;
}

int listar_livros() {
    int i;

    if (quantidade_livros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return 0;
    }

    printf("==================== LISTA DE LIVROS ====================\n");

    for (i = 0; i < quantidade_livros; i++) {
        printf("ISBN: %ld\n", livros[i].isbn);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);
        printf("Ano: %d\n", livros[i].ano);
        printf("Quantidade total: %d\n", livros[i].quantidade_total);
        printf("Quantidade disponivel: %d\n", livros[i].quantidade_disponivel);
        printf("----------------------------------------------------------\n");
    }

    return 1;
}

int excluir_livro(long isbn) {
    int indice;
    int i;

    indice = encontrar_indice_livro(isbn);
    if (indice == -1) {
        return 0;
    }

    if (livros[indice].quantidade_disponivel < livros[indice].quantidade_total) {
        printf("Livro nao pode ser excluido, pois possui exemplar emprestado.\n");
        return 0;
    }

    for (i = indice; i < quantidade_livros - 1; i++) {
        livros[i] = livros[i + 1];
    }

    quantidade_livros--;

    return 1;
}
