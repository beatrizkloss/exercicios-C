#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


void preenche_vetor(int *vetor, int n) {
    for(int i = 0; i < n; i++) {
        printf("Digite o valor para a posição %d do vetor: ", i);
        scanf("%d", &vetor[i]);
    }
}

int busca_linear(int *vetor, int n, int valor) {
    for(int i = 0; i < n; i++) {
        if(vetor[i] == valor) {
            return i;
        }
    }
    return -1;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    int n;
    printf("Digite a dimensão do vetor: ");
    scanf("%d", &n);

    int vetor[n];
    preenche_vetor(vetor, n);

    int valor, posicao;
    char continuar = 's';
    while(continuar == 's' || continuar == 'S') {
        printf("Digite o valor a ser buscado: ");
        scanf("%d", &valor);

        posicao = busca_linear(vetor, n, valor);
        if(posicao != -1) {
            printf("O valor %d foi encontrado na posição %d do vetor.\n", valor, posicao);
        } else {
            printf("O valor %d não foi encontrado no vetor.\n", valor);
        }

        printf("Deseja realizar outra busca? (s/n): ");
        scanf(" %c", &continuar);
    }

    return 0;
}

