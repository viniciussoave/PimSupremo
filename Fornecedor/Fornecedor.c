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

//espacamento para a subtabelanome
void espacamento(int k,int arrayforne,inserir fornecedor[],int* maiorValor){
 int j;
    *maiorValor = 0;
if (arrayforne == 0) {
        return;
    }
    
    for (j = 0; j < arrayforne; j++) {
        int comprimentoNome = strlen(fornecedor[j].nome);
        if (comprimentoNome > *maiorValor) {
            *maiorValor = comprimentoNome;
        }
    }

   
    for (int l = 0; l < (*maiorValor - k + 0); l++) {
        printf(" ");
    }
}

//espacamento para a tabela
void espacatipo(int k,int arrayforne,inserir fornecedor[],int* maiortipo){
 int j;
    *maiortipo = 0;
if (arrayforne == 0) {
        return;
    }
    
    for (j = 0; j < arrayforne; j++) {
        int comprimentoTipo = strlen(fornecedor[j].tipo);
        if (comprimentoTipo > *maiortipo) {
            *maiortipo = comprimentoTipo;
        }
    }

   
    for (int l = 4; l < (*maiortipo - k + 0); l++) {
        printf(" ");
    }
}

//espcamento subtabela
void espacatipo1(int k,int arrayforne,inserir fornecedor[],int* maiortipo){
 int j;
    *maiortipo = 0;
if (arrayforne == 0) {
        return;
    }
    
     for (j = 0; j < arrayforne; j++) {
        int comprimentoTipo = strlen(fornecedor[j].tipo);
        if (comprimentoTipo > *maiortipo) {
            *maiortipo = comprimentoTipo;
        }
    }
   
    for (int l = 0; l < (*maiortipo - k + 0); l++) {
        printf(" ");
    }
}


//espacamento para gmail tabela
void espacagmail(int k,int arrayforne,inserir fornecedor[],int* maioremail){
 int j;
    *maioremail = 0;
if (arrayforne == 0) {
        return;
    }
    
    for (j = 0; j < arrayforne; j++) {
        int comprimentoNome = strlen(fornecedor[j].email);
        if (comprimentoNome > *maioremail) {
            *maioremail = comprimentoNome;
        }
    }

   
    for (int l = 5; l < (*maioremail - k + 0); l++) {
        printf(" ");
    }
}

//espacamento para gmail subtabela
void espacagmail1(int k,int arrayforne,inserir fornecedor[],int* maioremail){
 int j;
    *maioremail = 0;
if (arrayforne == 0) {
        return;
    }
    
     for (j = 0; j < arrayforne; j++) {
        int comprimentoEmail = strlen(fornecedor[j].email);
        if (comprimentoEmail > *maioremail) {
            *maioremail = comprimentoEmail;
        }
    }
   
    for (int l = 0; l < (*maioremail - k + 0); l++) {
        printf(" ");
    }
}

inserir cadastro(inserir fornecedor[],int arrayforne) {         //cadastrar fornecedor
inserir x;
int existir=0;
int existir2=0;
int existir3=0;
int existir4=0;
int existir5=0;
int existir6=0;
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
            existir2=1;
            break;
       }
    }
if(existir2){
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
            existir3=1;
            break;
       }
    }
if(existir3){
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
            existir4=1;
            break;
       }
    }
if(existir4){
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
            existir5=1;
            break;
       }
    }
if(existir5){
        printf("email ja cadastrado\n");
        printf("escreva outro email\n");
    fgets(x.email, sizeof(x.email), stdin);
    x.email[strcspn(x.email, "\n")] = 0; 
    }


    printf("Fale o cep\n");
    fgets(x.cep, sizeof(x.cep), stdin);
    x.cep[strcspn(x.cep, "\n")] = 0; 
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


void cnpjvoid( char *cnpj){ //formatacao do cnpj
    char cnpjcerto[20];
    snprintf(cnpjcerto, sizeof(cnpjcerto), "%c%c.%c%c%c.%c%c%c/%c%c%c%c-%c%c",
     cnpj[0],cnpj[1],
     cnpj[2],cnpj[3],cnpj[4],
     cnpj[5],cnpj[6],cnpj[7],
     cnpj[8],cnpj[9],cnpj[10],cnpj[11],
     cnpj[12],cnpj[13]);
    printf("%s|",cnpjcerto);
    
}

void telefone(char *tele){//formatacao do contato
    char tele1[18];
    snprintf(tele1,sizeof(tele1),"(%c%c)%c%c%c%c%c-%c%c%c%c",
   tele[0],tele[1],
   tele[2],tele[3],tele[4],tele[5],tele[6],
   tele[7],tele[8],tele[9],tele[10]);
   printf("%s",tele1);
}


void cepcerto( char *cep){ //formatacao cep
    char cep1[13];
    snprintf(cep1,sizeof(cep1),"%c%c%c%c%c-%c%c%c",
    cep[0],cep[1],cep[2],cep[3],cep[4],
    cep[5],cep[6],cep[7]);
    printf("|%s",cep1);
}


void subproduto(produto y){ // os dados dos produtos
    printf("|%.f|%s|%.2f|%.2f|%.2f|%.2f|%.2f|",y.id,y.nproduto,y.qtd,y.unidade,
    y.frete,y.desconto,y.valortotal);
}

void subtabela(inserir x, int arrayforne, inserir fornecedor[]) {
    int l;
    int maiorValor;
    int k = strlen(x.nome);
    
    printf("|%3.f|", x.id);
    printf("%s", x.nome);
    
    espacamento(k, arrayforne, fornecedor, &maiorValor);
    printf("|");

    cnpjvoid(x.cnpj);
    telefone(x.contato);
    printf("|%s", x.email);
    espacagmail1(strlen(x.email), arrayforne, fornecedor, &maiorValor); // Verifique a passagem do comprimento correto
    cepcerto(x.cep);
    printf("|%s", x.tipo);
    espacatipo1(strlen(x.tipo), arrayforne, fornecedor, &maiorValor);
    printf("|\n");
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


//espacamento para tabela nome
void espacamento2(int k,int arrayforne,inserir fornecedor[],int* maiorValor){ 
 int j;
    *maiorValor = 0;

 
    for (j = 0; j < arrayforne; j++) {
        int comprimentoNome = strlen(fornecedor[j].nome);
        if (comprimentoNome > *maiorValor) {
            *maiorValor = comprimentoNome;
        }
    }

   
    for (int l = 4; l < (*maiorValor - k + 0); l++) {
        printf(" ");
    }
}

void tabela1(int arrayforne, inserir fornecedor[]) {       //Tabela principal
int l;
int maiorValor;

  for (int j = 0; j < arrayforne; j++) {
        int comprimentoNome = strlen(fornecedor[j].nome);
        if (comprimentoNome > maiorValor) {
            maiorValor = comprimentoNome;
        }
    }
	printf("|ID ");
printf("|NOME");
 espacamento2(0, arrayforne, fornecedor, &maiorValor);
	printf("|CNPJ              ");
	printf("|CONTATO       ");
	printf("|EMAIL");
	espacagmail(0, arrayforne, fornecedor, &maiorValor);
	printf("|CEP      ");
	printf("|TIPO");
	espacatipo(0, arrayforne, fornecedor, &maiorValor);
printf("|");
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
		 tabela1(arrayforne, fornecedor);
		
		printf("\n");
		for(i=0;i<arrayforne;i++){
			subtabela(fornecedor[i],arrayforne,fornecedor);
		}
		printf("\n");
		break;
case 3:

prod[arrayprod++]=cadproduto(prod, arrayprod,arrayforne, fornecedor);
printf("\n");
break;

case 4:
linha();
	subtabela(fornecedor[i],arrayforne,fornecedor);
	
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
