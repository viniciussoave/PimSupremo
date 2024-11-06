

#include <stdio.h>
#include <string.h>




void linha() {
	printf("___________\n");

}


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

int j;
int compnome;int compcnpj;int compemail;int compcontato;

    printf("Fale o numero do id\n");
    scanf("%f", &x.id);
    while (x.id < 0 || x.id >= 1000) {
    printf("Escreva um id de 0 até 999\n");
    printf("Fale o numero do id\n");
    scanf("%f", &x.id);
}
    
    do{for(j=0;j<arrayforne;j++){
      existir=0;
       if(fornecedor[j].id ==x.id){
            existir=1;
            break;
       }
    }
    if(existir){
        printf("ID ja cadastrado\n");
        printf("Fale o numero do id(1-999)\n");
    scanf("%f", &x.id);
  
    }
    }while(existir);
    getchar(); 

    printf("Fale o nome\n");
    fgets(x.nome, sizeof(x.nome), stdin);
    x.nome[strcspn(x.nome, "\n")] = 0; 
    
   
do{for(j=0;j<arrayforne;j++){
    compnome = strcmp(x.nome,fornecedor[j].nome);
        existir2=0;
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
    }}while(existir2);
    

    printf("Fale o cnpj (apenas numeros(14))\n");
    fgets(x.cnpj, sizeof(x.cnpj), stdin);
    x.cnpj[strcspn(x.cnpj, "\n")] = 0; 
    
    
    //while para ficar apenas os caracter necessario
    while(strlen(x.cnpj)<14){
     
        printf("Escreva um cpnj existente\n");
         printf("Fale o cnpj\n");
    fgets(x.cnpj, sizeof(x.cnpj), stdin);
    x.cnpj[strcspn(x.cnpj, "\n")] = 0;
     
    }
    
    if(strlen(x.cnpj)>14){
        x.cnpj[14]='\0';
    }
    do{for(j=0;j<arrayforne;j++){
    compcnpj = strcmp(x.cnpj,fornecedor[j].cnpj);
       existir3=0;
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
    }}while(existir3);

    printf("Fale o contato (Apenas numero(10 ou 11))\n");
    fgets(x.contato, sizeof(x.contato), stdin);
    x.contato[strcspn(x.contato, "\n")] = 0; 
    
    while(strlen(x.contato)<10){
        printf("Escreva um contato existente\n");
        printf("Fale o contato\n");
    fgets(x.contato, sizeof(x.contato), stdin);
    x.contato[strcspn(x.contato, "\n")] = 0; 
    }
    
    if(strlen(x.contato)>12){
        x.contato[11]='\0';
    }
    
    
    do{for(j=0;j<arrayforne;j++){
    compcontato = strcmp(x.contato,fornecedor[j].contato);
       existir4=0;
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
    }}while(existir4);


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


    printf("Fale o cep(Apenas numero(8))\n");
    fgets(x.cep, sizeof(x.cep), stdin);
    x.cep[strcspn(x.cep, "\n")] = 0; 
    
    if(strlen(x.cep)>8){
        x.cep[8]='\0';
    }
    
    
    
    while(strlen(x.cep)<8){
        printf("Escreva um Cep existente\n");
        fgets(x.cep, sizeof(x.cep), stdin);
    x.cep[strcspn(x.cep, "\n")] = 0; 
    }
    if(strlen(x.cep) > 8) {
    x.cep[8] = '\0'; 
}
    printf("Fale o tipo\n");
    fgets(x.tipo, sizeof(x.tipo), stdin);
    x.tipo[strcspn(x.tipo, "\n")] = 0; 
     return x;
}


void cnpjvoid( char *cnpj){ //formatacao do cnpj
    char cnpjcerto[20];
    int i;
   
  for ( i = 0; i< strlen(cnpj); i++) {
        if (cnpj[i] < '0' || cnpj[i] > '9') {
       cnpj[i]='0';
         
        }
    }
    
    
    snprintf(cnpjcerto, sizeof(cnpjcerto), "%c%c.%c%c%c.%c%c%c/%c%c%c%c-%c%c",
     cnpj[0],cnpj[1],
     cnpj[2],cnpj[3],cnpj[4],
     cnpj[5],cnpj[6],cnpj[7],
     cnpj[8],cnpj[9],cnpj[10],cnpj[11],
     cnpj[12],cnpj[13]);
    printf("%s|",cnpjcerto);
    
}

void telefone(char *tele){//formatacao do contato
    char tele1[19];
int i;
 for ( i = 0; i< strlen(tele); i++) {
        if (tele[i] < '0' || tele[i] > '9') {
      tele[i]='0';
         
        }
    }
int fixo=strlen(tele);

if (fixo == 10) {
        snprintf(tele1, sizeof(tele1), "(%c%c)%c%c%c%c-%c%c%c%c%c",
                 tele[0], tele[1],
                 tele[2], tele[3], tele[4], tele[5], tele[6],
                 tele[7], tele[8], tele[9], tele[10]);
                 printf(" ");
    }
    
    else if (fixo == 11) {
        snprintf(tele1, sizeof(tele1), "(%c%c)%c%c%c%c%c-%c%c%c%c",
                 tele[0], tele[1],
                 tele[2], tele[3], tele[4], tele[5], tele[6],
                 tele[7], tele[8], tele[9], tele[10]);
                 
    }
    printf("%s", tele1);
    }


void cepcerto( char *cep){ //formatacao cep
    char cep1[13];
    int i;
    for ( i = 0; i< strlen(cep); i++) {
        if (cep[i] < '0' || cep[i] > '9') {
       cep[i]='0';
         
        }
    }
    snprintf(cep1,sizeof(cep1),"%c%c%c%c%c-%c%c%c",
    cep[0],cep[1],cep[2],cep[3],cep[4],
    cep[5],cep[6],cep[7]);
    printf("|%s",cep1);
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
    espacagmail1(strlen(x.email), arrayforne, fornecedor, &maiorValor); 
    cepcerto(x.cep);
    printf("|%s", x.tipo);
    espacatipo1(strlen(x.tipo), arrayforne, fornecedor, &maiorValor);
    printf("|\n");
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



//Salvar os arquivos
void arquivosalvar(FILE *arquivo,int arrayforne,inserir fornecedor[]){
    int i;
    for(i=0;i<arrayforne;i++){
   
        fprintf(arquivo," %0.f, ", fornecedor[i].id); 
          fprintf(arquivo, "%s, ", fornecedor[i].nome);
     
        fprintf(arquivo,"%s, ", fornecedor[i].cnpj);
        fprintf(arquivo," %s, ", fornecedor[i].contato);
        fprintf(arquivo," %s, ", fornecedor[i].email);
        fprintf(arquivo," %s, ", fornecedor[i].cep);
        fprintf(arquivo," %s ", fornecedor[i].tipo);
        fprintf(arquivo,"\n");
        
    }
    
   
}

//ler o arquivo
void arquivoleitura(char *arquivo, inserir fornecedor[], int *arrayforne) {
    FILE *file = fopen(arquivo, "r");
    
    
    
     while (fscanf(file, "%f, %99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %99[^\n]\n",
                  &fornecedor[*arrayforne].id,
                  fornecedor[*arrayforne].nome,
                  fornecedor[*arrayforne].cnpj,
                  fornecedor[*arrayforne].contato,
                  fornecedor[*arrayforne].email,
                  fornecedor[*arrayforne].cep,
                  fornecedor[*arrayforne].tipo) == 7) {
        (*arrayforne)++;
    }
    
    
    
    
    
}
// pesquisar 3 opção
void pesquisar1(int arrayforne,inserir fornecedor[],inserir x){
    int number;
    int number2;
    int j;
    int verificar;
      float idnovo;
          int idExistente = 0;
          int i;
          char nomenovo[100];
        int nomeExiste=0;
        int cnpjExiste=0;
        char cnpjnovo[100];
         int contatoExiste=0;
        char contatonovo[100];
         int emailExiste=0;
         char emailnovo[100];
         char cepnovo[100];
        printf("Escreva o id\n");
     scanf("%f",&x.id);
        
    do{ 
         verificar = 0; 
        for (j = 0; j < arrayforne; j++) {
                if (fornecedor[j].id == x.id) { 
                    verificar = 1; 
                    break; 
                }
            }
    if(!verificar){
        printf("ID nao encontrado\n");
        printf("Fale o numero do id\n");
    scanf("%f", &x.id);
    }
    }while(!verificar);
     printf("====== Fornecedor ======\n");
          printf("ID encontrado: %0.f\n", x.id); 
          printf("Nome: %s\n", fornecedor[j].nome);
        printf("CNPJ: %s\n", fornecedor[j].cnpj);
        printf("Contato: %s\n", fornecedor[j].contato);
        printf("Email: %s\n", fornecedor[j].email);
        printf("CEP: %s\n", fornecedor[j].cep);
        printf("Tipo: %s\n", fornecedor[j].tipo);
         printf("=======================\n");
        printf("o que voce quer fazer\n");
        printf("1-Modificar algum dado\n");
        printf("2-Sair\n");
        scanf("%d",&number);
if(number ==1){
   printf("o que voce quer modificar?\n");
   printf("1-ID\n");
   printf("2-Nome\n");
   printf("3-CNPJ\n");
   printf("4-Contato\n");
   printf("5-Email\n");
   printf("6-Cep\n");
   printf("7-Tipo\n");
   printf("=======================\n");
   scanf("%d",&number2);
      getchar(); 
   switch(number2){
       case 1:
       {
                    printf("Informe o novo ID:\n");
                    scanf("%f", &idnovo);
                while (idnovo< 0 || idnovo >= 1000) {
    printf("Escreva um id de 0 até 999\n");
    printf("Fale o numero do id\n");
    scanf("%f", &idnovo);
}
                    for (i = 0; i < arrayforne; i++) {
                        if (fornecedor[i].id == idnovo) {
                            idExistente = 1; 
                            break;
                        }
                    }

                    if (!idExistente) {
                        fornecedor[j].id = idnovo;
                        printf("Novo id: %.0f\n", idnovo);
                    } else {
                        printf("ID já existente\n");
                    }
                }
       
       break;
        case 2:
        
        printf("Informe o novo nome:\n");
        fgets(nomenovo, sizeof(nomenovo), stdin);
        nomenovo[strcspn(nomenovo, "\n")] = '\0';
        
    for (i = 0; i < arrayforne; i++) {
    if(strcmp(fornecedor[i].nome,nomenovo)==0){
        nomeExiste=1;
        break;
    }
    }
    if(!nomeExiste){
        strcpy(fornecedor[j].nome,nomenovo);
        printf("nome novo é %s\n",nomenovo);
    }else{
         printf("Nome já existente\n");
    }
        
        
        break;
        case 3:
        
        printf("Informe o cnpj\n");
        fgets(cnpjnovo, sizeof(cnpjnovo), stdin);
        cnpjnovo[strcspn(cnpjnovo, "\n")] = '\0';
        while(strlen(cnpjnovo)<14){
     
        printf("Escreva um cpnj existente(14 numeros)\n");
         printf("Fale o cnpj\n");
    fgets(cnpjnovo, sizeof(cnpjnovo), stdin);
    cnpjnovo[strcspn(cnpjnovo, "\n")] = 0;
     
    }
    
    if(strlen(cnpjnovo)>14){
        cnpjnovo[14]='\0';
    }
    for (i = 0; i < arrayforne; i++) {
    if(strcmp(fornecedor[i].cnpj,cnpjnovo)==0){
        cnpjExiste=1;
        break;
    }
    }
    if(!cnpjExiste){
        strcpy(fornecedor[j].cnpj,cnpjnovo);
        printf("cnpj novo é %s\n",cnpjnovo);
    }else{
         printf("cnpj já existente\n");
    }
        
        
        break;
        
        case 4:
       
        printf("Informe o contato\n");
         fgets(contatonovo, sizeof(contatonovo), stdin);
        contatonovo[strcspn(contatonovo, "\n")] = '\0';
        while(strlen(contatonovo)<10){
        printf("Escreva um contato existente\n");
        printf("Fale o contato\n");
    fgets(contatonovo, sizeof(contatonovo), stdin);
    contatonovo[strcspn(contatonovo, "\n")] = 0; 
    }
    
    if(strlen(contatonovo)>11){
        contatonovo[11]='\0';
    }
        
        
        
    for (i = 0; i < arrayforne; i++) {
    if(strcmp(fornecedor[i].contato,contatonovo)==0){
        contatoExiste=1;
        break;
    }
    }
    if(!contatoExiste){
        strcpy(fornecedor[j].contato,contatonovo);
        printf("contato novo é %s\n",contatonovo);
    }else{
         printf("contato já existente\n");
    }
        break;
        
        case 5:
        
        printf("Informe o Email\n");
        fgets(emailnovo, sizeof(emailnovo), stdin);
        emailnovo[strcspn(emailnovo, "\n")] = '\0';
        
    for (i = 0; i < arrayforne; i++) {
    if(strcmp(fornecedor[i].email,emailnovo)==0){
        emailExiste=1;
        break;
    }
    }
    if(!emailExiste){
        strcpy(fornecedor[j].email,emailnovo);
        printf("email novo é %s\n",emailnovo);
    }else{
         printf("email já existente\n");
    }
        break;
        
        case 6:
        
        printf("Informe o cep\n");
         fgets(cepnovo,sizeof(cepnovo),stdin);
        cepnovo[strcspn(cepnovo, "\n")] = 0;
        
         while(strlen(cepnovo)<8){
        printf("Escreva um Cep existente\n");
        fgets(cepnovo, sizeof(cepnovo), stdin);
    cepnovo[strcspn(cepnovo, "\n")] = 0; 
    }
    if(strlen(cepnovo) > 8) {
    cepnovo[8] = '\0'; 
}
        
        strcpy(fornecedor[j].cep,cepnovo);
        
        break;
        
        case 7:
        printf("Informe o tipo\n");
         fgets(fornecedor[j].tipo,sizeof(fornecedor[j].tipo),stdin);
        fornecedor[j].tipo[strcspn(fornecedor[j].tipo, "\n")] = 0;
        break;
   } 

   
 FILE *arquivo = fopen("Fornecedor.txt", "w");
 arquivosalvar(arquivo, arrayforne, fornecedor);
    fclose(arquivo);
}


}


int main()

{ 
    FILE*arquivo;
    arquivo=fopen("Fornecedor.txt","a");
if (arquivo == NULL) {
        perror("Arquivo nao abriu");
        return 1;
    }



     inserir fornecedor[100]; 
    inserir x;
    int arrayprod=0,arrayforne=0;
    int i,j;
        arquivoleitura("Fornecedor.txt", fornecedor, &arrayforne);
x.id = 0;
    strcpy(x.nome, "");
    strcpy(x.contato, "");
    strcpy(x.email, "");
    strcpy(x.tipo, "");
    strcpy(x.cnpj, "");
    strcpy(x.cep, "");
	int numero;

do{
       system("cls");
   printf("====== menu de fornecedores======\n");
	printf("1-Cadastrar fornecedor\n");
	printf("2-Mostrar tabela dos fornecedores\n");
	printf("3-Pesquisar Fornecedor\n");
	printf("5-Sair \n");
	printf("================================\n");
	printf("escolha a opcao\n");

    
	scanf("%d",&numero);
getchar();
	switch(numero) {

	case 1:
	
	   fornecedor[arrayforne++] = cadastro(fornecedor,arrayforne);
	   FILE *arquivo = fopen("Fornecedor.txt", "w");
	         arquivosalvar(arquivo, arrayforne, fornecedor);
	         
	break;
	case 2:
		
		 tabela1(arrayforne, fornecedor);
		
		printf("\n");
		for(i=0;i<arrayforne;i++){
			subtabela(fornecedor[i],arrayforne,fornecedor);
		}
        system("pause");
		printf("\n");
        
		break;
		case 3:
		pesquisar1(arrayforne,fornecedor, x);


		break;
}
}while(numero !=5);	

fclose(arquivo);
	return 0;
} 
