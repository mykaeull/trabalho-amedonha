#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct player Player;
typedef struct pontoParcial PontoParcial;

struct pontoParcial {
    char modalidade[20];
    int ponto;
    char resposta[30];
};

struct player {
  char name[13];
  int pontoFinal;
  PontoParcial pontoParcial[3];
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
        scanf("%s", convert);
        n = atoi(convert);
    }
    return n;
}

int check_letter(int *letter_draw, int index) {
    int checked = 0;
    if (index == letter_draw[index]) {
        return 1;
    } else {
        letter_draw[index] = index;
        return checked;
    }
}

char get_letter(char *alphabet, int *letter_draw) {
    int index;

    index = rand()%23;

    while(check_letter(letter_draw, index)) {
        index = rand()%23;
    }

    return alphabet[index];
}

int check_category(int *category_draw, int index) {
    int checked = 0;
    if (index == category_draw[index]) {
        return 1;
    } else {
        category_draw[index] = index;
        return checked;
    }
}

char* get_category(char **category, int *category_draw) {
    int index;

    index = rand()%5;

    while(check_category(category_draw, index)) {
        index = rand()%5;
    }

    return category[index];
}

Player* players(int n) {
    Player *player = (Player*)malloc(n*sizeof(Player));
    return player;
}

void players_name(Player *player, int n) {
    for (int i = 0; i < n; i++) {
        memset(player[i].name, 0, sizeof(player[i].name));
        printf("nome jogador %d: ", i+1);
        scanf("%s", player[i].name);
        while (player[i].name[12]) {
            memset(player[i].name, 0, sizeof(player[i].name));
            printf("nome jogador %d: ", i+1);
            scanf("%s", player[i].name);

        }
    }
}

void showPlayersScore(Player *player, int players, int countMatchs, char *categoryType){
    printf("------------------------------------------------------\n");
    printf("Jogadas Realizadas\n");
    printf("------------------------------------------------------\n");
    
    for(int i = 0; i < players; i++){
        for(int j = 0; j < 4; j++){
            if(player[i].pontoParcial[j].modalidade == categoryType){
                printf("Player %s: %s\n",player[i].name, player[i].pontoParcial[j].resposta);
            }
        }
    }

    printf("------------------------------------------------------\n");
    printf("TABELA DE SCORES DA RODADA\n");
    printf("------------------------------------------------------\n");

    for(int i  = 0; i < players; i++){
        printf("------------------------------------------------------\n");
        printf("Player %s - \n", player[i].name);
        printf("------------------------------------------------------\n");
        for(int j = 0; j < 4; j++){
            // mostrara os resultados parciais
            if(player[i].pontoParcial[j].ponto != 0){
                printf("Type:  %s \n", player[i].pontoParcial[j].modalidade);
                printf("Score:  %d \n", player[i].pontoParcial[j].ponto);
            }
        }
        // mostrara os resultados finais
        if(countMatchs == 3){
            printf("Final Score:  %d \n", player[i].pontoFinal);
        }

    }

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
    int random1, random2, random3;
    int countMatchs = 0;
    Player *player;

    memset(letter_draw, -1, sizeof(letter_draw));
    memset(category_draw, -1, sizeof(category_draw));

    srand(time(NULL));

    printf("entre a quantidade de jogadores: ");
    scanf("%s", &convert);
    n = atoi(convert);

    n = check_qtd_players(n);
    
    player = players(n);

    players_name(player, n);

    /* TESTE DE NOMES
    printf("%s\n", player[0].nome);
    printf("%s\n", player[1].nome);
    printf("%s\n", player[2].nome);
    */

    fill_alphabet(alphabet);
    fill_category(category);

    do{
        letter = get_letter(alphabet, letter_draw);

        printf("------------------------------------------------------\n");
        printf("letra sorteada: %c\n", letter);
        printf("------------------------------------------------------\n");

        category_selected = get_category(category, category_draw);

        printf("------------------------------------------------------\n");
        printf("categoria sorteada: %s\n", category_selected);
        printf("------------------------------------------------------\n");


        // Loop para os jogadores
            // escolher um jogador randomicamente
            // pegar as respostas por jogador
            // ele tem N segundos para responder
            // computar a resposta

        // Mostrar Respostas Parciais
        showPlayersScore(player, n, countMatchs, category_selected);
        countMatchs++;
    }while(countMatchs < 3);
        showPlayersScore(player, n, countMatchs, category_selected);



    printf("\ntudo certo ate aqui!\n");    

    /*char v[14];
    memset(v, 0, sizeof(v));
    scanf("%s", v);
    while (v[13]) {
        memset(v, 0, sizeof(v));
        scanf("%s", v);
    }
    printf("%s\n", v);
    printf("%lu\n", strlen(v));*/

    return 0;
}