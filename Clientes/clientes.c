#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


void linha(){
	printf("\n===========================================\n");
}

struct estrutura_cliente{
	char cNome[81];
	char cCpf[13];
	char cTelefone[15]; // 14 caracteres + 1 teminador
	struct estrutura_cliente *ProxCliente;
};
typedef struct estrutura_cliente DadosCliente; //defina o tipo de estrutura estrutura_cliente como DadosCliente

void clrscr();
void OpcaoInvalida();
void CabecalhoTabela();
void ComoPreencher();
void RetornaMenuPrincipal();
void FalhaNoArquivo();

//Procedimento para ler o arquivo no começo e atualizar a lista!
void LerClientesNoArquivo(DadosCliente **Primeiro);

//Procedimento de Cadastro do cliente!
void RecebeCliente(DadosCliente **Primeiro);

//Procedimento para pesquisar clientes e edita-los
void PesquisaCliente(DadosCliente **Primeiro);

//Procedimento para listar os clientes
void ListaClientes(DadosCliente **Primeiro);

//Procedimento para remover cliente
void RemoverCliente(DadosCliente **Primeiro);
void Remover(DadosCliente **Primeiro, char *cpf);

//validação para os dados inseridos
int validaCPF(char *cpf);
int validaTelefone(char *telefone);
int validaNome(char *nome);
int CpfExistente(char *cpf, DadosCliente *Primeiro);

int main(){
	
	setlocale(LC_ALL, "");
	
	FILE *ArqPrincipal;
	ArqPrincipal = fopen("Principal.txt", "r");
	if(ArqPrincipal == NULL){
		fprintf(stderr, "Erro ao abrir arquivo!");
		return 1;
	}
	fclose(ArqPrincipal);
	
	//Primeiro: ponteiro que vai apontar para o primeiro da lista	
	DadosCliente *Primeiro = NULL;
	DadosCliente *NovoCliente;
	DadosCliente *Ultimo = (DadosCliente*) malloc(sizeof(DadosCliente));
	
	//opcao dos menus e submenus
	int iOpcaoMenuClientes;
	int iOpcaoRm;
	
	//Variáveis Pesquisa para
	int iEncontrou = 0;
	
	//função que vai atualizar a lista de cliente lendo o arquivo ao iniciar o programa
	LerClientesNoArquivo(&Primeiro);
	
		do{
				linha();
				printf("\t====Menu Clientes====\n");
				printf("\n 1. Cadastrar cliente");
				printf("\n 2. Pesquisar cliente");
				printf("\n 3. Listar clientes");
				printf("\n 4. Remover cliente");
				printf("\n 5. Voltar ao Menu Principal");
				linha();
				printf("\tEscolha uma opção: ");
				scanf("%d", &iOpcaoMenuClientes);
	        	while(getchar()!='\n');
		
				switch(iOpcaoMenuClientes){
				
					case 1://Cadastro cliente
						RecebeCliente(&Primeiro);
						clrscr();
						break;
					case 2://Pesquisar/Editar cliente
				    	PesquisaCliente(&Primeiro);
				    	clrscr();
				    break;
					case 3://listar clientes
						ListaClientes(&Primeiro);
						clrscr();
					break;
					case 4://Remove cliente
						RemoverCliente(&Primeiro);
						clrscr();
					break;
					case 5://Volta para o menu principal
						RetornaMenuPrincipal();
						clrscr();
					break;
					default:
						OpcaoInvalida();
						clrscr();
					break;	
				}
			}while(iOpcaoMenuClientes != 5);
			return 0;
		}
		
void clrscr(){
	linha();
	system("pause");
	linha();
	system("cls");
}
	
void RetornaMenuPrincipal(){
	linha();
	printf("Retornando ao Menu Principal");
	linha();
}

void RetornaMenuClientes(){
	linha();
	printf("\n\nRetornando ao Menu Clientes!\n\n");
	linha();
}

void OpcaoInvalida(){
	linha();
	fprintf(stderr, "\t  Opção Inválida\nInsira uma das opções disponíveis no menu!");
	linha();
}

void CabecalhoTabela(){
	printf("_______________________________________________________________________________________\n");
	printf("|%-51s|%-15s|%-17s|\n", "NOME", "CPF", "TELEFONE");
}

void ComoPreencher(){
	linha();
	printf("====== Formato para Preenchimento ======");
	printf("\n- Nome: Máximo de 40 caracteres. Informe até o 3º nome do cliente.\n");
	printf("- CPF : Utilize o formato: xxxxxxxxxxx/xx\n");
	printf("- Telefone: Utilize o formato: (DDD)xxxxx-xxxx");
	linha();
}

void FalhaNoArquivo(){
	linha();
	fprintf(stderr, "\nFalha ao abrir o arquivo!\n");
	linha();
}

int validaNome(char *nome){
	return((strlen(nome) < 50) && (strlen(nome) != 0));
}

int validaCPF(char *cpf){
	return((cpf[9] == '/') && (strlen(cpf) == 12));
}

int CpfExistente(char *cpf, DadosCliente *Primeiro){//somente ponteiro pois eu só vou precisar dos dados do cliente que o primeiro aponta

	DadosCliente *BuscaCPF = Primeiro;
	
	while(BuscaCPF != NULL){
		
		if(strcmp(BuscaCPF->cCpf, cpf) == 0){
			return 1;
		}else{
			BuscaCPF = BuscaCPF->ProxCliente;
		}
	}
	return 0; //quando não tem cpf igual 
}

int validaTelefone(char *telefone){
	return ((telefone[0] == '(') && (telefone[3] == ')') && (telefone[9] == '-'));
}

//**Primeiro = conteúdo do primeiro nó da lista (cpf, nome, telefone)     *Primeiro = é o ponteiro simples, o qual aponta par um endereço de memória!
void LerClientesNoArquivo(DadosCliente **Primeiro){ //o ponteiro de ponteiro vai mudar diretamente o valor do ponteiro que foi passado a função // ponteiro de ponteiro pois eu vou precisar acessar o endereço que o primeiro aponta
	
    FILE *ArqPrincipal;
	ArqPrincipal = fopen("Principal.txt", "r");
    if (ArqPrincipal == NULL) {
        FalhaNoArquivo();
    }

    DadosCliente *ClienteAtual  = *Primeiro;//Atual aponta para o primeiro, para percorrer cada nó da lista e libera-la
        
	//Limpando a lista para escrever os dados, liberando a lista existente
	while(ClienteAtual != NULL){
		DadosCliente *AuxProx = ClienteAtual->ProxCliente;//Auxiliar para guardar o proximo cliente, para poder liberar Atual
        free(ClienteAtual);
        ClienteAtual = AuxProx;
	}

	*Primeiro = NULL;//definindo a lista como vazia
		
	DadosCliente *Ultimo = NULL;
		
	while (!feof(ArqPrincipal)){
		DadosCliente *NovoCliente = (DadosCliente *) malloc(sizeof(DadosCliente));
		
        //Vai ler o nome, CPF e telefone do cliente no arquivo e atribuir para NovoCliente
        if(fscanf(ArqPrincipal, "%80[^;];%13[^;];%14[^\n]\n", NovoCliente->cNome, NovoCliente->cCpf, NovoCliente->cTelefone) == 3) {
            NovoCliente->ProxCliente = NULL;
            if(*Primeiro == NULL){ //Pega o primeiro cliente da lista e atribui os dados do primeiro cliente do arquivo
                *Primeiro = NovoCliente;//Primeiro aponta para o primeiro cliente lido no arquivo
            	Ultimo = NovoCliente;// Ultimo está apontando para o ultimo cliente que foi adicionado na lista
            }else{
                Ultimo->ProxCliente = NovoCliente;// O último cliente adicionado aponta para o novo cliente
            	Ultimo = NovoCliente;// Ultimo está apontando para o ultimo cliente que foi adicionado na lista		
			}
		}else{
            free(NovoCliente);
            break;
        }    
	}
    fclose(ArqPrincipal);
}

void RecebeCliente(DadosCliente **Primeiro){
	
	DadosCliente *NovoCliente = (DadosCliente*) malloc(sizeof(DadosCliente));
	
	linha();
	printf("\t====Adicionar Cliente===");
	ComoPreencher();
						
	//coletando as informações do cliente
	do{
		printf("\nDigite o nome do cliente: ");
		fgets(NovoCliente->cNome, sizeof(NovoCliente->cNome), stdin);
		NovoCliente->cNome[strlen(NovoCliente->cNome)-1] = '\0'; //substitui o \n capturado pelo fgets por um terminador \0 para não dar ruim na tabela
		fflush(stdin);
	}while(!validaNome(NovoCliente->cNome));
	do{
		printf("\nDigite o CPF do cliente: ");
		fgets(NovoCliente->cCpf, sizeof(NovoCliente->cCpf), stdin);
		NovoCliente->cCpf[strlen(NovoCliente->cCpf)] = '\0';
		fflush(stdin);
		if(!(CpfExistente(NovoCliente->cCpf, *Primeiro) == 0)){
			printf("\n\t*Atenção: o CPF digitado já consta no sistema\nverifique se os dados estão sendo inseridos corretamente ou se o cliente já está cadastrado!\n");
		}
	}while(!validaCPF(NovoCliente->cCpf)  || !(CpfExistente(NovoCliente->cCpf, *Primeiro) == 0));
	do{
		printf("\nDigite o número de telefone do cliente: ");
		fgets(NovoCliente->cTelefone, sizeof(NovoCliente->cTelefone), stdin);
		NovoCliente->cTelefone[strlen(NovoCliente->cTelefone)] = '\0';
	}while(!validaTelefone(NovoCliente->cTelefone));									
	
	if (Primeiro == NULL) { // Se a lista está vazia
    	NovoCliente->ProxCliente = NULL;
    	*Primeiro = NovoCliente;//Primeiro aponta para o novo nó
	}else{//se já existe cliente na lista
		NovoCliente->ProxCliente = *Primeiro;//NovoCliente aponta para o primeiro da lista (para o cliente que o ponteiro primeiro aponta)
    	*Primeiro = NovoCliente;//ponteiro primeiro aponta para o cliente que acabou de ser adicionado
	}
						
	//Abrindo o arquivo para inserir o cliente novo
	FILE *ArqPrincipal;
	ArqPrincipal = fopen("Principal.txt", "a");
	
	if(ArqPrincipal == NULL){
		fprintf(stderr, "\n\nFalha ao abrir o arquivo\n\n");
	}
	
	fprintf(ArqPrincipal, "%s;%s;%s\n", NovoCliente->cNome, NovoCliente->cCpf, NovoCliente->cTelefone);//escreve os dados no arquivo
	fclose(ArqPrincipal);
	printf("\n\tCadastro realizado!");
}

void PesquisaCliente(DadosCliente **Primeiro){
	
	char cCpfComparacao[13];//cpf para comparar com o do cliente que deseja pesquisar
	int iOpcaoMenuBuscar;
	int iEncontrou = 0;
	
	linha();
	printf("\t====Pesquisar Cliente====");
	printf("\n*Para preencher o CPF utilize o formato abaixo...*");
	printf("\n- CPF : Utilize o formato: xxxxxxxxxxx/xx");
	linha();
		do {
			printf("Digite o CPF do cliente: ");
			fgets(cCpfComparacao, sizeof(cCpfComparacao), stdin);
			cCpfComparacao[strlen(cCpfComparacao)] = '\0';
			}while(!validaCPF(cCpfComparacao));
					
			DadosCliente *Buscar = *Primeiro;
			// Abrindo arquivo temporário apenas uma vez em modo de sobrescrever
			FILE *ArqSecundario;
			ArqSecundario = fopen("Secundario.txt", "w");
			if (ArqSecundario == NULL) {
				FalhaNoArquivo();
				return;
			}
				
			while(Buscar != NULL){
				    	
				if (strcmp(cCpfComparacao, Buscar->cCpf) == 0){//procura o cliente na lista
				    iEncontrou = 1; //cliente encontrado
				    linha();
				    printf("====Cliente encontrado====");
				    
				    
				    linha();
				    printf("Nome: %s", Buscar->cNome);
				    printf("\nCPF: %s", Buscar->cCpf);
				    printf("\nTelefone: %s", Buscar->cTelefone);
				    linha();
				    printf("\n1. Editar Informações.\n");
				    printf("\n2. Voltar ao menu clientes.\n");
				    linha();
				    printf("Escolha uma opção: ");
				    scanf("%d", &iOpcaoMenuBuscar);
				    while(getchar() != '\n');
				    system("cls");
				    fflush(stdin);
				
				        if(iOpcaoMenuBuscar == 1){
				                
							linha();
				            printf("\t===Editar Informações===");
				            printf("\nNome: %s", Buscar->cNome);
				    		printf("\nCPF: %s", Buscar->cCpf);
				    		printf("\nTelefone: %s", Buscar->cTelefone);
				    		linha();
				            printf("=====Digite os novos dados do cliente=====");
				            ComoPreencher();
				            do{
				                fflush(stdin);
				                printf("\nNome do cliente: ");
				                fgets(Buscar->cNome, sizeof(Buscar->cNome), stdin);
				                Buscar->cNome[strlen(Buscar->cNome) - 1] = '\0';
				            }while(!validaNome(Buscar->cNome));
				
				            do{
				                fflush(stdin);
				                printf("\nCPF do cliente: ");
				                fgets(Buscar->cCpf, sizeof(Buscar->cCpf), stdin);
				                Buscar->cCpf[strlen(Buscar->cCpf)] = '\0';
				            }while(!validaCPF(Buscar->cCpf));
				
				            do{
				                fflush(stdin);
				                printf("\nTelefone do cliente: ");
				                fgets(Buscar->cTelefone, sizeof(Buscar->cTelefone), stdin);
				                Buscar->cTelefone[strlen(Buscar->cTelefone)] = '\0';
				            }while(!validaTelefone(Buscar->cTelefone));
				
				            linha();
				            printf("Informações atualizadas com sucesso!!");
				            linha();
				        }else{
				        	linha();
							printf("Retornando ao menu clientes!");
							linha();
						}					        
				}    
				fprintf(ArqSecundario, "%s;%s;%s\n", Buscar->cNome, Buscar->cCpf, Buscar->cTelefone);//Escreve no arquivo secundario (seja cliente editado ou não)							
				Buscar = Buscar->ProxCliente;
			}
				// Remove o arquivo antigo e renomeia o temporário
				fclose(ArqSecundario);
				remove("Principal.txt");
				rename("Secundario.txt", "Principal.txt");
				
				if (remove("Principal.txt") != 0) {
				    perror("Erro ao remover o arquivo Cadastro.txt");
				} else {
				    printf("Arquivo ArqPrincipal removido com sucesso.\n");
				}
				
				if (rename("Secundario.txt", "Principal.txt") != 0) {
				    perror("Erro ao renomear ArqSecundario.txt para Cadastro.txt");
				} else {
				    printf("Arquivo Secundario.txt renomeado para Cadastro.txt com sucesso.\n");
				}
				
				//free(Buscar);    
				if(iEncontrou != 1) {
				    linha();
				    printf("\tCliente não encontrado!");
				    linha();
				}
}

void ListaClientes(DadosCliente **Primeiro){
	
	linha();
	printf("\t===Lista de Clientes===\n");
					
	DadosCliente *Auxiliar = *Primeiro;//define um auxiliar para percorrer a lista desde o primeiro cliente (ultimo cliente adicionado)
					
	if(Auxiliar == NULL){//se não tiver nenhum cliente cadastrado, não lÊ
		linha();
		printf("\nNenhum cliente foi encontrado !\n");
		linha();
	}else{
		CabecalhoTabela();
		while(Auxiliar != NULL){
			printf("|%-51s|%-15s|%-17s|\n", Auxiliar->cNome, Auxiliar->cCpf, Auxiliar->cTelefone);
			Auxiliar = Auxiliar->ProxCliente;
		}
	}
}

void RemoverCliente(DadosCliente **Primeiro){
	
	int iOpcaoRm;
    char cCpfComparacao[13];
    int iOpcaoMenuRemover;
    int iEncontrou = 0;
    DadosCliente *Buscar = *Primeiro;
	char cOpcaoRm;
	do{
	linha();
	printf("Você realmente deseja remover um cliente do sistema?");
	printf("\n\t   [S] -- SIM\n\t   [N] -- NÃO");
	linha();
	printf("Digite a sua resposta aqui: ");
	scanf("%c", &cOpcaoRm);
	while (getchar() != '\n');
	system("cls");
	}while((cOpcaoRm != 's') && (cOpcaoRm != 'S') && (cOpcaoRm != 'N') && (cOpcaoRm != 'n'));
	
	if(cOpcaoRm == 's' || cOpcaoRm == 'S'){
		linha();    
		printf("\t====Remover Cliente====");
		ComoPreencher();
	    do {
	        printf("Digite o CPF do cliente a ser removido: ");
	        fgets(cCpfComparacao, sizeof(cCpfComparacao), stdin);
	        cCpfComparacao[strlen(cCpfComparacao)] = '\0';
	    }while(!validaCPF(cCpfComparacao));
	
	    // Procura o cliente na lista
	    while (Buscar != NULL) {
	        if(strcmp(cCpfComparacao, Buscar->cCpf) == 0){// Cliente encontrado
	            iEncontrou = 1;
	            linha();
	            printf("==== Cliente encontrado ====");
	            printf("\nNome: %s", Buscar->cNome);
	            printf("\nCPF: %s", Buscar->cCpf);
	            printf("\nTelefone: %s", Buscar->cTelefone);
	            linha();
	            printf("\n1. Remover Cliente.\n");
	            printf("\n2. Voltar ao menu.\n");
	            linha();
	            printf("Escolha uma opção: ");
	            scanf("%d", &iOpcaoMenuRemover);
	            fflush(stdin);
	
	            if (iOpcaoMenuRemover == 1) { // Remove o cliente
	                Remover(Primeiro, Buscar->cCpf);
	                printf("\nCliente removido com sucesso!\n");
					break;            
				}   
	        }
	        Buscar = Buscar->ProxCliente;
	    }
	
	    // Atualiza o arquivo após remoção
	    FILE *ArqSecundario = fopen("Secundario.txt", "w");
	    if (ArqSecundario == NULL) {
	        FalhaNoArquivo();
	        return;
	    }
	    
	    Buscar = *Primeiro; //vai ler a lista tudo denovo só que sem o cliente removido
	    
		while (Buscar != NULL) {
	        fprintf(ArqSecundario, "%s;%s;%s\n", Buscar->cNome, Buscar->cCpf, Buscar->cTelefone);
	        Buscar = Buscar->ProxCliente;
	    }
	    
	    fclose(ArqSecundario);
	    remove("Principal.txt");
	    rename("Secundario.txt", "Principal.txt");
	    
	    if (iEncontrou != 1) {
	        linha();
	        printf("\tCliente não encontrado!");
	        linha();
	    }
	}else{
		RetornaMenuClientes();
	}
}

void Remover(DadosCliente **Primeiro, char *cpf){
	
	DadosCliente *Atual = *Primeiro;
	DadosCliente *Anterior = NULL;
	
	while(Atual != NULL && strcmp(Atual->cCpf, cpf) != 0){
		Anterior = Atual;
		Atual = Atual->ProxCliente;
	}
	
	if(Atual == NULL){
		printf("\nO cpf %s não foi encontrado\n", cpf);
		return;
	}
	
	if(Anterior == NULL){
		*Primeiro = Atual->ProxCliente;
	}else{
		Anterior->ProxCliente = Atual->ProxCliente;
	}
	free(Atual);
}
