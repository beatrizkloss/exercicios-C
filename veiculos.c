#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Veiculo {
    char codigo[10];
    char cor[20];
    char marca[50];
    char chassi[17];
    char dono[50];
    char anoCompra[5];
    char anoFabricacao[5];
    int tipo; // 1 para carro, 2 para moto
    int ativo;
};

void incluirVeiculo(struct Veiculo veiculos[], int *numVeiculos) {
    if (*numVeiculos < MAX) {
        printf("Digite o codigo do veiculo: ");
        scanf("%s", veiculos[*numVeiculos].codigo);
        printf("Digite a cor do veiculo: ");
        scanf("%s", veiculos[*numVeiculos].cor);
        printf("Digite a marca do veiculo: ");
        scanf("%s", veiculos[*numVeiculos].marca);
        printf("Digite o chassi do veiculo: ");
        scanf("%s", veiculos[*numVeiculos].chassi);
        printf("Digite o dono do veiculo: ");
        scanf("%s", veiculos[*numVeiculos].dono);
        printf("Digite o ano de compra do veiculo: ");
        scanf("%s", veiculos[*numVeiculos].anoCompra);
        printf("Digite o ano de fabricacao do veiculo: ");
        scanf("%s", veiculos[*numVeiculos].anoFabricacao);
        printf("Digite o tipo do veiculo (1 para carro, 2 para moto): ");
        scanf("%d", &veiculos[*numVeiculos].tipo);
        veiculos[*numVeiculos].ativo = 1;
        (*numVeiculos)++;
        printf("Veiculo adicionado com sucesso!\n");
    } else {
        printf("O arquivo de veiculos esta cheio, nao e possivel adicionar mais veiculos.\n");
    }
    system("PAUSE");
    system("cls");
}

void listarVeiculosPorTipo(struct Veiculo veiculos[], int numVeiculos, int tipo) {
    int count = 0;
    printf("Lista de Veiculos:\n");
    for (int i = 0; i < numVeiculos; i++) {
        if (veiculos[i].ativo && veiculos[i].tipo == tipo) {
            printf("Codigo: %s\n", veiculos[i].codigo);
            printf("Cor: %s\n", veiculos[i].cor);
            printf("Marca: %s\n", veiculos[i].marca);
            printf("Chassi: %s\n", veiculos[i].chassi);
            printf("Dono: %s\n", veiculos[i].dono);
            printf("Ano de Compra: %s\n", veiculos[i].anoCompra);
            printf("Ano de Fabricacao: %s\n", veiculos[i].anoFabricacao);
            printf("\n");
            count++;
        }
    }
    if (count == 0) {
        printf("Nenhum veiculo do tipo selecionado foi encontrado.\n");
    }
    system("PAUSE");
    system("cls");
}


void consultarVeiculo(struct Veiculo veiculos[], int numVeiculos) {
    char codigoBusca[10];
    printf("Digite o codigo do veiculo a ser consultado: ");
    scanf("%s", codigoBusca);
    for (int i = 0; i < numVeiculos; i++) {
        if (veiculos[i].ativo && strcmp(veiculos[i].codigo, codigoBusca) == 0) {
            printf("Codigo: %s\n", veiculos[i].codigo);
            printf("Cor: %s\n", veiculos[i].cor);
            printf("Marca: %s\n", veiculos[i].marca);
            printf("Chassi: %s\n", veiculos[i].chassi);
            printf("Dono: %s\n", veiculos[i].dono);
            printf("Ano de Compra: %s\n", veiculos[i].anoCompra);
            printf("Ano de Fabricacao: %s\n", veiculos[i].anoFabricacao);
            printf("\n");
            system("PAUSE");
            system("cls");
            return;
        }
    }
    printf("Veiculo nao encontrado.\n");
    system("PAUSE");
    system("cls");
}

void alterarVeiculo(struct Veiculo veiculos[], int numVeiculos) {
    char codigoBusca[10];
    printf("Digite o codigo do veiculo a ser alterado: ");
    scanf("%s", codigoBusca);
    for (int i = 0; i < numVeiculos; i++) {
        if (veiculos[i].ativo && strcmp(veiculos[i].codigo, codigoBusca) == 0) {
            printf("Digite o novo codigo do veiculo: ");
            scanf("%s", veiculos[i].codigo);
            printf("Digite a nova cor do veiculo: ");
            scanf("%s", veiculos[i].cor);
            printf("Digite a nova marca do veiculo: ");
            scanf("%s", veiculos[i].marca);
            printf("Digite o novo chassi do veiculo: ");
            scanf("%s", veiculos[i].chassi);
            printf("Digite o novo dono do veiculo: ");
            scanf("%s", veiculos[i].dono);
            printf("Digite o novo ano de compra do veiculo: ");
            scanf("%s", veiculos[i].anoCompra);
            printf("Digite o novo ano de fabricacao do veiculo: ");
            scanf("%s", veiculos[i].anoFabricacao);
            printf("Digite o novo tipo do veiculo (1 para carro, 2 para moto): ");
            scanf("%d", &veiculos[i].tipo);
            printf("Veiculo alterado com sucesso!\n");
            system("PAUSE");
            system("cls");
            return;
        }
    }
    printf("Veiculo nao encontrado.\n");
    system("PAUSE");
    system("cls");
}

void excluirVeiculo(struct Veiculo veiculos[], int numVeiculos) {
    char codigoBusca[10];
    printf("Digite o codigo do veiculo a ser excluido: ");
    scanf("%s", codigoBusca);
    for (int i = 0; i < numVeiculos; i++) {
        if (veiculos[i].ativo && strcmp(veiculos[i].codigo, codigoBusca) == 0) {
            veiculos[i].ativo = 0;
            printf("Veiculo excluido com sucesso!\n");
            system("PAUSE");
            system("cls");
            return;
        }
    }
    printf("Veiculo nao encontrado.\n");
    system("PAUSE");
    system("cls");
}

void salvarVeiculos(struct Veiculo veiculos[], int numVeiculos) {
    FILE *arquivo = fopen("veiculos.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fwrite(veiculos, sizeof(struct Veiculo), numVeiculos, arquivo);
    fclose(arquivo);
}

void carregarVeiculos(struct Veiculo veiculos[], int *numVeiculos) {
    FILE *arquivo = fopen("veiculos.dat", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de veiculos nao encontrado. Criando novo arquivo.\n");
        return;
    }
    *numVeiculos = fread(veiculos, sizeof(struct Veiculo), MAX, arquivo);
    fclose(arquivo);
}

int main(void) {
    struct Veiculo veiculos[MAX];
    int numVeiculos = 0;
    int escolha;
    
    carregarVeiculos(veiculos, &numVeiculos);

    do {
        printf("+------------------------+\n");
        printf("|  * * *  M E N U * * *  |\n");
        printf("+------------------------+\n");
        printf("|   [1] Incluir          |\n");
        printf("|   [2] Consultar        |\n");
        printf("|   [3] Alterar          |\n");
        printf("|   [4] Excluir          |\n");
        printf("|   [5] Relatorio Carros |\n");
        printf("|   [6] Relatorio Motos  |\n");
        printf("|   [7] Finalizar        |\n");
        printf("+------------------------+\n");
        printf("\nSua escolha? ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                incluirVeiculo(veiculos, &numVeiculos);
                salvarVeiculos(veiculos, numVeiculos);
                break;
            case 2:
                consultarVeiculo(veiculos, numVeiculos);
                break;
            case 3:
                alterarVeiculo(veiculos, numVeiculos);
                salvarVeiculos(veiculos, numVeiculos);
                break;
            case 4:
                excluirVeiculo(veiculos, numVeiculos);
                salvarVeiculos(veiculos, numVeiculos);
                break;
            case 5:
                listarVeiculosPorTipo(veiculos, numVeiculos, 1); // 1 para carros
                break;
            case 6:
                listarVeiculosPorTipo(veiculos, numVeiculos, 2); // 2 para motos
                break;
            case 7:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 7);

    return 0;
}

