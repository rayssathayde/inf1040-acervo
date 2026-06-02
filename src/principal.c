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

void limpar_modulos();

void limpar_um_modulo(const char* nome, int(*func)());

int main(void){
    int input, output;
    iniciar_dados();
    exibir_opcoes();
    printf("Opcao:");
    scanf("%d", &input);
    while (input > 0){
        if (input == 1){
            exibir_opcoes();
        }
        else if (input == 2){
            int matricula;
            char nome[100];
            char curso[100];
            printf("Matricula:");
            scanf("%d", &matricula);
            getchar();
            printf("Nome:");
            fgets(nome, 100, stdin);
            printf("Curso:");
            fgets(curso, 100, stdin);
            output = cadastrar_aluno(matricula, nome, curso);
            if (output == 1)
                printf("Cadastro com sucesso.\n");
            else if (output == 0)
                printf("Aluno ja esta no sistema.\n");
            else
                printf("Matricula invalida.\n");
        }
        else if (input == 3){
            long isbn; 
            char titulo[100], autor[100]; 
            int ano, quantidade;
            printf("ISBN: "); 
            scanf("%ld", &isbn); 
            getchar();
            printf("Titulo: "); 
            fgets(titulo, 100, stdin);
            printf("Autor: "); 
            fgets(autor, 100, stdin);
            printf("Ano: "); 
            scanf("%d", &ano);
            printf("Quantidade: "); 
            scanf("%d", &quantidade);
            output = cadastrar_livro(isbn, titulo, autor, ano, quantidade);
            if (output == 1)
                printf("Cadastro com sucesso.\n");
            else if (output == 0)
                printf("Livro ja esta no sistema.\n");
            else
                printf("Quantidade de livros invalida. A quantidade deve ser maior que zero.\n");
        }
        else if (input == 4){
            int matricula;
            long isbn;
            printf("Matricula:");
            scanf("%d", &matricula);
            printf("ISBN:");
            scanf("%ld", &isbn);
            output = emprestar_livro(isbn, matricula);
            if (output == 0){
                printf("Livro esgotado. E possivel reservar o livro digitando 6.\n");
            }
            else if(output == -1)
                printf("Livro nao encontrado.\n");
            else if(output == -2)
                printf("Aluno nao encontrado.\n");
            else if(output == -3)
                printf("Aluno ja possui esse livro emprestado.\n");
            else
                printf("Emprestimo registrado com sucesso.\n");
        }
        else if (input == 5){
            int matricula;
            long isbn;
            printf("Matricula:");
            scanf("%d", &matricula);
            printf("ISBN:");
            scanf("%ld", &isbn);
            output = devolver_livro(isbn, matricula);
            if (output == 1){
                printf("Devolucao do emprestimo registrada com sucesso.\n");
                output = proxima_reserva(isbn, &matricula);
                if (output == 1){
                    char nome[100];
                    obter_nome_aluno(matricula, nome);
                    printf("Proximo na fila:%s\n", nome);
                }
                else if (output == 0)
                    printf("Nao ha reservas para esse livro.\n");
                else
                    printf("Livro nao encontrado\n");
            }
            else if (output == 0)
                printf("Emprestimo nao encontrado.\n");
            else if (output == -1)
                printf("Livro nao encontrado.\n");
            else 
                printf("Aluno nao encontrado.\n");
            
        }
        else if (input == 6){
            int matricula;
            long isbn;
            printf("Matricula:");
            scanf("%d", &matricula);
            printf("ISBN:");
            scanf("%ld", &isbn);
            output = verificar_emprestimo(isbn, matricula);
            if(output == 0){
                output = criar_reserva(isbn, matricula);
                if (output == 1)
                    printf("Reserva realizada com sucesso\n");
                else if (output == 0)
                    printf("Livro disponivel para emprestimo. Caso deseje fazer o emprestimo, digite 4.\n");
                else if (output == -1)
                    printf("Livro nao encontrado.\n");
                else if (output == -2)
                    printf("Aluno nao encontrado.\n");
                else
                    printf("Aluno ja reservou esse livro.\n");
            }
            else if (output == 1)
                printf("Aluno ja possui esse livro emprestado.\n");
            else if (output == -1)
                printf("Livro nao encontrado.\n");
            else
                printf("Aluno nao encontrado.\n");
        }
        else if (input == 7){
            int matricula;
            long isbn;
            printf("Matricula:");
            scanf("%d", &matricula);
            printf("ISBN:");
            scanf("%ld", &isbn);
            output = cancelar_reserva(isbn, matricula);
            if (output == 1)
                printf("reserva cancelada com sucesso\n");
            else if (output == 0)
                printf("Reserva nao encontrada\n");
            else if (output == -1)
                printf("Livro nao encontrado.\n");
            else
                printf("Aluno nao encontrado\n");              
        }
        else if (input == 8){
            if (listar_alunos() == 0)
                printf("Nenhum aluno cadastrado.\n");
        }
        else if (input == 9){
            if (listar_livros()== 0)
                printf("Nenhum livro cadastrado.\n");
        }
        else if (input == 10){
            int matricula;
            printf("Matricula:");
            scanf("%d", &matricula);
            output = listar_emprestimos_aluno(matricula);
            if (output == 0)
                printf("Aluno nao possui emprestimos\n");
            else if (output == -1)
                printf("Aluno nao encontrado.\n");
        }
        else if (input == 11){
            long isbn;
            printf("ISBN:");
            scanf("%ld", &isbn);
            output = listar_emprestimos_livro(isbn);
            if (output == 0)
                printf("Livro nao possui emprestimos\n");
            else if (output == 0)
                printf("Livro nao encontrado\n");
        }
        else if (input == 12){
            int matricula;
            printf("Matricula:");
            scanf("%d", &matricula);
            output = listar_reservas_aluno(matricula);
            if (output == 0)
                printf("Aluno nao possui reservas.\n");
            else if (output == -1)
                printf("Aluno nao encontrado.\n");
        }
        else if (input == 13){
            long isbn;
            printf("ISBN:");
            scanf("%ld", &isbn);
            output = listar_reservas_livro(isbn);
            if (output == 0)
                printf("Livro nao possui reservas\n");
            else if (output == 0)
                printf("Livro nao encontrado\n");

        }
        else if (input == 14){
            int matricula;
            printf("Matricula:");
            scanf("%d", &matricula);
            output = aluno_possui_emprestimo(matricula);
            if (output == 1)
                printf("Aluno nao pode ser excluido por ainda possuir livros emprestados\n");
            else if (output == -1)
                printf("Aluno nao encontrado\n");
            else{
                excluir_aluno(matricula);
                printf("Aluno excluido com sucesso\n");
            }
        }
        else if (input == 15){
            long isbn;
            printf("ISBN:");
            scanf("%ld", & isbn);
            output = excluir_livro(isbn);
            if (output == 1)
                printf("Livro excluido com sucesso.\n");
            else if (output == 0)
                printf("Livro nao encontrado.\n");
            else
                printf("Livro ainda possui exemplares emprestados.\n");
            
        }
        else if (input == 16){
            long isbn;
            int quantidade;
            printf("ISBN");
            scanf("%ld", &isbn);
            printf("Insira a nova quantidade total desse livro:");
            scanf("%d", &quantidade);
            output == alterar_quantidade(isbn, quantidade);
            if (output == 1)
                printf("Quantidade alterada com sucesso.\n");
            else if (output == 0)
                printf("Livro nao encontrado.\n");
            else 
                printf("Quantidade total menor que a quantidade de livros ja emprestados.\n");
        }
        else {
            printf("Input invalido, insira um valor valido.\n");
        }
        printf("Caso precise de ajuda, digite 1 para visualisar todas as opções\n"
        "Opcao:");
        scanf("%d", &input);
    }
    salvar_dados();
    limpar_modulos();
    return 0;
}

void carregar_dados(const char* nome,const char* arq, int(*func)(const char*)){
    int retorno;
    retorno = func(arq);
    if (retorno == 1)
        printf("Dados de %s carregados com sucesso.\n", nome);
    else{
        if (retorno == 0)
            printf("Dados de %s nao encontrados, inicializando sistema vazio.\n", nome);
        else
            printf("Erro ao carregar os dados de %s.\n", nome);
    }
}

void iniciar_dados(){
    carregar_dados("alunos", "data/alunos.txt", carregar_alunos);
    carregar_dados("livros", "data/livros.txt", carregar_livros);
    carregar_dados("emprestimos", "data/emprestimos.txt", carregar_emprestimos);
    carregar_dados("reservas", "data/reservas.txt", carregar_reservas);
}

void salvar_dados(){
    salvar_um_dado("alunos", "data/alunos.txt", salvar_alunos);
    salvar_um_dado("livros", "data/livros.txt", salvar_livros);
    salvar_um_dado("emprestimos", "data/emprestimos.txt", salvar_emprestimos);
    salvar_um_dado("reservas", "data/reservas.txt", salvar_reservas);
}

void salvar_um_dado(const char* nome,const char* arq, int(*func)(const char*)){
    int retorno;
    retorno = func(arq);
    if (retorno == 1)
        printf("Dados de %s salvos com sucesso.\n", nome);
    else
        printf("Erro ao salvar os dados de %s.\n", nome);
}

void limpar_modulos(){
    limpar_um_modulo("alunos", liberar_alunos);
    limpar_um_modulo("livros", liberar_livros);
    limpar_um_modulo("emprestimos", liberar_emprestimos);
    limpar_um_modulo("reservas", liberar_reservas);
}

void limpar_um_modulo(const char* nome, int(*func)()){
    int retorno; 
    retorno = func();
    if (retorno ==1)
        printf("Dados de %s liberados com sucesso.\n", nome);
    else
        printf("Erro ao liberar dados de %s.\n", nome);
}

void exibir_opcoes(){
    printf("===== Sistema Biblioteca ======\n"
    "1 - Exibir todas as opções\n"
    "2 - Cadastrar aluno\n"
    "3 - Cadastrar livro\n"
    "4 - Emprestar livro\n"
    "5 - Devolver livro\n"
    "6 - Criar reserva\n"
    "7 - Cancelar reserva\n"
    "8 - Listar alunos\n"
    "9 - Listar livros\n"
    "10 - Listar emprestimos de um aluno\n"
    "11 - Listar emprestimos de um livro\n"
    "12 - listar reservas de um aluno\n"
    "13 - Listar reservas de um livro\n"
    "14 - Excluir aluno\n"
    "15 - Excluir livro\n"
    "16 - Alterar quantidade livro\n"
    "0 - Sair\n");
}