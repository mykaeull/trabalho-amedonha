#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

typedef struct player Player;
// typedef struct pontoParcial PontoParcial;

/*struct pontoParcial {
    char modalidade[20];
    int ponto;
    char resposta[30];
};*/

struct player {
  char name[256]; 
  int pontoFinal; 
  int ponto_parcial[5];
  char resposta[256];
};

void fill_alphabet(char *alphabet) {
  alphabet[0] = 'a';
  alphabet[1] = 'b';
  alphabet[2] = 'c';
  alphabet[3] = 'd';
  alphabet[4] = 'e';
  alphabet[5] = 'f';
  alphabet[6] = 'g';
  alphabet[7] = 'h';
  alphabet[8] = 'i';
  alphabet[9] = 'j';
  alphabet[10] = 'l';
  alphabet[11] = 'm';
  alphabet[12] = 'n';
  alphabet[13] = 'o';
  alphabet[14] = 'p';
  alphabet[15] = 'q';
  alphabet[16] = 'r';
  alphabet[17] = 's';
  alphabet[18] = 't';
  alphabet[19] = 'u';
  alphabet[20] = 'v';
  alphabet[21] = 'x';
  alphabet[22] = 'z';
}

void fill_category(char **category) {
    category[0] = "profissoes";
    category[1] = "nomes de pessoas";
    category[2] = "nomes de cidade";
    category[3] = "nomes de animais";
    category[4] = "nomes de comida";
}

int check_qtd_players(int n) {
    char convert[256];
    while (n < 2 || n > 10) {
        printf("------------------------------------------------------\n");
        printf("Erro: Quantidade invalida\n");
        printf("Entre com um valor entre 2 e 10\n");
        printf("------------------------------------------------------\n");
        printf("entre a quantidade de jogadores: ");
        fgets(convert, 256, stdin);
        //scanf("%s", convert);
        n = atoi(convert);
    }
    return n;
}

int draw_number(int range) {
    int draw = rand()%range;
    return draw;
}

int check_draw(int *array_draw, int index) {
    if(array_draw[index] == index) {
        return 1;
    } else {
        array_draw[index] = index;
        return 0;
    }
}

int get_index(int *array_draw, int n) {
    int index = draw_number(n);

    while(check_draw(array_draw, index)) {
        index = draw_number(n);
    }

    return index;
}

void random_order(int *vet1, int *vet2, int n) {
    int index = draw_number(n);

    for (int i = 0; i < n; i++) {
        while (check_draw(vet1, index)) {
            index = draw_number(n);
        }
        vet2[i] = vet1[index];
    }
}

Player* players(int n) {
    Player *player = (Player*)malloc(n*sizeof(Player));
    return player;
}

void players_name(Player *player, int n) {
    for (int i = 0; i < n; i++) {
        memset(player[i].name, 0, sizeof(player[i].name));
        printf("nome jogador %d: ", i+1);
        fgets(player[i].name, 256, stdin);
        player[i].name[strlen(player[i].name) - 1] = '\0'; // tira o \n do fgets
        while (player[i].name[13]) {
            memset(player[i].name, 0, sizeof(player[i].name));
            printf("nome jogador %d: ", i+1);
            fgets(player[i].name, 256, stdin);
            player[i].name[strlen(player[i].name) - 1] = '\0';
        }
    }
}

void show_order(Player *player, int *vet2, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i+1, player[vet2[i]].name);
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

int verificar_respostas(char *resposta, char letter,char *category_selected){

    if(strcmp(category_selected,"nomes de pessoas") == 0){
        primeiro_nome(resposta);
        tratar_respostas(resposta);
    }else{
        tratar_respostas(resposta);
    }

    if(strlen(resposta) <= 30 && resposta[0] == letter){
        return 1;
    }else {
        return 0;
    }
}

void respostas(Player *player, int *vet2, char letter, char *category_selected, int n, char **vet_respostas) { // tem q colocar um cont pro ponto parcial
    char resultado;
    int mostrar_mensagem = 1;
    struct timeval  inicio, fim;
    double tempo_total;

    for (int k = 0; k < n;) {
        gettimeofday(&inicio, NULL);
        if (mostrar_mensagem) {
            printf("%s, voce deve entrar um '%s' com a letra '%c' em tantos segundos\n", player[vet2[k]].name, category_selected, letter);
        }
        mostrar_mensagem = 1;
        fgets(player[vet2[k]].resposta, 256, stdin);
        player[vet2[k]].resposta[strlen(player[vet2[k]].resposta) - 1] = '\0';
        resultado = verificar_respostas(player[vet2[k]].resposta, letter, category_selected);

        if (resultado) {
            gettimeofday(&fim, NULL);
            tempo_total = (double) (fim.tv_usec - inicio.tv_usec) / 1000000 + (double) (fim.tv_sec - inicio.tv_sec);
            if (tempo_total <= (double)((8 + (2*n) - (2*k)))) {
              printf("\n%f\n", tempo_total);
              vet_respostas[vet2[k]] = player[vet2[k]].resposta;
              k++;
            } else {
              printf("\n%f\n", tempo_total);
              vet_respostas[vet2[k]] = "";
              k++;
            }
            //system("cls");
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
                //printf("deu certo\n");
                cont += 1;
            }
            //printf("aqui\n");
        }
        div = (((double)strlen(vet_respostas[i]))/((double)cont));
        teto = ((int)div);
        teto += ((double)teto!=div);
        //printf("\nAQUIII\n");
        player[i].ponto_parcial[k] = teto;
        cont = 0;
    }
}

void show_points(Player* player,int* ordemJogador, char** categories_played,int nJogadores,int rodada ){
    printf("------------------------------------------------------\n");
    printf("Jogadas Realizadas:\n");
    printf("------------------------------------------------------\n");
    for (int j = 0; j < nJogadores; j++){
        printf("%s: ", player[ordemJogador[j]].name);
        printf("%s ", player[ordemJogador[j]].resposta);
        printf("\n");
    }
    printf("------------------------------------------------------\n");
    printf("\nConcluida a rodada, esta eh a tabela de escores:\n\n");

    // printar espaço
    printf("\t\t");
    for (int k = 0; k <= rodada; k++){
        printf("%s  ", categories_played[k]);
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
      printf("%s: ", player[ordemJogador[j]].name);
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

void gerarVencedor(Player* player,int nJogadores){
  int maior_ponto = 0;
  for(int i = 0; i < nJogadores; i++){
    if(maior_ponto < player[i].pontoFinal){
      maior_ponto = player[i].pontoFinal;
    }
  }

  for(int i = 0; i < nJogadores; i++){
    if(maior_ponto == player[i].pontoFinal){
      printf("O ganhador eh: %s", player[i].name);
    }
  }
}

void clear_window() {
    system("cls");
}

int main () {
    char alphabet[23];
    int letter_draw[23];
    char letter;
    char *category[5];
    int category_draw[5];
    char *category_selected;
    char convert[256];
    int n;
    int *vet1;
    int *vet2;
    int countMatchs = 0;
    char *categories_played[5];
    char *vet_respostas[10]; // *p
    Player *player;

    memset(letter_draw, -1, sizeof(letter_draw));
    memset(category_draw, -1, sizeof(category_draw));

    srand(time(NULL));

    printf("entre a quantidade de jogadores: ");
    fgets(convert, 256, stdin);
    //scanf("%s", &convert);
    n = atoi(convert);
    n = check_qtd_players(n);
    
	vet1 = malloc(n * sizeof(int));
	vet2 = malloc(n * sizeof(int));

    player = players(n);

    players_name(player, n);

    /* TESTE DE NOMES
    printf("%s\n", player[0].nome);
    printf("%s\n", player[1].nome);
    printf("%s\n", player[2].nome);
    */

    fill_alphabet(alphabet);
    fill_category(category);

    clear_window();
	
    for (int i = 0; i < 5; i++) {

        letter = alphabet[get_index(letter_draw, 23)];

        printf("------------------------------------------------------\n");
        printf("letra sorteada: %c\n", letter);
        printf("------------------------------------------------------\n");

        category_selected = category[get_index(category_draw, 5)];
        categories_played[i] = category_selected;

        printf("------------------------------------------------------\n");
        printf("categoria sorteada: %s\n", category_selected);
        printf("------------------------------------------------------\n");

        memset(vet1, -1, n * sizeof(int));
        random_order(vet1, vet2, n); // ordem aleatoria ta no vet2

        printf("------------------------------------------------------\n");
        printf("A ordem desta rodada sera: \n");
        show_order(player, vet2, n);
        printf("------------------------------------------------------\n");

        printf("Aperte enter\n");
        getchar();
        clear_window();

        respostas(player, vet2, letter, category_selected, n, vet_respostas);
        printf("\n");
        computar_resposta(player, vet_respostas, n, i);
        
        show_points(player,vet2,categories_played,n,i);

        if(i == 4){
          gerarVencedor(player,i);
        }
        //printf("\n%d\n", player[0].ponto_parcial[i]);
        //getchar();

        // printf("\n%s\n", vet_respostas[0]);

    }

    printf("\ntudo certo ate aqui!\n");    

    return 0;
}