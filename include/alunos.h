#ifndef ALUNOS_H
#define ALUNOS_H

/**
 * @file alunos.h
 * @brief Interface do módulo de gerenciamento de alunos.
 *
 * Este módulo é responsável por cadastrar, buscar e excluir alunos usando alocação dinâmica.
 *
 * @details
 * Este módulo é independente e atua como base para os módulos de
 * empréstimos e reservas.
 * @pre carregar_alunos() deve ser chamado antes de qualquer função deste módulo.
 */

typedef struct aluno Aluno;


/**
 * @brief Carrega dados de alunos no sistema.
 * * @param arquivo Caminho do arquivo de dados dos alunos.
 * * @return int
 * @retval 1 Dados carregados com sucesso.
 * @retval 0 Arquivo não existe ou está vazio (primeira inicialização).
 * @retval -1 Erro de leitura física no disco.
 * @retval -2 Ponteiro nulo.
 * @retval -3 Falha de alocação de memória.
 */
int carregar_alunos(const char *arquivo);


/**
 * @brief Salva os dados de alunos no sistema.
 * * @param arquivo Caminho do arquivo de dados dos alunos.
 * * @return int
 * @retval 1 Dados salvos com sucesso.
 * @retval -1 Erro ao criar ou abrir o arquivo no disco.
 * @retval -2 Ponteiro nulo.
 * @retval -3 Erro de escrita no disco.
 */
int salvar_alunos(const char *arquivo);


/**
 * @brief Realiza o cadastro de um aluno de forma dinâmica.
 * * @param matricula Identificador único do aluno.
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
 * @retval -2 Falha de alocação de memória.
 * @retval -3 Ponteiros inválidos.
 */
int cadastrar_aluno(int matricula, char *nome, char *curso);


/**
 * @brief Realiza a busca por um aluno na lista.
 * * @param matricula Identificador único do aluno.
 *
 * @return int 
 * @retval 1 Aluno encontrado.
 * @retval 0 Aluno não encontrado. 
 * @retval -1 Matrícula inválida.
 */
int buscar_aluno(int matricula);


/**
 * @brief Obtém o nome de um aluno cadastrado.
 *
 * @param matricula Identificador único do aluno.
 * @param nome Vetor que receberá o nome do aluno. 
 *
 * @pre O ponteiro 'nome' não pode ser nulo (NULL) e deve ter espaço alocado suficiente.
 *
 * @return int
 * @retval 1 Nome obtido com sucesso.
 * @retval 0 Aluno não encontrado.
 * @retval -1 Aluno ou ponteiro inválido.
 */
int obter_nome_aluno(int matricula, char* nome);


/**
 * @brief Lista todos os alunos cadastrados no console.
 * * @return int
 * @retval 1 Listagem realizada com sucesso.
 * @retval 0 Nenhum aluno cadastrado.
 */
int listar_alunos();


/**
 * @brief Exclui um aluno da lista e liberta a sua memória.
 * * @param matricula Identificador único do aluno.
 *
 * @post Se retornou 1, o nó correspondente foi libertado da memória.
 *
 * @return int
 * @retval 1 Aluno excluído com sucesso.
 * @retval 0 Aluno não encontrado.
 * @retval -1 Matrícula inválida.
 */
int excluir_aluno(int matricula);

#endif