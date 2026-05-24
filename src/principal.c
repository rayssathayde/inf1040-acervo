#include <stdio.h>
#include <stdlib.h>
#include "alunos.h"
#include "livros.h"
#include "emprestimos.h"
#include "reservas.h"

void iniciar_dados();

void carregar_dados(const char* nome,const char* arq, int(*func)(const char*));

void salvar_dados();

void salvar_um_dado(const char* nome,const char* arq, int(*func)(const char*));

void exibir_opcoes();

int main(void){
    int input;
    iniciar_dados();
    exibir_opcoes();
    scanf("%d", &input);
    while (input > 0){
        scanf("%d", &input);
    }
    salvar_dados();
    return;
}

void carregar_dados(const char* nome,const char* arq, int(*func)(const char*)){
    int retorno;
    retorno = func(arq);
    if (retorno == 1)
        printf("Dados de %s carregados com sucesso.\n", nome);
    else{
        if (retorno == 0)
            printf("Dados de %s não encontrados, inicializando sistema vazio.\n", nome);
        else
            printf("Erro ao carregar os dados de %s.\n", nome);
    }
}

void iniciar_dados(){
    carregar_dados("alunos", "alunos.txt", carregar_alunos);
    carregar_dados("livros", "livros.txt", carregar_livros);
    carregar_dados("emprestimos", "emprestimos.txt", carregar_emprestimos);
    carregar_dados("reservas", "reservas.txt", carregar_reservas);
}

void salvar_todos_dados(){
    salvar_dado("alunos", "alunos.txt", carregar_alunos);
    salvar_dado("livros", "livros.txt", carregar_livros);
    salvar_dado("emprestimos", "emprestimos.txt", carregar_emprestimos);
    salvar_dado("reservas", "reservas.txt", carregar_reservas);
}

void salvar_dado(const char* nome,const char* arq, int(*func)(const char*)){
    int retorno;
    retorno = func(arq);
    if (retorno == 1)
        printf("Dados de %s salvos com sucesso.\n", nome);
    else
        printf("Erro ao salvar os dados de %s.\n", nome);
}

void exibir_opcoes(){
    printf("Seja bem vindo ao sistema Arcevo.\n"
        "Digite 1 para cadastrar um aluno no sistema\n"
        "Digite 2 para procurar pelo nome de um aluno no sistema usando sua matricula\n"
        "Digite 3 para visualizar todos os alunos no sistema\n"
        "Digite 4 para excluir um aluno do sistema\n\n"
        "Digite 5 para cadastrar um livro no sistema\n"
        "Digite 6 para encontrar o titulo de um livro no sistema com o seu ISBN\n"
        "Digite 7 para visualizar todos os livros no sistema\n"
        "Digite 8 para alterar a quantidade total de exemplares de um livro\n"
        "Digite 9 para verificar se um ha um exemplar de um livro disponivel para empréstimo\n"
        "Digite 10 para excluir um livro do sistema.\n\n"
        "Digite 11 para registrar o emprestimo de um livro para um aluno\n"
        "Digite 12 para registrar a devolucao de um livro por um aluno\n"
        "Digite 13 para visualizar todos os emprestimos atuais de um livro\n"
        "Digite 14 para visualizar todos os emprestimos atuais de um aluno\n"
        "Digite 15 para verificar se um usuario tem empréstimos ativos\n"
        "Digite 16 para verificar se ha exemplares de um livro emprestados\n\n"
        "Digite 17 para registar a reserva de um livro para um aluno\n"
        "Dgite 18 para cancelar a reserva de um livro por um aluno\n"
        "Digite 19 para visualizar a fila de reserva de um livro\n"
        "Digite 20 para visualizar todos os livros reservados por um aluno\n"
        "Digite 21 para verificar o próximo na fila de reserva de um livro.\n\n"
        "Caso queira encerrar o sistema, digite 0\n");
}