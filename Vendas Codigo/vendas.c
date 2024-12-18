#include <stdio.h> //Falta fazer a parte de registrar vendas, já foi feito a parte de inserir ID do produto.
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

float stringParaFloat(char *str) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
    return atof(str);
}

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

int main(){
    setlocale(LC_ALL,"pt-BR.UTF-8");
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

    return 0;
}
