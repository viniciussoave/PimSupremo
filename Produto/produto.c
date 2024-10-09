#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

int main() {
    int subOpcao, subSubOpcao;
    int indice = 0;

    typedef struct { // Variáveis dos produtos
        int id;
        int qtd;
        float precoUnidade;
        float desconto;
        float valorFinal;
        char nomeProduto[100];
    } produto;

    produto temp;
    temp.id = 0;
    temp.qtd = 0;
    temp.precoUnidade = 0;
    temp.desconto = 0;
    temp.valorFinal = 0;
    temp.nomeProduto[0] = '\0';

    produto Prod[100];

    do {
        printf("=== Menu de Produtos ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Editar Produtos\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        system("cls");

        switch (subOpcao) {
            case 1:
            while(subSubOpcao != 7 && subSubOpcao != 6 ){
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
                
                switch (subSubOpcao) {
                    case 1:
                        system("cls");
                        printf("Id = ");
                        scanf("%d", &temp.id);
                        system("cls");
                        break;
                    case 2:
                        system("cls");
                        printf("Nome = ");
                        getchar();
                        fgets(temp.nomeProduto, sizeof(temp.nomeProduto), stdin);
                        temp.nomeProduto[strcspn(temp.nomeProduto, "\n")] = '\0';
                        system("cls");
                        break;
                    case 3:
                        system("cls");
                        printf("Quantidade = ");
                        scanf("%d", &temp.qtd);
                        system("cls");
                        break;
                    case 4:
                        system("cls");
                        printf("Preço por unidade = ");
                        scanf("%f", &temp.precoUnidade);
                        system("cls");
                        break;
                    case 5:
                        system("cls");
                        printf("Desconto = ");
                        scanf("%f", &temp.desconto);
                        system("cls");
                        break;
                    case 6:
                        temp.valorFinal = (temp.precoUnidade * temp.qtd) * (1 - (temp.desconto / 100));
                        
                        Prod[indice].id = temp.id;
                        strcpy(Prod[indice].nomeProduto, temp.nomeProduto);
                        Prod[indice].qtd = temp.qtd;
                        Prod[indice].precoUnidade = temp.precoUnidade;
                        Prod[indice].desconto = temp.desconto;
                        Prod[indice].valorFinal = temp.valorFinal;
                        indice++;
                        printf("Produto criado com sucesso.\n");
                        temp.id = 0;
                        temp.qtd = 0;
                        temp.precoUnidade = 0;
                        temp.desconto = 0;
                        temp.valorFinal = 0;
                        temp.nomeProduto[0] = '\0';
                        system("pause");
                        system("cls");
                        break;
                    case 7:
                            temp.id = 0;
                            temp.qtd = 0;
                            temp.precoUnidade = 0;
                            temp.desconto = 0;
                            temp.valorFinal = 0;
                            temp.nomeProduto[0] = '\0';
                            system("cls");
                            break;
                        
                }
            }
                break;

            case 2:
                printf("Editar produtos\n");
                break;

            case 3:
                break;

            default:
                printf("Escolha uma opção válida.\n");
                break;
        }
    } while (subOpcao != 3);

    return 0;
}
