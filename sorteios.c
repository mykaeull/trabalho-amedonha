// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int sortear_numero(int range) { // Myka
    int sorteado = rand()%range;
    return sorteado;
}

int verificar_sorteado(int *vetor_de_sorteados, int indice) { // Myka
    if(vetor_de_sorteados[indice] == indice) {
        return 1;
    } else {
        vetor_de_sorteados[indice] = indice;
        return 0;
    }
}

int gerar_indice(int *vetor_de_sorteados, int n) { // Myka
    int indice = sortear_numero(n);

    while(verificar_sorteado(vetor_de_sorteados, indice)) {
        indice = sortear_numero(n);
    }

    return indice;
}

void gerar_ordem_aleatoria(int *vet1, int *vet2, int n) { // Myka
    int indice = sortear_numero(n);

    for (int i = 0; i < n; i++) {
        while (verificar_sorteado(vet1, indice)) {
            indice = sortear_numero(n);
        }
        vet2[i] = vet1[indice];
    }
}
