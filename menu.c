#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int subOpcao=0;

void produto(){
    typedef struct prod{
        int ID;
        char nome[100];
        int precoEmCentavos;
        int QntRestante;
        int vendas;
        int doados;
    }Produto;


    do{
    printf("=== Menu de Produtos ===\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Editar Produtos\n");
    printf("3. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    system("cls");
    switch(subOpcao){
        case 1:
        printf("Cadastro de produtos\n");
        break;

        case 2:
        printf("Editar produtos\n");
        break;

        case 3:
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 3);
}

void estoque(){
do{
    printf("=== Menu do Estoque ===\n");
    printf("1. Consultar estoque\n");
    printf("2. Editar Estoque\n");
    printf("3. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    system("cls");
    switch(subOpcao){
        case 1:
        printf("Consultar estoque\n");
        break;

        case 2:
        printf("Editar Estoque\n");
        break;

        case 3:
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 3);

}

void vendas(){
    do{
    printf("=== Menu de Vendas ===\n");
    printf("1. Consultar vendas\n");
    printf("2. Registrar vendas\n");
    printf("3. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    system("cls");
    switch(subOpcao){
        case 1:
        printf("Consultar vendas\n");
        break;

        case 2:
        printf("Registrar vendas\n");
        break;

        case 3:
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 3);


}

void financeiro(){
        do{
    printf("=== Menu do Financeiro ===\n");
    printf("1. Ver receita\n");
    printf("2. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    system("cls");
    switch(subOpcao){
        case 1:
        printf("Consulta de receita\n");
        break;

        case 2:
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 2);

}

void clientes(){
        do{
    printf("=== Menu de clientes ===\n");
    printf("1. Consultar clientes\n");
    printf("2. Adicionar clientes\n");
    printf("3. Remover clientes\n");
    printf("4. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    system("cls");
    switch(subOpcao){
        case 1:
        printf("Consultar clientes\n");
        break;

        case 2:
        printf("Adicionar cliente\n");
        break;

        case 3:
        printf("Remover cliente\n");
        break;

        case 4:
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 4);

}

void funcionarios(){
     do{
    printf("=== Menu de funcionários ===\n");
    printf("1. Consultar funcionários\n");
    printf("2. Adicionar funcionário\n");
    printf("3. Remover funcionário\n");
    printf("4. Voltar ao Menu Principal\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);
    system("cls");
    switch(subOpcao){
        case 1:
        printf("Consultar funcionários\n");
        break;

        case 2:
        printf("Adicionar funcionário\n");
        break;

        case 3:
        printf("Remover funcionário\n");
        break;

        case 4:
        break;

        default:
        printf("Escolha uma opção valida.\n");
    }
    } while (subOpcao != 4);

}


void fornecedores(){
    do{
        printf("=== Menu de fornecedores ===\n");
        printf("1. Consultar fornecedores\n");
        printf("2. Adicionar fornecedor\n");
        printf("3. Remover fornecedor\n");
        printf("4. Solicitar produtos\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        system("cls");
        switch(subOpcao){
            case 1:
            printf("Consultar fornecedores\n");
            break;

            case 2:
            printf("Adicionar fornecedor\n");
            break;

            case 3:
            printf("Remover fornecedor\n");
            break;

            case 4:
            printf("Solicitar produtos\n");
            break;

            case 5:
            break;

            default:
            printf("Escolha uma opção valida.\n");
        }
    } while (subOpcao != 5);
}

void gerenciamentoDeDoacoes(){
    do{
        printf("=== Gereciamento de doações ===\n");
        printf("1. Registrar Doação\n");
        printf("2. Consultar Doações\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &subOpcao);
        system("cls");
        switch(subOpcao){
            case 1:
            printf("Registrar Doação\n");
            break;

            case 2:
            printf("Consultar Doações\n");
            break;

            case 3:
            break;

            default:
            printf("Escolha uma opção valida.\n");
        }
    } while (subOpcao != 3);
}


int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao=0;
    int iD = 0;

    while(opcao!=9){
        printf("\n=== Menu Principal ===\n");
        printf("1. Produto\n");
        printf("2. Estoque\n");
        printf("3. Vendas\n");
        printf("4. Financeiro\n");
        printf("5. Clientes\n");
        printf("6. Funcionários\n");
        printf("7. Fornecedores\n");
        printf("8. Gerenciamento de Doações\n");    
        printf("9. Sair\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        system("cls");

        switch(opcao){
            case 1:
            produto();
            break;

            case 2:
            estoque();
            break;

            case 3:
            vendas();
            break;

            case 4:
            financeiro();
            break;

            case 5:
            clientes();
            break;

            case 6:
            funcionarios();
            break;

            case 7:
            fornecedores();
            break;

            case 8:
            gerenciamentoDeDoacoes();
            break;

            case 9:
            printf("Até a proxima.\n");
            system("pause");
            break;

            default:
            printf("Escolha uma opção valida\n");
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}
