#ifndef ALUNOS_H
#define ALUNOS_H

/**
 * @file alunos.h
 * @brief Interface do módulo de gerenciamento de alunos.
 *
 * Este módulo é responsável por cadastrar, buscar e excluir alunos.
 *
 * @details
 * Este módulo é independente e atua como base para os módulos de 
 * empréstimos e reservas.
 * 
 * @pre carregar_alunos() deve ser chamado antes de qualquer função deste módulo.
 */

typedef struct aluno Aluno;


/**
 * @brief Carrega dados de alunos no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados dos alunos.
 * 
 * @return int
 * @retval 1 Dados carregados com sucesso.
 * @retval 0 Arquivo não existe ou está vazio (primeira inicialização).
 * @retval -1 Erro ao ler arquivo.
 * @retval -2 Ponteiro nulo.
 */
int carregar_alunos(const char *arquivo);


/**
 * @brief Salva os dados de alunos no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados dos alunos.
 * 
 * @return int
 * @retval 1 Dados salvos com sucesso.
 * @retval -1 Erro ao escrever no arquivo.
 * @retval -2 Ponteiro nulo.
 */
int salvar_alunos(const char *arquivo);


/**
 * @brief Realiza o cadastro de um aluno.
 * 
 * @param matricula Identificador único do aluno.
 * @param nome Nome do aluno.
 * @param curso Curso que o aluno está matriculado.
 *
 * @pre Os ponteiros 'nome' e 'curso' não podem ser nulos (NULL).
 *
 * @note Não é permitido cadastrar dois alunos com a mesma matrícula.
 *
 * @return int
 * @retval 1 Cadastro realizado com sucesso.
 * @retval 0 Aluno já cadastrado.
 * @retval -1 Matrícula inválida.
 * @retval -2 Limite máximo de alunos atingido
 * @retval -3 Ponteiros inválidos.
 */
int cadastrar_aluno(int matricula, char *nome, char *curso);


/**
 * @brief Realiza a busca por um aluno.
 * 
 * @param matricula Identificador único do aluno.
 *
 * @pre A matrícula deve ser um número inteiro positivo (> 0).
 *
 * @return int 
 * @retval 1 Aluno encontrado.
 * @retval 0 Aluno não encontrado. 
 * @retval -1 Matrícula inválida.
 */
int buscar_aluno(int matricula);


/**
 * @brief Obtem o nome de um aluno.
 *
 * @param matricula Identificador único do aluno.
 * @param nome Vetor que receberá o nome do aluno. 
 *
 * @pre O ponteiro 'nome' não pode ser nulo (NULL) e deve ter espaço alocado suficiente para receber a string.
 *
 * @return int
 * @retval 1 Nome obtido com sucesso.
 * @retval 0 Aluno não encontrado.
 * @retval -1 Aluno inválido.
 */
int obter_nome_aluno(int matricula, char* nome);


/**
 * @brief Lista todos os alunos cadastrados.
 * 
 * @return int
 * @retval 1 Listagem realizada com sucesso.
 * @retval 0 Nenhum aluno cadastrado.
 *
 * @note Imprime os resultados diretamente no console via printf.
 */
int listar_alunos();


/**
 * @brief Exclui um aluno.
 * 
 * @param matricula Identificador único do aluno.
 *
 * @post Se retornou 1, quantidade_alunos foi reduzida em 1.
 *
 * @note Esta função não verifica se o aluno possui empréstimos ativos. Essa validação deve ser feita pelo módulo principal antes da chamada.
 *
 * @return int
 * @retval 1 Aluno excluído com sucesso.
 * @retval 0 Aluno não encontrado.
 * @retval -1 Matrícula inválida.
 */
int excluir_aluno(int matricula);


#endif
