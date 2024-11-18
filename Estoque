#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

typedef struct { // Estrutura heterogenea de produtos... (Vinicius)
    int id;
    int qtd;
    float precoUnidade;
    float desconto;
    float valorFinal;
    char nomeProduto[50];
} produto;

int main() {

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
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch(opcao) {
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
            exit(1);
            break;
        default:
            printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void listarItens(produto produtos[], int totalProdutos) {
    printf("\n=== lista de prosdutos ===\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("ID: %d\nnome: %s\npreço Unidade: %.2f\ndesconto: %.2f\nvalor final: %.2f\nestoque: %d unidades\n",
               produtos[i].id, produtos[i].nomeProduto, produtos[i].precoUnidade,
               produtos[i].desconto, produtos[i].valorFinal, produtos[i].qtd);
        printf("------------------------\n");
    }
}

void carregarProdutos(produto produtos[], int *totalProdutos) { //incluindo os pararmetros
    *totalProdutos = 0; // o total do array precisa come�a com 0
    FILE *arquivo = fopen("E:\\Linguagem_C\\Projeto PIM 2\\Projeto\\bin\\Debug\\Produtos.txt", "r"); // acesso o arquivo do vinicius
    if (arquivo == NULL) {
        printf("Arquivo n�o existe!!!!"); // programa��o defensiva...
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
    bool idExiste = false; // boolean pra controlar o la�o se o id existir no array struct.
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
        printf("Produto com ID %d n�o encontrado.\n", id);
    }
}

void removerItemEstoque(produto produtos[], int *totalProdutos) {
    int idEstoque, qtdRemover;
    bool idExiste = false;

    printf("Escreva o ID do item que voc� deseja remover do estoque: ");
    scanf("%d", &idEstoque);

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].id == idEstoque) {
            idExiste = true;
            printf("Produto selecionado: %s\n", produtos[i].nomeProduto);
            printf("Selecione a quantidade de itens que voc� deseja remover: ");
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
        printf("Produto com ID %d n�o encontrado.\n", idEstoque);
    }
}


void salvarProdutos(produto produtos[], int totalProdutos) {
    FILE *arquivo = fopen("E:\\Linguagem_C\\Projeto PIM 2\\Projeto\\bin\\Debug\\Produtos.txt", "w");
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
