#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

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
        printf("5. Voltar ao Menu Principal\n");
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

            case 5:
                // Voltar ao menu principal
                break;

            default:
                printf("Escolha uma opcao válida.\n");
                memset(&temp, 0, sizeof(temp)); 
                break;
        }
    } while (subOpcao != 5);
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
            printf("Saindo do programa...\n");
        salvarProdutos(produtos, totalProdutos);
            break;
        default:
            printf("Opção invalida! Tente novamente.\n");
        }
    } while (subOpcao != 0);
}



void vendas(){
    do{
    printf("=== Menu de Vendas ===\n");
    printf("1. Consultar vendas\n");
    printf("2. Registrar vendas\n");
    printf("3. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    getchar();
    system("cls");
    switch(subOpcao){
        case 1:
        printf("Consultar vendas\n");
        break;

        case 2:
        printf("Registrar vendas\n");
        break;

        case 3:
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 3);


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
            printf("Saindo do sistema financeiro...\n");
            break;

        default:
        printf("Escolha uma opção valida.\n");
        system("pause");
    }
    } while (subOpcao != 0);

}

void clientes(){
        do{
    printf("=== Menu de clientes ===\n");
    printf("1. Consultar clientes\n");
    printf("2. Adicionar clientes\n");
    printf("3. Remover clientes\n");
    printf("4. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    getchar();
    system("cls");
    switch(subOpcao){
        case 1:
        printf("Consultar clientes\n");
        break;

        case 2:
        printf("Adicionar cliente\n");
        break;

        case 3:
        printf("Remover cliente\n");
        break;

        case 4:
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 4);

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
    printf("5- Sair\n");
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
          
        case 5:
            salvarFuncionarios(funcionarios, total_funcionarios);  
            break;

        default:
            printf("Opção inválida.\n");
            break;
        }
    }while (subOpcao != 5);

}


void fornecedores(){
    do{
        printf("=== Menu de fornecedores ===\n");
        printf("1. Consultar fornecedores\n");
        printf("2. Adicionar fornecedor\n");
        printf("3. Remover fornecedor\n");
        printf("4. Solicitar produtos\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        getchar();
        system("cls");
        switch(subOpcao){
            case 1:
            printf("Consultar fornecedores\n");
            break;

            case 2:
            printf("Adicionar fornecedor\n");
            break;

            case 3:
            printf("Remover fornecedor\n");
            break;

            case 4:
            printf("Solicitar produtos\n");
            break;

            case 5:
            break;

            default:
            printf("Escolha uma opção valida.\n");
        }
    } while (subOpcao != 5);
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
                printf("Saindo do programa...\n");
                salvarProdutos(produtos, totalProdutos);
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;

        }
    } while (subOpcao != 0);
}


int main(){
    system("color 70");
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
            vendas();
            break;

            case 4:
            MenuFinanceiro();
            break;

            case 5:
            clientes();
            break;

            case 6:
            MenuFuncionarios();
            break;

            case 7:
            fornecedores();
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

