#include <stdio.h>

#include "emprestimos.h"
#include "alunos.h"
#include "livros.h"
#include "teste_utils.h"



void testar_emprestar_livro() {
    liberar_emprestimos(); // limpa estado 
    int caso_1 = emprestar_livro(10341, 202410001); // livro existe e disponivel, aluno existe
    checar(caso_1 == 1, "emprestar_livro: emprestimo valido");
    int caso_2 = emprestar_livro(10342, 202410001); // livro existe mas indisponivel, aluno existe
    checar(caso_2 == 0, "emprestar_livro: livro indisponivel"); 
    int caso_3 = emprestar_livro(78304, 202410001); // livro nao existe, aluno existe
    checar(caso_3 == -1, "emprestar_livro: livro nao encontrado");
    int caso_4 = emprestar_livro(10341, 202820001); // livro existe e disponivel, aluno nao existe
    checar(caso_4 == -2, "emprestar_livro: aluno nao encontrado");
    emprestar_livro(10341, 202410001); // primeiro emprestimo
    int caso_5 = emprestar_livro(10341, 202410001);  // mesmo livro, mesmo aluno - aluno esta com esse livro
    checar(caso_5 == -3, "emprestar_livro: aluno ja possui esse livro");
}


void testar_devolver_livro() {
    liberar_emprestimos(); // limpa estado 
    emprestar_livro(10341, 202410001); // realizar o emprestimo
    int caso_1 = devolver_livro(10341, 202410001); // emprestimo existe 
    checar(caso_1 == 1, "devolver_livro: devolucao valida");
    int caso_2 = devolver_livro(10341, 202410001); // emprestimo nao existe 
    checar(caso_2 == 0, "devolver_livro: emprestimo nao encontrado");
    int caso_3 = devolver_livro(78304, 202410001); // livro nao existe 
    checar(caso_3 == -1, "devolver_livro: livro nao encontrado");
    int caso_4 = devolver_livro(10341, 202820001); // aluno nao existe 
    checar(caso_4 == -2, "devolver_livro: aluno nao encontrado");
}


void testar_listar_emprestimos_livro() {
    liberar_emprestimos(); // limpa estado
    emprestar_livro(10341, 202410001); // realizar o emprestimo
    int caso_1 = listar_emprestimos_livro(10341); // emprestimo existe para esse livro
    checar(caso_1 == 1, "listar_emprestimos_livro: lista impressa com sucesso");
    devolver_livro(10341, 202410001); 
    int caso_2 = listar_emprestimos_livro(10341); // emprestimo nao existe para esse livro
    checar(caso_2 == 0, "listar_emprestimos_livro: nenhum emprestimo encontrado");
    int caso_3 = listar_emprestimos_livro(78304); // livro nao encontrado
    checar(caso_3 == -1, "listar_emprestimos_livro: livro nao encontrado");
}


void testar_listar_emprestimos_aluno() {
    liberar_emprestimos(); // limpa estado 
    emprestar_livro(10341, 202410001); // realizar o emprestimo
    int caso_1 = listar_emprestimos_aluno(202410001); // emprestimo existe para esse aluno
    checar(caso_1 == 1, "listar_emprestimos_aluno: lista impressa com sucesso");
    devolver_livro(10341, 202410001); 
    int caso_2 = listar_emprestimos_aluno(202410001); // emprestimo nao existe para esse aluno
    checar(caso_2 == 0, "listar_emprestimos_aluno: nenhum emprestimo encontrado");
    int caso_3 = listar_emprestimos_aluno(202820001); // aluno nao encontrado
    checar(caso_3 == -1, "listar_emprestimos_aluno: aluno nao encontrado");
}


void testar_aluno_possui_emprestimo() {
    liberar_emprestimos(); // limpa estado
    emprestar_livro(10341, 202410001); // realizar o emprestimo
    int caso_1 = aluno_possui_emprestimo(202410001); // aluno possui emprestimo
    checar(caso_1 == 1, "aluno_possui_emprestimo: aluno possui emprestimo");
    devolver_livro(10341, 202410001); 
    int caso_2 = aluno_possui_emprestimo(202410001); // aluno nao possui emprestimo
    checar(caso_2 == 0, "aluno_possui_emprestimo: aluno nao possui emprestimo");
    int caso_3 = aluno_possui_emprestimo(202820001); // aluno nao encontrado
    checar(caso_3 == -1, "aluno_possui_emprestimo: aluno nao encontrado");
}


void testar_livro_esta_emprestado() {
    liberar_emprestimos(); // limpa estado
    emprestar_livro(10341, 202410001); // realizar o emprestimo
    int caso_1 = livro_esta_emprestado(10341); // livro esta emprestado
    checar(caso_1 == 1, "livro_esta_emprestado: livro esta emprestado");
    devolver_livro(10341, 202410001); 
    int caso_2 = livro_esta_emprestado(10341); // livro nao esta emprestado
    checar(caso_2 == 0, "livro_esta_emprestado: livro nao esta emprestado");
    int caso_3 = livro_esta_emprestado(78304); // livro nao encontrado
    checar(caso_3 == -1, "livro_esta_emprestado: livro nao encontrado");
}


void testar_carregar_salvar_emprestimos() {
    liberar_emprestimos(); // limpa estado
    emprestar_livro(10341, 202410001); // cria emprestimo na lista

    int caso_1 = salvar_emprestimos("data/teste_emprestimos.txt");
    checar(caso_1 == 1, "salvar_emprestimos: dados salvos com sucesso");

    liberar_emprestimos(); // limpa lista para testar o carregamento

    int caso_2 = carregar_emprestimos("data/teste_emprestimos.txt");
    checar(caso_2 == 1, "carregar_emprestimos: dados carregados com sucesso");

    int caso_3 = aluno_possui_emprestimo(202410001); // verifica se o dado voltou
    checar(caso_3 == 1, "carregar_emprestimos: dados recuperados corretamente");

    int caso_4 = carregar_emprestimos("data/arquivo_inexistente.txt");
    checar(caso_4 == 0, "carregar_emprestimos: arquivo inexistente");

    liberar_emprestimos();
    remove("data/teste_emprestimos.txt"); // remove arquivo temporario de teste
}



int main() {
    liberar_emprestimos(); // limpar estado
    printf("\n--- TESTES DE: emprestar_livro ---\n");
    testar_emprestar_livro();

    printf("\n--- TESTES DE: devolver_livro ---\n");
    testar_devolver_livro();

    printf("\n--- TESTES DE: listar_emprestimos_livro ---\n");
    testar_listar_emprestimos_livro();

    printf("\n--- TESTES DE: listar_emprestimos_aluno ---\n");
    testar_listar_emprestimos_aluno();

    printf("\n--- TESTES DE: aluno_possui_emprestimo ---\n");
    testar_aluno_possui_emprestimo();

    printf("\n--- TESTES DE: livro_esta_emprestado ---\n");
    testar_livro_esta_emprestado();

    printf("\n--- TESTES DE: carregar_emprestimos e salvar_emprestimos ---\n");
    testar_carregar_salvar_emprestimos();
    return 0;
}
