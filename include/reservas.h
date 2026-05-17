#ifndef RESERVAS_H
#define RESERVAS_H

/**
 * @file reservas.h
 * @brief Interface do módulo de gerenciamento de reservas.
 *
 * Este módulo é responsável por gerenciar reservas de livros.
 *
 * @details
 * Este módulo depende dos módulos de alunos e livros para validação
 * de dados e controle de disponibilidade.
 */

typedef struct reserva Reserva;
typedef struct nolistareserva NoListaReserva; //nao precisa estar no .h pode so deixar no .c


/**
 * @brief Carrega dados de reservas no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados das reservas.
 * 
 * @return int
 * @retval 1 Dados carregados com sucesso.
 * @retval 0 Arquivo não existe ou está vazio (primeira inicialização).
 * @retval -1 Erro ao ler arquivo.
 */
int carregar_reservas(const char *arquivo);


/**
 * @brief Salva os dados de reservas no sistema.
 * 
 * @param arquivo Caminho do arquivo de dados das reservas.
 * 
 * @return int
 * @retval 1 Dados salvos com sucesso.
 * @retval -1 Erro ao escrever no arquivo.
 */
int salvar_reservas(const char *arquivo);


/**
 * @brief Cria a reserva de um livro para um aluno.
 * 
 * @param id_livro Identificador único do livro.
 * @param matricula Identificador único do aluno.
 * 
 * @return int
 * @retval 1 Reserva realizada com sucesso.
 * @retval 0 Livro disponível para empréstimo (não precisa reservar).
 * @retval -1 Livro não encontrado.
 * @retval -2 Aluno não encontrado.
 * @retval -3 Aluno já reservou esse livro.
 */
int criar_reserva(int id_livro, int matricula);


/**
 * @brief Cancela uma reserva de um livro por um aluno.
 * 
 * @param id_livro Identificador único do livro.
 * @param matricula Identificador único do aluno.
 *
 * @return int
 * @retval 1 Reserva cancelada com sucesso.
 * @retval 0 Reserva não encontrada.
 * @retval -1 Livro não encontrado.
 * @retval -2 Aluno não encontrado.
 */
int cancelar_reserva(int id_livro, int matricula);


/**
 * @brief Lista todas as reservas do livro.
 * @param id_livro Identificador único do livro.
 */
void listar_reservas_livro(int id_livro);


/**
 * @brief Lista todas as reservas de um aluno.
 * @param matricula Identificador único do aluno.
 */
void listar_reservas_aluno(int matricula);


/**
 * @brief Obtém a próxima reserva (primeiro da fila) de um livro.
 * 
 * @param id_livro Identificador único do livro.
 * @param matricula Ponteiro para variável que receberá a matrícula do próximo da fila.
 *
 * @return int
 * @retval 1 Próxima reserva encontrada (matrícula preenchida).
 * @retval 0 Não há reservas.
 * @retval -1 Livro não encontrado.
 */
int proxima_reserva(int id_livro, int *matricula);



#endif 
