#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char linha[999];
    int id, qtd;
    float precoPorUnidade, desconto, precoFinal;
    char nome[50];

a
    file = fopen("arquivo.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }


    while (fgets(linha, sizeof(linha), file)) {

        sscanf(linha, "%d,%49[^,],%d,%f,%f,%f", &id, nome, &qtd, &precoPorUnidade, &desconto, &precoFinal); //essa bomba lê a linha e organiza cada valor em sua devida variavel.

   
        printf("ID: %d, Nome: %s, Quantidade: %d, Preço por unidade: R$%.2f, Desconto: %.2f, Preço Final: %.2f\n",
               id, nome, qtd, precoPorUnidade, desconto, precoFinal); //essa bomba mostra os valores.
    }


    fclose(file);
    return 0;
}
