#ifndef LIVROS_H
#define LIVROS_H

/**
 * @file livros.h
 * @brief Interface do módulo de gerenciamento de livros.
 *
 * Este módulo é responsável por cadastrar, buscar e gerenciar livros do acervo, incluindo 
 * controle de disponibilidade.  
 */

typedef struct livro Livro;


/**
 * @brief Carrega dados de livros no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados dos livros.
 * 
 * @pre O ponteiro 'arquivo' não pode ser nulo (NULL).
 * 
 * @return int
 * @retval 1 Dados carregados com sucesso.
 * @retval 0 Arquivo não existe ou está vazio (primeira inicialização).
 * @retval -1 Erro de leitura física no disco.
 * @retval -2 Ponteiro nulo.
 * @retval -3 Falha de alocação de memória.
 */
int carregar_livros(const char *arquivo);


/**
 * @brief Salva os dados de livros no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados dos livros.
 * 
 * @pre O ponteiro 'arquivo' não pode ser nulo (NULL).
 * 
 * @return int
 * @retval 1 Dados salvos com sucesso.
 * @retval -1 Erro ao criar ou abrir o arquivo no disco.
 * @retval -2 Ponteiro nulo.
 * @retval -3 Erro de escrita no disco.
 */
int salvar_livros(const char *arquivo);


/**
 * @brief Realiza o cadastro de um livro.
 * 
 * @param isbn Identificador único do livro.
 * @param titulo Título do livro.
 * @param autor Nome do autor do livro.
 * @param ano Ano de lançamento do livro.
 * @param quantidade Quantidade de exemplares do livro no acervo.
 * 
 * @pre Os ponteiros 'titulo' e 'autor' não podem ser nulos (NULL).
 * 
 * @note Não é permitido cadastrar dois livros com o mesmo ISBN.
 * 
 * @return int
 * @retval 1 Cadastro realizado com sucesso.
 * @retval 0 Livro já cadastrado.
 * @retval -1 Quantidade inválida (<= 0).
 * @retval -2 Falha de alocação de memória.
 * @retval -3 Ponteiros inválidos (titulo ou autor NULL).
 */
int cadastrar_livro(long isbn, char *titulo, char *autor, int ano, int quantidade);


/**
 * @brief Realiza a busca por um livro.
 * 
 * @param isbn Identificador único do livro.
 *
 * @return int
 * @retval 1 Livro encontrado.
 * @retval 0 Livro não encontrado.
 */
int buscar_livro(long isbn);


/**
 * @brief Retorna o título de um livro.
 *
 * @param isbn Identificador único do livro.
 * @param titulo Vetor que receberá título do livro.
 *
 * @pre O ponteiro 'titulo' não pode ser nulo (NULL).
 *
 * @return int
 * @retval 1 Título obtido com sucesso.
 * @retval 0 Livro não encontrado.
 * @retval -1 Ponteiro inválido.
 */
int obter_titulo_livro(long isbn, char* titulo);


/**
 * @brief Altera a quantidade total de exemplares de um livro no acervo.
 * 
 * @param isbn Identificador único do livro.
 * @param nova_quantidade Nova quantidade do livro.
 *
 * @return int
 * @retval 1 Alteração realizada com sucesso.
 * @retval 0 Livro não encontrado.
 * @retval -1 Quantidade inválida (<= 0 ou menor do que exemplares emprestados).
 */
int alterar_quantidade(long isbn, int nova_quantidade);


/**
 * @brief Verifica a disponibilidade para empréstimo de um livro no acervo.
 * @note Utilizada pelos módulos de empréstimos e reservas.
 *
 * @param isbn Identificador único do livro.
 *
 * @return int
 * @retval 1 Livro disponível para empréstimo.
 * @retval 0 Livro indisponível para empréstimo.
 * @retval -1 Livro não encontrado.
 */
int verificar_disponibilidade(long isbn);


/**
 * @brief Reduz a quantidade de exemplares disponíveis para empréstimo de um livro no acervo.
 * @note Utilizada pelo módulo de empréstimos.
 *
 * @param isbn Identificador único do livro.
 *
 * @return int
 * @retval 1 Redução realizada com sucesso.
 * @retval 0 Livro não encontrado.
 * @retval -1 Nenhum exemplar disponível para empréstimo.
 */
int reduzir_disponivel(long isbn);


/**
 * @brief Aumenta a quantidade de exemplares disponíveis para empréstimo de um livro no acervo.
 * @note Utilizada pelo módulo de empréstimos.
 *
 * @param isbn Identificador único do livro.
 *
 * @return int
 * @retval 1 Aumento realizado com sucesso.
 * @retval 0 Livro não encontrado.
 * @retval -1 Todos os exemplares já estão disponíveis.
 */
int aumentar_disponivel(long isbn);


/**
 * @brief Lista todos os livros cadastrados.
 * 
 * @note Imprime os resultados via printf.
 * 
 * @return int
 * @retval 1 Listagem realizada com sucesso.
 * @retval 0 Nenhum livro cadastrado.
 */
int listar_livros();


/**
 * @brief Exclui um livro.
 * 
 * @param isbn Identificador único do livro.
 *
 * @return int
 * @retval 1 Livro excluído com sucesso.
 * @retval 0 Livro não encontrado.
 * @retval -2 Livro possui empréstimos ativos.
 */
int excluir_livro(long isbn);


/**
 * @brief Libera toda a memória alocada para os livros.
 * 
 * @return int
 * @retval 1 Memória liberada com sucesso.
 */
int liberar_livros(void);


#endif
