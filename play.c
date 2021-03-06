// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

/*a função "play_game" é a responsável por gerir toda a lógica do jogo, primeiro declaramos as variaveis necessárias para receber os dados do jogo como letras do alfabeto, quantidade de jogadores, vetor com o nome das categorias, a ordem que sera jogada em cada rodada, o vetor que armazena os jogadores. Primeiro e pedido ao jogador que digite quantas pessoas estão jogando, com base na resposta e criado um vetor com o tamanho digitado e logo na sequencia e pedido para que se digite o nome de cada um. Por fim entrasse num loop que representa cada rodada, nesse loop são gerados a letra, a ordem em que os jogadores irão jogar e pegar as respostas, apos isso e mostrado o resultado a cada rodada e se caso for a rodada final, mostra-se o vencedor*/
void play_game() {
    char alfabeto[23];
    int letra_sorteada[23];
    char letra;
    char *categoria[5];
    int categoria_sorteada[5];
    char *categoria_selecionada;
    char converter[256];
    int nJogadores;
    int *vetor_de_sorteados;
    int *vetor_ordem;
    char *categorias_jogadas[5];
    char *vet_respostas[10];
    Player *player;

    memset(letra_sorteada, -1, sizeof(letra_sorteada));
    memset(categoria_sorteada, -1, sizeof(categoria_sorteada));

    srand(time(NULL));

    printf("entre a quantidade de jogadores: ");
    fgets(converter, 256, stdin);
    nJogadores = atoi(converter);
    nJogadores = verificar_qtd_players(nJogadores);
    
    vetor_de_sorteados = malloc(nJogadores * sizeof(int));
    vetor_ordem = malloc(nJogadores * sizeof(int));

    player = criar_players(nJogadores);

    verificar_nome(player, nJogadores);

    preencher_alfabeto(alfabeto);
    preencher_categoria(categoria);

    system("clear");

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

        memset(vetor_de_sorteados, -1, nJogadores * sizeof(int));
        gerar_ordem_aleatoria(vetor_de_sorteados, vetor_ordem, nJogadores); 

        printf("------------------------------------------------------\n");
        printf("A ordem desta rodada sera: \n");
        mostrar_ordem(player, vetor_ordem, nJogadores);
        printf("------------------------------------------------------\n");

        printf("Tecle [ENTER] para iniciar a rodada\n");
        getchar();
        system("clear");

        respostas(player, vetor_ordem, letra, categoria_selecionada, nJogadores, vet_respostas);
        printf("\n");
        computar_resposta(player, vetor_ordem, vet_respostas, nJogadores, i);
        
        mostrar_pontos(player, vetor_ordem,categorias_jogadas, nJogadores, i);

        if(i == 4){
            gerar_vencedor(player,i);
        }
    }
}