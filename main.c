#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

typedef struct player Player;

struct player {
  char nome[256]; 
  int pontoFinal; 
  int ponto_parcial[5];
  char resposta[256];
  double tempo_total;
};

void preencher_alfabeto(char *alfabeto) {
  alfabeto[0] = 'a';
  alfabeto[1] = 'b';
  alfabeto[2] = 'c';
  alfabeto[3] = 'd';
  alfabeto[4] = 'e';
  alfabeto[5] = 'f';
  alfabeto[6] = 'g';
  alfabeto[7] = 'h';
  alfabeto[8] = 'i';
  alfabeto[9] = 'j';
  alfabeto[10] = 'l';
  alfabeto[11] = 'm';
  alfabeto[12] = 'n';
  alfabeto[13] = 'o';
  alfabeto[14] = 'p';
  alfabeto[15] = 'q';
  alfabeto[16] = 'r';
  alfabeto[17] = 's';
  alfabeto[18] = 't';
  alfabeto[19] = 'u';
  alfabeto[20] = 'v';
  alfabeto[21] = 'x';
  alfabeto[22] = 'z';
}

void preencher_categoria(char **categoria) {
    categoria[0] = "profissoes";
    categoria[1] = "nomes de pessoas";
    categoria[2] = "nomes de cidade";
    categoria[3] = "nomes de animais";
    categoria[4] = "nomes de comida";
}

int verificar_qtd_players(int n) {
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

int sortear_numero(int range) {
    int sorteado = rand()%range;
    return sorteado;
}

int verificar_sorteado(int *vetor_de_sorteados, int indice) {
    if(vetor_de_sorteados[indice] == indice) {
        return 1;
    } else {
        vetor_de_sorteados[indice] = indice;
        return 0;
    }
}

int gerar_indice(int *vetor_de_sorteados, int n) {
    int indice = sortear_numero(n);

    while(verificar_sorteado(vetor_de_sorteados, indice)) {
        indice = sortear_numero(n);
    }

    return indice;
}

void gerar_ordem_aleatoria(int *vet1, int *vet2, int n) {
    int indice = sortear_numero(n);

    for (int i = 0; i < n; i++) {
        while (verificar_sorteado(vet1, indice)) {
            indice = sortear_numero(n);
        }
        vet2[i] = vet1[indice];
    }
}

Player* criar_players(int n) {
    Player *player = (Player*)malloc(n*sizeof(Player));
    return player;
}

void verificar_nome(Player *player, int n) {
    for (int i = 0; i < n; i++) {
        memset(player[i].nome, 0, sizeof(player[i].nome));
        printf("nome jogador %d: ", i+1);
        fgets(player[i].nome, 256, stdin);
        player[i].nome[strlen(player[i].nome) - 1] = '\0'; // tira o \n do fgets
        while (player[i].nome[12]) {
            memset(player[i].nome, 0, sizeof(player[i].nome));
            printf("nome jogador %d: ", i+1);
            fgets(player[i].nome, 256, stdin);
            player[i].nome[strlen(player[i].nome) - 1] = '\0';
        }
    }
}

void mostrar_ordem(Player *player, int *vet2, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i+1, player[vet2[i]].nome);
    }
}

void primeiro_nome(char *resposta){
  char* parte = strtok(resposta," ");
}

void tratar_respostas(char *resposta){
    int i = 0;

    for(i = 0; i < strlen(resposta); i++){
        resposta[i] = tolower(resposta[i]);
    }
    // printf("%s", resposta);
}

int verificar_respostas(char *resposta, char letra,char *categoria_selecionada){

    if(strcmp(categoria_selecionada,"nomes de pessoas") == 0){
        primeiro_nome(resposta);
        tratar_respostas(resposta);
    }else{
        tratar_respostas(resposta);
    }

    if(strlen(resposta) <= 30 && resposta[0] == letra){
        return 1;
    }else {
        return 0;
    }
}

void respostas(Player *player, int *vet2, char letra, char *categoria_selecionada, int n, char **vet_respostas) { // tem q colocar um cont pro ponto parcial
    char resultado;
    int mostrar_mensagem = 1;
    struct timeval  inicio, fim;
    double tempo_total;

    for (int k = 0; k < n;) {
        gettimeofday(&inicio, NULL);
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
            system("cls");
        } else {
            mostrar_mensagem = 0;
            printf("Resposta Invalida, digite novamente:\n");
        }
    }
}

void computar_resposta(Player *player, char **vet_respostas, int n, int k) {
    int cont = 0;
    double div;
    int teto;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(vet_respostas[i], vet_respostas[j]) == 0) {
                cont += 1;
            }
        }
        div = (((double)strlen(vet_respostas[i]))/((double)cont));
        teto = ((int)div);
        teto += ((double)teto!=div);
        player[i].ponto_parcial[k] = teto;
        cont = 0;
    }
}

void mostrar_pontos(Player* player,int* ordemJogador, char** categorias_jogadas,int nJogadores,int rodada ){
    printf("------------------------------------------------------\n");
    printf("Jogadas Realizadas:\n");
    printf("------------------------------------------------------\n");
    for (int j = 0; j < nJogadores; j++){
        printf("%s: ", player[ordemJogador[j]].nome);
        printf("%s ", player[ordemJogador[j]].resposta);
        printf("\n");
    }
    printf("------------------------------------------------------\n");
    printf("\nConcluida a rodada, esta eh a tabela de escores:\n\n");

    // printar espaço
    printf("\t\t");
    for (int k = 0; k <= rodada; k++){
        printf("%s  ", categorias_jogadas[k]);
    }
    //  caso forem 3 rodadas
    if(rodada == 4){
      printf("Total Geral");
    }else{
      printf("Total Parcial");
    }
    printf("\n");
    for (int j = 0; j < nJogadores; j++){
      int ponto_total = 0;
      printf("%s: ", player[ordemJogador[j]].nome);
      for (int k = 0; k <= rodada; k++){
          ponto_total += player[ordemJogador[j]].ponto_parcial[k]; 
          printf("\t\t\t\t");
          printf("%d ", player[ordemJogador[j]].ponto_parcial[k]);
      }
      printf("\t\t\t");
      printf("%d", ponto_total);
      if(rodada == 4){
        player[ordemJogador[j]].pontoFinal = ponto_total;
      }
      printf("\n");
      printf("\n");
    }
}

void gerar_vencedor(Player* player,int nJogadores){
  int maior_ponto = 0;
  for(int i = 0; i < nJogadores; i++){
    if(maior_ponto < player[i].pontoFinal){
      maior_ponto = player[i].pontoFinal;
    }
  }

  for(int i = 0; i < nJogadores; i++){
    if(maior_ponto == player[i].pontoFinal){
      printf("O ganhador eh: %s", player[i].nome);
    }
  }
}

void limpar_tela() {
    system("cls");
}

int main () {
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
    //scanf("%s", &converter);
    n = atoi(converter);
    n = verificar_qtd_players(n);
    
	vet1 = malloc(n * sizeof(int));
	vet2 = malloc(n * sizeof(int));

    player = criar_players(n);

    verificar_nome(player, n);

    /* TESTE DE NOMES
    printf("%s\n", player[0].nome);
    printf("%s\n", player[1].nome);
    printf("%s\n", player[2].nome);
    */

    preencher_alfabeto(alfabeto);
    preencher_categoria(categoria);

    limpar_tela();
	
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
        gerar_ordem_aleatoria(vet1, vet2, n); // ordem aleatoria ta no vet2

        printf("------------------------------------------------------\n");
        printf("A ordem desta rodada sera: \n");
        mostrar_ordem(player, vet2, n);
        printf("------------------------------------------------------\n");

        printf("Aperte enter\n");
        getchar();
        limpar_tela();

        respostas(player, vet2, letra, categoria_selecionada, n, vet_respostas);
        printf("\n");
        computar_resposta(player, vet_respostas, n, i);
        
        mostrar_pontos(player, vet2,categorias_jogadas, n, i);

        if(i == 4){
          gerar_vencedor(player,i);
        }
        //printf("\n%d\n", player[0].ponto_parcial[i]);
        //getchar();

        // printf("\n%s\n", vet_respostas[0]);

    }

    printf("\ntudo certo ate aqui!\n");    

    return 0;
}