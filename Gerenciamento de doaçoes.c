#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char produto[50];
    int qtd;
    char data[20];
} Doacao;

void registroDoacao(FILE *arquivo) {
    Doacao doacao;
    getchar();
    printf("Produto a ser doado: ");
    fgets(doacao.produto, sizeof(doacao.produto), stdin);
    printf("Quantidade a ser doada: ");
    scanf("%d", &doacao.qtd);
    getchar();
    printf("Data da doação: ");
    fgets(doacao.data, sizeof(doacao.data), stdin);
    fprintf(arquivo, "Produto: %sQuantidade: %d\nData: %s\n\n", doacao.produto, doacao.qtd, doacao.data);
    printf("Doação registrada com sucesso!\n");
}

int main() {
    int subOpcao = 0;

    do {
        FILE *arquivo = fopen("C:\\Users\\Usuario\\Desktop\\pim\\Registro_Doaçoes.txt", "a");
        if (arquivo == NULL) {
            perror("Erro ao abrir o arquivo!\n");
            return 1;
        }

        printf("=== Gerenciamento de Doações ===\n");
        printf("1. Registrar Doação\n");
        printf("2. Consultar Doações\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        system("cls");

        switch (subOpcao) {
            case 1:
                printf("Registrar Doação\n");
                registroDoacao(arquivo);
                break;
            case 2:
                printf("Consultar Doações\n");
                break;
            case 3:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Escolha uma opção válida.\n");
        }

        fclose(arquivo);

    } while (subOpcao != 3);

    return 0;
}
