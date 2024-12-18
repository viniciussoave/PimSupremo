#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int subOpcao=0;


// Funções do menu Produtos
typedef struct { 
    int id;
    int qtd;
    float precoUnidade;
    float desconto;
    float valorFinal;
    char nomeProduto[50];
} produto;

int verificarID(produto Prod[], int indice, int id) {
	int i;
    for (i = 0; i < indice; i++) {
        if (Prod[i].id == id) {
            return 1;
        }
    }
    return 0;
}

float stringParaFloat(char *str) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            str[i] = ',';
        }
    }
    return atof(str);
}

int ConsultaIDrep(int idConsulta) {
    char linha[999];
    int x;
    int Ids[999]; //armazena os ids que serao lidos
    int indice = 0;
    FILE *produtos;
    produtos = fopen("produtos.txt","r");

    if (produtos == NULL) {
        perror("Erro ao abrir o arquivo");
        system("cls");
    }

    while (fgets(linha, sizeof(linha), produtos)) { //armazena os valores de ID
        sscanf(linha, "%d", &Ids[indice]);
        indice++;
    }
 
        for(x=0;x<indice;x++){ //verificar se o ID novo já tem no arquivo produtos.txt
            if(idConsulta == Ids[x]){
                return 1;
            }
        }
    fclose(produtos);
    indice = 0;
    return 0;
}

void ConsultaProd(){
    FILE *arquivo;
    char linha[999];
    int id, qtd;
    float precoPorUnidade, desconto, precoFinal;
    char nome[50];

    arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        system("cls");
    }


    while (fgets(linha, sizeof(linha), arquivo)) {

        sscanf(linha, "%d,%49[^,],%d,%f,%f,%f", &id, nome, &qtd, &precoPorUnidade, &desconto, &precoFinal); //essa bomba lê a linha e organiza cada valor em sua devida variavel.

   
        printf("ID: %d, Nome: %s, Preco por unidade: R$%.2f, Desconto: %.2f%%, Preco Final: R$%.2f\n",
               id, nome, precoPorUnidade, desconto, precoFinal); //essa bomba mostra os valores.
    }


    fclose(arquivo);
}

void EditarProd(){
            int mudar=0;
            int erro=0;
            int existe = 0;
            int opc = 0;
            int pesquisaID = 0;
            char linha[999];
            int id,qtd;
            char nome[50];
            float precoPorUnidade,desconto,precoFinal;
            printf("Digite o ID do produto que você quer alterar: ");
            scanf("%d", &pesquisaID);
            getchar();


        FILE *arquivo;
        arquivo = fopen("produtos.txt", "r");
        if (arquivo == NULL) {
            perror("Erro ao abrir o arquivo");
            system("cls");
        }


        while (fgets(linha, sizeof(linha), arquivo)) {
            sscanf(linha, "%d,%49[^,],%d,%f,%f,%f", &id, nome, &qtd, &precoPorUnidade, &desconto, &precoFinal);
            if(id != pesquisaID){
                //diferente do id procurado
                FILE *arquiv;
                arquiv = fopen("temp.txt", "a");
                fprintf(arquiv,"%d,%s,%d,%0.2f,%0.2f,%0.2f\n", id,nome,qtd,precoPorUnidade,desconto,precoFinal);
                fclose(arquiv);
            } else {
                // igual ao id procurado
                while(opc != 5 && opc != 6){
                    system("cls");
                    existe = 1;
                    printf("1. ID = %d\n", id);
                    printf("2. Nome = %s\n", nome);
                    printf("3. Preco por unidade = %.2f\n", precoPorUnidade);
                    printf("4. Desconto = %.2f\n",desconto);
                    printf("5. Alterar produto\n");
                    printf("6. Cancelar");
                    printf("\nO que deseja alterar: ");
                    scanf("%d", &opc);
                    getchar();
                    switch(opc){
                        case 1:
                            system("cls");
                            printf("Aviso: Nao é possivel editar o ID.\n");
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            system("cls");
                            printf("Nome = ");
                            fgets(nome, sizeof(nome), stdin);
                            nome[strcspn(nome, "\n")] = '\0';
                            
                            break;
                        case 3:
                            system("cls");
                            char precoStr[20];
                            printf("Preco por unidade = ");
                            fgets(precoStr, sizeof(precoStr), stdin);
                            precoPorUnidade = stringParaFloat(precoStr);
                            system("cls");
                            break;
                        case 4:
                            system("cls");
                            char descStr[20];
                            printf("Desconto = ");
                            fgets(descStr, sizeof(descStr), stdin);
                            desconto = stringParaFloat(descStr);
                            system("cls");
                            break;
                        case 5:
                            if (strlen(nome) == 0) {
                                erro = 1;
                                printf("Erro: Nome do produto nao pode estar vazio.\n");
                                system("pause");
                                system("cls");
                                break;
                            }
        
                            if(precoPorUnidade<0){
                                erro = 1;
                                printf("Erro: O preco tem que ser positivo.\n");
                                system("pause");
                                system("cls");
                                break;
                            }

                            if(desconto<0){
                                erro = 1;
                                printf("Erro: O desconto tem que ser positivo.\n");
                                system("pause");
                                system("cls");
                                break;
                            }

                            mudar = 1;
                            FILE *arquiv;
                            arquiv = fopen("temp.txt", "a");
                            precoFinal = precoPorUnidade * (1 - (desconto / 100));
                            fprintf(arquiv,"%d,%s,%d,%0.2f,%0.2f,%0.2f,\n", id,nome,qtd,precoPorUnidade,desconto,precoFinal);
                            fclose(arquiv);
                            break;
                        case 6:
                            break;
                    }
                }

            }
        }
        
        fclose(arquivo);
        

        if(existe == 0){
            remove("temp.txt");
            printf("Produto nao encontrado.\n");
            system("pause");
            system("cls");
        } else {
            if(erro == 0 && mudar == 1){
                remove("produtos.txt");
                rename("temp.txt", "produtos.txt");
                system("cls");
            } else {
                remove("temp.txt");
                system("cls");
                erro = 0;
            }
        }
        
}

void RemoverProd(){
            FILE *arquivo;
            int verificar = 0;
            int existe = 0;
            int pesquisaID = 0;
            char linha[999];
            int id,qtd;
            char nome[50];
            float precoPorUnidade,desconto,precoFinal;
            printf("Digite o ID do produto que você quer remover: ");
            scanf("%d", &pesquisaID);
            getchar();

            printf("Tem certeza que quer excluir o produto com o id %d? (1- Sim,2- Nao)\n", pesquisaID);
            scanf("%d", &verificar);
            getchar();

        switch(verificar){
            case 1:
            
            arquivo = fopen("produtos.txt", "r");
            if (arquivo == NULL) {
            perror("Erro ao abrir o arquivo");
            system("cls");
            }

            while (fgets(linha, sizeof(linha), arquivo)) {
                sscanf(linha, "%d,%49[^,],%d,%f,%f,%f", &id, nome, &qtd, &precoPorUnidade, &desconto, &precoFinal);
                if(id != pesquisaID){
                    //diferente do id procurado
                    FILE *arquiv;
                    arquiv = fopen("temp.txt", "a");
                    fprintf(arquiv,"%d,%s,%d,%0.2f,%0.2f,%0.2f\n", id,nome,qtd,precoPorUnidade,desconto,precoFinal);
                    fclose(arquiv);
                } else {
                    // igual ao id procurado
                        existe = 1;
                    }
                }

                fclose(arquivo);

                if(existe == 0){
                    remove("temp.txt");
                    printf("Produto nao encontrado.\n");
                    system("pause");
                    system("cls");
            } else {
                    remove("produtos.txt");
                    rename("temp.txt", "produtos.txt");
                    system("cls");
                    printf("Produto excluido com sucesso\n");
                    system("pause");
                    system("cls");
            }

            break;
            case 2:
            break;
            default:
                printf("Escolha uma opcão valida");
                system("pause");
                system("cls");
        }
        

}
// FIM Menu PRODUTO


//FUNÇÕES MENU ESTOQUE

void salvarProdutos(produto produtos[], int totalProdutos) {
    FILE *arquivo = fopen("Produtos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de produtos para salvar.\n");
        exit(1);
    }
    for (int i = 0; i < totalProdutos; i++) {
        fprintf(arquivo, "%d,%s,%d,%.2f,%.2f,%.2f\n",
                produtos[i].id,
                produtos[i].nomeProduto,
                produtos[i].qtd, // salvando direto do arquivo vinicius
                produtos[i].precoUnidade,
                produtos[i].desconto,
                produtos[i].valorFinal);
    }
    fclose(arquivo);
}

void listarItens(produto produtos[], int totalProdutos) {
    printf("\n=== lista de produtos ===\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("ID: %d\nnome: %s\npreço Unidade: %.2f\ndesconto: %.2f\nvalor final: %.2f\nestoque: %d unidades\n",
               produtos[i].id, produtos[i].nomeProduto, produtos[i].precoUnidade,
               produtos[i].desconto, produtos[i].valorFinal, produtos[i].qtd);
        printf("------------------------\n");
    }
}

void carregarProdutos(produto produtos[], int *totalProdutos) { //incluindo os pararmetros
    *totalProdutos = 0; // o total do array precisa começa com 0
    FILE *arquivo = fopen("Produtos.txt", "r"); // acesso o arquivo do vinicius
    if (arquivo == NULL) {
        printf("Arquivo não existe!!!!"); // programação defensiva...
        exit(1);
    }
    while (fscanf(arquivo, "%d,%49[^,],%d,%f,%f,%f", &produtos[*totalProdutos].id,
                  produtos[*totalProdutos].nomeProduto,
                  &produtos[*totalProdutos].qtd,
                  &produtos[*totalProdutos].precoUnidade,
                  &produtos[*totalProdutos].desconto,
                  &produtos[*totalProdutos].valorFinal) == 6) {
        (*totalProdutos)++; // pegando o ponteiro e apontando de forma em que haja o incremento, percorrendo todo o array struct
    }
    fclose(arquivo);
}

void adicionarItemEstoque(produto produtos[], int *totalProdutos) {
    bool idExiste = false; // boolean pra controlar o laço se o id existir no array struct.
    int id, quantidade; // declarando o id e quantidade que do produto em questao...
    printf("Insira o ID do produto: ");
    scanf("%d", &id);
    for (int i = 0; i <totalProdutos; i++) {
        if (produtos[i].id == id) {
            idExiste = true;
            printf("Produto selecionado: %s\n", produtos[i].nomeProduto);
            printf("Digite a quantidade de estoque do produto: " );
            scanf("%d", &quantidade);
            produtos[i].qtd += quantidade;
            printf("Estoque atualizado com sucesso!\nEstoque atual do produto: %d", produtos[i].qtd);
            salvarProdutos(produtos, *totalProdutos);
            break;
        }
    }
    if (!idExiste) {
        printf("Produto com ID %d não encontrado.\n", id);
    }
}

void removerItemEstoque(produto produtos[], int *totalProdutos) {
    int idEstoque, qtdRemover;
    bool idExiste = false;

    printf("Escreva o ID do item que voce deseja remover do estoque: ");
    scanf("%d", &idEstoque);

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].id == idEstoque) {
            idExiste = true;
            printf("Produto selecionado: %s\n", produtos[i].nomeProduto);
            printf("Selecione a quantidade de itens que você deseja remover: ");
            scanf("%d", &qtdRemover);

            if (produtos[i].qtd >= qtdRemover) {
                produtos[i].qtd -= qtdRemover;
                printf("Estoque atualizado com sucesso!\nEstoque atual do produto: %d\n", produtos[i].qtd);
            } else {
                printf("Erro: Quantidade insuficiente em estoque.\n");
            }

            salvarProdutos(produtos, *totalProdutos);

            break;
        }
    }

    if (!idExiste) {
        printf("Produto com ID %d não encontrado.\n", idEstoque);
    }
}


//FIM MENU ESTOQUE

//COMEÇO MENU FINANCEIRO
typedef struct {
    int idVenda;
    int idProd;
    char nomeProd[50];
    int qtdVendida;
    float precoTotal;
    int dia, mes, ano;
} venda;

void carregarArquivoVendas(venda vendas[], int *totalVendas)  { // aqui eu vou precisar de uma funcao void quer carregue o arquivo contendo as informacoes da venda.
    FILE *arquivo = fopen("vendas.txt", "r"); // vo acessa pra ler o arquivo de vendas
    if (arquivo == NULL) {
        printf("Arquivo não encontrado."); // programacao defensiva
        }
          *totalVendas = 0;  // comecando com 0 pra comecar a percorrer na leitura
        while (fscanf(arquivo, "%d,%d,%49[^,],%d,%f,%d,%d,%d",
                       &vendas[*totalVendas].idVenda,
                  &vendas[*totalVendas].idProd,
                  vendas[*totalVendas].nomeProd,
                  &vendas[*totalVendas].qtdVendida,
                  &vendas[*totalVendas].precoTotal,
                  &vendas[*totalVendas].dia,
                  &vendas[*totalVendas].mes,
                  &vendas[*totalVendas].ano) == 8) {

            (*totalVendas)++;
        }
        fclose(arquivo);
    }


float calculoDeReceita(venda vendas[], int totalVendas) {
    float receita = 0;
    for (int i = 0; i < totalVendas; i++) {
        receita += vendas[i].precoTotal;
    }
    return receita;
}

void mostrarResumoReceitas(venda vendas[], int totalVendas) { // relatorio resumido
    printf("\n=== Resumo das receitas - venda ===\n");
    for (int i = 0; i < totalVendas; i++) {
        printf("Id Venda: %d | Produto: %s | Quantidade Vendida: %d |preco Total: R$ %.2f | Data: %d/%d/%d\n",
               vendas[i].idVenda, vendas[i].nomeProd, vendas[i].qtdVendida, vendas[i].precoTotal,
               vendas[i].dia, vendas[i].mes, vendas[i].ano);
    }
    printf("total de vendas que constam no registro: %d\n", totalVendas);
}

//FIM MENU FINANCEIRO

//COMECO MENU DOAÇÃO
typedef struct {
    char produto[50];
    int qtd;
    char data[20];
    char local[100];
} Doacao;

void registroDoacao(produto produtos[], int *totalProdutos, FILE *arquiv) {
    Doacao doacao;
    bool encontrado;

    do {
        system("cls");
        printf("Produto a ser doado: ");
        fgets(doacao.produto, sizeof(doacao.produto), stdin);
        doacao.produto[strcspn(doacao.produto, "\n")] = 0;

        encontrado = false;
        for (int i = 0; i < *totalProdutos; i++) {
            if (strcmp(produtos[i].nomeProduto, doacao.produto) == 0) {
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            printf("Produto não encontrado no estoque. Tente novamente.\n");
            system("pause");
        }
    } while (!encontrado);

    printf("Quantidade a ser doada: ");
    scanf("%d", &doacao.qtd);
    getchar();

    printf("Instituição a ser Doada: ");
    fgets(doacao.local, sizeof(doacao.local), stdin);
    doacao.local[strcspn(doacao.local, "\n")] = 0;

    printf("Data da doação (DD/MM/AAAA): ");
    fgets(doacao.data, sizeof(doacao.data), stdin);
    doacao.data[strcspn(doacao.data, "\n")] = 0;

    for (int i = 0; i < *totalProdutos; i++) {
        if (strcmp(produtos[i].nomeProduto, doacao.produto) == 0) { 
            if (produtos[i].qtd >= doacao.qtd) {
                produtos[i].qtd -= doacao.qtd;
                salvarProdutos(produtos, *totalProdutos);
                fprintf(arquiv, "%s,%d,%s,%s\n", doacao.produto, doacao.qtd, doacao.local, doacao.data);
                printf("Doação registrada com sucesso!\n");
                printf("Estoque atualizado após doação.\n");
            } else {
                printf("Erro: Estoque insuficiente para realizar a doação.\n");
            }
            break;
        }
    }

    system("pause");
    system("cls");
}

void consultarDoacao(FILE *arquiv) {
    Doacao doacao;
    char linha[999];
    system("cls");
    printf("=== Doações Registradas ===\n");

    while (fgets(linha, sizeof(linha), arquiv)) {
        sscanf(linha, "%49[^,],%d,%99[^,],%19[^\n]", doacao.produto, &doacao.qtd, doacao.local, doacao.data);
        printf("Produto: %s\nQuantidade: %d\nInstituição: %s\nData: %s\n\n", doacao.produto, doacao.qtd, doacao.local, doacao.data);
    }

    printf("=== Fim da Consulta ===\n");
    system("pause");
    system("cls");
}

void excluirDoacao(FILE *arquiv, produto produtos[], int *totalProdutos) {
    #define MAX_DOACOES 999
    Doacao doacoes[MAX_DOACOES];
    int totalDoacoes = 0;
    char linha[999];

    while (fgets(linha, sizeof(linha), arquiv) && totalDoacoes < MAX_DOACOES) {
        sscanf(linha, "%49[^,],%d,%99[^,],%19[^\n]", doacoes[totalDoacoes].produto,
               &doacoes[totalDoacoes].qtd, doacoes[totalDoacoes].local, doacoes[totalDoacoes].data);
        totalDoacoes++;
    }
    fclose(arquiv);

    printf("=== Doações Registradas ===\n");
    for (int i = 0; i < totalDoacoes; i++) {
        printf("%d. Produto: %s | Quantidade: %d | Instituição: %s | Data: %s\n", i + 1,
               doacoes[i].produto, doacoes[i].qtd, doacoes[i].local, doacoes[i].data);
    }

    int escolha;
    printf("Digite o número da doação que deseja excluir: ");
    scanf("%d", &escolha);
    getchar();

    if (escolha < 1 || escolha > totalDoacoes) {
        printf("Opção inválida!\n");
        return;
    }

    bool encontrado = false;
    for (int i = 0; i < *totalProdutos; i++) {
        if (strcmp(produtos[i].nomeProduto, doacoes[escolha - 1].produto) == 0) {
            produtos[i].qtd += doacoes[escolha - 1].qtd;
            salvarProdutos(produtos, *totalProdutos);
            printf("Estoque restaurado. Doação excluída com sucesso.\n");
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto não encontrado no estoque.\n");
    }

    system("pause");
    system("cls");
}

void listarItensDoacao(produto produtos[], int totalProdutos) {
    system("cls");
    printf("=== Itens no Estoque ===\n");

    for (int i = 0; i < totalProdutos; i++) {
        printf("ID: %d | Produto: %s | Quantidade: %d | Preço: %.2f | Valor Final: %.2f\n",
               produtos[i].id, produtos[i].nomeProduto, produtos[i].qtd, produtos[i].precoUnidade, produtos[i].valorFinal);
    }

    printf("=== Fim do Estoque ===\n");
    system("pause");
}


//FIM MENU DOAÇÃO

//COMECO MENU FUNCIONARIOS
typedef struct {
    int id;
    char nome[50];
    char cargo[30];
    float salario;
    char horario_entrada[10];
    char horario_saida[10];
    int ativo; 
} Funcionario;

void exibirLinhaFuncionario(Funcionario f) {
    printf("| %-3d | %-20s | %-20s | %-10.2f | %-10s | %-10s |\n",
           f.id, f.nome, f.cargo, f.salario, f.horario_entrada, f.horario_saida);
}

void criarTabela(Funcionario funcionarios[], int total, int ativo) {
    printf("+-----+----------------------+----------------------+------------+------------+------------+\n");
    printf("| ID  | Nome                 | Cargo                | Salário    | Entrada    | Saída      |\n");
    printf("+-----+----------------------+----------------------+------------+------------+------------+\n");

    for (int i = 0; i < total; i++) {
        if (funcionarios[i].ativo == ativo) {
            exibirLinhaFuncionario(funcionarios[i]);
        }
    }

    printf("+-----+----------------------+----------------------+------------+------------+------------+\n");
}

void adicionarFuncionario(Funcionario funcionarios[], int *total, int MAX_FUNCIONARIOS) {
    if (*total >= MAX_FUNCIONARIOS) {
        printf("Limite de funcionários atingido.\n");
        return;
    }

    Funcionario novo;
    novo.id = *total + 1;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Cargo: ");
    scanf(" %[^\n]", novo.cargo);
    printf("Salário: ");
    scanf("%f", &novo.salario);
    printf("Horário de entrada: ");
    scanf(" %[^\n]", novo.horario_entrada);
    printf("Horário de saída: ");
    scanf(" %[^\n]", novo.horario_saida);
    novo.ativo = 1;  

    funcionarios[*total] = novo;
    (*total)++;
    printf("Funcionário adicionado com sucesso!\n");
}

void removerFuncionario(Funcionario funcionarios[], int total) {
    int id;
    printf("ID do funcionário a ser removido: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++) {
        if (funcionarios[i].id == id) {
            funcionarios[i].ativo = 0;
            printf("Funcionário removido com sucesso!\n");
            return;
        }
    }
    printf("Funcionário não encontrado.\n");
}

void salvarFuncionarios(Funcionario funcionarios[], int total) {
    FILE *arquivo = fopen("funcionarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%d;%s;%s;%.2f;%s;%s;%d\n",
                funcionarios[i].id, funcionarios[i].nome, funcionarios[i].cargo,
                funcionarios[i].salario, funcionarios[i].horario_entrada,
                funcionarios[i].horario_saida, funcionarios[i].ativo);
    }

    fclose(arquivo);
    
}

void carregarFuncionarios(Funcionario funcionarios[], int *total) {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado. Nenhum funcionário foi carregado.\n");
        *total = 0;
        return;
    }

    *total = 0;
    while (fscanf(arquivo, "%d;%49[^;];%29[^;];%f;%9[^;];%9[^;];%d\n",
                  &funcionarios[*total].id, funcionarios[*total].nome,
                  funcionarios[*total].cargo, &funcionarios[*total].salario,
                  funcionarios[*total].horario_entrada,
                  funcionarios[*total].horario_saida,
                  &funcionarios[*total].ativo) != EOF) {
        (*total)++;
     
    }

    fclose(arquivo);
 
}
//FIM MENU FUNCIONARIOS


//COMECO MENU FORNECEDORES
typedef struct{   // variaveis dos fornecedores
    int id;
	char nome[100],contato[100],email[100],tipo[100],cnpj[100],cep[100]; 
}inserir;

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
        } }
    for (int l = 0; l < (*maiorValor - k + 0); l++) {
        printf(" ");
    }     }

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
        }     }

    for (int l = 4; l < (*maiortipo - k + 0); l++) {
        printf(" ");
    } }

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
        }}
    for (int l = 5; l < (*maioremail - k + 0); l++) {
        printf(" ");
    }   }

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
int existir=0, existir2=0, existir3=0,  existir4=0, existir5=0,j;
int compnome;int compcnpj;int compemail;int compcontato;

    while (1) {
        printf("Fale o numero do id\n");

        if (scanf("%d", &x.id) != 1) {
            while (getchar() != '\n'); 
           
        } else {
                if (x.id >= 0 && x.id < 1000) {
                
                 
                break;  
            } else {
               
        }   } }

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
    scanf("%d", &x.id);
  if(x.id >= 0 && x.id < 1000){
     printf("Fale o numero do id(1-999)\n");
    scanf("%d", &x.id);
  }
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
    
    printf("|%3.d|", x.id);
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
        }   }

    for (int l = 4; l < (*maiorValor - k + 0); l++) {
        printf(" ");
    }   }

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
   
        fprintf(arquivo," %d, ", fornecedor[i].id); 
          fprintf(arquivo, "%s, ", fornecedor[i].nome);
     
        fprintf(arquivo,"%s, ", fornecedor[i].cnpj);
        fprintf(arquivo," %s, ", fornecedor[i].contato);
        fprintf(arquivo," %s, ", fornecedor[i].email);
        fprintf(arquivo," %s, ", fornecedor[i].cep);
        fprintf(arquivo," %s ", fornecedor[i].tipo);
        fprintf(arquivo,"\n");
        
    }  }

//ler o arquivo
void arquivoleitura(char *arquivo, inserir fornecedor[], int *arrayforne) {
    FILE *file = fopen(arquivo, "r");
    
     while (fscanf(file, "%d, %99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %99[^\n]\n",
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
      int idnovo;
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
     scanf("%d",&x.id);
        
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
    scanf("%d", &x.id);
    }
    }while(!verificar);
     printf("====== Fornecedor ======\n");
          printf("ID encontrado: %d\n", x.id); 
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
                    scanf("%d", &idnovo);
                while (idnovo< 0 || idnovo >= 1000) {
    printf("Escreva um id de 0 até 999\n");
    printf("Fale o numero do id\n");
    scanf("%d", &idnovo);
}
                    for (i = 0; i < arrayforne; i++) {
                        if (fornecedor[i].id == idnovo) {
                            idExistente = 1; 
                            break;
                        }
                    }

                    if (!idExistente) {
                        fornecedor[j].id = idnovo;
                        printf("Novo id: %.0d\n", idnovo);
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
//FIM MENU FORNECEDORES 

//COMECO MENU CLIENTES
void linha(){
	printf("\n===========================================\n");
}

struct estrutura_cliente{
	char cNome[81];
	char cCpf[14];
	char cTelefone[16];
	struct estrutura_cliente *ProxCliente;
};

typedef struct estrutura_cliente DadosCliente;

void clrscr(){
	linha();
	system("pause");
	linha();
	system("cls");
}
	
void RetornaMenuPrincipal(){
	linha();
	printf("Voltando ao menu principal...");
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
	printf("\n- Nome: Máximo de 40 caracteres.\n");
	printf("- CPF : Utilize o formato: xxxxxxxxxxx/xx -> 9 números / 2 números\n");
	printf("- Telefone: Utilize o formato: (DDD)xxxxx-xxxx -> (2 números) 5 números - 4 números");
	linha();
}

void FalhaNoArquivo(){
	linha();
	fprintf(stderr, "\nFalha ao abrir o arquivo!\n");
	linha();
}

int validaNome(char *nome){
	
	if((strlen(nome) < 50) && (strlen(nome) !=0)){
		return 1;
	}else{
		return 0;
	}
}

int validaCPF(char *cpf){
	int i;
	//Verifica o tamanho do cpf digitado e se tem /
    if(strlen(cpf) != 12 || cpf[9] != '/')
        return 0;
    //Verificar se os 9 primeiros são números (antes do /)
    for(i = 0; i < 9; i++){
        if(cpf[i] < '0' || cpf[i] > '9')
            return 0;
    }
    // Verificar depois do / são números
    for(i = 10; i < 12; i++){
        if(cpf[i] < '0' || cpf[i] > '9')
            return 0;
    }
    return 1; // CPF inserido corretamente
}

int CpfExistente(char *cpf, DadosCliente *Primeiro){//somente ponteiro pois eu são vou precisar dos dados do cliente que o primeiro aponta

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
	int i;
	// ve o tamanho do telefone digitado e se possui os separadores corretos
    if (strlen(telefone) != 14 || telefone[0] != '(' || telefone[3] != ')' || telefone[9] != '-')
        return 0;

    //ve se o ddd é número
    if (telefone[1] < '0' || telefone[1] > '9' || telefone[2] < '0' || telefone[2] > '9')
        return 0;

    //ve se os 5 primeiros digitos são números
    for (i = 4; i < 9; i++) {
        if (telefone[i] < '0' || telefone[i] > '9')
            return 0;
    }

    // verifica se os quatro ultimos (depois do -) são números
    for (i = 10; i < 14; i++) {
        if (telefone[i] < '0' || telefone[i] > '9')
            return 0;
    }

    return 1; // Telefone inserido corretamente
}

//**Primeiro = conteúdo do primeiro nó da lista (cpf, nome, telefone)     *Primeiro = É o ponteiro simples, o qual aponta par um endereço de memória!
void LerClientesNoArquivo(DadosCliente **Primeiro){ //o ponteiro de ponteiro vai mudar diretamente o valor do ponteiro que foi passado a função // ponteiro de ponteiro pois eu vou precisar acessar o endereço que o primeiro aponta
	
    FILE *ArqPrincipal;
	ArqPrincipal = fopen("Lista_Clientes.txt", "r");
    if (ArqPrincipal == NULL) {
        printf("\n\nErro ao abrir arquivo!");
    }
	
	*Primeiro = NULL;//definindo a lista como vazia
		
	DadosCliente *NovoCliente = (DadosCliente*) malloc(sizeof(DadosCliente));
		
	while (!feof(ArqPrincipal)){
		DadosCliente *NovoCliente = (DadosCliente *) malloc(sizeof(DadosCliente));
		
        //Vai ler o nome, CPF e telefone do cliente no arquivo e atribuir para NovoCliente
        if(fscanf(ArqPrincipal, "%80[^;];%13[^;];%14[^\n]\n", NovoCliente->cNome, NovoCliente->cCpf, NovoCliente->cTelefone) == 3){
            NovoCliente->ProxCliente = NULL;
	        if(Primeiro == NULL) { // Se a lista estão vazia
	    		NovoCliente->ProxCliente = NULL;
	    		*Primeiro = NovoCliente;//Primeiro aponta para o novo não
			}else{//se já existe cliente na lista
				NovoCliente->ProxCliente = *Primeiro;//NovoCliente aponta para o primeiro da lista (para o cliente que o ponteiro primeiro aponta)
	    		*Primeiro = NovoCliente;//ponteiro primeiro aponta para o cliente que acabou de ser adicionado
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
						
	//Coletando as informações do cliente
	do{
		printf("\nDigite o nome do cliente: ");
		fgets(NovoCliente->cNome, sizeof(NovoCliente->cNome), stdin);
		NovoCliente->cNome[strlen(NovoCliente->cNome)-1] = '\0'; //substitui o \n por um terminador \0
		fflush(stdin);
	}while(!validaNome(NovoCliente->cNome));
	do{
		printf("\nDigite o CPF do cliente: ");
		fgets(NovoCliente->cCpf, sizeof(NovoCliente->cCpf), stdin);
		NovoCliente->cCpf[strlen(NovoCliente->cCpf)-1] = '\0';
		fflush(stdin);
		if(!(CpfExistente(NovoCliente->cCpf, *Primeiro) == 0)){
			printf("\n\t*Atenção: o CPF digitado já consta no sistema\nverifique se os dados estão sendo inseridos corretamente ou se o cliente já estão cadastrado!\n");
		}
		if((validaCPF(NovoCliente->cCpf) == 0)){
			printf("\n\t*Atenção: o CPF digitado não está seguindo o formato especificado\n");
		}
	}while((validaCPF(NovoCliente->cCpf) == 0) || !(CpfExistente(NovoCliente->cCpf, *Primeiro) == 0));
	do{
		printf("\nDigite o número de telefone do cliente: ");
		fgets(NovoCliente->cTelefone, sizeof(NovoCliente->cTelefone), stdin);
		NovoCliente->cTelefone[strlen(NovoCliente->cTelefone)-1] = '\0';
		fflush(stdin);
		if(!validaTelefone(NovoCliente->cTelefone)){
			printf("\n\t*Atenção: o telefone digitado não está seguindo o formato especificado\n");
		}
	}while(!validaTelefone(NovoCliente->cTelefone));									
	
	if (Primeiro == NULL) {//Se a lista está vazia entre nesse primeiro if
    	NovoCliente->ProxCliente = NULL;
    	*Primeiro = NovoCliente;//Primeiro aponta para o novo nó
	}else{//se já existe cliente na lista
		NovoCliente->ProxCliente = *Primeiro;//NovoCliente aponta para o primeiro da lista (para o cliente que o ponteiro primeiro aponta)
    	*Primeiro = NovoCliente;//ponteiro primeiro aponta para o cliente que acabou de ser adicionado
	}
						
	//Abrindo o arquivo para inserir o cliente novo
	FILE *ArqPrincipal;
	ArqPrincipal = fopen("Lista_Clientes.txt", "a");
	
	if(ArqPrincipal == NULL){
		printf("\n\nErro ao abrir arquivo!");
	}
	
	fprintf(ArqPrincipal, "%s;%s;%s\n", NovoCliente->cNome, NovoCliente->cCpf, NovoCliente->cTelefone);//escreve os dados no arquivo
	fclose(ArqPrincipal);
	printf("\n\tCadastro realizado!");
}

void PesquisaCliente(DadosCliente **Primeiro){
	
	char cCpfComparacao[14];//cpf para comparar com o do cliente que deseja pesquisar
	int iOpcaoMenuBuscar;
	int iEncontrou = 0;
	
	linha();
	printf("\t====Pesquisar Cliente====");
	printf("\n*Para preencher o CPF utilize o formato abaixo...*");
	printf("\nCPF : Utilize o formato: xxxxxxxxxxx/xx -> 9 números / 2 números");
	linha();
		do {
			printf("Digite o CPF do cliente: ");
			fgets(cCpfComparacao, sizeof(cCpfComparacao), stdin);
			cCpfComparacao[strlen(cCpfComparacao)-1] = '\0';
			if((validaCPF(cCpfComparacao) == 0)){
				printf("\n\t*Atenção: o CPF digitado não está seguindo o formato especificado\n");
			}
		}while(!validaCPF(cCpfComparacao));
					
			DadosCliente *Buscar = *Primeiro;
			
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
				                Buscar->cNome[strlen(Buscar->cNome)-1] = '\0';
				            }while(!validaNome(Buscar->cNome));
				
				            do{
				                fflush(stdin);
				                printf("\nCPF do cliente: ");
				                fgets(Buscar->cCpf, sizeof(Buscar->cCpf), stdin);
				                Buscar->cCpf[strlen(Buscar->cCpf)-1] = '\0';
				                if((validaCPF(Buscar->cCpf) == 0)){
									printf("\n\t*Atenção: o CPF digitado não está seguindo o formato especificado\n");
								}
				            }while(!validaCPF(Buscar->cCpf));
				
				            do{
				                fflush(stdin);
				                printf("\nTelefone do cliente: ");
				                fgets(Buscar->cTelefone, sizeof(Buscar->cTelefone), stdin);
				                Buscar->cTelefone[strlen(Buscar->cTelefone)-1] = '\0';
				                if(!validaTelefone(Buscar->cTelefone)){
									printf("\n\t*Atenção: o telefone digitado não está seguindo o formato especificado\n");
								}
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
				//Escreve no arquivo secundario (seja cliente editado ou nÃ£o)							
				Buscar = Buscar->ProxCliente;
			}
				 
				if(iEncontrou != 1) {
				    linha();
				    printf("\tCliente não encontrado!");
				    linha();
				}
				free(Buscar);
}

void ListaClientes(DadosCliente **Primeiro){
	
	linha();
	printf("\t===Lista de Clientes===\n");
					
	DadosCliente *Auxiliar = *Primeiro;//define um auxiliar para percorrer a lista desde o primeiro cliente (ultimo cliente adicionado)
					
	if(Auxiliar == NULL){//se não tiver nenhum cliente cadastrado, não lê
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
}

void RemoverCliente(DadosCliente **Primeiro){
	
    char cCpfComparacaoRm[14];
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
	        fgets(cCpfComparacaoRm, sizeof(cCpfComparacaoRm), stdin);
	        cCpfComparacaoRm[strlen(cCpfComparacaoRm)-1] = '\0';
	        if((validaCPF(cCpfComparacaoRm) == 0)){
				printf("\n\t*Atenção: o CPF digitado não está seguindo o formato especificado\n");
			}
	    }while(!validaCPF(cCpfComparacaoRm));
	
	    // Procura o cliente na lista
	    while (Buscar != NULL) {
	        if(strcmp(cCpfComparacaoRm, Buscar->cCpf) == 0){// Cliente encontrado
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
	            while(getchar() != '\n');
	
	            if (iOpcaoMenuRemover == 1) { // Remove o cliente
	                Remover(Primeiro, Buscar->cCpf);
	                printf("\nCliente removido com sucesso!\n");
					break;            
				}   
	        }
	        Buscar = Buscar->ProxCliente;
	    }
	
	    if(iEncontrou != 1){
	        linha();
	        printf("\tCliente não encontrado!");
	        linha();
	    }
	}else{
		RetornaMenuClientes();
	}
}



void AtualizaLista(DadosCliente **Primeiro){//a cada loop le a lista encadeada (editada ou não) e sobrescreve no arquivo Principal 
	
	DadosCliente *Buscar;
	Buscar = *Primeiro; //vai ler a lista tudo denovo sÃ³ que sem o cliente removido
	
	FILE *ArqPrincipal = NULL;
	ArqPrincipal = fopen("Lista_Clientes.txt", "w");//sobreescreve o arquivo
	
	while(Buscar != NULL) {
	fprintf(ArqPrincipal, "%s;%s;%s\n", Buscar->cNome, Buscar->cCpf, Buscar->cTelefone);
	Buscar = Buscar->ProxCliente;
	}
	fclose(ArqPrincipal);	
}

//FIM MENU CLIENTES


//COMECO MENU VENDAS

int VerificaUltimoIdVenda(){ //função criada para ser feito o auto-incremento nos ID de venda.
    FILE *arquivoVendas;
    char linha[999];
    int idVenda = 0;
    int maiorID = 0;

    arquivoVendas = fopen("vendas.txt","r");

    if(arquivoVendas == NULL){
        fclose(arquivoVendas);
        return -1;
    };

    while (fgets(linha, sizeof(linha), arquivoVendas)) {
        sscanf(linha, "%d", &idVenda);
        if(maiorID<idVenda){
            maiorID = idVenda;
        }
    }
    fclose(arquivoVendas);
    return maiorID;
}

void RegistrarVenda(){
    int mudar=0;
    int temp=0;
    int erro=0;
    int qntVendidaTemp=0;
    int qntRestante=0;
    int qntRestanteTemp=0;
    float precoProd=0;
    float precoProdTemp = 0;
    FILE *arquivoVendas;
    FILE *tempVendas;
    time_t agora;
    int opcReg = 0;
    char linha[999];
    int diaAtual=0,mesAtual=0,AnoAtual=0;
    int dia=0,mes=0,ano=0,idVenda=0,idProd=0,idProdTemp=0,idProdLeitura=0,qntVendida=0;
    int diaTemp=0,mesTemp=0,anoTemp=0;
    float precoTotal=0;
    int idValido=0;
    char nomeProd[50]={0};
    char nomeProdLeitura[50];
    int id,qtd;
    char nome[50];
    float precoPorUnidade,desconto,precoFinal;

    idVenda = VerificaUltimoIdVenda()+1;

    time(&agora);

    struct tm *tempoLocal = localtime(&agora);

    diaAtual = tempoLocal->tm_mday;
    mesAtual = tempoLocal->tm_mon+1;
    AnoAtual = tempoLocal->tm_year+1900;

    dia = diaAtual;
    mes = mesAtual;
    ano = AnoAtual;

do{
    precoTotal = precoProd * qntVendida;
    idValido = 0;
    printf("Registro de Venda:\n");
    printf("1. Id da venda = %d\n", idVenda); //não tem como alterar
    printf("2. Id do produto = %d\n", idProd); //Alteravel
    printf("3. Nome do produto = %s\n", nomeProd); //não tem como alterar, vai ser buscado após o ID do produto for inserido
    printf("4. Quantidade Vendida = %d\n", qntVendida); //Alteravel
    printf("5. Data = %02d/%02d/%02d\n",dia,mes,ano); //Alteravel

    printf("Preço Final: %0.2f\n", precoTotal);
    printf("6. Registrar venda.\n");
    printf("7. Cancelar\n");

    scanf("%d",&opcReg);

    switch(opcReg){
        case 1:
        system("cls");
        printf("Erro: Não é possivel alterar o id da venda!\n");
        system("pause");
        system("cls");
        break;

        case 2:
        system("cls");
        printf("Id do produto = ");
        scanf("%d", &idProdTemp);
        getchar();
        FILE *arquivoProd;
        arquivoProd = fopen("produtos.txt","r");
        while (fgets(linha, sizeof(linha), arquivoProd)) {
            sscanf(linha, "%d,%49[^,],%d,%f,%f,%f", &idProdLeitura, nomeProdLeitura,&qntRestanteTemp,&temp,&temp,&precoProdTemp);
            if(idProdTemp == idProdLeitura){
                idProd = idProdTemp;
                strcpy(nomeProd,nomeProdLeitura);
                precoProd = precoProdTemp;
                qntRestante = qntRestanteTemp;
                idValido = 1;
            }
        }

        if(idValido != 1){
            printf("Erro: ID invalido!\n");
            system("pause");
            system("cls");
        }
        fclose(arquivoProd);
        break;

        case 3:
        system("cls");
        printf("Erro: Não é possivel o nome do produto!\n");
        system("pause");
        system("cls");
        break;

        case 4:
        system("cls");
        printf("Quantidade de produtos vendidos: ");
        scanf("%d", &qntVendidaTemp);
        getchar();
        system("cls");
        if(qntVendidaTemp<=0){
            system("cls");
            printf("Erro: A quantidade tem que ser acima de zero\n");
            system("pause");
            system("cls");
        } else {
            if(qntVendidaTemp>qntRestante){
                system("cls");
                printf("Erro: Não tem esse numero de produtos no estoque!\n");
                system("pause");
                system("cls");
            } else {
                qntVendida = qntVendidaTemp;
                qntVendidaTemp = 0;
            }
        }
        //Fazer inserir a quantidade de produtos vendidos
        break;

        case 5:
        printf("Coloque a data da venda no seguinte formato (Dia/Mes/Ano):\n");
        scanf("%d/%d/%d",&diaTemp,&mesTemp,&anoTemp);
        getchar();

        if(diaTemp < 0 || mesTemp < 0 || anoTemp < 0 || mesTemp > 12 || diaTemp > 31 || anoTemp < 2000){
            printf("Erro: Verifique a data.\n");
            system("pause");
            system("cls");
        } else {
            if(diaTemp>diaAtual&&mesTemp>=mesAtual&&anoTemp>=AnoAtual){
                        printf("Erro: Verifique a data.\n");
                        system("pause");
                        system("cls");
                    } else { 
                        if(diaTemp <= diaAtual-3){
                            printf("Aviso: Só pode registrar vendas de até 3 dias!\n");
                            system("pause");
                            system("cls");
                        } else {
                            dia = diaTemp;
                            mes = mesTemp;
                            ano = anoTemp;
                        } 
                    }
        }

        system("cls");

        
        

        //Fazer inserir a data(modificar a data que já vai ser puxada)
        break;

        case 6:
        if(qntVendida<=0){ //Dupla verificação se a quantidade é diferente de 0
            printf("Erro: A quantidade vendida não pode ser menor ou igual a zero.");
            system("pause");
            system("cls");
        } else if(idProd == 0){
            printf("Erro: Escolha um produto para registrar a venda.");
            system("pause");
            system("cls");
        }else {
            mudar = 1;
            arquivoVendas = fopen("vendas.txt", "a");
            arquivoProd = fopen("produtos.txt", "r");
            //tempVendas

            if(arquivoVendas == NULL){
                printf("Erro ao abrir o arquivo de vendas.");
                system("pause");
                system("cls");
                erro = 1;
            }

            if(arquivoProd == NULL){
                printf("Erro ao abrir o arquivo de produtos.");
                system("pause");
                system("cls");
                erro = 1;
            }

            while (fgets(linha, sizeof(linha), arquivoProd)) {
            sscanf(linha, "%d,%49[^,],%d,%f,%f,%f", &id, nome, &qtd, &precoPorUnidade, &desconto, &precoFinal);
            if(id != idProd){
                tempVendas = fopen("tempVProd.txt", "a");
                fprintf(tempVendas,"%d,%s,%d,%0.2f,%0.2f,%0.2f\n", id,nome,qtd,precoPorUnidade,desconto,precoFinal);
                fclose(tempVendas);
            } else {
                qtd = qtd-qntVendida;
                tempVendas = fopen("tempVProd.txt", "a");
                fprintf(tempVendas,"%d,%s,%d,%0.2f,%0.2f,%0.2f\n", id,nome,qtd,precoPorUnidade,desconto,precoFinal);
                fclose(tempVendas);
            }
        }

            fprintf(arquivoVendas,"%d",idVenda);
            fprintf(arquivoVendas, ",");
            fprintf(arquivoVendas,"%d",idProd);
            fprintf(arquivoVendas, ",");
            fprintf(arquivoVendas,"%s",nomeProd);
            fprintf(arquivoVendas, ",");
            fprintf(arquivoVendas,"%d",qntVendida);
            fprintf(arquivoVendas, ",");
            fprintf(arquivoVendas,"%0.2f",precoTotal);
            fprintf(arquivoVendas, ",");
            fprintf(arquivoVendas,"%02d,%02d,%02d", dia,mes,ano);
            fprintf(arquivoVendas, "\n");
            printf("Registro de venda criado com sucesso!\n");
            system("pause");
            system("cls");

            fclose(arquivoVendas);
            fclose(arquivoProd);
        
        

        //Adicionar ao arquivo de vendas a venda atual
        break;

        case 7:
        break;

        default:
        printf("Escolha uma opção valida!\n");
        system("pause");
        system("cls");
        break;

 } } }while(opcReg != 6 && opcReg != 7);

    if(erro == 0 && mudar == 1){
                remove("produtos.txt");
                rename("tempVProd.txt", "produtos.txt");
                system("cls");
            } else {
                remove("tempVProd.txt");
                system("cls");
                erro = 0;
            }

        }

 
    

void ConsultaVendas(){
    FILE *arquivoVendas;
    char linha[999];
    int dia,mes,ano,idVenda,idProd,qntVendida;
    float precoTotal;
    char nomeProd[50]={0};
    arquivoVendas = fopen("vendas.txt", "r");

    if(arquivoVendas == NULL){
        perror("Erro ao abrir o arquivo");
        system("cls");
    }

    while (fgets(linha, sizeof(linha), arquivoVendas)) {
        sscanf(linha, "%d,%d,%49[^,],%d,%f,%d,%d,%d", &idVenda,&idProd, nomeProd, &qntVendida, &precoTotal, &dia, &mes, &ano); //essa bomba lê a linha e organiza cada valor em sua devida variavel.

   
        printf("ID da venda: %d, ID do Produto: %d, Nome do produto: %s, Quantidade vendida: %d, Preço final: %0.2f, Data: %02d/%02d/%02d\n", idVenda,idProd,nomeProd,qntVendida,precoTotal,dia,mes,ano);
    }
    fclose(arquivoVendas);

}


void DeletarVenda(){
    int id,qtd;
    char nome[50];
    float precoPorUnidade,desconto,precoFinal;
    FILE *ArquivoProd;
    FILE *arquivoVendas;
    FILE *tempVendas;
    char linha[999];
    int dia,mes,ano,idVenda,idProd,qntVendida;
    float precoTotal;
    char nomeProd[50]={0};
    int rvendaID=0;
    int encontrado=0;
    int confirmRVenda=0;
    printf("Qual o id da venda que você deseja remover: ");
    scanf("%d", &rvendaID);

    arquivoVendas = fopen("vendas.txt", "r");

    if(arquivoVendas == NULL){
        perror("Erro ao abrir o arquivo");
        system("cls");
    }

    while (fgets(linha, sizeof(linha), arquivoVendas)) {
        sscanf(linha, "%d,%d,%49[^,],%d,%f,%d,%d,%d", &idVenda,&idProd, nomeProd, &qntVendida, &precoTotal, &dia, &mes, &ano); //essa bomba lê a linha e organiza cada valor em sua devida variavel.
    if(rvendaID != idVenda){ //ID de venda diferente do procurado
        tempVendas = fopen("tempV.txt", "a");
        fprintf(tempVendas,"%d,%d,%s,%d,%0.2f,%2d,%02d,%02d\n",idVenda,idProd,nomeProd,qntVendida,precoTotal,dia,mes,ano);
        fclose(tempVendas);
    } else {
        encontrado = 1;
        printf("ID da venda: %d, ID do Produto: %d, Nome do produto: %s, Quantidade vendida: %d, Preço final: %0.2f, Data: %02d/%02d/%02d\n", idVenda,idProd,nomeProd,qntVendida,precoTotal,dia,mes,ano);
        printf("Tem certeza que deseja remover o seguinte registro de venda (1 - Sim, 2 - Não): ");
        scanf("%d", &confirmRVenda);
        switch(confirmRVenda){
            case 1:
            ArquivoProd = fopen("produtos.txt", "r");
            while (fgets(linha, sizeof(linha), ArquivoProd)) {
            sscanf(linha, "%d,%49[^,],%d,%f,%f,%f", &id, nome, &qtd, &precoPorUnidade, &desconto, &precoFinal);
            if(id != idProd){ //ID diferente do id da venda escolhida
                tempVendas = fopen("tempVProd.txt", "a");
                fprintf(tempVendas,"%d,%s,%d,%0.2f,%0.2f,%0.2f\n", id,nome,qtd,precoPorUnidade,desconto,precoFinal);
                fclose(tempVendas);

            } else {
                qtd = qtd+qntVendida;
                tempVendas = fopen("tempVProd.txt", "a");
                fprintf(tempVendas,"%d,%s,%d,%0.2f,%0.2f,%0.2f\n", id,nome,qtd,precoPorUnidade,desconto,precoFinal);
                fclose(tempVendas);
                }

            }

            fclose(ArquivoProd);
            break;
            
            case 2:
            confirmRVenda = 0;
            break;
        }
        //Aqui vai remover a venda solicitada
    }
    }

    fclose(arquivoVendas);
    if(encontrado == 1 && confirmRVenda == 1){
        remove("vendas.txt");
        rename("tempV.txt", "vendas.txt");
        remove("produtos.txt");
        rename("tempVProd.txt", "produtos.txt");
        encontrado = 0;
        system("cls");
        printf("Registro de venda removido com sucesso!\n");
        system("pause");
        system("cls");
    } else {
        system("cls");
        remove("tempV.txt");
        if(encontrado == 0){
            printf("Erro: Registro de venda não encontrado.\n");
            system("pause");
            system("cls");
        }


    }
    }

//Começo das funções do MENU abaixo:
void MenuProduto(){
    int subOpcao, subSubOpcao = 0;
    int indice = 0;
    produto temp = {0};
    
    do {
        printf("=== Menu de Produtos ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Exibir Produtos\n");
        printf("3. Editar Produtos\n");
        printf("4. Excluir Produtos\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &subOpcao);
        getchar();
        system("cls");

        switch (subOpcao) {
            case 1:
                do {
                    temp.valorFinal = temp.precoUnidade * (1 - (temp.desconto / 100));
                    printf("Cadastro de produtos:\n");
                    printf("1. Id = %d \n", temp.id);
                    printf("2. Nome = %s \n", temp.nomeProduto);
                    printf("3. Preco por unidade = R$%.2f \n", temp.precoUnidade);
                    printf("4. Desconto = %.2f%% \n", temp.desconto);
                    printf("\n");
                    printf("Valor Final por unidade: R$%.2f \n", temp.valorFinal);
                    printf("5. Criar produto\n");
                    printf("6. Cancelar\n");
                    printf("Escolha um dos valores para editar ou criar o produto: \n");
                    scanf("%d", &subSubOpcao);
                    getchar();
                    
                    switch (subSubOpcao) {
                        case 1:
                            system("cls");
                            printf("Id (1-999) = ");
                            scanf("%d", &temp.id);
                            getchar();
                            system("cls");
                            break;
                        case 2:
                            system("cls");
                            printf("Nome = ");
                            fgets(temp.nomeProduto, sizeof(temp.nomeProduto), stdin);
                            temp.nomeProduto[strcspn(temp.nomeProduto, "\n")] = '\0';
                            system("cls");
                            break;
                        case 3:
                            system("cls");
                            char precoStr[20];
                            printf("Preco por unidade = ");
                            fgets(precoStr, sizeof(precoStr), stdin);
                            temp.precoUnidade = stringParaFloat(precoStr);
                            system("cls");
                            break;
                        case 4:
                            system("cls");
                            char descontoStr[20];
                            printf("Desconto = ");
                            fgets(descontoStr, sizeof(descontoStr), stdin);
                            temp.desconto = stringParaFloat(descontoStr);
                            system("cls");
                            break;
                        case 5:
                            system("cls");

                            if (temp.id < 1 || temp.id > 999) {
                                printf("Erro: ID deve estar entre 1 e 999.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }

                            if (strlen(temp.nomeProduto) == 0) {
                                printf("Erro: Nome do produto nao pode estar vazio.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }

                            temp.valorFinal = temp.precoUnidade * (1 - (temp.desconto / 100));
                            temp.qtd = 0;

                            FILE *produto;
                            produto = fopen("produtos.txt", "a");

                            if (produto == NULL){
                                printf("Nao foi possivel criar/editar o arquivo.");
                                system("pause");
                            }

                            if(ConsultaIDrep(temp.id) == 1){
                                printf("Erro: Já tem um produto com esse id.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }

                            if(temp.precoUnidade<0){
                                printf("Erro: O preco nao pode ser negativo.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }

                            if(temp.desconto>100){
                                printf("Erro: O desconto nao pode ser acima de 100%.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }

                            if(temp.desconto<0){
                                printf("Erro: O desconto nao pode ser negativo.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }


                            fprintf(produto,"%d",temp.id);
                            fprintf(produto, ",");
                            fprintf(produto,"%s",temp.nomeProduto);
                            fprintf(produto, ",");
                            fprintf(produto,"%d",temp.qtd);
                            fprintf(produto, ",");
                            fprintf(produto,"%0.2f",temp.precoUnidade);
                            fprintf(produto, ",");
                            fprintf(produto,"%0.2f",temp.desconto);
                            fprintf(produto, ",");
                            fprintf(produto,"%0.2f",temp.valorFinal);
                            fprintf(produto, "\n");
                            fclose(produto);
                            
                            printf("Produto criado com sucesso.\n");

                            memset(&temp, 0, sizeof(temp));
                            
                            system("pause");
                            system("cls");

                            break;
                        case 6:
                             memset(&temp, 0, sizeof(temp));
                             system("cls");
                             break;                        
                        default:
                             printf("Escolha uma opcao válida.\n");
                             memset(&temp, 0, sizeof(temp));
                             break;
                    }
                } while (subSubOpcao != 6 && subSubOpcao != 5);

                break;

            case 2:
                ConsultaProd();
                system("pause");
                system("cls");
                
                break;

            case 3:
                EditarProd();
                break;

            case 4:
                RemoverProd();
                break;

            case 0:
                system("cls");
                printf("Voltando ao menu principal...\n");
                system("pause");
                system("cls");
                break;

            default:
                printf("Escolha uma opcao válida.\n");
                memset(&temp, 0, sizeof(temp)); 
                break;
        }
    } while (subOpcao != 0);
}

void MenuEstoque(){

    #define MAX_PRODUTOS 999
    produto produtos[MAX_PRODUTOS];
    int totalProdutos = 0;
    int opcao;
    carregarProdutos(produtos, &totalProdutos);

do {
        printf("\n=== Menu de Estoque===\n"); // submenu do estoque...
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        getchar();

        switch(subOpcao) {
        case 1:
            adicionarItemEstoque(produtos, &totalProdutos);
            break;
        case 2:
            removerItemEstoque(produtos, &totalProdutos);
            break;
        case 3:
            listarItens(produtos, totalProdutos);
            break;
        case 0:
            system("cls");
            printf("Voltando ao menu principal...\n");
            salvarProdutos(produtos, totalProdutos);
            system("pause");
            system("cls");
            break;
        default:
            printf("Opção invalida! Tente novamente.\n");
        }
    } while (subOpcao != 0);
}



void MenuVendas(){
    int subOpcao=0;

    do{
    printf("=== Menu de Vendas ===\n");
    printf("1. Consultar vendas\n");
    printf("2. Registrar vendas\n");
    printf("3. Remover venda\n");
    printf("0. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    getchar();
    system("cls");
    switch(subOpcao){
        case 1:
        ConsultaVendas();
        system("pause");
        system("cls");
        break;

        case 2:
        RegistrarVenda();
        break;

        case 3:
        DeletarVenda();
        break;

        case 0:
        system("cls");
        printf("Voltando ao menu principal...");
        system("pause");
        system("cls");
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    }while(subOpcao != 0);


}

void MenuFinanceiro(){
        #define maximoDeVendas 10000
        venda vendas[maximoDeVendas];
        float totalReceita=0;
        int totalVendas = 0;

        do{
        carregarArquivoVendas(vendas, &totalVendas);
    printf("=== Menu do Financeiro ===\n");
    printf("1. Ver Receita Total\n");
    printf("2. Exibir Resumo de Receitas\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    getchar();
    system("cls");
    switch(subOpcao){
        case 1:
            totalReceita = calculoDeReceita(vendas, totalVendas);  // total vai recebe o calculo total receita vinda da funcao que realiza toda a soma
            printf("Receita Total: R$ %.2f\n", totalReceita);
            break;

        case 2:
            mostrarResumoReceitas(vendas, totalVendas);
            break;

        case 0:
            system("cls");
            printf("Voltando ao menu principal...\n");
            system("pause");
            system("cls");
            break;

        default:
        printf("Escolha uma opção valida.\n");
        system("pause");
        system("cls");
    }
    } while (subOpcao != 0);

}

void MenuClientes(){
        FILE *ArqPrincipal;
	ArqPrincipal = fopen("Lista_Clientes.txt", "r");
	if(ArqPrincipal == NULL){
		printf("\n\nErro ao abrir arquivo!");
	}
	fclose(ArqPrincipal);
	
	
	
	//Primeiro: ponteiro que vai apontar para o primeiro da lista	
	DadosCliente *Primeiro = NULL;
	
	//NovoCliente: quem vai receber as informações do usuário
	DadosCliente *NovoCliente;
	
	//opcao dos menus e submenus
	int iOpcaoMenuClientes;
	
	//função que vai atualizar a lista de cliente lendo o arquivo ao iniciar o programa
	LerClientesNoArquivo(&Primeiro);
	
		do{
				linha();
				printf("\t====Menu Clientes====\n");
				printf("\n 1. Cadastrar cliente");
				printf("\n 2. Pesquisar cliente");
				printf("\n 3. Listar clientes");
				printf("\n 4. Remover cliente");
				printf("\n 0. Voltar ao Menu Principal");
				linha();
				printf("\tEscolha uma opção: ");
				scanf("%d", &iOpcaoMenuClientes);
	        	while(getchar()!='\n');
		
				switch(iOpcaoMenuClientes){
				
					case 1://Cadastro cliente
						RecebeCliente(&Primeiro);
						clrscr();
						break;
					case 2://Pesquisar e Editar cliente
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
					case 0://Volta para o menu principal
                        system("cls");
						RetornaMenuPrincipal();
						clrscr();
					break;
					default:
						OpcaoInvalida();
						clrscr();
					break;
				}
				AtualizaLista(&Primeiro);
			}while(iOpcaoMenuClientes != 0);

}

void MenuFuncionarios(){
    #define MAX_FUNCIONARIOS 100
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int total_funcionarios = 0;

    carregarFuncionarios(funcionarios, &total_funcionarios);

     do{
    system("cls");
    printf("================Menu=====================\n");
    printf("1- Exibir tabela de funcionários ativos\n");
    printf("2- Exibir tabela de funcionários demitidos\n");
    printf("3- Adicionar funcionário\n");
    printf("4- Remover funcionário\n");
    printf("0- Sair\n");
    printf("==========================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    getchar();
    salvarFuncionarios(funcionarios, total_funcionarios);
    system("cls");
    switch(subOpcao){
        case 1:
            printf("\nTabela de Funcionários Ativos:\n");
            criarTabela(funcionarios, total_funcionarios, 1);
            system("pause");
            break;
        case 2:
            printf("\nTabela de Funcionários Demitidos:\n");
            criarTabela(funcionarios, total_funcionarios, 0);
            system("pause");
            break;
        case 3:
            adicionarFuncionario(funcionarios, &total_funcionarios, MAX_FUNCIONARIOS);
             system("pause");
            break;
        case 4:
            removerFuncionario(funcionarios, total_funcionarios);
            system("pause");
            break;
          
        case 0:
                system("cls");
                salvarFuncionarios(funcionarios, total_funcionarios);  
                printf("Voltando ao menu principal...\n");
                system("pause");
                system("cls");
            break;

        default:
            printf("Opção inválida.\n");
            break;
        }
    }while (subOpcao != 0);

}


void MenuFornecedores(){
    FILE*arquivo;
    arquivo=fopen("Fornecedor.txt","a");
if (arquivo == NULL) {
        perror("Arquivo nao abriu");
    }
     inserir fornecedor[100]; 
    inserir x;
    int arrayforne=0;
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
    printf("====== Menu de fornecedores======\n");
	printf("1-Cadastrar fornecedor\n");
	printf("2-Mostrar tabela dos fornecedores\n");
	printf("3-Pesquisar Fornecedor\n");
	printf("0-Sair \n");
	printf("================================\n");
	printf("Escolha uma opção: ");
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

        case 0:
        system("cls");
        printf("Voltando ao menu principal...\n");
        system("pause");
        system("cls");
        break;
}
}while(numero !=0);	

fclose(arquivo);
}

void MenuGerenciamentoDeDoacoes(){
    FILE *arquiv;
    produto produtos[MAX_PRODUTOS];
    int totalProdutos = 0;
    carregarProdutos(produtos, &totalProdutos);
    do{
        printf("=== Gereciamento de doações ===\n");
        printf("1. Registrar Doação\n");
        printf("2. Consultar Doações\n");
        printf("3. Excluir Doação\n");
        printf("4. Listar Itens no Estoque\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        getchar();
        system("cls");
        switch(subOpcao){
            case 1:
                arquiv = fopen("Doacoes.txt", "a");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para registro!");
                }
                registroDoacao(produtos, &totalProdutos, arquiv);
                fclose(arquiv);
                break;

            case 2:
                arquiv = fopen("Doacoes.txt", "r");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para consulta!");
                }
                consultarDoacao(arquiv);
                fclose(arquiv);
                break;

            case 3:
            arquiv = fopen("Doacoes.txt", "r");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para exclusão!");
                }
            excluirDoacao(arquiv, produtos, &totalProdutos);
            break;

            case 4:
                listarItens(produtos, totalProdutos);
                break;
            
            case 0:
                system("cls"); 
                printf("Voltando ao menu principal...\n");
                salvarProdutos(produtos, totalProdutos);
                system("pause");
                system("cls");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;

        }
    } while (subOpcao != 0);
}


int main(){
    system("color F0");
    setlocale(LC_ALL,"pt-BR.UTF-8");
    int opcao=0;
    int iD = 0;

    while(opcao!=9){
        printf("\n=== Menu Principal ===\n");
        printf("1. Produto\n");
        printf("2. Estoque\n");
        printf("3. Vendas\n");
        printf("4. Financeiro\n");
        printf("5. Clientes\n");
        printf("6. Funcionários\n");
        printf("7. Fornecedores\n");
        printf("8. Gerenciamento de Doações\n");    
        printf("9. Sair\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        system("cls");

        switch(opcao){
            case 1:
            MenuProduto();
            break;

            case 2:
            MenuEstoque();
            break;

            case 3:
            MenuVendas();
            break;

            case 4:
            MenuFinanceiro();
            break;

            case 5:
            MenuClientes();
            break;

            case 6:
            MenuFuncionarios();
            break;

            case 7:
            MenuFornecedores();
            break;

            case 8:
            MenuGerenciamentoDeDoacoes();
            break;

            case 9:
            printf("Até a proxima.\n");
            system("pause");
            break;

            default:
            printf("Escolha uma opção valida\n");
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}
