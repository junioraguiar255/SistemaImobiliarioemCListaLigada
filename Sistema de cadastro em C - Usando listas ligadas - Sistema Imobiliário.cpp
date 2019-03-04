#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct imoveis Imoveis;
typedef struct vendedor Vendedor;

struct vendedor {
	int idVendedor, qtdvenda;
	char nome[20];
};



struct imoveis {
	Vendedor v;
	int id;
	int cep, statusVenda, idVendido;
	struct imoveis* prox;
};



Imoveis* inicializaNULL()
{
	return NULL;
}
Imoveis* criaNo()
{
	Imoveis *novo = (Imoveis*) malloc (sizeof(Imoveis));
	return novo;
}

Imoveis* insereEstatico(Imoveis* cabeca, int cep, int id)
{
	Imoveis *novo = criaNo();
	novo->cep = cep;
	novo->id = id;
	novo->statusVenda = 0;
	if(cabeca == NULL) {
		cabeca = novo;
		novo->prox = NULL;
	} else {
		novo->prox = cabeca;
		cabeca = novo;
	}
	return cabeca;
}





Imoveis* insere(Imoveis* cabeca)
{
	Imoveis *novo = criaNo();
	printf("\n Escreva o CEP do imovel \n");
	scanf("%d", &novo->cep);
	printf("\n Escreva o id do imovel  \n");
	scanf("%d", &novo->id);
	novo->statusVenda = 0;
	if(cabeca == NULL) {
		novo->prox = NULL;
		cabeca = novo;
	} else {
		Imoveis *aux = cabeca;
		while(aux->prox != NULL) {
			aux = aux->prox;
		}
		novo->prox = NULL;
		aux->prox = novo;
	}
	return cabeca;

}
void ListasVendasRealizadas(Imoveis *cabeca)
{
	Imoveis *aux = cabeca;
	while(aux != NULL) {
		if(aux->statusVenda == 1) {
			printf("ID vendido: %d \n ", aux->id);
			printf("CEP vendido: %d \n", aux->cep);
		}

		aux = aux->prox;
	}
	getch();
}


void listarAvenda(Imoveis* cabeca)
{
	Imoveis *aux = cabeca;


	if(cabeca == NULL) {
		printf("\n Sem cadastros armazenados");
	} else {
		system("CLS");
		printf("\n Imoveis cadastrados : \n");
		while(aux != NULL) {
			if(aux->statusVenda == 0) {
				printf("CEP do imovel  \n  %d ", aux->cep);
				printf("\n  ID DO imovel  \n  %d  \n", aux->id);

			}
			aux = aux->prox;
		}
	}

}
void realizarVenda(Imoveis* cabeca)
{
	Imoveis *aux = cabeca;
	int op;
	printf("Digite o id do imovel a ser vendido: \n");
	scanf("%d", &op);
	while(aux != NULL && aux->id != op) {
		aux = aux->prox;

	}
	if(aux == NULL) {
		printf("\n Imovel não encontrado");

	} else {
		aux->statusVenda = 1;
		printf("\n Imovel vendido");

	}
	printf("\n Pressione qualquer tecla para continuar");
	getch();


}

Imoveis* excluir(Imoveis* cabeca)
{
	Imoveis* aux = cabeca;
	Imoveis* anterior = NULL;
	int codigo = 0;

	printf("\n Digite o codigo do imovel a ser excluido:   \n");
	scanf("%d", &codigo);



	while(aux != NULL && aux->id != codigo) {
		anterior = aux;
		aux = aux->prox;
	}



	if(aux == NULL) {
		printf("Imovel nao encontrado  ");
		getch();
		return cabeca;
	}
	if(anterior == NULL) {

		cabeca = aux->prox;


		printf("\n  Conteudo excluido com sucesso.  ");
		getch();



	} else {
		printf(" Conteudo excluido com sucesso  ");
		anterior->prox = aux->prox;
		getch();

	}
	free(aux);
	return cabeca;



}


void alterarCadImovel(Imoveis* cabeca)
{
	int cepAux, cod;
	Imoveis *aux = cabeca;
	printf("\n Digite o codigo do imovel para ser alterado: \n");
	scanf("%d", &cod);
	while(aux != NULL && aux->id != cod) {
		aux = aux->prox;
	}
	if(aux != NULL) {
		printf("\n Digite o novo CEP do id %d : \n", cod);
		scanf("%d", &cepAux);
		aux->cep = cepAux;
		printf("\n =>  Dados alterados com sucesso");
		getch();
	} else {
		printf("\n Imovel nao encontrado");
	}
	printf("\n Pressione qualquer tecla para continuar");
}

void escreveMenu()
{
	printf("==================== Cadastro de imoveis  ====================\n");
	printf("==================== 1 - Novo cadastro  ====================\n");
	printf("==================== 2 - Listar moveis a venda ==================== \n");
	printf("==================== 3 - Excluir cadastro  ====================\n");
	printf("==================== 4 - Alterar cadastro  ====================\n");
	printf("==================== 5 - Realizar venda ====================\n");
	printf("==================== 6 - Listar vendas realizadas ====================\n");
	printf("==================== 0 - Sair  ====================\n");

}



void executaMenu(Imoveis* cabeca, int escolha)
{

	switch(escolha) {
	case 1:
		printf("==================== NOVO CADASTRO  ====================\n");
		cabeca = insere(cabeca);
		getch();
		system("cls");
		break;
	case 2:
		printf("==================== Imoveis a venda  ====================\n");
		listarAvenda(cabeca);
		getch();
		break;
	case 3:
		printf("\n====================  Exclusao de cadastros ====================\n");
		cabeca = excluir(cabeca);
		getch();
		break;
	case 4:
		printf("==================== Alterando cadastros ====================\n");
		alterarCadImovel(cabeca);
		break;
	case 5:
		printf("==================== Vendendo Imoveis ====================\n");
		realizarVenda(cabeca);
		break;
	case 6:
		printf("==================== Listando vendas ====================\n");
		ListasVendasRealizadas(cabeca);
		break;
	default:
		break;
	}
}


int main()
{

	Imoveis *cabeca;
	cabeca = inicializaNULL();
	cabeca = insereEstatico(cabeca, 65602300, 1);
	int opc;
	while(opc != 0) {
		system("CLS");
		escreveMenu();
		printf("==================== Digite a sua opcao=========\n");
		scanf("%d", &opc);
		executaMenu(cabeca, opc);
	}
	return 0;
}

