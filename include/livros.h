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
 * @return int
 * @retval 1 Dados carregados com sucesso.
 * @retval 0 Arquivo não existe ou está vazio (primeira inicialização).
 * @retval -1 Erro ao ler arquivo.
 */
int carregar_livros(const char *arquivo);


/**
 * @brief Salva os dados de livros no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados dos livros.
 * 
 * @return int
 * @retval 1 Dados salvos com sucesso.
 * @retval -1 Erro ao escrever no arquivo.
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
 * @return int
 * @retval 1 Cadastro realizado com sucesso.
 * @retval 0 Livro já cadastrado.
 * @retval -1 Quantidade inválida (<= 0).
 */
int cadastrar_livro(int isbn, char *titulo, char *autor, int ano, int quantidade);


/**
 * @brief Realiza a busca por um livro.
 * 
 * @param id_livro Identificador único do livro.
 *
 * @return Ponteiro para o livro ou NULL se não encontrado.
 */
const Livro* buscar_livro(int id_livro);


/**
 * @brief Retorna o título de um livro.
 *
 * @param l Ponteiro para o livro.
 *
 * @return Título do livro.
 */
const char* obter_titulo_livro(const Livro *l);


/**
 * @brief Altera a quantidade total de exemplares de um livro no acervo.
 * 
 * @param id_livro Identificador único do livro.
 * @param nova_quantidade Nova quantidade do livro.
 *
 * @return int
 * @retval 1 Alteração realizada com sucesso.
 * @retval 0 Livro não encontrado.
 * @retval -1 Quantidade inválida (menor do que exemplares emprestados).
 */
int alterar_quantidade(int id_livro, int nova_quantidade);


/**
 * @brief Verifica a disponibilidade para empréstimo de um livro no acervo.
 * @note Utilizada pelos módulos de empréstimos e reservas.
 *
 * @param id_livro Identificador único do livro.
 *
 * @return int
 * @retval 1 Livro disponível para empréstimo.
 * @retval 0 Livro indisponível para empréstimo.
 * @retval -1 Livro não encontrado.
 */
int verificar_disponibilidade(int id_livro);


/**
 * @brief Reduz a quantidade de exemplares disponíveis para empréstimo de um livro no acervo.
 * @note Utilizada pelo módulo de empréstimos.
 *
 * @param id_livro Identificador único do livro.
 *
 * @return int
 * @retval 1 Redução realizada com sucesso.
 * @retval 0 Livro não encontrado. 
 * @retval -1 Quantidade de exemplares já é 0.
 */
int reduzir_disponivel(int id_livro);


/**
 * @brief Aumenta a quantidade de exemplares disponíveis para empréstimo de um livro no acervo.
 * @note Utilizada pelo módulo de empréstimos.
 *
 * @param id_livro Identificador único do livro.
 *
 * @return int
 * @retval 1 Aumento realizado com sucesso.
 * @retval 0 Livro não encontrado.
 * @retval -1 Quantidade de exemplares já é a quantidade total de exemplares.
 */
int aumentar_disponivel(int id_livro);


/**
 * @brief Lista todos os livros cadastrados.
 */
void listar_livros(); 


/**
 * @brief Exclui um livro.
 * 
 * @param id_livro Identificador único do livro.
 *
 * @return int
 * @retval 1 Livro excluído com sucesso.
 * @retval 0 Livro não encontrado.
 */
int excluir_livro(int id_livro);


#endif
