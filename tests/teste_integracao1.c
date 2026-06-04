#include <stdio.h>

#include "alunos.h"
#include "livros.h"
#include "emprestimos.h"
#include "reservas.h"
#include "teste_utils.h"

void testar_fluxo_completo() {
    printf("\n--- TESTE INTEGRADO: fluxo biblioteca ---\n");

    liberar_alunos();
    liberar_livros();
    liberar_emprestimos();
    liberar_reservas();

    // alunos (matriculas válidas e usadas corretamente)
    cadastrar_aluno(2410001, "Ana Silva", "Computacao");
    cadastrar_aluno(2423575, "Bruno Lima", "Matematica");

    // livro com 1 exemplar
    cadastrar_livro(10342, "Livro Integrado", "Autor X", 2020, 1);

    // 1. emprestimo inicial (Ana)
    int caso_1 = emprestar_livro(10342, 2410001);
    checar(caso_1 == 1, "emprestimo inicial");

    // 2. tentar emprestar (Bruno) → sem disponibilidade
    int caso_2 = emprestar_livro(10342, 2423575);
    checar(caso_2 != 1, "emprestimo bloqueado (sem disponibilidade)");

    // 3. reserva (Bruno)
    int caso_3 = criar_reserva(10342, 2423575);
    checar(caso_3 == 1, "reserva criada");

    // 4. indisponível
    int caso_4 = verificar_disponibilidade(10342);
    checar(caso_4 == 0, "livro indisponivel");

    // 5. devolução (Ana)
    int caso_5 = devolver_livro(10342, 2410001);
    checar(caso_5 == 1, "devolucao realizada");

    // 6. próxima reserva (Bruno)
    int matricula;
    int caso_6 = proxima_reserva(10342, &matricula);
    checar(caso_6 == 1 && matricula == 2423575,
           "proxima reserva correta");

    liberar_alunos();
    liberar_livros();
    liberar_emprestimos();
    liberar_reservas();
}


int main() {
    testar_fluxo_completo();
    return 0;
}
