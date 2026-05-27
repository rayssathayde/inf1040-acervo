#ifndef ALUNOS_H
#define ALUNOS_H

/**
 * @file alunos.h
 * @brief Interface do módulo de gerenciamento de alunos.
 *
 * Este módulo é responsável por cadastrar, buscar, listar e excluir alunos,
 * além de gerenciar a persistência desses dados em disco.
 *
 * @details
 * Este módulo é independente e atua como base de dados para os módulos de 
 * empréstimos e reservas.
 * * @pre carregar_alunos() deve ser chamado antes de qualquer outra função deste módulo.
 */

typedef struct aluno Aluno;


/**
 * @brief Carrega dados de alunos no sistema a partir de um arquivo.
 * * @param arquivo Caminho do arquivo binário de dados dos alunos.
 * * @pre O ponteiro 'arquivo' não pode ser nulo (NULL).
 * * @return int
 * @retval 1 Dados carregados com sucesso.
 * @retval 0 Arquivo não existe ou está vazio (primeira inicialização do sistema).
 * @retval -1 Erro ao ler o arquivo ou formato inválido.
 */
int carregar_alunos(const char *arquivo);


/**
 * @brief Salva os dados atuais de alunos no disco.
 * * @param arquivo Caminho do arquivo binário de dados dos alunos.
 * * @pre O ponteiro 'arquivo' não pode ser nulo (NULL).
 * * @return int
 * @retval 1 Dados salvos com sucesso.
 * @retval -1 Erro ao escrever no arquivo ou permissão negada.
 */
int salvar_alunos(const char *arquivo);


/**
 * @brief Realiza o cadastro de um novo aluno no sistema.
 * * @param matricula Identificador único do aluno.
 * @param nome Nome do aluno.
 * @param curso Curso no qual o aluno está matriculado.
 *
 * @pre Os ponteiros 'nome' e 'curso' não podem ser nulos (NULL).
 * @pre A matrícula deve ser um número inteiro estritamente positivo (> 0).
 *
 * @post Se retornou 1, um novo registro de aluno foi adicionado ao sistema 
 * e a quantidade total de alunos aumentou em 1.
 *
 * @note Não é permitido cadastrar dois alunos com a mesma matrícula.
 *
 * @return int
 * @retval 1 Cadastro realizado com sucesso.
 * @retval 0 Aluno já cadastrado (matrícula duplicada).
 * @retval -1 Matrícula inválida (menor ou igual a zero).
 * @retval -2 Limite máximo de alunos atingido (banco de dados cheio).
 * @retval -3 Ponteiros inválidos (nome ou curso nulos).
 */
int cadastrar_aluno(int matricula, char *nome, char *curso);


/**
 * @brief Realiza a busca por um aluno usando a matrícula.
 * * @param matricula Identificador único do aluno.
 *
 * @return int 
 * @retval 1 Aluno encontrado no sistema.
 * @retval 0 Aluno não encontrado ou matrícula inválida. 
 */
int buscar_aluno(int matricula);


/**
 * @brief Obtém o nome de um aluno a partir da sua matrícula.
 *
 * @param matricula Identificador único do aluno.
 * @param nome Vetor de caracteres que receberá a string do nome. 
 *
 * @pre O ponteiro 'nome' não pode ser nulo (NULL) e deve ter espaço alocado 
 * suficiente para receber a string (tamanho mínimo sugerido: 100 bytes).
 *
 * @post Se retornou 1, o vetor 'nome' foi preenchido com o nome correspondente à matrícula.
 *
 * @return int
 * @retval 1 Nome obtido com sucesso.
 * @retval 0 Aluno não encontrado ou parâmetros inválidos.
 */
int obter_nome_aluno(int matricula, char* nome);


/**
 * @brief Lista todos os alunos cadastrados no sistema.
 * * @note Imprime os resultados diretamente no console via printf.
 * * @return int
 * @retval 1 Listagem realizada com sucesso.
 * @retval 0 Nenhum aluno cadastrado no sistema.
 */
int listar_alunos();


/**
 * @brief Exclui um aluno do sistema baseado na matrícula.
 * * @param matricula Identificador único do aluno.
 *
 * @post Se retornou 1, o aluno foi removido definitivamente do sistema e a 
 * quantidade total de alunos cadastrados foi reduzida em 1.
 *
 * @note Esta função não verifica se o aluno possui empréstimos ou reservas ativos. 
 * Essa validação deve ser feita pelo módulo principal (ou chamador) antes da chamada.
 *
 * @return int
 * @retval 1 Aluno excluído com sucesso.
 * @retval 0 Aluno não encontrado ou matrícula inválida.
 */
int excluir_aluno(int matricula);


#endif