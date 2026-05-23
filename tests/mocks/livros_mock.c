#include <string.h>
#include "livros.h"


// ISBN na base: 10341
// ISBN na base, mas livro indisponivel: 10342
// ISBN nao existe na base: 78304


int buscar_livro(int id_livro) {
    if (id_livro == 10341) return 1; // livro encontrado
    return 0; // livro nao encontrado
}


int obter_titulo_livro(int id_livro, char* titulo) {
    if (id_livro == 10341) {
        strcpy(titulo, "A Sombra do Vento"); // titulo copiado para vetor
        return 1; // titulo obtido com sucesso
    }
    return 0; // livro nao encontrado
}


int verificar_disponibilidade(int id_livro) {
    if (id_livro == 10341) return 1; // livro disponivel
    if (id_livro == 10342) return 0; // livro indisponivel
    return -1; // nao encontrado (mas buscar_livro já trata isso antes)
}


int reduzir_disponivel(int id_livro) {
    return 1; // reducao realizada com sucesso
}


int aumentar_disponivel(int id_livro) {
    return 1; // aumento realizado com sucesso
}