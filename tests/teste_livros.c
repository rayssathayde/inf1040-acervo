#include <stdio.h>
#include <string.h>

#include "livros.h"
#include "teste_utils.h"

void testar_cadastrar_livro() {
    liberar_livros(); // limpa estado
    int caso_1 = cadastrar_livro(1001, "Livro A", "Autor A", 2020, 5);
    checar(caso_1 == 1, "cadastrar_livro: cadastro valido");
    int caso_2 = cadastrar_livro(1001, "Livro A", "Autor A", 2020, 5);
    checar(caso_2 == 0, "cadastrar_livro: livro ja cadastrado");
    int caso_3 = cadastrar_livro(1002, "Livro B", "Autor B", 2021, 0);
    checar(caso_3 == -1, "cadastrar_livro: quantidade invalida");
    int caso_4 = cadastrar_livro(1003, NULL, "Autor C", 2022, 3);
    checar(caso_4 == -3, "cadastrar_livro: ponteiros invalidos");
    int caso_5 = cadastrar_livro(1004, "Livro D", NULL, 2022, 3);
    checar(caso_5 == -3, "cadastrar_livro: autor nulo");
}

void testar_buscar_livro() {
    liberar_livros();
    cadastrar_livro(2001, "Livro X", "Autor X", 2019, 2);
    int caso_1 = buscar_livro(2001);
    checar(caso_1 == 1, "buscar_livro: livro encontrado");
    int caso_2 = buscar_livro(9999);
    checar(caso_2 == 0, "buscar_livro: livro nao encontrado");
}

void testar_obter_titulo_livro() {
    liberar_livros();
    cadastrar_livro(3001, "Livro Y", "Autor Y", 2018, 4);
    char titulo[100];
    int caso_1 = obter_titulo_livro(3001, titulo);
    checar(caso_1 == 1 && strcmp(titulo, "Livro Y") == 0,
           "obter_titulo_livro: titulo obtido com sucesso");
    int caso_2 = obter_titulo_livro(9999, titulo);
    checar(caso_2 == 0, "obter_titulo_livro: livro nao encontrado");
    int caso_3 = obter_titulo_livro(3001, NULL);
    checar(caso_3 == -1, "obter_titulo_livro: ponteiro invalido");
}

void testar_verificar_disponibilidade() {
    liberar_livros();
    cadastrar_livro(4001, "Livro Z", "Autor Z", 2017, 1);
    int caso_1 = verificar_disponibilidade(4001);
    checar(caso_1 == 1, "verificar_disponibilidade: disponivel");
    reduzir_disponivel(4001);
    int caso_2 = verificar_disponibilidade(4001);
    checar(caso_2 == 0, "verificar_disponibilidade: indisponivel");
    int caso_3 = verificar_disponibilidade(9999);
    checar(caso_3 == -1, "verificar_disponibilidade: livro nao encontrado");
}

void testar_reduzir_aumentar() {
    liberar_livros();
    cadastrar_livro(5001, "Livro W", "Autor W", 2020, 1);
    int caso_1 = reduzir_disponivel(5001);
    checar(caso_1 == 1, "reduzir_disponivel: sucesso");
    int caso_2 = reduzir_disponivel(5001);
    checar(caso_2 == -1, "reduzir_disponivel: nenhum disponivel");
    int caso_3 = aumentar_disponivel(5001);
    checar(caso_3 == 1, "aumentar_disponivel: sucesso");
    int caso_4 = aumentar_disponivel(5001);
    checar(caso_4 == -1, "aumentar_disponivel: todos disponiveis");
}

void testar_alterar_quantidade() {
    liberar_livros();
    cadastrar_livro(6001, "Livro Q", "Autor Q", 2015, 5);
    reduzir_disponivel(6001); // 1 emprestado
    int caso_1 = alterar_quantidade(6001, 6);
    checar(caso_1 == 1, "alterar_quantidade: aumento valido");
    int caso_2 = alterar_quantidade(6001, 0);
    checar(caso_2 == -1, "alterar_quantidade: quantidade invalida");
    int caso_3 = alterar_quantidade(9999, 5);
    checar(caso_3 == 0, "alterar_quantidade: livro nao encontrado");
}

void testar_listar_livros() {
    liberar_livros();
    cadastrar_livro(7001, "Livro L", "Autor L", 2010, 2);
    int caso_1 = listar_livros();
    checar(caso_1 == 1, "listar_livros: lista impressa com sucesso");
}

void testar_excluir_livro() {
    liberar_livros();
    cadastrar_livro(8001, "Livro M", "Autor M", 2005, 2);
    int caso_1 = excluir_livro(8001);
    checar(caso_1 == 1, "excluir_livro: exclusao valida");
    int caso_2 = excluir_livro(8001);
    checar(caso_2 == 0, "excluir_livro: livro nao encontrado");
    cadastrar_livro(8002, "Livro N", "Autor N", 2006, 2);
    reduzir_disponivel(8002);
    int caso_3 = excluir_livro(8002);
    checar(caso_3 == -2, "excluir_livro: possui emprestimos");
}

void testar_carregar_salvar_livros() {
    liberar_livros();
    cadastrar_livro(9001, "Livro T", "Autor T", 2000, 3);
    int caso_1 = salvar_livros("data/teste_livros.txt");
    checar(caso_1 == 1, "salvar_livros: dados salvos com sucesso");
    liberar_livros();
    int caso_2 = carregar_livros("data/teste_livros.txt");
    checar(caso_2 == 1, "carregar_livros: dados carregados com sucesso");
    int caso_3 = buscar_livro(9001);
    checar(caso_3 == 1, "carregar_livros: dados recuperados corretamente");
    int caso_4 = carregar_livros("data/arquivo_inexistente.txt");
    checar(caso_4 == 0, "carregar_livros: arquivo inexistente");
    liberar_livros();
    remove("data/teste_livros.txt");
}

int main() {
    printf("\n--- TESTES DE: cadastrar_livro ---\n");
    testar_cadastrar_livro();

    printf("\n--- TESTES DE: buscar_livro ---\n");
    testar_buscar_livro();

    printf("\n--- TESTES DE: obter_titulo_livro ---\n");
    testar_obter_titulo_livro();

    printf("\n--- TESTES DE: verificar_disponibilidade ---\n");
    testar_verificar_disponibilidade();

    printf("\n--- TESTES DE: reduzir/aumentar_disponivel ---\n");
    testar_reduzir_aumentar();

    printf("\n--- TESTES DE: alterar_quantidade ---\n");
    testar_alterar_quantidade();

    printf("\n--- TESTES DE: listar_livros ---\n");
    testar_listar_livros();

    printf("\n--- TESTES DE: excluir_livro ---\n");
    testar_excluir_livro();

    printf("\n--- TESTES DE: carregar_livros e salvar_livros ---\n");
    testar_carregar_salvar_livros();

    return 0;
}
