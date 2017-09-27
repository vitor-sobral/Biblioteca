#include "dinamica.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//FUNCAO PARA CRIACAO DE UMA FILA DE ESPERA.
FilaEspera *FilaCria(){
	FilaEspera *F = NULL;
	F = (FilaEspera *)malloc(sizeof(FilaEspera));
	if(F == NULL) return NULL;
	F->inicio = NULL;
	F->fim = NULL;
	return F;
}

//FUNCAO PARA CRIACAO DE UMA LISTA DE LIVROS.
void CriarListaLivros(ListaLivros *L){
	L->inicio = NULL;
	L->fim = NULL;
}

//FUNCAO PARA CRIACAO DE UMA LISTA DE ALUNOS.
void CriarListaAlunos(ListaAlunos *L){
	L->inicio = NULL;
	L->fim = NULL;
}

//FUNCAO PARA VERIFICAR SE DETERMINADO LIVRO SE ENCONTRA NA LISTA DE LIVROS. TRATA-SE DE UMA AUXILIAR PARA A FUNCAO CADASTRALIVRO.
int Livro_Na_Lista(ListaLivros *L, Livro *X){
	
	no_livro *p;
	p=L->inicio;
	
	while((p != NULL)&&(strcmp(p->info->titulo, X->titulo))){
		p=p->prox;
	}
	
	if(p==NULL)
		return 0;
		else{
			p->info->total += X->total;
			return 1;
		}
}

//FUNCAO PARA INSERCAO NA LISTA DE LIVROS. TRATA-SE DE UMA AUXILIAR PARA A FUNCAO CADASTRALIVRO.
void LivroInsere(ListaLivros *L, Livro *X){
	
	no_livro *p;
	
	p = (no_livro*)malloc(sizeof(no_livro));
	if(p==NULL){
		return;
	}

	p->info = X;
	
	p->prox = NULL;
	
	if(L->inicio == NULL)
		L->inicio = p;
	else L->fim->prox = p;

	p->info->Fila = FilaCria();	
	L->fim = p;	
}

//FUNCAO PARA CADASTRAR UM LIVRO NA LISTA. POSSUI VARIAS FUNCOES AUXILIARES.
int CadastrarLivro(ListaLivros *B, char *titulo, char *autor, char *ISBN, char *editora, char *ano, char *edicao, int quantidade){
	Livro *L = NULL;

	L = (Livro *) malloc (sizeof(Livro));
	if(L==NULL){
		return 0;
	}

	L->titulo = titulo;
	L->autor = autor;
	L->ISBN = ISBN;
	L->editora = editora;
	L->ano = ano;
	L->edicao = edicao;
	L->total = quantidade;

	if(Livro_Na_Lista(B, L)){ //Se o livro já estiver na lista, apenas a quantidade é incrementada.
		free(L);
		return 1;
	} 
	LivroInsere(B, L);
	
	return 1;
}

//FUNCAO PARA ELIMINAR UM LIVRO DE UMA LISTA DE LIVROS.TRATA-SE DE UMA AUXILIAR PARA A FUNCAO REMOVERLIVRO.
void LivroElimina(ListaLivros *L, no_livro* anterior, no_livro* atual, char *X){
	
	if(atual == NULL);
	else if(!strcmp(atual->info->titulo, X)){
		if(atual == L->inicio){
			L->inicio = L->inicio->prox;
			if(L->inicio == NULL)
				L->fim = NULL;
		} else if(atual == L->fim){
			L->fim = anterior;
			L->fim->prox = NULL;		
		} else anterior->prox = atual->prox;
		free(atual);
	}else LivroElimina(L, atual, atual->prox, X);
	
}

//FUNCAO PARA REMOVER UM LIVRO DE UMA LISTA DE LIVROS.
void RemoverLivro(ListaLivros *L, char *titulo){
	LivroElimina(L, L->inicio, L->inicio, titulo);
}

//FUNCAO PARA INSERIR UM ALUNO EM UMA LISTA DE ALUNOS.TRATA-SE DE UMA AUXILIAR PARA A FUNCAO CADASTRAALUNO.
void AlunoInsere(ListaAlunos *L, Aluno *X){
	
	no_aluno *p;

	p = (no_aluno*)malloc(sizeof(no_aluno));
	if(p==NULL){
		return;
	}
	
	p->info = X;
	p->prox = NULL;
	
	if(L->inicio == NULL)
		L->inicio = p;
		else L->fim->prox = p;
		
	L->fim = p;
	
}

//FUNCAO PARA CADASTRAR UM ALUNO EM UMA LISTA DE ALUNOS.
int CadastrarAluno(ListaAlunos *A, char *nome, char *NUSP, char *telefone, char *email){
	Aluno *L = NULL;

	L = (Aluno *) malloc (sizeof(Aluno));
	if(L==NULL){
		return 0;
	}

	L->nome = nome;
	L->NUSP = NUSP;
	L->telefone = telefone;
	L->email = email;

	AlunoInsere(A, L);
	return 1;
}

//FUNCAO PARA ELIMINACAO DE UM ALUNO DA LISTA DE ALUNOS.TRATA-SE DE UMA AUXILIAR PARA A FUNCAO REMOVERALUNO.
void AlunoElimina(ListaAlunos *L, no_aluno* anterior, no_aluno* atual, char *X){
	
	if(atual == NULL);
	else if(!strcmp(atual->info->nome, X)){
		if(atual == L->inicio){
			L->inicio = L->inicio->prox;
			if(L->inicio == NULL)
				L->fim = NULL;
		} else if(atual == L->fim){
			L->fim = anterior;
			L->fim->prox = NULL;		
		} else anterior->prox = atual->prox;
		free(atual);
	}else AlunoElimina(L, atual, atual->prox, X);
	
}

//FUNCAO QUE ELIMINA UM ALUNO DE UMA FILA DE ESPERA.
void AlunoEliminaFila(FilaEspera *L, no_aluno *anterior, no_aluno *atual, char *X){


	if(atual == NULL);
	else if(!strcmp(atual->info->nome, X)){
		if(atual == L->inicio){
			L->inicio = L->inicio->prox;
			if(L->inicio == NULL)
				L->fim = NULL;
		} else if(atual == L->fim){
			L->fim = anterior;
			L->fim->prox = NULL;		
		} else anterior->prox = atual->prox;
		free(atual);
	}else AlunoEliminaFila(L, atual, atual->prox, X);
}

//FUNCAO PARA REMOVER UM ALUNO DE UMA LISTA DE ALUNOS.
void RemoverAluno(ListaAlunos *A, char *nome, ListaLivros *B){
	AlunoElimina(A, A->inicio, A->inicio, nome);
	
	no_livro *p;
	FilaEspera *F;

	p = B->inicio;

	while(p != NULL){
		F = p->info->Fila;
		AlunoEliminaFila(F, F->inicio, F->inicio, nome);
		p = p->prox;
	}
	
}

//FUNCAO PARA INSERIR UM ALUNO NUMA FILA DE ESPERA PARA UM DETERMINADO LIVRO.
void FilaEntra(FilaEspera *F, Aluno *X){
	
	no_aluno *p;
	p = (no_aluno *)malloc (sizeof(no_aluno));
	if(p==NULL) return;
	
	p->info = X;
	p->prox = NULL;
	
	if(F->inicio == NULL){
		F->inicio = p;
	}
		else {
			F->fim->prox = p;
		}

	F->fim = p;	
	
}

//FUNCAO PARA BUSCA DE UM ALUNO NA LISTA DE ALUNOS. RETORNA O ALUNO EM QUESTAO SE ESTIVER NA LISTA.
Aluno *BuscaAluno(ListaAlunos *L, char *nome){
	no_aluno *p;
	p=L->inicio;

	while((p != NULL)&&(strcmp(p->info->nome, nome))){
		p=p->prox;
	}
	
	if(p==NULL)
		return NULL;
	else return p->info;
}

//FUNCAO PARA BUSCA DE UM LIVRO NA LISTA DE LIVROS. RETORNA O LIVRO EM QUESTAO SE ESTIVER NA LISTA.
Livro *BuscaLivro(ListaLivros *L, char *titulo){
	no_livro *p;
	p=L->inicio;

	while((p != NULL)&&(strcmp(p->info->titulo, titulo))){
		p=p->prox;
	}
	
	if(p==NULL)
		return NULL;
	else return p->info;	
	
}

//FUNCAO RESPONSAVEL POR REALIZAR UM EMPRESTIMO DE LIVRO A UM DETERMINADO ALUNO CADASTRADO.
int EmprestaLivro(ListaAlunos *A, char *nome, ListaLivros *B, char *titulo){
	Livro *L;
	Aluno *Al;
	L = BuscaLivro(B, titulo);
	Al = BuscaAluno(A, nome);

		if(L->total == 0){
			//adiciona na fila
			FilaEntra(L->Fila, Al);
		} else{
			//reduz a quantidade de livros
			L->total--;
		}
}

//FUNCAO REPSONSAVEL POR RETIRAR UM ALUNO DE UMA FILA DE ESPERA DE UM LIVRO.
void FilaSai(FilaEspera *F){
	
	no_aluno *p;
	
	if(F->inicio == NULL) return;

	p = F->inicio;
	F->inicio = F->inicio->prox;
	if(F->inicio == NULL)
		F->fim=NULL;
	free(p);
	
}

//FUNCAO QUE DEVOLVE UM LIVRO ESPRESTADO DE VOLTA A LISTA DE LIVROS, DANDO SEQUENCIA A FILA DE ESPERA.
void DevolveLivro(ListaLivros *B, char *titulo){
	Livro *L;
	L = BuscaLivro(B, titulo);

	if(L->Fila->inicio == NULL){
			L->total++;
			return;
	}	

	FilaSai(L->Fila);
}

//FUNCAO PARA IMPRESSAO DA FILA DE ESPERA DOS LIVROS.
void imprime_fila(FilaEspera *F){
	no_aluno *p;

	p = F->inicio;

	while(p != NULL){
		printf("%s | ", p->info->nome);
		p = p->prox;
	}
}

//FUNCAO PARA IMPRESSAO DOS ALUNOS CADASTRADOS NA LISTA.
void imprime_alunos(ListaAlunos *L){
	no_aluno *p;

	p = L->inicio;
	printf("\n");
	printf("ALUNOS\n");
	while(p != NULL){
		printf("-> %s   ", p->info->nome);
		p = p->prox;
		printf("\n");
	}
	printf("\n");
}

//FUNCAO PARA IMPRESSAO DOS LIVROS CADASTRADOS EM UMA LISTA.
void imprime(ListaLivros *L){
	no_livro *p;

	p = L->inicio;
	printf("\n");
	printf("LIVROS\n");
	while(p != NULL){
		printf("-> %s   ", p->info->titulo);
		imprime_fila(p->info->Fila);
		p = p->prox;
		printf("\n");
	}
	printf("\n");
}

//FUNCAO PARA DESTRUICAO DE UMA FILA DE ESPERA (UTILIZADA PARA LIBERAR AS REGIOES DE MEMORIA UTILIZADAS).
void FilaFinaliza(FilaEspera *L){
	no_aluno *p;
	
	p = L->inicio;	
	
	while(p!=NULL){
		L->inicio = L->inicio->prox;
		free(p);
		p = L->inicio;
	}
	
	L->fim = p;
}

//FUNCAO RESPONSAVEL POR LIBERAR TODO O ESPACO DE MEMORIA UTILIZADO PELO PROGRAMA NO DECORRER DE SUA EXECUCAO.
void LiberaMemoria(ListaAlunos *A, ListaLivros *B){
	no_aluno *a, *a_aux;
	no_livro *b, *b_aux;
	FilaEspera *F, *aux;

	b = B->inicio;

	while(b != NULL){
		F = b->info->Fila;
		
		FilaFinaliza(F);
		
		
		b_aux = b;
		b = b->prox;

		free(b_aux->info->titulo);
		free(b_aux->info->autor);
		free(b_aux->info->ISBN);
		free(b_aux->info->editora);
		free(b_aux->info->ano);
		free(b_aux->info->edicao);
		free(b_aux);
	}

	a = A->inicio;

	while(a != NULL){
		a_aux = a;
		a = a->prox;

		free(a_aux->info->nome);
		free(a_aux->info->NUSP);
		free(a_aux->info->telefone);
		free(a_aux->info->email);
		free(a_aux);

	}

}
