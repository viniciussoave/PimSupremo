#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

typedef struct { 
    int id;
    int qtd;
    float precoUnidade;
    float desconto;
    float valorFinal;
    char nomeProduto[100];
} produto;

int verificarID(produto Prod[], int indice, int id) {
    for (int i = 0; i < indice; i++) {
        if (Prod[i].id == id) {
            return 1;
        }
    }
    return 0;
}

float stringParaFloat(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
    return atof(str);
}

int ConsultaIDrep(int idConsulta) {
    char linha[999];
    int x;
    int Ids[999]; //armazena os ids que serão lidos
    int indice = 0;
    FILE *produtos;
    produtos = fopen("produtos.txt","r");

    if (produtos == NULL) {
        perror("Erro ao abrir o arquivo");
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
    }


    while (fgets(linha, sizeof(linha), arquivo)) {

        sscanf(linha, "%d,%49[^,],%d,%f,%f,%f", &id, nome, &qtd, &precoPorUnidade, &desconto, &precoFinal); //essa bomba lê a linha e organiza cada valor em sua devida variavel.

   
        printf("ID: %d, Nome: %s, Quantidade: %d, Preço por unidade: R$%.2f, Desconto: %.2f, Preço Final: %.2f\n",
               id, nome, qtd, precoPorUnidade, desconto, precoFinal); //essa bomba mostra os valores.
    }


    fclose(arquivo);
}

int main() {
    int subOpcao, subSubOpcao = 0;
    int indice = 0;

    produto temp = {0};
    produto Prod[100] = {0};

    do {
        printf("=== Menu de Produtos ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Exibir Produtos\n");
        printf("3. Editar Produtos\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        getchar();
        system("clear");

        switch (subOpcao) {
            case 1:
                do {
                    temp.valorFinal = temp.precoUnidade * (1 - (temp.desconto / 100));
                    printf("Cadastro de produtos:\n");
                    printf("1. Id = %d \n", temp.id);
                    printf("2. Nome = %s \n", temp.nomeProduto);
                    printf("3. Quantidade = %d \n", temp.qtd);
                    printf("4. Preço por unidade: %.2f \n", temp.precoUnidade);
                    printf("5. Desconto: %.2f%% \n", temp.desconto);
                    printf("\n");
                    printf("Valor Final por unidade: %.2f \n", temp.valorFinal);
                    printf("6. Criar produto\n");
                    printf("7. Cancelar\n");
                    printf("Escolha um dos valores para editar ou criar o produto: \n");
                    scanf("%d", &subSubOpcao);
                    getchar();
                    
                    switch (subSubOpcao) {
                        case 1:
                            system("clear");
                            printf("Id (1-999) = ");
                            scanf("%d", &temp.id);
                            getchar();
                            system("clear");
                            break;
                        case 2:
                            system("clear");
                            printf("Nome = ");
                            fgets(temp.nomeProduto, sizeof(temp.nomeProduto), stdin);
                            temp.nomeProduto[strcspn(temp.nomeProduto, "\n")] = '\0';
                            system("clear");
                            break;
                        case 3:
                            system("clear");
                            printf("Quantidade = ");
                            scanf("%d", &temp.qtd);
                            getchar();
                            system("clear");
                            break;
                        case 4:
                            system("clear");
                            char precoStr[20];
                            printf("Preço por unidade = ");
                            fgets(precoStr, sizeof(precoStr), stdin);
                            temp.precoUnidade = stringParaFloat(precoStr);
                            system("clear");
                            break;
                        case 5:
                            system("clear");
                            char descontoStr[20];
                            printf("Desconto = ");
                            fgets(descontoStr, sizeof(descontoStr), stdin);
                            temp.desconto = stringParaFloat(descontoStr);
                            system("clear");
                            break;
                        case 6:
                            system("clear");

                            if (temp.id < 1 || temp.id > 999) {
                                printf("Erro: ID deve estar entre 1 e 999.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("clear");
                                break;
                            }

                            if (verificarID(Prod, indice, temp.id)) {
                                printf("Erro: Já existe um produto com esse ID.\n"); //tenho que corrigir o problema de verificar ID
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("clear");
                                break;
                            }
                            
                            if (strlen(temp.nomeProduto) == 0) {
                                printf("Erro: Nome do produto não pode estar vazio.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("clear");
                                break;
                            }

                            if (temp.qtd <= 0) {
                                printf("Erro: Quantidade deve ser maior que zero.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("clear");
                                break;
                            }

                            temp.valorFinal = (temp.precoUnidade * temp.qtd) * (1 - (temp.desconto / 100));
                            
                            Prod[indice].id = temp.id;
                            strcpy(Prod[indice].nomeProduto, temp.nomeProduto);
                            Prod[indice].qtd = temp.qtd;
                            Prod[indice].precoUnidade = temp.precoUnidade;
                            Prod[indice].desconto = temp.desconto;
                            Prod[indice].valorFinal = temp.valorFinal;
                            
                            FILE *produto;
                            produto = fopen("produtos.txt", "a");

                            if (produto == NULL){
                                printf("Não foi possivel criar/editar o arquivo.");
                                return 1;
                            }

                            if(ConsultaIDrep(temp.id) == 1){
                                printf("Erro: Já tem um produto com esse id.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("clear");
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
                            system("clear");

                            break;
                        case 7:
                             memset(&temp, 0, sizeof(temp));
                             system("clear");
                             break;                        
                        default:
                             printf("Escolha uma opção válida.\n");
                             memset(&temp, 0, sizeof(temp));
                             break;
                    }
                } while (subSubOpcao != 7 && subSubOpcao != 6);

                break;

            case 2:
                ConsultaProd();
                system("pause"); 
                
                break;

            case 3:
                // Implementar edição de produtos aqui
                break;

            case 4:
                // Voltar ao menu principal
                break;

            default:
                printf("Escolha uma opção válida.\n");
                memset(&temp, 0, sizeof(temp)); 
                break;
        }
    } while (subOpcao != 4);

    return 0;
}
