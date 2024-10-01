#include <stdio.h>
#include <string.h>
void linha() {
	printf("___________\n");

}
typedef struct{ //variaveis dos produtos
float id;
float qtd;
float unidade;
float frete;
float desconto;
float valortotal;
char nproduto[100];


}produto;

typedef struct{   // variaveis dos fornecedores
    float id;
	char nome[100],contato[100],email[100],tipo[100],cnpj[100],cep[100];
}inserir;

inserir cadastro(inserir fornecedor[],int arrayforne) {         //cadastrar fornecedor
inserir x;
int existir=0;
int j;
int compnome;
int compcnpj;
int compcontato;
int compemail;
int compcep;
    printf("Fale o numero do id\n");
    scanf("%f", &x.id);
    for(j=0;j<arrayforne;j++){
       if(fornecedor[j].id ==x.id){
            existir=1;
            break;
       }
    }
    if(existir){
        printf("ID ja cadastradon\n");
        printf("Fale o numero do id\n");
    scanf("%f", &x.id);
    }
    getchar(); 

    printf("Fale o nome\n");
    fgets(x.nome, sizeof(x.nome), stdin);
    x.nome[strcspn(x.nome, "\n")] = 0; 
    
    strcmp(x.nome,fornecedor[j].nome);
for(j=0;j<arrayforne;j++){
    compnome = strcmp(x.nome,fornecedor[j].nome);
       if(compnome == 0){
           printf("a\n");
            existir=1;
            break;
       }
    }
if(existir){
        printf("Nome ja cadastrado\n");
        printf("escreva outro nome\n");
    fgets(x.nome, sizeof(x.nome), stdin);
    x.nome[strcspn(x.nome, "\n")] = 0; 
    }


    printf("Fale o cnpj\n");
    fgets(x.cnpj, sizeof(x.cnpj), stdin);
    x.cnpj[strcspn(x.cnpj, "\n")] = 0; 
    for(j=0;j<arrayforne;j++){
    compcnpj = strcmp(x.cnpj,fornecedor[j].cnpj);
       if(compcnpj == 0){
           printf("a\n");
            existir=1;
            break;
       }
    }
if(existir){
        printf("Cnpj ja cadastrado\n");
        printf("escreva outro cnpj\n");
    fgets(x.cnpj, sizeof(x.cnpj), stdin);
    x.cnpj[strcspn(x.cnpj, "\n")] = 0; 
    }

    printf("Fale o contato\n");
    fgets(x.contato, sizeof(x.contato), stdin);
    x.contato[strcspn(x.contato, "\n")] = 0; 
    
    for(j=0;j<arrayforne;j++){
    compcontato = strcmp(x.contato,fornecedor[j].contato);
       if(compcontato == 0){
           printf("a\n");
            existir=1;
            break;
       }
    }
if(existir){
        printf("Contato ja cadastrado\n");
        printf("escreva outro contato\n");
    fgets(x.contato, sizeof(x.contato), stdin);
    x.contato[strcspn(x.contato, "\n")] = 0; 
    }

    printf("Fale o email\n");
    fgets(x.email, sizeof(x.email), stdin);
    x.email[strcspn(x.email, "\n")] = 0; 
    
    for(j=0;j<arrayforne;j++){
    compemail = strcmp(x.email,fornecedor[j].email);
       if(compemail == 0){
           printf("a\n");
            existir=1;
            break;
       }
    }
if(existir){
        printf("email ja cadastrado\n");
        printf("escreva outro email\n");
    fgets(x.email, sizeof(x.email), stdin);
    x.email[strcspn(x.email, "\n")] = 0; 
    }


    printf("Fale o cep\n");
    fgets(x.cep, sizeof(x.cep), stdin);
    x.cep[strcspn(x.cep, "\n")] = 0; 
 
    for(j=0;j<arrayforne;j++){
    compcep = strcmp(x.cep,fornecedor[j].cep);
       if(compcep == 0){
           printf("a\n");
            existir=1;
            break;
       }
    }
if(existir){
        printf("Cep ja cadastrado\n");
        printf("escreva outro cep\n");
    fgets(x.cep, sizeof(x.cep), stdin);
    x.cep[strcspn(x.cep, "\n")] = 0; 
    }


    printf("Fale o tipo\n");
    fgets(x.tipo, sizeof(x.tipo), stdin);
    x.tipo[strcspn(x.tipo, "\n")] = 0; 
     return x;
}
produto cadproduto(produto prod[], int arrayprod,int arrayforne,inserir fornecedor[]){ //cadastrar os produtos
 
    produto y;
    float prodfornecedor;
    int existi=0;
    int j;
    
    printf("Em qual fornecedor voce ira cadastrar o produto?\n");
 scanf("%f",&prodfornecedor); 

  for(j=0;j<prodfornecedor;j++){
if(fornecedor[j].id !=prodfornecedor){
    printf("Nenhum id localizado \n");

  
    
}
}


   getchar();
    printf("Escreva o id do produto\n");
    scanf("%f",&y.id);
     for(j=0;j<arrayprod;j++){
        if(prod[j].id == y.id){
            
            existi=1;
            break;
        }
    }
    
    if(existi){
        printf("ID ja existente cadastre outro\n");
        printf("Escreva o id do produto\n");
    scanf("%f",&y.id);
        
        
    }
 
    getchar();
    
    printf("Escreva o nome do produto\n");
    fgets(y.nproduto,sizeof(y.nproduto),stdin);
    y.nproduto[strcspn(y.nproduto, "\n")] = 0; 
    printf("Escreva a quantidade de produto\n");
    scanf("%f",&y.qtd);
    getchar();
    
    printf("escreva o valor do produto\n");
    scanf("%f",&y.unidade);
    getchar();
    
    printf("Escreva o valor do frete");
scanf("%f",&y.frete);
    getchar();
    
     printf("Escreva o valor do desconto");
scanf("%f",&y.desconto);
    getchar();
    y.valortotal=((((y.qtd)*(y.unidade))+y.frete)-y.desconto);
return y;
}

void tabela1() {       //Tabela principal
	printf("|ID|");
	printf("|NOME    |");
	printf("|CNPJ|");
	printf("|CONTATO|");
	printf("|EMAIL|");
	printf("|CEP|");
	printf("|TIPO|");

}

void subproduto(produto y){ // os dados dos produtos
    printf("|%.f|%s|%.2f|%.2f|%.2f|%.2f|%.2f|",y.id,y.nproduto,y.qtd,y.unidade,
    y.frete,y.desconto,y.valortotal);
}

void subtabela(inserir x){ //os dados dos fornecedores
   
     printf("|%.f|%s|%s|%s|%s|%s|%s|\n", x.id, x.nome, x.cnpj, x.contato,
           x.email, x.cep, x.tipo);
    
}

void tabela2(){ //tabela dos produtos
    printf("|ID|");
    printf("|PRODUTO|");
    printf("|QUANTIDADE|");
    printf("|PRECO UNITARIO|");
    printf("|FRETE|");
    printf("|DESCONTO|");
    printf("|TOTAL|");
    
}

int main()

{ produto prod[100];

     inserir fornecedor[100]; 
    inserir x;
    int arrayprod=0,arrayforne=0;
    int i,j;
x.id = 0;
    strcpy(x.nome, "");
    strcpy(x.contato, "");
    strcpy(x.email, "");
    strcpy(x.tipo, "");
    strcpy(x.cnpj, "");
    strcpy(x.cep, "");
	int numero;
do{
    linha();
	printf("1-Cadastrar fornecedor\n");
	printf("2-Mostrar tabela dos fornecedores\n");
	printf("3-Cadastrar produto\n");
	printf("4-Mostrar tabela dos produtos\n");
	printf("5-Sair \n");
	printf("escolha a opcao\n");
	scanf("%d",&numero);

	switch(numero) {
	case 1:
	   fornecedor[arrayforne++] = cadastro(fornecedor,arrayforne);
	break;
	case 2:
		linha();
		tabela1();
		printf("\n");
		for(i=0;i<arrayforne;i++){
		subtabela(fornecedor[i]);
		}
		printf("\n");
		break;
case 3:

prod[arrayprod++]=cadproduto(prod, arrayprod,arrayforne, fornecedor);
printf("\n");
break;

case 4:
linha();
	subtabela(fornecedor[i]);
	
tabela2();
printf("\n");
for(j=0;j<arrayprod;j++){
subproduto(prod[j]);
printf("\n");
}
printf("\n");
break;
}
}while(numero !=5);	

	return 0;
}