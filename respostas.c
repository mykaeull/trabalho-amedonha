// Bruna Raynara Maia Batista - 499257
// Carlos Alberto Sampaio Sales Junior - 485181
// Domingos Mykaeull Gomes Peres - 500594

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "funcoes.h"

int verificar_respostas(char *resposta, char letra,char *categoria_selecionada){ //BRUNA

    if(strcmp(categoria_selecionada,"nomes de pessoas") == 0){
        primeiro_nome(resposta);
        tratar_respostas(resposta);
    }else{
        tratar_respostas(resposta);
    }

    if(strlen(resposta) <= 30 && resposta[0] == letra){
        return 0;
    }else {
        return 1;
    }
}

void respostas(Player *player, int *vet2, char letra, char *categoria_selecionada, int n, char **vet_respostas) { // BRUNA
    int resultado;
    int mostrar_mensagem = 1;
    struct timeval  inicio, fim;
    double tempo_total;
    
    for (int k = 0; k < n; k++) {
        gettimeofday(&inicio, NULL);
        printf("%s, voce deve entrar um '%s' com a letra '%c' em %d segundos\n", player[vet2[k]].nome, categoria_selecionada, letra, ((8 + (2*n)) - (2*k)));
        fgets(player[vet2[k]].resposta, 256, stdin);
        player[vet2[k]].resposta[strlen(player[vet2[k]].resposta) - 1] = '\0';
        resultado = verificar_respostas(player[vet2[k]].resposta, letra, categoria_selecionada);
        while (resultado) {
            printf("Resposta Invalida, digite novamente:\n");
            fgets(player[vet2[k]].resposta, 256, stdin);
            player[vet2[k]].resposta[strlen(player[vet2[k]].resposta) - 1] = '\0';
            resultado = verificar_respostas(player[vet2[k]].resposta, letra, categoria_selecionada);
        }
        gettimeofday(&fim, NULL);
        tempo_total = (double) (fim.tv_usec - inicio.tv_usec) / 1000000 + (double) (fim.tv_sec - inicio.tv_sec);
        player[vet2[k]].tempo_total += tempo_total;
        if (tempo_total <= (double)((8 + (2*n) - (2*k)))) {
            vet_respostas[vet2[k]] = player[vet2[k]].resposta;
        } else {
            vet_respostas[vet2[k]] = "";
        }
        system("clear");
        /*gettimeofday(&inicio, NULL);
        if (mostrar_mensagem) {
            printf("%s, voce deve entrar um '%s' com a letra '%c' em %d segundos\n", player[vet2[k]].nome, categoria_selecionada, letra, ((8 + (2*n)) - (2*k)));
        }
        mostrar_mensagem = 1;
        fgets(player[vet2[k]].resposta, 256, stdin);
        player[vet2[k]].resposta[strlen(player[vet2[k]].resposta) - 1] = '\0';
        resultado = verificar_respostas(player[vet2[k]].resposta, letra, categoria_selecionada);

        if (resultado) {
            gettimeofday(&fim, NULL);
            tempo_total = (double) (fim.tv_usec - inicio.tv_usec) / 1000000 + (double) (fim.tv_sec - inicio.tv_sec);
            player[vet2[k]].tempo_total += tempo_total;
            if (tempo_total <= (double)((8 + (2*n) - (2*k)))) {
              vet_respostas[vet2[k]] = player[vet2[k]].resposta;
              k++;
            } else {
              vet_respostas[vet2[k]] = "";
              k++;
            }
            system("clear");
        } else {
            mostrar_mensagem = 0;
            printf("Resposta Invalida, digite novamente:\n");*/
    }
}


void computar_resposta(Player *player, int* ordemJogador, char **vet_respostas, int nJogadores, int n_rodadas) { // BRUNA
    int cont = 0;
    double div;
    int teto;

    for (int i = 0; i < nJogadores; i++) {
        for (int j = 0; j < nJogadores; j++) {
            if (strcmp(vet_respostas[i], vet_respostas[j]) == 0) {
                cont += 1;
            }
        }
        div = (((double)strlen(vet_respostas[i]))/((double)cont));
        teto = ((int)div);
        teto += ((double)teto!=div);

        player[i].ponto_parcial[n_rodadas] = teto;
        player[i].ponto_final += player[i].ponto_parcial[n_rodadas];
        cont = 0;
    }
}

void tratar_respostas(char *resposta){ // BRUNA
    int i = 0;

    for(i = 0; i < strlen(resposta); i++){
        resposta[i] = tolower(resposta[i]);
    }
}

void primeiro_nome(char *resposta){ // BRUNA
  char* parte = strtok(resposta," ");
}