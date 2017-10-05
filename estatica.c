#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estatica.h"

//PESQUISA UM ALUNO E RETORNA O NÚMERO DO INDICE NO VETOR ONDE ESTÁ LOCALIZADO.
int BuscaAluno(ListaAlunos *Lista, char *aluno){
	int i = 0,aux=Lista->inicio;

	for(i = 0; i < Lista->total; i++){
		if(!strcmp(Lista->alunos[aux].nome, aluno)){
			return aux;
		}
        aux=Lista->alunos[aux].prox;
	}

	return -1;
}

//PESQUISA UM LIVRO E RETORNA O NÚMERO DO INDICE NO VETOR ONDE ESTÁ LOCALIZADO.
int BuscaLivro(ListaLivros *Lista,char *livro){
	int i = 0,aux=Lista->inicio;

	for(i = 0; i < Lista->total; i++){
		if(!strcmp(Lista->livros[aux].titulo, livro)){
			return i;
		}
        aux=Lista->livros[aux].prox;
	}

	return -1;
}

//CRIA UMA LISTA DE ALUNOS.
void CriarListaAlunos(ListaAlunos *Lista){
    int i;
    Lista->total=0;
	Lista->inicio=0;
    Lista->fim = 0;
    Lista->pv=0;

	for(i=0;i<tam_lista_alunos;i++)
        Lista->alunos[i].prox=i+1;

    Lista->alunos[i].prox=-1;
	return;
}

//CRIA UMA LISTA DE LIVROS.
void CriarListaLivros(ListaLivros *Lista){
	int i;

	Lista->fim = 0;
	Lista->inicio=0;
	Lista->total=0;
	Lista->pv=0;

	for(i=0;i<tam_lista_livros;i++){
        Lista->livros[i].prox=i+1;
        //printf("// %d -> %d //",i,Lista->livros[i].prox);
	}

    Lista->livros[tam_lista_livros-1].prox=-1;
	return;
}

void imprime_espera(Livro L){

	int i = 0,aux=L.Fila.inicio;

	for(i = L.Fila.inicio; i < L.Fila.total; i++){
		printf("%s | ", L.Fila.espera[aux].nome);
		aux=L.Fila.espera[aux].prox;
	}

}

void imprime(ListaLivros *Lista){
	int i = 0,aux;
	printf("\n");
	aux=Lista->inicio;
	for(i=0;i<Lista->total;i++){
		printf("[%d] - %s\t", i, Lista->livros[aux].titulo);
		imprime_espera(Lista->livros[aux]);
		aux=Lista->livros[aux].prox;
	}
	printf("\n");
}

void imprime_alunos(ListaAlunos *A){
    int i,aux;
    aux=A->inicio;
    for(i=0;i<A->total;i++){
        printf("Nome    -   %s\nNumero USP  -   %s    \nTelefone    -   %s\nEmail   -   %s",A->alunos[aux].nome,A->alunos[aux].NUSP,A->alunos[aux].telefone,A->alunos[aux].email);
        aux=A->alunos[aux].prox;
    }

}

//CADASTRA UM NOVO ALUNO NA LISTA. RETORNO: 1 SE SUCESSO. 0 SE FRACASSO.
int CadastrarAluno(ListaAlunos *Lista,char *nome,char *NUSP,char *telefone,char *email){
	int numaluno;

	if(Lista->total >= tam_lista_alunos)
        return 0;

    numaluno = BuscaAluno(Lista, nome);

	if(numaluno != -1)
        return 1;

	strcpy(Lista->alunos[Lista->pv].nome,nome);
	strcpy(Lista->alunos[Lista->pv].NUSP,NUSP);
	strcpy(Lista->alunos[Lista->pv].telefone,telefone);
	strcpy(Lista->alunos[Lista->pv].email,email);
	if(Lista->fim!=Lista->pv)
        Lista->alunos[Lista->fim].prox=Lista->pv;
	Lista->fim=Lista->pv;
	//Lista->alunos[Lista->fim].prox=-1;
	Lista->pv=Lista->alunos[Lista->pv].prox;
	Lista->total+=1;
	return 1;
}

//CADASTRA UM NOVO LIVRO. RETORNO: 1, SE SUCESSO. 0, SE FRACASSO.
int CadastrarLivro(ListaLivros *Lista,char *titulo,char *autor,char *ISBN,char *editora,char *ano,char *edicao,int quantidade){
	int numlivro;

	if(Lista->total >= tam_lista_livros)
        return 0;

	numlivro = BuscaLivro(Lista, titulo);

	if(numlivro != -1){
		Lista->livros[numlivro].total += quantidade;
		return 1;
	}

	strcpy(Lista->livros[Lista->pv].titulo,titulo);
	strcpy(Lista->livros[Lista->pv].autor,autor);
	strcpy(Lista->livros[Lista->pv].ISBN,ISBN);
	strcpy(Lista->livros[Lista->pv].editora,editora);
	strcpy(Lista->livros[Lista->pv].ano,ano);
	strcpy(Lista->livros[Lista->pv].edicao,edicao);
	Lista->livros[Lista->pv].total = quantidade;
    //Lista->livros[Lista->pv].prox=-1;
    if(Lista->fim!=Lista->pv)
        Lista->livros[Lista->fim].prox=Lista->pv;
    Lista->fim=Lista->pv;
    Lista->pv=Lista->livros[Lista->pv].prox;
    Lista->total+=1;

	return 1;
}

//EMPRÉSTIMO DE UM LIVRO. RETORNO: 1, SE SUCESSO. 0, SE FRACASSO.
int EmprestaLivro(ListaAlunos *ListaAluno,char *aluno,ListaLivros *ListaLiv,char *livro){
	int numaluno,numlivro;

	numaluno = BuscaAluno(ListaAluno,aluno);
	numlivro = BuscaLivro(ListaLiv,livro);

	//Se não houverem livros disponíveis
	if(ListaLiv->livros[numlivro].total==0){
	    ListaLiv->livros[numlivro].Fila.espera[ListaLiv->livros[numlivro].Fila.pv] = ListaAluno->alunos[numaluno];
	    ListaLiv->livros[numlivro].Fila.fim = ListaLiv->livros[numlivro].Fila.pv;
	    ListaLiv->livros[numlivro].Fila.pv=ListaLiv->livros[numlivro].Fila.espera[ListaLiv->livros[numlivro].Fila.pv].prox;
	    ListaLiv->livros[numlivro].Fila.espera[ListaLiv->livros[numlivro].Fila.fim].prox=-1;
	    ListaLiv->livros[numlivro].Fila.total += 1;
	    return 0;
	}

	else{
		//Se houverem livros e não existir fila de espera
	    if(ListaLiv->livros[numlivro].Fila.total==0){
	        ListaLiv->livros[numlivro].total -= 1;
	        return 1;
	    }

	}
	return 0;
}

//DEVOLVE UM LIVRO E JÁ O EMPRESTA PARA O PŔOXIMO DA FILA DE ESPERA, SE HOUVER.
void DevolveLivro(ListaLivros *Lista, char *livro){
	int numlivro;

	numlivro = BuscaLivro(Lista,livro);

	Lista->livros[numlivro].total+=1;

	//Implementar alguma função para avisar o aluno que o livro pode ser retirado.
	if(Lista->livros[numlivro].Fila.total > 0){
		Lista->livros[numlivro].Fila.inicio = Lista->livros[numlivro].Fila.espera[Lista->livros[numlivro].Fila.inicio].prox;
	    Lista->livros[numlivro].Fila.total -= 1;
	    Lista->livros[numlivro].total -= 1;
	}
}

//REMOVE UM LIVRO DA BIBLIOTECA, COLOCA O LIVRO NO PRIMEIRO VAZIO.
void RemoverLivro(ListaLivros *L,char *livro){
	int numlivro,i,aux=L->inicio;

    if(!strcmp(L->livros[aux].titulo,livro)){
        L->inicio=L->livros[L->inicio].prox;
        L->livros[aux].prox=L->pv;
        L->pv=aux;
        L->total-=1;
        L->livros[aux].Fila.total = 0;
        L->livros[aux].Fila.inicio = 0;
        L->livros[aux].Fila.fim = 0;
    }
    else{
    for(i=0;i<L->total;i++){
        if(!strcmp(L->livros[L->livros[aux].prox].titulo,livro)){
            numlivro=L->livros[aux].prox;
            L->livros[aux].prox=L->livros[numlivro].prox;
            L->livros[numlivro].prox=L->pv;
            L->pv=numlivro;
            L->total-=1;
            L->livros[numlivro].Fila.total = 0;
            L->livros[numlivro].Fila.inicio = 0;
            L->livros[numlivro].Fila.fim = 0;
            break;
        }
    }
    }
}

//REMOVE UM ALUNO DA BIBLIOTECA, COLOCA O ALUNO NO PRIMEIRO VAZIO.
void RemoverAluno(ListaAlunos *Lista,char *aluno,ListaLivros *Liv){
	int i=0,aux=Lista->inicio,numaluno;

	//numaluno = BuscaAluno(Lista,aluno);

    for(i=0;i<Lista->total;i++){
        if(!strcmp(Lista->alunos[Lista->alunos[aux].prox].nome,aluno)){
            numaluno=Lista->alunos[aux].prox;
            Lista->alunos[aux].prox=Lista->alunos[numaluno].prox;
            Lista->alunos[numaluno].prox=Lista->pv;
            Lista->pv=numaluno;
            Lista->total-=1;
            break;
        }
    }


	for(i=0;i<Liv->fim;i++)
        AlunoFilaRemove(Lista,&numaluno,&Liv->livros[i]);
}

void AlunoFilaRemove(ListaAlunos *A,int *numaluno, Livro *L){
    int i,aux,anterior;
    aux=L->Fila.inicio;
    for(i=0;i<L->Fila.total;i++){
        if(!strcmp(L->Fila.espera[aux].nome,A->alunos[*numaluno].nome)){
            L->Fila.espera[anterior].prox=-1;
            L->Fila.espera[aux].prox=L->Fila.pv;
            L->Fila.pv=aux;
        }
        anterior=aux;
        aux=L->Fila.espera[aux].prox;
    }
}

void LiberaMemoria(ListaAlunos *A,ListaLivros *L){
return;
}
