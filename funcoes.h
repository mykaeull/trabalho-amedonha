// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#ifndef funcoes_h
#define funcoes_h

#include <stdio.h>
#include <stdlib.h>

typedef struct player Player;

struct player {
  char nome[256]; 
  int ponto_final; 
  int ponto_parcial[5];
  char resposta[256];
  double tempo_total;
};

// prototipos

  //
void play_game(); 

  //
void preencher_alfabeto(char *);
void preencher_categoria(char **);
  // 
int sortear_numero(int);
int verificar_sorteado(int *, int);
int gerar_indice(int *, int);
void gerar_ordem_aleatoria(int *, int *, int);
  // 
Player* criar_players(int);
void verificar_nome(Player *player, int);
int verificar_qtd_players(int);
 //
void mostrar_ordem(Player *player, int *, int);
void mostrar_pontos(Player* player,int *, char **, int, int );
void gerar_vencedor(Player* player, int);
  // 
void tratar_respostas(char *);
int verificar_respostas(char *, char ,char *);
void respostas(Player *player, int *, char, char *, int, char **);
void computar_resposta(Player *player, int *, char **, int, int);
void primeiro_nome(char *);

#endif