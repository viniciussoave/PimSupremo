#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

typedef struct {
    char produto[50];
    int qtd;
    char data[20];
    char local[100];
} Doacao;

typedef struct {
    int id;
    int qtd;
    float precoUnidade;
    float desconto;
    float valorFinal;
    char nomeProduto[50];
} produto;

#define MAX_PRODUTOS 999
produto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

void carregarProdutos();
void salvarProdutos();
void registroDoacao(FILE *arquiv);
void consultarDoacao(FILE *arquiv);
void excluirDoacao(FILE *arquiv);
void listarItens();

int main() {
    int opcao;
    setlocale(LC_ALL, "pt-BR.UTF-8");
    carregarProdutos();

    do {
        printf("\n=== Menu de Estoque e Doações ===\n");
        printf("1. Registrar Doação\n");
        printf("2. Consultar Doações\n");
        printf("3. Excluir Doação\n");
        printf("4. Listar Itens no Estoque\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: {
                FILE *arquiv = fopen("Doacoes.txt", "a");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para registro!");
                    return 1;
                }
                registroDoacao(arquiv);
                fclose(arquiv);
                break;
            }
            case 2: {
                FILE *arquiv = fopen("Doacoes.txt", "r");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para consulta!");
                    return 1;
                }
                consultarDoacao(arquiv);
                fclose(arquiv);
                break;
            }
            case 3: {
                FILE *arquiv = fopen("Doacoes.txt", "r");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para exclusão!");
                    return 1;
                }
                excluirDoacao(arquiv);
                break;
            }
            case 4:
                listarItens();
                break;
            case 0:
                printf("Saindo do programa...\n");
                salvarProdutos();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void carregarProdutos() {
    totalProdutos = 0;
    FILE *arquivo = fopen("Produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de produtos não encontrado.\n");
        exit(1);
    }
    while(fscanf(arquivo, "%d,%49[^,],%d,%f,%f,%f", &produtos[totalProdutos].id,
                 produtos[totalProdutos].nomeProduto,
                 &produtos[totalProdutos].qtd,
                 &produtos[totalProdutos].precoUnidade,
                 &produtos[totalProdutos].desconto,
                 &produtos[totalProdutos].valorFinal) == 6) {
        totalProdutos++;
    }
    fclose(arquivo);
}

void salvarProdutos() {
    FILE *arquivo = fopen("Produtos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de produtos para salvar.\n");
        exit(1);
    }
    for (int i = 0; i < totalProdutos; i++) {
        fprintf(arquivo, "%d,%s,%d,%.2f,%.2f,%.2f\n",
                produtos[i].id,
                produtos[i].nomeProduto,
                produtos[i].qtd,
                produtos[i].precoUnidade,
                produtos[i].desconto,
                produtos[i].valorFinal);
    }
    fclose(arquivo);
}

void registroDoacao(FILE *arquiv) {
    Doacao doacao;
    bool encontrado;

    do {
        system("cls");
        printf("Produto a ser doado: ");
        fgets(doacao.produto, sizeof(doacao.produto), stdin);
        doacao.produto[strcspn(doacao.produto, "\n")] = 0;

        encontrado = false;
        for (int i = 0; i < totalProdutos; i++) {
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

    fprintf(arquiv, "%s,%d,%s,%s\n", doacao.produto, doacao.qtd, doacao.local, doacao.data);
    printf("Doação registrada com sucesso!\n");

    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(produtos[i].nomeProduto, doacao.produto) == 0) {
            if (produtos[i].qtd >= doacao.qtd) {
                produtos[i].qtd -= doacao.qtd;
                salvarProdutos();
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

void excluirDoacao(FILE *arquiv) {
    Doacao doacoes[999];
    int totalDoacoes = 0;
    char linha[999];

    while (fgets(linha, sizeof(linha), arquiv) && totalDoacoes < 999) {
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
    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(produtos[i].nomeProduto, doacoes[escolha - 1].produto) == 0) {
            produtos[i].qtd += doacoes[escolha - 1].qtd;
            salvarProdutos();
            printf("Estoque atualizado após exclusão da doação.\n");
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto não encontrado no estoque para repor a quantidade.\n");
    }

    arquiv = fopen("Doacoes.txt", "w");
    if (arquiv == NULL) {
        perror("Erro ao abrir o arquivo para reescrever!");
        return;
    }

    for (int i = 0; i < totalDoacoes; i++) {
        if (i != escolha - 1) {
            fprintf(arquiv, "%s,%d,%s,%s\n", doacoes[i].produto, doacoes[i].qtd, doacoes[i].local, doacoes[i].data);
        }
    }
    fclose(arquiv);

    printf("Doação excluída com sucesso!\n");
    system("pause");
    system("cls");
}

void listarItens() {
    printf("\n=== Lista de Produtos ===\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("ID: %d\nNome: %s\nPreço Unidade: %.2f\nDesconto: %.2f\nValor Final: %.2f\nEstoque: %d unidades\n",
               produtos[i].id, produtos[i].nomeProduto, produtos[i].precoUnidade, produtos[i].desconto,
               produtos[i].valorFinal, produtos[i].qtd);
        printf("------------------------\n");
 }
}
