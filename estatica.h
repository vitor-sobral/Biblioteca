#ifndef ESTATICA_H
#define ESTATICA_H

#define TamPilha 100
#define TamFila 100
#define tam_lista_livros 200
#define tam_lista_alunos 200
#define tam_lista_espera 50

typedef struct {
	char nome[100], NUSP[6], telefone[10],email[50];
} Aluno;

typedef struct {
	int fim;
	Aluno alunos[tam_lista_alunos];
} ListaAlunos;

typedef struct {
	int inicio,fim,total;
	Aluno espera[tam_lista_espera];
}FilaEspera;

typedef struct {
	char titulo[100],autor[100],ISBN[20],editora[50],ano[4],edicao[3];
	int total;
	FilaEspera Fila;
} Livro;

typedef struct {
	int fim;
	Livro livros[tam_lista_livros];
} ListaLivros;

void CriarListaLivros(ListaLivros *);
void CriarListaAlunos(ListaAlunos *);
int BuscaAluno(ListaAlunos *Lista, char *aluno);
int BuscaLivro(ListaLivros *Lista,char *livro);
void imprime(ListaLivros *Lista);
void imprime_espera(Livro L);
int CadastrarAluno(ListaAlunos *Lista,char *nome,char *NUSP,char *telefone,char *email);
int CadastrarLivro(ListaLivros *Lista,char *titulo,char *autor,char *ISBN,char *editora,char *ano,char *edicao,int quantidade);
int EmprestaLivro(ListaAlunos *ListaAluno,char *aluno,ListaLivros *ListaLiv,char *livro);
void DevolveLivro(ListaLivros *Lista, char *livro);
void RemoverLivro(ListaLivros *Lista,char *livro);
void RemoverAluno(ListaAlunos *Lista,char *aluno);



#endif //INCLUDED
