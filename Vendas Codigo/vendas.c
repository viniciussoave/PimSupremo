#include <stdio.h> //Falta fazer a parte de registrar vendas, já foi feito a parte de inserir ID do produto.
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

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
    FILE *arquivoVendas;
    int opcReg = 0;
    char linha[999];
    int dia=0,mes=0,ano=0,idVenda=0,idProd=0,idProdTemp=0,idProdLeitura=0,qntVendida=0;
    float precoTotal;
    int idValido=0;
    char nomeProd[50]={0};
    char nomeProdLeitura[50];
    arquivoVendas = fopen("vendas.txt", "a");
    idVenda = VerificaUltimoIdVenda()+1;
do{
    idValido = 0;
    printf("Registro de Venda:\n");
    printf("1. Id da venda = %d\n", idVenda); //não tem como alterar
    printf("2. Id do produto = %d\n", idProd); //Alteravel
    printf("3. Nome do produto = %s\n", nomeProd); //não tem como alterar, vai ser buscado após o ID do produto for inserido
    printf("4. Quantidade Vendida = %d\n", qntVendida); //Alteravel
    printf("5. Data = %02d/%02d/%02d\n",dia,mes,ano); //Alteravel
    printf("6. Registrar venda.");

    scanf("%d",&opcReg);

    switch(opcReg){
        case 1:
        printf("Erro: Não é possivel alterar o id da venda!\n");
        system("pause");
        system("cls");
        break;

        case 2:
        system("cls");
        printf("Id do produto = ");
        scanf("%d", &idProdTemp);
        FILE *arquivoProd;
        arquivoProd = fopen("produtos.txt","r");
        while (fgets(linha, sizeof(linha), arquivoProd)) {
            sscanf(linha, "%d,%49[^,]", &idProdLeitura, nomeProdLeitura);
            if(idProdTemp == idProdLeitura){
                idProd = idProdTemp;
                strcpy(nomeProd,nomeProdLeitura);
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
        printf("Erro: Não é possivel o nome do produto!\n");
        system("pause");
        system("cls");
        break;

        case 4:
        //Fazer inserir a quantidade de produtos vendidos
        break;

        case 5:
        //Fazer inserir a data(modificar a data que já vai ser puxada)
        break;

        case 6:
        //Adicionar ao arquivo de vendas a venda atual
        break;

        default:
        printf("Escolha uma opção valida!\n");
        system("pause");
        system("cls");
        break;
    }
    } while(opcReg != 6);
    fclose(arquivoVendas);
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

int main(){
    setlocale(LC_ALL,"pt-BR.UTF-8");
    int subOpcao=0;

    do{
    printf("=== Menu de Vendas ===\n");
    printf("1. Consultar vendas\n");
    printf("2. Registrar vendas\n");
    printf("3. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
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
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 3);

    return 0;
}
