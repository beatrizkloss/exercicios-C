
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Defini��o da estrutura do n�
typedef struct No {
    int dado;
    struct No* proximo;
} No;

// Fun��es para manipula��o da lista
No* criarNo(int dado);
void inserirNoFim(No** cabeca, int dado);
void inserirNaPosicao(No** cabeca, int dado, int posicao);
void deletarPenultimo(No** cabeca);
void imprimirLista(No* cabeca);
int buscar(No* cabeca, int alvo);
void liberarLista(No* cabeca);

// Fun��o para criar um novo n�
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(1);
    }
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    return novoNo;
}

// Fun��o para inserir um n� no final da lista
void inserirNoFim(No** cabeca, int dado) {
    No* novoNo = criarNo(dado);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        No* temp = *cabeca;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
    }
}

// Fun��o para inserir um n� em uma posi��o espec�fica da lista
void inserirNaPosicao(No** cabeca, int dado, int posicao) {
    No* novoNo = criarNo(dado);
    if (posicao == 1) {
        novoNo->proximo = *cabeca;
        *cabeca = novoNo;
    } else {
        No* temp = *cabeca;
        for (int i = 1; i < posicao - 1 && temp != NULL; i++) {
            temp = temp->proximo;
        }
        if (temp != NULL) {
            novoNo->proximo = temp->proximo;
            temp->proximo = novoNo;
        } else {
            printf("Posi��o inv�lida.\n");
            free(novoNo);
        }
    }
}

// Fun��o para deletar o pen�ltimo n� da lista
void deletarPenultimo(No** cabeca) {
    if (*cabeca == NULL || (*cabeca)->proximo == NULL) {
        printf("A lista � muito curta para deletar o pen�ltimo elemento.\n");
        return;
    }

    No* temp = *cabeca;
    No* penultimo = NULL;

    while (temp->proximo->proximo != NULL) {
        penultimo = temp;
        temp = temp->proximo;
    }

    if (penultimo == NULL) { // Se a lista tem exatamente dois elementos
        penultimo = *cabeca;
        *cabeca = (*cabeca)->proximo;
        free(penultimo);
    } else {
        penultimo->proximo = temp->proximo;
        free(temp);
    }
}

// Fun��o para imprimir a lista
void imprimirLista(No* cabeca) {
    No* temp = cabeca;
    while (temp != NULL) {
        printf("%d -> ", temp->dado);
        temp = temp->proximo;
    }
    printf("NULL\n");
}

// Fun��o para buscar um valor na lista
int buscar(No* cabeca, int alvo) {
    No* temp = cabeca;
    int posicao = 1;
    while (temp != NULL) {
        if (temp->dado == alvo) {
            return posicao;
        }
        temp = temp->proximo;
        posicao++;
    }
    return -1;
}

// Fun��o para liberar a mem�ria da lista
void liberarLista(No* cabeca) {
    No* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    No* cabeca = NULL;
    int opcao, valorUsuario, valorBusca, resultadoBusca;

    // Inicializando a gerador de n�meros aleat�rios
    srand(time(NULL));

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar 5 valores aleat�rios\n");
        printf("2. Adicionar valor na segunda posi��o\n");
        printf("3. Deletar pen�ltimo elemento\n");
        printf("4. Buscar valor\n");
        printf("5. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
        	// Programa inicia aleatoriamente 5 valores inteiros
            case 1:
                printf("Adicionando 5 valores inteiros aleat�rios � lista:\n");
                for (int i = 0; i < 5; i++) {
                    int valorAleatorio = rand() % 100; // Gerando um n�mero aleat�rio entre 0 e 99
                    inserirNoFim(&cabeca, valorAleatorio);
                }
                imprimirLista(cabeca);
                system("pause");
                break;
                //usu�rio digita um valor para adicionar na segunda posi��o
            case 2:
                printf("Digite um valor para adicionar na segunda posi��o da lista: ");
                scanf("%d", &valorUsuario);
                inserirNaPosicao(&cabeca, valorUsuario, 2);
                imprimirLista(cabeca);
                system("pause");
                break;
                //usu�rio deleta pen�ltimo elemento (ignora null)
            case 3:
                printf("Deletando o pen�ltimo elemento da lista.\n");
                deletarPenultimo(&cabeca);
                imprimirLista(cabeca);
                system("pause");
                break;
                //usu�rio busca um valor na lista
            case 4:
                printf("Digite um valor para buscar na lista: ");
                scanf("%d", &valorBusca);
                resultadoBusca = buscar(cabeca, valorBusca);
                if (resultadoBusca != -1) {
                    printf("Valor encontrado na posi��o %d.\n", resultadoBusca);
                } else {
                    printf("Valor n�o encontrado na lista.\n");
                }
                system("pause");
                break;
            case 5:
                liberarLista(cabeca);
                printf("Saindo do programa.\n");
                system("pause");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
                system("pause");
        }
        system("cls"); // Limpa o terminal
    } while (opcao != 5);

    return 0;
}



