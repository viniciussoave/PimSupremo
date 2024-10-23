#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

// Definição da estrutura produto
typedef struct { 
    int id;
    int qtd;
    float precoUnidade;
    float desconto;
    float valorFinal;
    char nomeProduto[100];
} produto;

// Função para verificar se o ID já existe
int verificarID(produto Prod[], int indice, int id) {
    for (int i = 0; i < indice; i++) {
        if (Prod[i].id == id) {
            return 1; // ID já existe
        }
    }
    return 0; // ID não existe
}

// Função para converter string para float, substituindo ',' por '.'
float stringParaFloat(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.'; // Substitui ',' por '.'
        }
    }
    return atof(str); // Converte a string para float
}

// Função para consultar produtos
void consultarProdutos(produto Prod[], int indice) {
    if (indice == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    
    printf("=== Produtos Cadastrados ===\n");
    for (int i = 0; i < indice; i++) {
        printf("ID: %d\n", Prod[i].id);
        printf("Nome: %s\n", Prod[i].nomeProduto);
        printf("Quantidade: %d\n", Prod[i].qtd);
        printf("Preço por Unidade: %.2f\n", Prod[i].precoUnidade);
        printf("Desconto: %.2f%%\n", Prod[i].desconto);
        printf("Valor Final: %.2f\n", Prod[i].valorFinal);
        printf("--------------------------\n");
    }
}

int main() {
    int subOpcao, subSubOpcao = 0; // Inicializa subSubOpcao
    int indice = 0;

    produto temp = {0}; // Inicializa todos os campos da estrutura temp para 0
    produto Prod[100] = {0}; // Inicializa todos os campos da estrutura Prod para 0

    do {
        printf("=== Menu de Produtos ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Consultar produtos\n");
        printf("3. Editar Produtos\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        getchar(); // Limpa o buffer de entrada
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
                    getchar(); // Limpa o buffer de entrada
                    
                    switch (subSubOpcao) {
                        case 1:
                            system("cls");
                            printf("Id (1-999) = ");
                            scanf("%d", &temp.id);
                            getchar(); // Limpa o buffer de entrada
                            system("cls");
                            break;
                        case 2:
                            system("cls");
                            printf("Nome = ");
                            fgets(temp.nomeProduto, sizeof(temp.nomeProduto), stdin);
                            temp.nomeProduto[strcspn(temp.nomeProduto, "\n")] = '\0'; // Remove nova linha
                            system("cls");
                            break;
                        case 3:
                            system("cls");
                            printf("Quantidade = ");
                            scanf("%d", &temp.qtd);
                            getchar(); // Limpa o buffer de entrada
                            system("cls");
                            break;
                        case 4:
                            system("cls");
                            char precoStr[20]; // String para armazenar o preço temporariamente
                            printf("Preço por unidade = ");
                            fgets(precoStr, sizeof(precoStr), stdin); // Lê como string
                            temp.precoUnidade = stringParaFloat(precoStr); // Converte para float
                            system("cls");
                            break;
                        case 5:
                            system("cls");
                            char descontoStr[20]; // String para armazenar o desconto temporariamente
                            printf("Desconto = ");
                            fgets(descontoStr, sizeof(descontoStr), stdin); // Lê como string
                            temp.desconto = stringParaFloat(descontoStr); // Converte para float
                            system("cls");
                            break;
                        case 6:
                            system("cls");

                            // Verifica se ID, nome e quantidade são válidos
                            if (temp.id < 1 || temp.id > 999) {
                                printf("Erro: ID deve estar entre 1 e 999.\n");
                                memset(&temp, 0, sizeof(temp)); // Zera a estrutura
                                system("pause");
                                system("cls");
                                break; // Retorna ao menu de cadastro
                            }

                            if (verificarID(Prod, indice, temp.id)) {
                                printf("Erro: Já existe um produto com esse ID.\n");
                                memset(&temp, 0, sizeof(temp)); // Zera a estrutura
                                system("pause");
                                system("cls");
                                break; // Retorna ao menu de cadastro
                            }
                            
                            if (strlen(temp.nomeProduto) == 0) {
                                printf("Erro: Nome do produto não pode estar vazio.\n");
                                memset(&temp, 0, sizeof(temp)); // Zera a estrutura
                                system("pause");
                                system("cls");
                                break; // Retorna ao menu de cadastro
                            }

                            if (temp.qtd <= 0) {
                                printf("Erro: Quantidade deve ser maior que zero.\n");
                                memset(&temp, 0, sizeof(temp)); // Zera a estrutura
                                system("pause");
                                system("cls");
                                break; // Retorna ao menu de cadastro
                            }

                            // Calcula o valor final ao criar o produto
                            temp.valorFinal = (temp.precoUnidade * temp.qtd) * (1 - (temp.desconto / 100));
                            
                            Prod[indice].id = temp.id;
                            strcpy(Prod[indice].nomeProduto, temp.nomeProduto);
                            Prod[indice].qtd = temp.qtd;
                            Prod[indice].precoUnidade = temp.precoUnidade;
                            Prod[indice].desconto = temp.desconto;
                            Prod[indice].valorFinal = temp.valorFinal;
                            
                            indice++;
                            
                            printf("Produto criado com sucesso.\n");

                            // Reseta os valores temporários
                            memset(&temp, 0, sizeof(temp)); // Limpa a estrutura
                            
                            system("pause");
                            system("cls");

                            break;
                        case 7:
                             // Reseta os valores temporários
                             memset(&temp, 0, sizeof(temp)); // Limpa a estrutura
                             system("cls");
                             break;                        
                        default:
                             printf("Escolha uma opção válida.\n");
                             memset(&temp, 0, sizeof(temp)); // Zera a estrutura em caso de erro
                             break;
                    }
                } while (subSubOpcao != 7 && subSubOpcao != 6); // Continua até cancelar

                break;

            case 2:
                consultarProdutos(Prod, indice); // Chama a função de consulta de produtos
                system("pause"); // Pausa para visualizar os resultados antes de limpar a tela
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
                memset(&temp, 0, sizeof(temp)); // Zera a estrutura em caso de erro
                break;
        }
    } while (subOpcao != 4);

    return 0;
}
