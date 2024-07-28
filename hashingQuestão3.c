
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

#define TAMANHO_TABELA 7

// Estrutura do nó da lista ligada
typedef struct No {
    int valor;
    char nome[50];
    struct No* prox;
} No;

// Estrutura da tabela hash, que contém uma lista ligada em cada posição
typedef struct {
    No* cabeca;
} TabelaHash;

// Inicializa a tabela hash, definindo todas as cabeças das listas ligadas como NULL
void inicializarTabela(TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela[i].cabeca = NULL;
    }
}

// Função de hash que calcula o índice baseado no valor
int funcaoHash(int valor) {
    return valor % TAMANHO_TABELA;
}

// Insere um novo elemento na tabela hash
void inserirElemento(TabelaHash* tabela, int valor, char* nome) {
    int indice = funcaoHash(valor);
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    strcpy(novoNo->nome, nome);
    novoNo->prox = tabela[indice].cabeca;
    tabela[indice].cabeca = novoNo;
}

// Exibe todos os elementos presentes na tabela hash
void exibirTabela(TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("Indice %d:\n", i);
        No* atual = tabela[i].cabeca;
        if (atual == NULL) {
            printf("  (vazio)\n");
        } else {
            while (atual != NULL) {
                printf("  Valor: %d, Nome: %s\n", atual->valor, atual->nome);
                atual = atual->prox;
            }
        }
        printf("-------------------------\n");
    }
}

// Verifica se uma string representa um número inteiro
bool ehNumero(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// Busca um elemento na tabela hash por valor ou nome
void buscarElemento(TabelaHash* tabela, char* entrada) {
    if (ehNumero(entrada)) {
        int valor = atoi(entrada);
        int indice = funcaoHash(valor);
        No* atual = tabela[indice].cabeca;
        bool encontrado = false;
        while (atual != NULL) {
            if (atual->valor == valor) {
                printf("Elemento encontrado:\n");
                printf("  Valor: %d, Nome: %s\n", atual->valor, atual->nome);
                encontrado = true;
                break;
            }
            atual = atual->prox;
        }
        if (!encontrado) {
            printf("Elemento não encontrado.\n");
        }
    } else {
        bool encontrado = false;
        for (int i = 0; i < TAMANHO_TABELA; i++) {
            No* atual = tabela[i].cabeca;
            while (atual != NULL) {
                if (strcmp(atual->nome, entrada) == 0) {
                    printf("Elemento encontrado:\n");
                    printf("  Valor: %d, Nome: %s\n", atual->valor, atual->nome);
                    encontrado = true;
                    break;
                }
                atual = atual->prox;
            }
            if (encontrado) break;
        }
        if (!encontrado) {
            printf("Elemento não encontrado.\n");
        }
    }
}

// Libera a memória alocada para a tabela hash
void liberarTabela(TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        No* atual = tabela[i].cabeca;
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    TabelaHash tabela[TAMANHO_TABELA];
    inicializarTabela(tabela);

    int opcao;
    do {
        system("cls"); // Limpa a tela
        printf("Menu:\n");
        printf("1. Inserir elemento\n");
        printf("2. Exibir tabela\n");
        printf("3. Buscar elemento\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

        switch (opcao) {
            case 1: {
                int valor;
                char nome[50];
                // Solicita o valor e o nome do usuário
                printf("Digite o valor: ");
                scanf("%d", &valor);
                getchar();
                printf("Digite o nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remover o caractere de nova linha
                // Insere o elemento na tabela
                inserirElemento(tabela, valor, nome);
                printf("Elemento inserido com sucesso.\n");
                system("pause");
                break;
            }
            case 2:
                // Exibe todos os elementos da tabela
                exibirTabela(tabela);
                system("pause");
                break;
            case 3: {
                char entrada[50];
                // Solicita a entrada para buscar
                printf("Digite o valor ou nome a ser buscado: ");
                fgets(entrada, 50, stdin);
                entrada[strcspn(entrada, "\n")] = '\0'; 
                // Busca o elemento na tabela NOME E VALOR
                buscarElemento(tabela, entrada);
                system("pause");
                break;
            }
            case 4:
                liberarTabela(tabela);
                printf("Saindo...\n");
                system("pause");
                break;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }
    } while (opcao != 4);

    return 0;
}


