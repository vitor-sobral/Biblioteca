#ifndef ESTATICA_H
#define ESTATICA_H

#define TamPilha 100
#define TamFila 100
#define tam_lista_livros 200
#define tam_lista_alunos 200
#define tam_lista_espera 50

typedef struct{
char msg[40];
}Recados;

typedef struct {
	char nome[100], NUSP[6], telefone[10],email[50];
	int prox,prox_espera,topo;
	Recados mensagem[5];
} Aluno;

typedef struct {
	int inicio,fim,pv,total;
	Aluno alunos[tam_lista_alunos];
} ListaAlunos;

typedef struct {
	int inicio,fim,total,pv;
	Aluno *espera[tam_lista_espera];
}FilaEspera;

typedef struct {
	char titulo[100],autor[100],ISBN[20],editora[50],ano[4],edicao[3];
	int total,prox;
	FilaEspera Fila;
} Livro;

typedef struct {
	int inicio,fim,pv,total;
	Livro livros[tam_lista_livros];
} ListaLivros;


void CriarListaLivros(ListaLivros *);
void CriarListaAlunos(ListaAlunos *);
int BuscaAluno(ListaAlunos*, char*);
int BuscaLivro(ListaLivros *,char *);
void imprime_alunos(ListaAlunos*);
void imprime(ListaLivros *);
void imprime_espera(Livro);
int CadastrarAluno(ListaAlunos *,char *,char *,char *,char *);
int CadastrarLivro(ListaLivros *,char *,char *,char *,char *,char *,char *,int);
int EmprestaLivro(ListaAlunos *,char *,ListaLivros *,char*);
void DevolveLivro(ListaLivros *, char *);
void RemoverLivro(ListaLivros *,char *);
void RemoverAluno(ListaAlunos *,char *,ListaLivros *);
void AlunoFilaRemove(ListaAlunos*,int*, Livro *);
void LiberaMemoria(ListaAlunos*,ListaLivros*);
void Mensagem(Aluno*,char*);
void Imprime_Mensagem(ListaAlunos*,char*);

#endif //INCLUDED
