#include <stdio.h>
#include <stdlib.h>

#include "emprestimos.h"
#include "alunos.h"
#include "livros.h"


#define MAX_EMPRESTIMOS 1000

struct emprestimo {
    long isbn;
    int matricula;
};

static Emprestimo emprestimos[MAX_EMPRESTIMOS];
static int num_emprestimos = 0;


int emprestar_livro(long isbn, int matricula) {
    int livro = buscar_livro(isbn);
    int aluno = buscar_aluno(matricula);
   
    if (!livro) return -1; // livro nao encontrado
    if (!aluno) return -2; // aluno nao encontrado

    // verifica se aluno ja esta com esse livro
    for (int i = 0; i < num_emprestimos; i++) {
        if (emprestimos[i].isbn == isbn &&
            emprestimos[i].matricula == matricula) {
            return -3;
        }
    }

    int disponivel = verificar_disponibilidade(isbn);
    if (!disponivel) return 0; // livro indisponivel

    // realiza o emprestimo
    emprestimos[num_emprestimos].isbn = isbn;
    emprestimos[num_emprestimos].matricula = matricula;
    num_emprestimos++;

    reduzir_disponivel(isbn);
    return 1;
}


int devolver_livro(long isbn, int matricula) {
    int livro = buscar_livro(isbn);
    int aluno = buscar_aluno(matricula);

    if (!livro) return -1; // livro nao encontrado
    if (!aluno) return -2; // aluno nao encontrado

    // verifica se emprestimo existe
    for (int i = 0; i < num_emprestimos; i++) {
        if (emprestimos[i].isbn == isbn &&
            emprestimos[i].matricula == matricula) {
                // remove emprestimo 
                for (int j = i; j < num_emprestimos - 1; j++) {
                    emprestimos[j] = emprestimos[j + 1];
                }
                num_emprestimos--;
                aumentar_disponivel(isbn);
                return 1;
        }
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
    for (int i = 0; i < num_emprestimos; i++) {
        if (emprestimos[i].isbn == isbn) {
            char nome[50];
            obter_nome_aluno(emprestimos[i].matricula, nome);
            printf("%d - %s\n", emprestimos[i].matricula, nome);
            encontrou = 1;
        }
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
    for (int i = 0; i < num_emprestimos; i++) {
        if (emprestimos[i].matricula == matricula) {
            char titulo[100];
            obter_titulo_livro(emprestimos[i].isbn, titulo);
            printf("%ld - %s\n", emprestimos[i].isbn, titulo);
            encontrou = 1;
        }
    }
    if (encontrou) return 1;
    
    printf("Nenhum emprestimo encontrado!\n");
    return 0;
}


int aluno_possui_emprestimo(int matricula) {
    int aluno = buscar_aluno(matricula);
    if (!aluno) return -1; // aluno nao encontrado

    for (int i = 0; i < num_emprestimos; i++) {
        if (emprestimos[i].matricula == matricula) {
            return 1;
        }
    }
    return 0;
}


int livro_esta_emprestado(long isbn) {
    int livro = buscar_livro(isbn);
    if (!livro) return -1; // livro nao encontrado

    for (int i = 0; i < num_emprestimos; i++) {
        if (emprestimos[i].isbn == isbn) {
            return 1;
        }
    }
    return 0;
}