#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void limpar_um_modulo(const char* nome, int(*func)(void));

void cadastrar_aluno_principal();

void cadastrar_livro_principal();

void emprestar_livro_principal();

void devolver_livro_principal();

void criar_reserva_principal();

void cancelar_reserva_principal();

void listar_emprestimos_aluno_principal();

void listar_emprestimos_livro_principal();

void listar_reservas_aluno_principal();

void listar_reservas_livro_principal();

void excluir_aluno_principal();

void excluir_livro_principal();

void alterar_quantidade_principal();

int main(void){
    int input;

    iniciar_dados();
    printf("\n");
    exibir_opcoes();
    printf("\n");

    printf("Opcao: ");
    scanf("%d", &input);
    printf("\n");
    
    while (input > 0){
        if (input == 1){
            exibir_opcoes();
        }
        else if (input == 2){
            cadastrar_aluno_principal();
        }

        else if (input == 3){
            cadastrar_livro_principal();
        }

        else if (input == 4){
            emprestar_livro_principal();
        }

        else if (input == 5){
            devolver_livro_principal();
        }
        else if (input == 6){
            criar_reserva_principal();
        }

        else if (input == 7){
            cancelar_reserva_principal();
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
            listar_emprestimos_aluno_principal();
        }
        else if (input == 11){
            listar_emprestimos_livro_principal();
        }

        else if (input == 12){
            listar_reservas_aluno_principal();
        }

        else if (input == 13){
            listar_reservas_livro_principal();
        }

        else if (input == 14){
            excluir_aluno_principal();
        }

        else if (input == 15){
            excluir_livro_principal();
        }

        else if (input == 16){
            alterar_quantidade_principal();
        }
        else {
            printf("Input invalido, insira um valor valido.\n");
        }
        printf("\n");
        printf("Caso precise de ajuda, digite 1 para visualisar todas as opcoes.\n"
        "Opcao: ");
        scanf("%d", &input);
    }

    printf("\n");
    salvar_dados();
    printf("\n");
    limpar_modulos();
    printf("\n");
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
            printf("Erro (%d) ao carregar %s\n", retorno, nome);
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
        printf("Erro (%d) ao salvar os dados de %s.\n", retorno, nome);
}

void limpar_modulos(){
    limpar_um_modulo("alunos", liberar_alunos);
    limpar_um_modulo("livros", liberar_livros);
    limpar_um_modulo("emprestimos", liberar_emprestimos);
    limpar_um_modulo("reservas", liberar_reservas);
}

void limpar_um_modulo(const char* nome, int(*func)(void)){
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
    "12 - Listar reservas de um aluno\n"
    "13 - Listar reservas de um livro\n"
    "14 - Excluir aluno\n"
    "15 - Excluir livro\n"
    "16 - Alterar quantidade livro\n"
    "0 - Sair\n");
}

void cadastrar_aluno_principal(){
    int matricula, output;
    char nome[100];
    char curso[100];
    printf("Matricula: ");
    scanf("%d", &matricula);
    getchar();
    printf("Nome: ");
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Curso: ");
    fgets(curso, 100, stdin);
    curso[strcspn(curso, "\n")] = '\0';
    output = cadastrar_aluno(matricula, nome, curso);
    if (output == 1)
        printf("Cadastro com sucesso.\n");
    else if (output == 0)
        printf("Aluno ja esta no sistema.\n");
    else
        printf("Matricula invalida.\n");
}

void cadastrar_livro_principal(){
    long isbn; 
    char titulo[100], autor[100]; 
    int ano, quantidade, output;
    printf("ISBN: "); 
    scanf("%ld", &isbn); 
    getchar();
    printf("Titulo: "); 
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';
    printf("Autor: "); 
    fgets(autor, 100, stdin);
    autor[strcspn(autor, "\n")] = '\0';
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

void emprestar_livro_principal(){
    int matricula, output;
    long isbn;
    printf("Matricula: ");
    scanf("%d", &matricula);
    printf("ISBN: ");
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

void devolver_livro_principal(){
    int matricula, output;
    long isbn;
    printf("Matricula: ");
    scanf("%d", &matricula);

    printf("ISBN: ");
    scanf("%ld", &isbn);

    output = devolver_livro(isbn, matricula);
    if (output == 1){
        printf("Devolucao do emprestimo registrada com sucesso.\n");
        output = proxima_reserva(isbn, &matricula);
        if (output == 1){
            char nome[100];
            output = obter_nome_aluno(matricula, nome);
            if (output == 1)
                printf("Proximo na fila: %s\n", nome);
            else 
                printf("Erro interno ao obter proximo da fila.\n");
        }
        else if (output == 0)
            printf("Nao ha reservas para esse livro.\n");
        else
            printf("Livro nao encontrado.\n");
    }
    else if (output == 0)
        printf("Emprestimo nao encontrado.\n");
    else if (output == -1)
        printf("Livro nao encontrado.\n");
    else 
        printf("Aluno nao encontrado.\n");
            
}

void criar_reserva_principal(){
    int matricula, output;
    long isbn;

    printf("Matricula: ");
    scanf("%d", &matricula);

    printf("ISBN: ");
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

void cancelar_reserva_principal(){
    int matricula, output;
    long isbn;

    printf("Matricula: ");
    scanf("%d", &matricula);

    printf("ISBN: ");
    scanf("%ld", &isbn);

    output = cancelar_reserva(isbn, matricula);
    if (output == 1)
        printf("Reserva cancelada com sucesso.\n");
    else if (output == 0)
        printf("Reserva nao encontrada.\n");
    else if (output == -1)
        printf("Livro nao encontrado.\n");
    else
        printf("Aluno nao encontrado.\n");              
}

void listar_emprestimos_aluno_principal(){
    int matricula, output;

    printf("Matricula: ");
    scanf("%d", &matricula);

    output = listar_emprestimos_aluno(matricula);
    if (output == 0)
        printf("Aluno nao possui emprestimos.\n");
    else if (output == -1)
        printf("Aluno nao encontrado.\n");
}

void listar_emprestimos_livro_principal(){
    long isbn;
    int output;
    printf("ISBN: ");
    scanf("%ld", &isbn);
    output = listar_emprestimos_livro(isbn);
    if (output == 0)
        printf("Livro nao possui emprestimos.\n");
    else if (output == -1)
        printf("Livro nao encontrado.\n");
}

void listar_reservas_aluno_principal(){
    int matricula, output;
    printf("Matricula: ");
    scanf("%d", &matricula);
    output = listar_reservas_aluno(matricula);
    if (output == 0)
        printf("Aluno nao possui reservas.\n");
    else if (output == -1)
        printf("Aluno nao encontrado.\n");
}

void listar_reservas_livro_principal(){
    long isbn;
    int output;
    printf("ISBN: ");
    scanf("%ld", &isbn);
    output = listar_reservas_livro(isbn);
    if (output == 0)
        printf("Livro nao possui reservas.\n");
    else if (output == -1)
        printf("Livro nao encontrado.\n");
}

void excluir_aluno_principal(){
    int matricula, output;
    printf("Matricula: ");
    scanf("%d", &matricula);
    output = aluno_possui_emprestimo(matricula);
    if (output == 1)
        printf("Aluno nao pode ser excluido por ainda possuir livros emprestados.\n");
    else if (output == -1)
        printf("Aluno nao encontrado.\n");
    else {
        int r = excluir_aluno(matricula);

        if (r == 1) {
            cancelar_reservas_aluno(matricula);
            printf("Aluno excluido com sucesso.\n");
        }
        else if (r == 0) {
            printf("Aluno nao encontrado.\n");
        }
        else {
            printf("Matricula invalida.\n");
        }
    }
}

void excluir_livro_principal(){
    long isbn;
    int output;

    printf("ISBN: ");
    scanf("%ld", & isbn);

    output = excluir_livro(isbn);
    if (output == 1) {
        cancelar_reservas_livro(isbn);
        printf("Livro excluido com sucesso.\n");
    }
    else if (output == 0)
        printf("Livro nao encontrado.\n");
    else
        printf("Livro ainda possui exemplares emprestados.\n");
            
}

void alterar_quantidade_principal(){
    long isbn;
    int quantidade, output;

    printf("ISBN: ");
    scanf("%ld", &isbn);

    printf("Insira a nova quantidade total desse livro: ");
    scanf("%d", &quantidade);

    output = alterar_quantidade(isbn, quantidade);
    if (output == 1)
        printf("Quantidade alterada com sucesso.\n");
    else if (output == 0)
        printf("Livro nao encontrado.\n");
    else 
        printf("Quantidade total menor que a quantidade de livros ja emprestados.\n");
}