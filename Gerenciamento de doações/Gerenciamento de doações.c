#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Doacao {
    char produto[50];
    int qtd;
    char data[20];
    char local[100];
} Doacao;

void registroDoacao(FILE *arquiv) {
    Doacao doacao;
    system("cls");
    printf("Produto a ser doado: ");
    fgets(doacao.produto, sizeof(doacao.produto), stdin);
    doacao.produto[strcspn(doacao.produto, "\n")] = 0;

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
    system("pause");
    system("cls");
}

void consultarDoacao(FILE *arquiv) {
    Doacao doacao2;
    char linha[999];
    system("cls");
    printf("=== Doações Registradas ===\n");

    while (fgets(linha, sizeof(linha), arquiv)) {
        sscanf(linha, "%49[^,],%d,%99[^,],%19[^\n]", doacao2.produto, &doacao2.qtd, doacao2.local, doacao2.data);
        printf("Produto: %s\nQuantidade: %d\nInstituição: %s\nData: %s\n\n", doacao2.produto, doacao2.qtd, doacao2.local, doacao2.data);
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

    
    arquiv = fopen("C:\\Users\\Usuario\\Desktop\\pim\\Registro_Doaçoes.txt", "w");
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

int main() {
    int subOpcao;
    setlocale(LC_ALL, "pt-BR.UTF-8");

    do {
        printf("=== Gerenciamento de Doações ===\n");
        printf("1. Registrar Doação\n");
        printf("2. Consultar Doações\n");
        printf("3. Excluir Doação\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        getchar();

        switch (subOpcao) {
            case 1: {
                FILE *arquiv = fopen("C:\\Users\\Usuario\\Desktop\\pim\\Registro_Doaçoes.txt", "a");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para registro!\n");
                    return 1;
                }
                registroDoacao(arquiv);
                fclose(arquiv);
                break;
            }
            case 2: {
                FILE *arquiv = fopen("C:\\Users\\Usuario\\Desktop\\pim\\Registro_Doaçoes.txt", "r");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo para consulta!\n");
                    return 1;
                }
                consultarDoacao(arquiv);
                fclose(arquiv);
                break;
            }
            case 3:
                FILE *arquiv = fopen("C:\\Users\\Usuario\\Desktop\\pim\\Registro_Doaçoes.txt", "r");
                if (arquiv == NULL) {
                    perror("Erro ao abrir o arquivo");
                    return 1;
            }
                excluirDoacao(arquiv);
            
                break;
            case 4:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Escolha uma opção válida.\n");
        }
    } while (subOpcao != 4);

    return 0;
}
