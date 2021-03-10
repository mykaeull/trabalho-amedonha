// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void mostrar_ordem(Player *player, int *vet2, int n) { // Carlos
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i+1, player[vet2[i]].nome);
    }
}

void mostrar_pontos(Player* player,int* ordemJogador, char** categorias_jogadas,int nJogadores,int rodada ){ // Carlos
    printf("------------------------------------------------------\n");
    printf("Jogadas Realizadas\n");
    for (int j = 0; j < nJogadores; j++){
        printf("%s: ", player[ordemJogador[j]].nome);
        printf("%s ", player[ordemJogador[j]].resposta);
        printf("\n");
    }
    printf("------------------------------------------------------\n");
    printf("\nConcluida a rodada, esta eh a tabela de escores\n");

    printf("=======================================================\n");
    for (int k = 0; k <= rodada; k++){
        printf("%s\n", categorias_jogadas[k]);
        for(int i = 0 ;i < nJogadores; i++){
          printf("%s: ", player[ordemJogador[i]].nome);
          printf("%d", player[ordemJogador[i]].ponto_parcial[k]);
          printf("\n");
        }
          printf("------------------------------------------------------\n");
          
    }
    if(rodada == 4){
      printf("Total Geral\n");
    }else{
      printf("Total Parcial\n");
    }
    for (int j = 0; j < nJogadores; j++){
        printf("%s: ", player[ordemJogador[j]].nome);
        printf("%d", player[ordemJogador[j]].ponto_final);
        printf("\n");
    }
    printf("=======================================================\n");
    printf("Tecle [ENTER] para iniciar a proxima rodada\n");
    getchar();
    system("clear");
}

void gerar_vencedor(Player* player,int nJogadores){ // Carlos
  int maior_ponto = 0;
  for(int i = 0; i < nJogadores; i++){
    if(maior_ponto < player[i].ponto_final){
      maior_ponto = player[i].ponto_final;
    }
  }

  int quant_nJogadore_ganhou = 0;
  for(int i = 0; i < nJogadores; i++){
    if(player[i].ponto_final == maior_ponto){
      quant_nJogadore_ganhou++;
    }
  }

  if(quant_nJogadore_ganhou == 1){
    for(int i = 0; i < nJogadores; i++){
      if(maior_ponto == player[i].ponto_final){
        printf("O ganhador eh: %s\n", player[i].nome);
      }
    }
  }else{
    double menorTempo = 0.0;
    for(int i = 0;i < nJogadores; i++){
      if(i == 0){
        menorTempo = player[i].tempo_total;
      }else{

        if(player[i].ponto_final == maior_ponto){
          if(menorTempo > player[i].tempo_total){
            menorTempo = player[i].tempo_total;
          }
        }

      } 
    }
    for(int i = 0;i < nJogadores; i++){
      if(player[i].tempo_total == menorTempo){
        printf("O ganhador por desempate foi: %s\n", player[i].nome);
      }
    }
  }
}