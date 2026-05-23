#include <string.h>
#include "alunos.h"

// matricula na base: 202410001
// matricula nao existe na base: 202820001

int buscar_aluno(int matricula) {
    if (matricula == 202410001) return 1; // aluno encontrado
    return 0; // aluno nao encontrado
}


int obter_nome_aluno(int matricula, char *nome) {
    if (matricula == 202410001) {
        strcpy(nome, "Ana Silva"); // nome copiado para vetor
        return 1; // nome obtido com sucesso
    }
    return 0; // aluno nao encontrado
}