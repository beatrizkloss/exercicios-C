
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura do n� da �rvore
typedef struct No {
    int valor;
    char nome[100];
    struct No* esquerda;
    struct No* direita;
} No;

// Fun��o para criar um novo n�
No* criarNo(int valor, char* nome) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    strcpy(novoNo->nome, nome);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Fun��o para inserir um n� na �rvore
No* inserir(No* raiz, int valor, char* nome) {
    // Se a �rvore est� vazia, retorna um novo n�
    if (raiz == NULL) {
        return criarNo(valor, nome);
    }

    // Insere recursivamente na sub�rvore esquerda ou direita
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor, nome);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor, nome);
    }

    // Retorna o ponteiro para a raiz
    return raiz;
}

// Fun��o para buscar um n� na �rvore pelo valor
No* buscar(No* raiz, int valor) {
    // Se a �rvore est� vazia ou o valor foi encontrado
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    // Busca recursivamente na sub�rvore esquerda ou direita
    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

// Fun��o para encontrar o n� com valor m�nimo (utilizado na remo��o)
No* encontrarMinimo(No* raiz) {
    No* atual = raiz;

    // Encontra o n� mais � esquerda da �rvore
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }

    return atual;
}

// Fun��o para remover um n� da �rvore
No* remover(No* raiz, int valor) {
    // Se a �rvore est� vazia
    if (raiz == NULL) {
        return raiz;
    }

    // Busca recursivamente o n� a ser removido
    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        // N� encontrado para remo��o
        // N� com apenas um filho ou nenhum filho
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // N� com dois filhos: encontrar o sucessor m�nimo na sub�rvore direita
        No* temp = encontrarMinimo(raiz->direita);

        // Copia o sucessor encontrado para este n�
        raiz->valor = temp->valor;
        strcpy(raiz->nome, temp->nome);

        // Remove o sucessor
        raiz->direita = remover(raiz->direita, temp->valor);
    }

    return raiz;
}

// Fun��o para exibir a �rvore em ordem
void exibir(No* raiz) {
    if (raiz != NULL) {
        exibir(raiz->esquerda);
        printf("Valor: %d, Nome: %s\n", raiz->valor, raiz->nome);
        exibir(raiz->direita);
    }
}

// Fun��o principal
int main(void) {
    setlocale(LC_ALL, "Portuguese");
    No* raiz = NULL;
    int opcao, valor;
    char nome[100];

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Inserir um n�\n");
        printf("2. Buscar um nome na �rvore\n");
        printf("3. Remover um valor da �rvore\n");
        printf("4. Exibir os elementos da �rvore\n");
        printf("5. Sair do programa\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Inserir um n� na �rvore
                printf("Digite o valor inteiro para inserir: ");
                scanf("%d", &valor);
                printf("Digite o nome para inserir: ");
                scanf("%s", nome);
                raiz = inserir(raiz, valor, nome);
                printf("No inserido com sucesso!\n");
                break;
            case 2:
                // Buscar um nome na �rvore pelo valor inteiro
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
                // Remover um valor da �rvore
                printf("Digite o valor inteiro para remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                printf("Valor %d removido da arvore.\n", valor);
                break;
            case 4:
                // Exibir todos os elementos da �rvore
                printf("Elementos da arvore:\n");
                exibir(raiz);
                break;
            case 5:
                // Sair do programa
                printf("Saindo do programa...\n");
                break;
            default:
                // Op��o inv�lida
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



