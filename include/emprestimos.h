#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

/**
 * @file emprestimos.h
 * @brief Interface do módulo de gerenciamento de empréstimos.
 *
 * Este módulo é responsável por gerenciar empréstimos e devoluções de livros.
 *
 * @details
 * Este módulo depende dos módulos de alunos e livros para validação
 * de dados e controle de disponibilidade.
 * 
 * @pre carregar_alunos() deve ser chamado antes de qualquer função deste módulo.
 * @pre carregar_livros() deve ser chamado antes de qualquer função deste módulo.
 * @pre carregar_emprestimos() deve ser chamado antes de qualquer outra função deste módulo.
 */

typedef struct emprestimo Emprestimo;


/**
 * @brief Carrega dados de empréstimos no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados dos empréstimos.
 * 
 * @pre O ponteiro 'arquivo' não pode ser nulo (NULL).
 * 
 * @return int
 * @retval 1 Dados carregados com sucesso.
 * @retval 0 Arquivo não existe ou está vazio (primeira inicialização).
 * @retval -1 Erro ao ler arquivo.
 * @retval -2 Erro de alocação (falta memória).
 */
int carregar_emprestimos(const char *arquivo);


/**
 * @brief Salva os dados de empréstimos no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados dos empréstimos.
 * 
 * @pre O ponteiro 'arquivo' não pode ser nulo (NULL).
 * 
 * @return int
 * @retval 1 Dados salvos com sucesso.
 * @retval -1 Erro ao escrever no arquivo.
 */
int salvar_emprestimos(const char *arquivo);


/**
 * @brief Realiza empréstimo de um livro para um aluno.
 * 
 * @param isbn Identificador único do livro.
 * @param matricula Identificador único do aluno.
 * 
 * @post Se retornou 1, quantidade_disponivel do livro foi reduzida em 1.
 * 
 * @note Um aluno não pode ter mais de um exemplar do mesmo livro.
 * 
 * @return int
 * @retval 1 Empréstimo realizado com sucesso.
 * @retval 0 Livro indisponível para empréstimo.
 * @retval -1 Livro não encontrado.
 * @retval -2 Aluno não encontrado.
 * @retval -3 Aluno já está com esse livro.
 * @retval -4 Erro de alocação, falta memória.
 */
int emprestar_livro(long isbn, int matricula);


/**
 * @brief Realiza devolução de um livro por um aluno.
 * 
 * @param isbn Identificador único do livro.
 * @param matricula Identificador único do aluno.
 * 
 * @post Se retornou 1, quantidade_disponivel do livro foi aumentada em 1.
 *
 * @return int
 * @retval 1 Devolução realizada com sucesso.
 * @retval 0 Empréstimo não encontrado.
 * @retval -1 Livro não encontrado.
 * @retval -2 Aluno não encontrado.
 */
int devolver_livro(long isbn, int matricula);


/**
 * @brief Lista todos os empréstimos de um livro.
 * 
 * @param isbn Identificador único do livro.
 * 
 * @note Imprime os resultados via printf.
 * 
 * @return int
 * @retval 1 Listagem realizada com sucesso.
 * @retval 0 Nenhum empréstimo encontrado.
 * @retval -1 Livro não encontrado.
 */
int listar_emprestimos_livro(long isbn); 


/**
 * @brief Lista todos os empréstimos de um aluno.
 * 
 * @param matricula Identificador único do aluno.
 * 
 * @note Imprime os resultados via printf.
 * 
 * @return int
 * @retval 1 Listagem realizada com sucesso.
 * @retval 0 Nenhum empréstimo encontrado.
 * @retval -1 Aluno não encontrado.
 */
int listar_emprestimos_aluno(int matricula); 


/**
 * @brief Verifica se o aluno possui algum empréstimo.
 * 
 * @param matricula Identificador único do aluno.
 *
 * @return int
 * @retval 1 Aluno possui empréstimo.
 * @retval 0 Aluno não possui empréstimo.
 * @retval -1 Aluno não encontrado.
 */
int aluno_possui_emprestimo(int matricula); 


/**
 * @brief Verifica se o livro está emprestado.
 * 
 * @param isbn Identificador único do livro.
 *
 * @return int
 * @retval 1 Livro está emprestado.
 * @retval 0 Livro não está emprestado.
 * @retval -1 Livro não encontrado.
 */
int livro_esta_emprestado(long isbn); 


/**
 * @brief Libera a memória alocada para a lista de empréstimos.
 * 
 * @return int
 * @retval 1 Memória liberada com sucesso.
 */
int liberar_emprestimos(void);


#endif
