#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "estatica.h"
//#include "dinamica.h"

char *readline(){
	int counter=0;
	char c=0, *string=NULL;

	do{
		c = fgetc(stdin);
		string = (char *)realloc(string, sizeof(char)*(counter+1));
		string[counter++] = c;
	}while(c!=10);

	string[counter-1] = '\0';

	return string;
}

//FUNCAO PARA IMPRESSAO DE UM MENU FUNCIONAL NAS PRINCIPAIS ITERACOES COM O SISTEMA
void menu(){

	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>> BIBLIOTECA <<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
	printf("O que voce deseja?\n\t0 - SAIR\n\t1 - CADASTRAR LIVRO\n\t2 - CADASTRAR ALUNO\n\t3 - EMPRESTAR LIVRO\n\t4 - DEVOLVER LIVRO\n\t5 - REMOVER LIVRO\n\t6 - REMOVER ALUNO\n\t7 - CHECAR MENSAGENS DE ALUNO\nOperacao: ");

}


int main (int argc, char *argv[]){
	ListaLivros B;
	ListaAlunos A;
	int op = 1, flag = 0, quantidade;
	char *nome = NULL, *NUSP = NULL, *telefone = NULL, *email = NULL,
		*titulo = NULL, *autor = NULL, *ISBN = NULL, *editora = NULL, *ano = NULL, *edicao = NULL;

	CriarListaLivros(&B);
	CriarListaAlunos(&A);

	while (op != 0){
		menu();
		scanf("%d", &op);
		switch(op){
			case 0://SAIR DO PROGRAMA
				break;
			case 1://CADASTRAR LIVRO
					printf("-> Cadastro de Livro ---------------------------------------\n");
					fgetc(stdin);
					printf("Titulo: ");
					titulo = readline();
					printf("Autor: ");
					autor = readline();
					printf("ISBN: ");
					ISBN = readline();
					printf("Editora: ");
					editora  = readline();
					printf("Ano: ");
					ano = readline();
					printf("Edicao: ");
					edicao = readline();
					printf("Quantidade: ");
					scanf("%d", &quantidade);
					flag = CadastrarLivro(&B, titulo, autor, ISBN, editora, ano, edicao, quantidade);
					//printf("\nFLAG = %d\n", flag);
					if(flag) printf("\n-> Livro cadastrado com sucesso \n------------------------------------------------------------\n");
					else printf("\n-> Livro nao pode ser cadastrado \n------------------------------------------------------------\n");
				break;
			case 2://CADASTRAR ALUNO
					printf("-> Cadastro de Aluno ---------------------------------------\n");
					fgetc(stdin);
					printf("Nome: ");
					nome = readline();
					printf("NUSP: ");
					NUSP = readline();
					printf("Telefone: ");
					telefone = readline();
					printf("Email: ");
					email = readline();
					flag = CadastrarAluno(&A, nome, NUSP, telefone, email);
					if(flag) printf("\n-> Aluno cadastrado com sucesso \n------------------------------------------------------------\n");
					else printf("\n-> Aluno nao pode ser cadastrado \n------------------------------------------------------------\n");
				break;
			case 3://EMPRESTAR LIVRO
					printf("-> Emprestimo de Livro ---------------------------------------\n");
					fgetc(stdin);
					printf("Nome do Aluno: ");
					nome = readline();
					printf("Titulo do Livro: ");
					titulo = readline();
					flag = EmprestaLivro(&A, nome, &B, titulo);
					if(flag == 1) printf("\n-> Emprestimo realizado com sucesso \n------------------------------------------------------------\n");
					if(flag == 0) printf("\n-> Emprestimo nao realizado. Voce esta na fila de espera!\n------------------------------------------------------------\n");
                    if(flag == 2) printf("\n-> Aluno não encontrado \n------------------------------------------------------------\n");
                    if(flag == 3) printf("\n-> Livro não encontrado \n------------------------------------------------------------\n");
				break;
			case 4://DEVOLVER LIVRO
					printf("-> Devolucao de Livro ---------------------------------------\n");
					fgetc(stdin);
					printf("Titulo: ");
					titulo = readline();
					DevolveLivro(&B, titulo);
					printf("\n-> Livro devolvido!\n------------------------------------------------------------\n");
				break;
			case 5://REMOVER LIVRO
					printf("-> Remocao de Livro ---------------------------------------\n");
					fgetc(stdin);
					printf("Titulo: ");
					titulo = readline();
					RemoverLivro(&B, titulo);
					printf("\n-> Livro removido!\n------------------------------------------------------------\n");
				break;
			case 6://REMOVER ALUNO
					printf("-> Remocao de Aluno ---------------------------------------\n");
					fgetc(stdin);
					printf("Nome: ");
					nome = readline();
					RemoverAluno(&A, nome, &B);
					printf("\n-> Aluno removido!\n------------------------------------------------------------\n");
				break;
			case 7://IMPRIMIR MENSAGENS DO ALUNO
					printf("-> Checar mensagens ---------------------------------------\n");
					fgetc(stdin);
					printf("Nome: ");
					nome = readline();
					Imprime_Mensagem(&A,nome);
					printf("\n-> Caixa de mensagens esvaziada!\n------------------------------------------------------------\n");
				break;
		}

		imprime(&B);
		imprime_alunos(&A);
	}

	LiberaMemoria(&A, &B);

	return 0;
}
