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

/* A função abaixo chama a função "primeiro_nome", caso a categoria sorteada seja
   "nomes de pessoas" para selecionar apenas o primeiro nome. Além de chamar a função 
   "tratar_respostas", a função "verificar_respostas" checa se a resposta que o usuário 
   digitou tem o tamanho desejado de até 30 caracteres e se a resposta começa com a primeira 
   letra sorteada pelo programa. */
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

/* A função "respostas" utiliza de um "for" para passar pela quantidade de jogadores 
   solicitando a resposta deles, assim ela armazena a resposta digitada pelo jogador com o 
   auxílio do "fgets". Além de contar o tempo que o jogador tem para realizar sua jogada. */
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
    }
}

/* A função "computar_resposta" verifica a quantidade de respostas iguais por rodada e 
   armazena o valor em um contador para auxiliar no cálculo da quantidade de pontos que cada 
   jogador obteve em uma rodada (em caso de pontuação com valor float de ",5" se armazena o 
   teto da pontuação). Além de utilizar uma variavel para somar o ponto final de cada jogador 
   ao final das 5 rodadas. */
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

/* A função abaixo traz uma cópia da cadeia de caracter convertida em 
   minúsculo, pois será necessário na comparação de respostas iguais visto que
   a linguagem C é case sensitive. */
void tratar_respostas(char *resposta){ // BRUNA
    int i = 0;

    for(i = 0; i < strlen(resposta); i++){
        resposta[i] = tolower(resposta[i]);
    }
}

/* Na função abaixo é selecionado apenas o primeiro nome caso o jogador 
   digite um nome composto na categoria "nomes de pessoas". */
void primeiro_nome(char *resposta){ // BRUNA
  char* parte = strtok(resposta," ");
}