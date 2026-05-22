#ifndef ALUNOS_H
#define ALUNOS_H

/**
 * @file alunos.h
 * @brief Interface do módulo de gerenciamento de alunos.
 *
 * Este módulo é responsável por cadastrar, buscar e excluir alunos.
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
 */
int salvar_alunos(const char *arquivo);


/**
 * @brief Realiza o cadastro de um aluno.
 * 
 * @param matricula Identificador único do aluno.
 * @param nome Nome do aluno.
 * @param curso Curso que o aluno está matriculado.
 * 
 * @return int
 * @retval 1 Cadastro realizado com sucesso.
 * @retval 0 Aluno já cadastrado.
 * @retval -1 Matrícula inválida.
 */
int cadastrar_aluno(int matricula, char *nome, char *curso);


/**
 * @brief Realiza a busca por um aluno.
 * 
 * @param matricula Identificador único do aluno.
 *
 * @return int 
 * @retval 1 Aluno encontrado.
 * @retval 0 Aluno não encontrado. 
 */
int buscar_aluno(int matricula);


/**
 * @brief Obtem o nome de um aluno.
 *
 * @param matricula Identificador único do aluno.
 * @param nome Vetor que receberá o nome do aluno. 
 *
 * @return int
 * @retval 1 Nome obtido com sucesso.
 * @retval 0 Aluno não encontrado.
 */
int obter_nome_aluno(int matricula, char* nome);


/**
 * @brief Lista todos os alunos cadastrados.
 * 
 * @return int
 * @retval 1 Listagem realizada com sucesso.
 * @retval 0 Nenhum aluno cadastrado.
 */
int listar_alunos();


/**
 * @brief Exclui um aluno.
 * 
 * @param matricula Identificador único do aluno.
 *
 * @return int
 * @retval 1 Aluno excluído com sucesso.
 * @retval 0 Aluno não encontrado.
 */
int excluir_aluno(int matricula);


#endif
