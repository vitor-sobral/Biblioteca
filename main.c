#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
	char *nome;		//NOME COMPLETO DO ALUNO
	char *usp;		//NUMERO USP DO ALUNO (STRING POIS PODE VIR A TER MUITOS DÍGITOS)
	char *telefone;	//NUMERO DE TELEFONE DO ALUNO PARA CONTATO (PODE TER MUITO MAIS DÍGITOS DO QUE UM INTEIRO PODE ARMAZENAR)
	char *email;	//EMAIL DO ALUNO PARA CONTATO
} Aluno;

typedef struct livro{
	char *titulo;	//TÍTULO DO LIVRO
	char *autor;	//NOME DO AUTOR
	char *isbn;		//ISBN DO LIVRO (NUMERO MUITO GRANDE PARA SER ARMAZENADO EM INT)
	char *editora;	//NOME DA EDITORA 
	int ano;		//ANO DA EDICAO
	int edicao;		//NUMERO DA EDICAO
	int copias;		//NUMERO DE CÓPIAS (DISPONÍVEIS)
	Fila *espera;	//FILA DE ESPERA DE ALUNOS
} Livro;

//FUNÇÃO DE CRIAÇÃO DA BIBLIOTECA (VÁLIDA TANTO PARA ESTÁTICA QUANTO PARA DINÂMICA?????????)
void cria_biblioteca(Biblioteca *B){
	
	B->n_livros = 0;
	B->livros = NULL;
}

//FUNÇÃO PARA IMPRESSÃO DE UM MENU FUNCIONAL NAS PRINCIPAIS ITERAÇÕES COM O SITEMA
void menu(){

	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>> BIBLIOTECA <<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
	printf("O que voce deseja?\n\t0 - SAIR\n\t1 - CADASTRAR LIVRO\n\t2 - RETIRAR LIVRO\n\t3 - DEVOLVER LIVRO\n\t4 - REMOVER LIVRO\nOperacao: ");

}


int main (int argc, char *argv[]){
	Biblioteca B;
	int op = 1, erro = 0;;

	cria_biblioteca(&B);

	while (op != 0){
		menu();
		scanf("%d", &op);

		switch(op){
			case 0://SAIR DO PROGRAMA
				break;	
			case 1://CADASTRAR LIVRO
				break;
			case 2://RETIRAR LIVRO
				break;
			case 3://DEVOLVER LIVRO
				break;
			case 4://REMOVER LIVRO
				break;
		}
		system("clear");
	}

	return 0;
}