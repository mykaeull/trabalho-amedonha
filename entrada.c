// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#include <stdio.h>
#include <string.h>
#include "funcoes.h"

// verifica se a quantidade de jogadores está entre 2 e 10; Caso não: um loop é ativado e só
// para quando a quantidade estiver correta / Caso sim: retorna a quantidade agora correta 
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

// cria dinamicamente os jogadores que possuem uma estrutura do tipo Player;
// após serem criados, um loop que vai de 0 até a quantidade de players - 1
// é ativado para tirar o lixo contido na criação do ponto final na struct Player
// e colocar ponto_final = 0 para futuros cálculos; ao final, retorna um array de players
Player* criar_players(int n) { // Myka
    Player *player = (Player*)malloc(n*sizeof(Player));
    for (int i = 0; i < n; i++) {
      player[i].ponto_final = 0; 
    }
    return player;
}

// verifica se o nome dos jogadores contém apenas 12 caracteres; a função "memset" é chamada
// para fazer a limpeza de lixo na string "player.nome"; em seguida, é verificado se a posição
// 12 da string "player.nome" possui um caractere e enquanto possuir, é solicitado que o jogador
// entre com um nome com até 12 caracteres 
void verificar_nome(Player *player, int n) { // Myka
    for (int i = 0; i < n; i++) {
        memset(player[i].nome, 0, sizeof(player[i].nome));
        printf("nome jogador %d: ", i+1);
        fgets(player[i].nome, 256, stdin);
        player[i].nome[strlen(player[i].nome) - 1] = '\0'; 
        while (player[i].nome[12]) {
            memset(player[i].nome, 0, sizeof(player[i].nome));
            printf("entre um nome com ate 12 caracteres\n");
            printf("nome jogador %d: ", i+1);
            fgets(player[i].nome, 256, stdin);
            player[i].nome[strlen(player[i].nome) - 1] = '\0';
        }
    }
}