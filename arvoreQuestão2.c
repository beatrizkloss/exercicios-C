
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura do nó da árvore
typedef struct No {
    int valor;
    char nome[100];
    struct No* esquerda;
    struct No* direita;
} No;

// Função para criar um novo nó
No* criarNo(int valor, char* nome) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    strcpy(novoNo->nome, nome);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um nó na árvore
No* inserir(No* raiz, int valor, char* nome) {
    // Se a árvore está vazia, retorna um novo nó
    if (raiz == NULL) {
        return criarNo(valor, nome);
    }

    // Insere recursivamente na subárvore esquerda ou direita
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor, nome);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor, nome);
    }

    // Retorna o ponteiro para a raiz
    return raiz;
}

// Função para buscar um nó na árvore pelo valor
No* buscar(No* raiz, int valor) {
    // Se a árvore está vazia ou o valor foi encontrado
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    // Busca recursivamente na subárvore esquerda ou direita
    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

// Função para encontrar o nó com valor mínimo (utilizado na remoção)
No* encontrarMinimo(No* raiz) {
    No* atual = raiz;

    // Encontra o nó mais à esquerda da árvore
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }

    return atual;
}

// Função para remover um nó da árvore
No* remover(No* raiz, int valor) {
    // Se a árvore está vazia
    if (raiz == NULL) {
        return raiz;
    }

    // Busca recursivamente o nó a ser removido
    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        // Nó encontrado para remoção
        // Nó com apenas um filho ou nenhum filho
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos: encontrar o sucessor mínimo na subárvore direita
        No* temp = encontrarMinimo(raiz->direita);

        // Copia o sucessor encontrado para este nó
        raiz->valor = temp->valor;
        strcpy(raiz->nome, temp->nome);

        // Remove o sucessor
        raiz->direita = remover(raiz->direita, temp->valor);
    }

    return raiz;
}

// Função para exibir a árvore em ordem
void exibir(No* raiz) {
    if (raiz != NULL) {
        exibir(raiz->esquerda);
        printf("Valor: %d, Nome: %s\n", raiz->valor, raiz->nome);
        exibir(raiz->direita);
    }
}

// Função principal
int main(void) {
    setlocale(LC_ALL, "Portuguese");
    No* raiz = NULL;
    int opcao, valor;
    char nome[100];

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Inserir um nó\n");
        printf("2. Buscar um nome na árvore\n");
        printf("3. Remover um valor da árvore\n");
        printf("4. Exibir os elementos da árvore\n");
        printf("5. Sair do programa\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Inserir um nó na árvore
                printf("Digite o valor inteiro para inserir: ");
                scanf("%d", &valor);
                printf("Digite o nome para inserir: ");
                scanf("%s", nome);
                raiz = inserir(raiz, valor, nome);
                printf("No inserido com sucesso!\n");
                break;
            case 2:
                // Buscar um nome na árvore pelo valor inteiro
                printf("Digite o valor inteiro para buscar: ");
                scanf("%d", &valor);
                No* encontrado = buscar(raiz, valor);
                if (encontrado != NULL) {
                    printf("Nome encontrado: %s\n", encontrado->nome);
                } else {
                    printf("Valor nao encontrado na arvore.\n");
                }
                break;
            case 3:
                // Remover um valor da árvore
                printf("Digite o valor inteiro para remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                printf("Valor %d removido da arvore.\n", valor);
                break;
            case 4:
                // Exibir todos os elementos da árvore
                printf("Elementos da arvore:\n");
                exibir(raiz);
                break;
            case 5:
                // Sair do programa
                printf("Saindo do programa...\n");
                break;
            default:
                // Opção inválida
                printf("Opcao invalida. Tente novamente.\n");
        }

        // Pausa para manter a interface limpa
        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 

        system("cls");

    } while (opcao != 5);

    return 0;
}



