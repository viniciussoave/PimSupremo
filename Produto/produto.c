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

void exibirTabela(produto Prod[], int indice) {
    if (indice == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int maxNome = 4;

    for (int i = 0; i < indice; i++) {
        if (strlen(Prod[i].nomeProduto) > maxNome) {
            maxNome = strlen(Prod[i].nomeProduto);
        }
    }

    printf("=== Produtos Cadastrados ===\n");
    printf("| ID | Nome%*s | Quantidade | Preço Unitário | Desconto | Valor Final |\n", maxNome - 4, "");
    printf("---------------------------------------------------------------\n");
    
    for (int i = 0; i < indice; i++) {
        printf("| %2d | %-*s | %10d | %13.2f | %8.2f%% | %11.2f |\n", 
               Prod[i].id, 
               maxNome, 
               Prod[i].nomeProduto, 
               Prod[i].qtd, 
               Prod[i].precoUnidade, 
               Prod[i].desconto, 
               Prod[i].valorFinal);
    }
    
    printf("---------------------------------------------------------------\n");
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
        system("cls");

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
                            printf("Quantidade = ");
                            scanf("%d", &temp.qtd);
                            getchar();
                            system("cls");
                            break;
                        case 4:
                            system("cls");
                            char precoStr[20];
                            printf("Preço por unidade = ");
                            fgets(precoStr, sizeof(precoStr), stdin);
                            temp.precoUnidade = stringParaFloat(precoStr);
                            system("cls");
                            break;
                        case 5:
                            system("cls");
                            char descontoStr[20];
                            printf("Desconto = ");
                            fgets(descontoStr, sizeof(descontoStr), stdin);
                            temp.desconto = stringParaFloat(descontoStr);
                            system("cls");
                            break;
                        case 6:
                            system("cls");

                            if (temp.id < 1 || temp.id > 999) {
                                printf("Erro: ID deve estar entre 1 e 999.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }

                            if (verificarID(Prod, indice, temp.id)) {
                                printf("Erro: Já existe um produto com esse ID.\n"); //tenho que corrigir o problema de verificar ID
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }
                            
                            if (strlen(temp.nomeProduto) == 0) {
                                printf("Erro: Nome do produto não pode estar vazio.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
                                break;
                            }

                            if (temp.qtd <= 0) {
                                printf("Erro: Quantidade deve ser maior que zero.\n");
                                memset(&temp, 0, sizeof(temp));
                                system("pause");
                                system("cls");
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
                            produto = fopen("\\\\192.168.68.101\\html\\produtos.txt", "a");

                            if (produto == NULL){
                                printf("Não foi possivel criar/editar o arquivo.");
                                return 1;
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
                        case 7:
                             memset(&temp, 0, sizeof(temp));
                             system("cls");
                             break;                        
                        default:
                             printf("Escolha uma opção válida.\n");
                             memset(&temp, 0, sizeof(temp));
                             break;
                    }
                } while (subSubOpcao != 7 && subSubOpcao != 6);

                break;

            case 2:
                exibirTabela(Prod, indice);
                system("pause"); 
                system("cls"); 
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
