#include <stdio.h>
#include <string.h>

int main() {
    int subOpcao, subSubOpcao;

    typedef struct { // Variáveis dos produtos
        int id;
        int qtd;
        float unidade;
        float desconto;
        float valorFinal;
        char nomeProduto[100];
    } produto;

    produto temp;
    temp.id = 0;
    temp.qtd = 0;
    temp.unidade = 0;
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
                printf("Cadastro de produtos:\n");
                printf("1. Id = %d \n", temp.id);
                printf("2. Nome = %s \n", temp.nomeProduto);
                printf("3. Quantidade = %d \n", temp.qtd);
                printf("4. Preço por unidade: %.2f \n", temp.unidade);
                printf("5. Desconto: %.2f%% \n", temp.desconto);
                printf("\n");
                printf("Valor Final: %.2f \n", temp.valorFinal);
                printf("6. Criar produto\n");
                printf("7. Cancelar\n");
                printf("Escolha um dos valores para editar ou criar o produto: \n");
                scanf("%d", &subSubOpcao);
                
                switch (subSubOpcao) {
                    case 1:
                        printf("Id = ");
                        scanf("%d", &temp.id);
                        break;
                    case 2:
                        printf("Nome = ");
                        getchar();
                        fgets(temp.nomeProduto, sizeof(temp.nomeProduto), stdin);
                        temp.nomeProduto[strcspn(temp.nomeProduto, "\n")] = '\0';
                        break;
                    case 3:
                        printf("Quantidade = ");
                        scanf("%d", &temp.qtd);
                        break;
                    case 4:
                        printf("Preço por unidade = ");
                        scanf("%f", &temp.unidade);
                        break;
                    case 5:
                        printf("Desconto = ");
                        scanf("%f", &temp.desconto);
                        break;
                    case 6:
                        temp.valorFinal = (temp.unidade * temp.qtd) * (1 - (temp.desconto / 100));
                        
                        Prod[0].id = temp.id;
                        strcpy(Prod[0].nomeProduto, temp.nomeProduto);
                        Prod[0].qtd = temp.qtd;
                        Prod[0].unidade = temp.unidade;
                        Prod[0].desconto = temp.desconto;
                        Prod[0].valorFinal = temp.valorFinal;
                        
                        printf("Produto criado com sucesso.\n");
                        system("pause");
                }
                break;

            case 2:
                printf("Editar produtos\n");
                break;

            case 3:
                break;

            default:
                printf("Escolha uma opção válida.\n");
        }
    } while (subOpcao != 3);

    return 0;
}
