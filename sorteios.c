// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

// gera um número aleatório entre 0 e um número armazenado na variável range e o retorna
int sortear_numero(int range) { // Myka
    int sorteado = rand()%range;
    return sorteado;
}

// verifica se o índice entrado na função já está contido em vetor_de_sorteados; inicialmente
// vetor_de_sorteados possui -1 em todas suas posições; a cada índice diferente de -1 entrado,
// este é alocado no vetor_de_sorteados; caso um índice já esteja contido no vetor_de_sorteados
// a função retorna 1 / caso não, a função retorna 0 
int verificar_sorteado(int *vetor_de_sorteados, int indice) { // Myka
    if(vetor_de_sorteados[indice] == indice) {
        return 1;
    } else {
        vetor_de_sorteados[indice] = indice;
        return 0;
    }
}

// gera um índice aleatório sem repetir a cada vez que é chamadae o retorna; utiliza as funções
// sortear_numero e verificar_sorteado para tal
int gerar_indice(int *vetor_de_sorteados, int n) { // Myka
    int indice = sortear_numero(n);

    while(verificar_sorteado(vetor_de_sorteados, indice)) {
        indice = sortear_numero(n);
    }

    return indice;
}

// processo parecido com a função "gerar_indice"; utiliza as funções sortear_numero (para gerar
// um número aleatório de range n) e verificar_sorteado (retorna um índice não repetido);
// recebe como parâmetro um vetor_ordem onde cada posição em ordem crescente vai conter os 
// índices que foram gerados de forma aleatória; exemplo: vetor_ordem[0] = 3, vetor[1] = 0, ...
void gerar_ordem_aleatoria(int *vetor_de_sorteados, int *vetor_ordem, int n) { // Myka
    int indice = sortear_numero(n);

    for (int i = 0; i < n; i++) {
        while (verificar_sorteado(vetor_de_sorteados, indice)) {
            indice = sortear_numero(n);
        }
        vetor_ordem[i] = vetor_de_sorteados[indice];
    }
}
