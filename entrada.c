// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int verificar_qtd_players(int n) { // Myka
    char converter[256];
    while (n < 2 || n > 10) {
        printf("------------------------------------------------------\n");
        printf("Erro: Quantidade invalida\n");
        printf("Entre com um valor entre 2 e 10\n");
        printf("------------------------------------------------------\n");
        printf("entre a quantidade de jogadores: ");
        fgets(converter, 256, stdin);
        n = atoi(converter);
    }
    return n;
}

Player* criar_players(int n) { // Myka
    Player *player = (Player*)malloc(n*sizeof(Player));
    for (int i = 0; i < n; i++) {
      player[i].ponto_final = 0; 
    }
    return player;
}

void verificar_nome(Player *player, int n) { // Myka
    for (int i = 0; i < n; i++) {
        memset(player[i].nome, 0, sizeof(player[i].nome));
        printf("nome jogador %d: ", i+1);
        fgets(player[i].nome, 256, stdin);
        player[i].nome[strlen(player[i].nome) - 1] = '\0'; 
        while (player[i].nome[12]) {
            memset(player[i].nome, 0, sizeof(player[i].nome));
            printf("nome jogador %d: ", i+1);
            fgets(player[i].nome, 256, stdin);
            player[i].nome[strlen(player[i].nome) - 1] = '\0';
        }
    }
}
