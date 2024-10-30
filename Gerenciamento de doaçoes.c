#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Doacao {
    char produto[50];
    int qtd;
    char data[20];
} Doacao;

void registroDoacao(FILE *arquiv) {
    Doacao doacao;
    getchar();
    printf("Produto a ser doado: ");
    fgets(doacao.produto, sizeof(doacao.produto), stdin);
    printf("Quantidade a ser doada: ");
    scanf("%d", &doacao.qtd);
    getchar();
    printf("Data da doação: ");
    fgets(doacao.data, sizeof(doacao.data), stdin);

    fprintf(arquiv, "Produto: %sQuantidade: %d\nData: %s\n\n", doacao.produto, doacao.qtd, doacao.data);
    printf("Doação registrada com sucesso!\n");
}

void ConsultarDoacao() {
    Doacao doacao2;
    char linha[999];

    FILE *arquivo = fopen("C:\\Users\\Usuario\\Desktop\\pim\\Registro_Doaçoes.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para consulta!\n");
        return;
    }

    printf("=== Doações Registradas ===\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "Produto: %49[^\n] Quantidade: %d Data: %19[^\n]", doacao2.produto, &doacao2.qtd, doacao2.data);
        printf("Produto: %s\nQuantidade: %d\nData: %s\n\n", doacao2.produto, doacao2.qtd, doacao2.data);
    }

    fclose(arquivo);
    printf("=== Fim da Consulta ===\n");
}

int main() {
    int subOpcao = 0;

    do {
        printf("=== Gerenciamento de Doações ===\n");
        printf("1. Registrar Doação\n");
        printf("2. Consultar Doações\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        system("cls");

        switch (subOpcao) {
            case 1: {
                FILE *arquiv = fopen("C:\\Users\\Usuario\\Desktop\\pim\\Registro_Doaçoes.txt", "a");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para registro!\n");
                    return 1;
                }
                printf("Registrar Doação\n");
                registroDoacao(arquiv);
                fclose(arquiv);
                break;
            }
            case 2:
                printf("Consultar Doações\n");
                ConsultarDoacao();
                break;
            case 3:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Escolha uma opção válida.\n");
        }

    } while (subOpcao != 3);

    return 0;
}
