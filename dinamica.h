#ifndef DINAMICA_H
#define DINAMICA_H

//#define NULL 0

typedef struct fila {
	struct bloco_aluno *inicio, *fim;
}FilaEspera;

typedef struct aluno{
	char *nome;		//NOME COMPLETO DO ALUNO
	char *NUSP;		//NUMERO USP DO ALUNO (STRING POIS PODE VIR A TER MUITOS DÍGITOS)
	char *telefone;	//NUMERO DE TELEFONE DO ALUNO PARA CONTATO (PODE TER MUITO MAIS DÍGITOS DO QUE UM INTEIRO PODE ARMAZENAR)
	char *email;	//EMAIL DO ALUNO PARA CONTATO
} Aluno;

typedef struct livro{
	char *titulo;	//TÍTULO DO LIVRO
	char *autor;	//NOME DO AUTOR
	char *ISBN;		//ISBN DO LIVRO (NUMERO MUITO GRANDE PARA SER ARMAZENADO EM INT)
	char *editora;	//NOME DA EDITORA 
	char *ano;		//ANO DA EDICAO
	char *edicao;	//NUMERO DA EDICAO
	int total;		//NUMERO DE CÓPIAS (DISPONÍVEIS)
	struct fila *Fila;//FILA DE ESPERA DE ALUNOS
} Livro;

typedef struct bloco_livro {
    Livro *info;
    struct bloco_livro *prox;
} no_livro;

typedef struct {
    struct bloco_livro *inicio, *fim;
} ListaLivros;


typedef struct bloco_aluno {
    Aluno *info;
    struct bloco_aluno *prox;
} no_aluno;

typedef struct {
	struct bloco_aluno *inicio, *fim;
} ListaAlunos;

//FUNCAO PARA DESTRUICAO DE UMA FILA DE ESPERA (UTILIZADA PARA LIBERAR AS REGIOES DE MEMORIA UTILIZADAS).
void FilaFinaliza(FilaEspera *L);	
//FUNCAO RESPONSAVEL POR LIBERAR TODO O ESPACO DE MEMORIA UTILIZADO PELO PROGRAMA NO DECORRER DE SUA EXECUCAO.
void LiberaMemoria(ListaAlunos *A, ListaLivros *B);
//FUNCAO QUE ELIMINA UM ALUNO DE UMA FILA DE ESPERA.
void AlunoEliminaFila(FilaEspera *L, no_aluno *anterior, no_aluno *atual, char *X);
//FUNCAO PARA IMPRESSAO DOS ALUNOS CADASTRADOS NA LISTA.
void imprime_alunos(ListaAlunos *L);
//FUNCAO PARA IMPRESSAO DA FILA DE ESPERA DOS LIVROS.
void imprime_fila(FilaEspera *F);
//FUNCAO PARA IMPRESSAO DOS LIVROS CADASTRADOS EM UMA LISTA.
void imprime(ListaLivros *L);
//FUNCAO PARA CRIACAO DE UMA FILA DE ESPERA.
FilaEspera *FilaCria();
//FUNCAO PARA CRIACAO DE UMA LISTA DE LIVROS.
void CriarListaLivros(ListaLivros *L);
//FUNCAO PARA CRIACAO DE UMA LISTA DE ALUNOS.
void CriarListaAlunos(ListaAlunos *L);
//FUNCAO PARA VERIFICAR SE DETERMINADO LIVRO SE ENCONTRA NA LISTA DE LIVROS. TRATA-SE DE UMA AUXILIAR PARA A FUNCAO CADASTRALIVRO.
int Livro_Na_Lista(ListaLivros *L, Livro *X);
//FUNCAO PARA INSERCAO NA LISTA DE LIVROS. TRATA-SE DE UMA AUXILIAR PARA A FUNCAO CADASTRALIVRO.
void LivroInsere(ListaLivros *L, Livro *X);
//FUNCAO PARA CADASTRAR UM LIVRO NA LISTA. POSSUI VARIAS FUNCOES AUXILIARES.
int CadastrarLivro(ListaLivros *B, char *titulo, char *autor, char *ISBN, char *editora, char *ano, char *edicao, int quantidade);
//FUNCAO PARA ELIMINAR UM LIVRO DE UMA LISTA DE LIVROS.TRATA-SE DE UMA AUXILIAR PARA A FUNCAO REMOVERLIVRO.
void LivroElimina(ListaLivros *L, no_livro* anterior, no_livro* atual, char *X);
//FUNCAO PARA REMOVER UM LIVRO DE UMA LISTA DE LIVROS.
void RemoverLivro(ListaLivros *L, char *titulo);
//FUNCAO PARA INSERIR UM ALUNO EM UMA LISTA DE ALUNOS.TRATA-SE DE UMA AUXILIAR PARA A FUNCAO CADASTRAALUNO.
void AlunoInsere(ListaAlunos *L, Aluno *X);
//FUNCAO PARA CADASTRAR UM ALUNO EM UMA LISTA DE ALUNOS.
int CadastrarAluno(ListaAlunos *A, char *nome, char *NUSP, char *telefone, char *email);
//FUNCAO PARA ELIMINACAO DE UM ALUNO DA LISTA DE ALUNOS.TRATA-SE DE UMA AUXILIAR PARA A FUNCAO REMOVERALUNO.
void AlunoElimina(ListaAlunos *L, no_aluno* anterior, no_aluno* atual, char *X);
//FUNCAO PARA REMOVER UM ALUNO DE UMA LISTA DE ALUNOS.
void RemoverAluno(ListaAlunos *L, char *nome, ListaLivros *B);
//FUNCAO PARA INSERIR UM ALUNO NUMA FILA DE ESPERA PARA UM DETERMINADO LIVRO.
void FilaEntra(FilaEspera *F, Aluno *X);
//FUNCAO PARA BUSCA DE UM ALUNO NA LISTA DE ALUNOS. RETORNA O ALUNO EM QUESTAO SE ESTIVER NA LISTA.
Aluno *BuscaAluno(ListaAlunos *L, char *nome);
//FUNCAO PARA BUSCA DE UM LIVRO NA LISTA DE LIVROS. RETORNA O LIVRO EM QUESTAO SE ESTIVER NA LISTA.
Livro *BuscaLivro(ListaLivros *L, char *titulo);
//FUNCAO RESPONSAVEL POR REALIZAR UM EMPRESTIMO DE LIVRO A UM DETERMINADO ALUNO CADASTRADO.
int EmprestaLivro(ListaAlunos *A, char *nome, ListaLivros *B, char *titulo);
//FUNCAO QUE DEVOLVE UM LIVRO ESPRESTADO DE VOLTA A LISTA DE LIVROS, DANDO SEQUENCIA A FILA DE ESPERA.
void DevolveLivro(ListaLivros *B, char *titulo);
//FUNCAO REPSONSAVEL POR RETIRAR UM ALUNO DE UMA FILA DE ESPERA DE UM LIVRO.
void FilaSai(FilaEspera *F);

#endif
