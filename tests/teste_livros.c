#include <stdio.h>
#include <string.h>

#include "../include/livros.h"

static void print_result(const char *desc, int res) {
	printf("%s: %d\n", desc, res);
}

int main(void) {
	char titulo[101];

	// tentar cadastrar
	print_result("cadastrar (esperado 1)", cadastrar_livro(12345L, "O Senhor dos Tests", "Autor X", 2020, 3));
	// cadastrar novamente -> já existe
	print_result("cadastrar repetido (esperado 0)", cadastrar_livro(12345L, "O Senhor dos Tests", "Autor X", 2020, 3));

	// buscar
	print_result("buscar existente (esperado 1)", buscar_livro(12345L));
	print_result("buscar inexistente (esperado 0)", buscar_livro(99999L));

	// obter título
	memset(titulo, 0, sizeof(titulo));
	print_result("obter_titulo (esperado 1)", obter_titulo_livro(12345L, titulo));
	printf("titulo obtido: %s\n", titulo);

	// alterar quantidade
	print_result("alterar_quantidade para 2 (esperado 1)", alterar_quantidade(12345L, 2));

	// disponibilidade
	print_result("verificar_disponibilidade (esperado 1)", verificar_disponibilidade(12345L));

	// reduzir disponibilidade duas vezes
	print_result("reduzir_disponivel #1 (esperado 1)", reduzir_disponivel(12345L));
	print_result("reduzir_disponivel #2 (esperado 1)", reduzir_disponivel(12345L));
	// agora disponibilidade deve ser 0
	print_result("reduzir_disponivel #3 (esperado -1)", reduzir_disponivel(12345L));

	// aumentar disponibilidade
	print_result("aumentar_disponivel #1 (esperado 1)", aumentar_disponivel(12345L));
	print_result("aumentar_disponivel #2 (esperado -1)", aumentar_disponivel(12345L));

	// tentar excluir (deve falhar enquanto emprestado)
	print_result("excluir_livro (esperado 0)", excluir_livro(12345L));

	// devolver todos os exemplares (ajustar para total)
	print_result("alterar_quantidade para 2 (restaurar) (esperado 1)", alterar_quantidade(12345L, 2));
	// aumentar disponivel até total
	print_result("aumentar_disponivel (esperado 1)", aumentar_disponivel(12345L));

	// agora pode excluir
	print_result("excluir_livro (esperado 1)", excluir_livro(12345L));

	// listar livros (nenhum cadastrado agora)
	print_result("listar_livros (esperado 0)", listar_livros());

	return 0;
}
