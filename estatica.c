#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <estatica.h>

//PESQUISA UM ALUNO E RETORNA O NÚMERO DO INDICE NO VETOR ONDE ESTÁ LOCALIZADO.
int BuscaAluno(ListaAlunos *Lista, char *aluno){
	int i = 0;

	for(i = 0; i < tam_lista_alunos; i++){
		if(!strcmp(Lista->alunos[i].nome, aluno)){
			return i;
		}
	}
}

//PESQUISA UM LIVRO E RETORNA O NÚMERO DO INDICE NO VETOR ONDE ESTÁ LOCALIZADO.
int BuscaLivro(ListaLivros *Lista,char *livro){
	int i = 0;

	for(i = 0; i < tam_lista_livros; i++){
		if(!strcmp(Lista->livros[i].titulo, livro)){
			return i;
		}
	}

	return -1;
}

//CRIA UMA LISTA DE ALUNOS.
void CriarListaAlunos(ListaAlunos *Lista){
	Lista->fim = 0;
	return;
}

//CRIA UMA LISTA DE LIVROS.
void CriarListaLivros(ListaLivros *Lista){
	Lista->fim = 0;
	return;
}

void imprime_espera(Livro L){

	int i = 0;

	for(i = L.Fila.inicio; i < L.Fila.fim; i++){
		printf("%s | ", L.Fila.espera[i].nome);
	}

}

void imprime(ListaLivros *Lista){
	int i = 0;
	printf("\n");
	while(i < Lista->fim){
		printf("[%d] - %s\t", i, Lista->livros[i].titulo);
		imprime_espera(Lista->livros[i]);
		i++;
	}
	printf("\n");
}

//CADASTRA UM NOVO ALUNO NA LISTA. RETORNO: 1 SE SUCESSO. 0 SE FRACASSO.
int CadastrarAluno(ListaAlunos *Lista,char *nome,char *NUSP,char *telefone,char *email){
	if(Lista->fim >= tam_lista_alunos) return 0; 
	
	strcpy(Lista->alunos[Lista->fim].nome,nome);
	strcpy(Lista->alunos[Lista->fim].NUSP,NUSP);
	strcpy(Lista->alunos[Lista->fim].telefone,telefone);
	strcpy(Lista->alunos[Lista->fim].email,email);
	Lista->fim+=1;
	
	return 1; 
}

//CADASTRA UM NOVO LIVRO. RETORNO: 1, SE SUCESSO. 0, SE FRACASSO.
int CadastrarLivro(ListaLivros *Lista,char *titulo,char *autor,char *ISBN,char *editora,char *ano,char *edicao,int quantidade){
	int numlivro;
	
	if(Lista->fim >= tam_lista_livros) return 0;
	
	numlivro = BuscaLivro(Lista, titulo);
	
	if(numlivro != -1){
		Lista->livros[numlivro].total += quantidade;	
		return 1;
	}
	
	strcpy(Lista->livros[Lista->fim].titulo,titulo);
	strcpy(Lista->livros[Lista->fim].autor,autor);
	strcpy(Lista->livros[Lista->fim].ISBN,ISBN);
	strcpy(Lista->livros[Lista->fim].editora,editora);
	strcpy(Lista->livros[Lista->fim].ano,ano);
	strcpy(Lista->livros[Lista->fim].edicao,edicao);
	Lista->livros[Lista->fim].total = quantidade;
	Lista->fim+=1;
	
	if(Lista->fim < tam_lista_livros){
		Lista->livros[Lista->fim].Fila.total=0;
		Lista->livros[Lista->fim].Fila.inicio=0;
		Lista->livros[Lista->fim].Fila.fim=0;
	}

	return 1;
}

//EMPRÉSTIMO DE UM LIVRO. RETORNO: 1, SE SUCESSO. 0, SE FRACASSO.
int EmprestaLivro(ListaAlunos *ListaAluno,char *aluno,ListaLivros *ListaLiv,char *livro){
	int numaluno,numlivro;
	
	numaluno = BuscaAluno(ListaAluno,aluno); //Implementar esta função
	numlivro = BuscaLivro(ListaLiv,livro);

	//Se não houverem livros disponíveis
	if(ListaLiv->livros[numlivro].total==0){
	    ListaLiv->livros[numlivro].Fila.espera[ListaLiv->livros[numlivro].Fila.fim] = ListaAluno->alunos[numaluno];
	    ListaLiv->livros[numlivro].Fila.fim += 1;
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
	
	if(Lista->livros[numlivro].Fila.total > 0){
		Lista->livros[numlivro].Fila.inicio += 1;
	    Lista->livros[numlivro].Fila.total -= 1;
	    Lista->livros[numlivro].total -= 1;
	}
}

//REMOVE UM LIVRO DA BIBLIOTECA, COLOCA O ULTIMO LIVRO NO LUGAR DO LIVRO RETIRADO.
void RemoverLivro(ListaLivros *Lista,char *livro){
	int numlivro;

	numlivro = BuscaLivro(Lista,livro);
	
	if(numlivro == tam_lista_livros - 1){
		Lista->fim -= 1; 
		return;
	}
	strcpy(Lista->livros[numlivro].titulo, Lista->livros[Lista->fim -1].titulo);
	strcpy(Lista->livros[numlivro].autor, Lista->livros[Lista->fim -1].autor);
	strcpy(Lista->livros[numlivro].ISBN, Lista->livros[Lista->fim -1].ISBN);
	strcpy(Lista->livros[numlivro].editora, Lista->livros[Lista->fim -1].editora);
	strcpy(Lista->livros[numlivro].ano, Lista->livros[Lista->fim -1].ano);
	strcpy(Lista->livros[numlivro].edicao, Lista->livros[Lista->fim -1].edicao);
	
	Lista->livros[numlivro].Fila.total=Lista->livros[Lista->fim -1].Fila.total;
	Lista->livros[numlivro].Fila.inicio=Lista->livros[Lista->fim -1].Fila.inicio;
	Lista->livros[numlivro].Fila.fim=Lista->livros[Lista->fim -1].Fila.fim;	
	
	Lista->livros[Lista->fim -1].Fila.total = 0;
	Lista->livros[Lista->fim -1].Fila.inicio = 0;
	Lista->livros[Lista->fim -1].Fila.fim = 0;


	Lista->livros[numlivro].total = Lista->livros[Lista->fim -1].total;
	Lista->fim -= 1; 
}

//REMOVE UM ALUNO DA BIBLIOTECA, COLOCA O ULTIMO ALUNO NO LUGAR DO ALUNO RETIRADO.
void RemoverAluno(ListaAlunos *Lista,char *aluno){
	int numaluno;
	int i = 0;
	int j = 0;

	numaluno = BuscaAluno(Lista,aluno);

	if(numaluno == tam_lista_alunos - 1){
		Lista->fim -= 1; 
		return;
	}
	strcpy(Lista->alunos[numaluno].nome, Lista->alunos[Lista->fim].nome);
	strcpy(Lista->alunos[numaluno].NUSP, Lista->alunos[Lista->fim].NUSP);
	strcpy(Lista->alunos[numaluno].telefone, Lista->alunos[Lista->fim].telefone);
	strcpy(Lista->alunos[numaluno].email,Lista->alunos[Lista->fim].email);

	Lista->fim -= 1; 
}

