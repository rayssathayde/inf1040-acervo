#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alunos.h"
#include "livros.h"
#include "reservas.h"

struct reserva {
    long isbn;
    int matricula;
};

struct nolistareserva {
    Reserva dados;
    struct nolistareserva *proximo;
};
typedef struct nolistareserva NoListaReserva;

static NoListaReserva *inicio_fila = NULL;

int carregar_reservas(const char *arquivo) {
    if (arquivo == NULL) return -2; // ponteiro nulo
    
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) return 0; // arquivo não existe ou está vazio

    liberar_reservas();

    Reserva res;
    NoListaReserva *atual = NULL;
    
    while (fscanf(f, "%ld;%d", &res.isbn, &res.matricula) == 2) {
        NoListaReserva *novo = (NoListaReserva *)malloc(sizeof(NoListaReserva));
        if (novo == NULL) {
            fclose(f);
            liberar_reservas();
            return -3; // falha na alocação de memoria
        }
        novo->dados = res;
        novo->proximo = NULL;

        if (inicio_fila == NULL) {
            inicio_fila = novo;
        } else {
            atual->proximo = novo;
        }
        atual = novo;
    }

    if (!feof(f)) {
        fclose(f);
        liberar_reservas();
        return -1;
    }
    fclose(f);
    return (inicio_fila != NULL) ? 1 : 0;  // dados carregados com sucesso
}

int salvar_reservas(const char *arquivo) {
    if (arquivo == NULL) return -2; // ponteiro nulo

    FILE *f = fopen(arquivo, "w");
    if (f == NULL) return -1; // erro ao criar/abrir arquivo

    NoListaReserva *atual = inicio_fila;
    while (atual != NULL) {
        if (fprintf(f, "%ld;%d\n", atual->dados.isbn, atual->dados.matricula) < 0) {
            fclose(f);
            return -1; // erro ao escrever no arquivo
        }
        atual = atual->proximo;
    }

    fclose(f);
    return 1; // dados salvos com sucesso
}

int criar_reserva(long isbn, int matricula) {
    if (buscar_livro(isbn) == 0) return -1; // livro não encontrado
    if (buscar_aluno(matricula) != 1) return -2; // aluno não encontrado 

    if (verificar_disponibilidade(isbn) == 1) return 0; // livro disponível para empréstimo (não precisa reservar)

    NoListaReserva *atual = inicio_fila;
    while (atual != NULL) {
        if (atual->dados.isbn == isbn && atual->dados.matricula == matricula) {
            return -3; // aluno já reservou esse livro
        }
        atual = atual->proximo;
    }

    NoListaReserva *novo = (NoListaReserva *)malloc(sizeof(NoListaReserva));
    if (novo == NULL) return -4; // falha de alocação de memória
    
    novo->dados.isbn = isbn;
    novo->dados.matricula = matricula;
    novo->proximo = NULL;

    if (inicio_fila == NULL) {
        inicio_fila = novo;
    } else {
        atual = inicio_fila;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    return 1; // reserva realizada com sucesso
}

int cancelar_reserva(long isbn, int matricula) {
    if (buscar_livro(isbn) == 0) return -1; // livro não encontrado
    if (buscar_aluno(matricula) != 1) return -2;  // aluno não encontrado

    NoListaReserva *atual = inicio_fila;
    NoListaReserva *anterior = NULL;

    while (atual != NULL) {
        if (atual->dados.isbn == isbn && atual->dados.matricula == matricula) {
            if (anterior == NULL) {
                inicio_fila = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return 1; //  reserva cancelada com sucesso
        }
        anterior = atual;
        atual = atual->proximo;
    }

    return 0; // reserva não encontrada
}

int listar_reservas_livro(long isbn) {
    if (buscar_livro(isbn) == 0) return -1;  // livro não encontrado
    
    int encontrou = 0;
    int posicao_fila = 1;
    NoListaReserva *atual = inicio_fila;

    printf("\n=== FILA DE RESERVAS DO LIVRO (ISBN: %ld) ===\n", isbn);
    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {
            char nome[100] = "Nome Indisponivel";
            obter_nome_aluno(atual->dados.matricula, nome);
            
            printf("%dº Lugar -> Matricula: %d | Nome: %s\n", posicao_fila, atual->dados.matricula, nome);
            encontrou = 1;
            posicao_fila++;
        }
        atual = atual->proximo;
    }
    
    if (!encontrou) {
        printf("Nenhuma reserva encontrada para este livro.\n");
        return 0; // nenhuma reserva encontrarda
    }
    printf("================================================\n");
    return 1; // listagem realizada com sucesso
}

int listar_reservas_aluno(int matricula) {
    if (buscar_aluno(matricula) != 1) return -1; // aluno não encontrado

    int encontrou = 0;
    NoListaReserva *atual = inicio_fila;

    char nome[100] = "Desconhecido";
    obter_nome_aluno(matricula, nome);

    printf("\n=== RESERVAS DO ALUNO: %s (%d) ===\n", nome, matricula);
    while (atual != NULL) {
        if (atual->dados.matricula == matricula) {
            printf("- Livro ISBN: %ld\n", atual->dados.isbn);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    
    if (!encontrou) {
        printf("Nenhuma reserva encontrada para este aluno.\n");
        return 0; // nenhuma reserva encontrarda
    }
    printf("=================================================\n");
    return 1; // listagem realizada com sucesso
} 

int proxima_reserva(long isbn, int *matricula) {
    if (buscar_livro(isbn) == 0) return -1; //livro não encontrado
    if (matricula == NULL) return -2;  // matrícula inválida 

    NoListaReserva *atual = inicio_fila;
    while (atual != NULL) {
        if (atual->dados.isbn == isbn) {
            *matricula = atual->dados.matricula;
            return 1; // próxima reserva encontrada (matrícula preenchida)
        }
        atual = atual->proximo;
    }

    return 0; // não há reservas
}


int liberar_reservas(void) {
    NoListaReserva *atual = inicio_fila;
    while (atual != NULL) {
        NoListaReserva *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicio_fila = NULL;
    return 1;
}