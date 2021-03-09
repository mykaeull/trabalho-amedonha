// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

void play_game() {

    char alfabeto[23];
    int letra_sorteada[23];
    char letra;
    char *categoria[5];
    int categoria_sorteada[5];
    char *categoria_selecionada;
    char converter[256];
    int n;
    int *vet1;
    int *vet2;
    char *categorias_jogadas[5];
    char *vet_respostas[10];
    Player *player;

    memset(letra_sorteada, -1, sizeof(letra_sorteada));
    memset(categoria_sorteada, -1, sizeof(categoria_sorteada));

    srand(time(NULL));

    printf("entre a quantidade de jogadores: ");
    fgets(converter, 256, stdin);
    n = atoi(converter);
    n = verificar_qtd_players(n);
    
    vet1 = malloc(n * sizeof(int));
    vet2 = malloc(n * sizeof(int));

    player = criar_players(n);

    verificar_nome(player, n);

    preencher_alfabeto(alfabeto);
    preencher_categoria(categoria);

    system("cls");

    for (int i = 0; i < 5; i++) {

        letra = alfabeto[gerar_indice(letra_sorteada, 23)];

        printf("------------------------------------------------------\n");
        printf("letra sorteada: %c\n", letra);
        printf("------------------------------------------------------\n");

        categoria_selecionada = categoria[gerar_indice(categoria_sorteada, 5)];
        categorias_jogadas[i] = categoria_selecionada;

        printf("------------------------------------------------------\n");
        printf("categoria sorteada: %s\n", categoria_selecionada);
        printf("------------------------------------------------------\n");

        memset(vet1, -1, n * sizeof(int));
        gerar_ordem_aleatoria(vet1, vet2, n); 

        printf("------------------------------------------------------\n");
        printf("A ordem desta rodada sera: \n");
        mostrar_ordem(player, vet2, n);
        printf("------------------------------------------------------\n");

        printf("Aperte enter\n");
        getchar();
        system("cls");

        respostas(player, vet2, letra, categoria_selecionada, n, vet_respostas);
        printf("\n");
        computar_resposta(player, vet2, vet_respostas, n, i);
        
        mostrar_pontos(player, vet2,categorias_jogadas, n, i);

        if(i == 4){
            gerar_vencedor(player,i);
        }
    }
}