#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct player Player;

struct player {
  char nome[13];
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

int check_letter(int *draw, int index) {
    int checked = 0;
    if (index == draw[index]) {
        return 1;
    } else {
        draw[index] = index;
        return checked;
    }
}

char get_letter(char *alphabet, int *draw) {
    int index;

    index = rand()%23;

    while(check_letter(draw, index)) {
        index = rand()%23;
    }

    return alphabet[index];
}

Player* players(int n) {
    Player *player = (Player*)malloc(n*sizeof(Player));
    return player;
}

void players_name(Player *player, int n) {
    for (int i = 0; i < n; i++) {
        memset(player[i].nome, 0, sizeof(player[i].nome));
        printf("nome jogador %d: ", i+1);
        scanf("%s", player[i].nome);
        while (player[i].nome[12]) {
            memset(player[i].nome, 0, sizeof(player[i].nome));
            printf("nome jogador %d: ", i+1);
            scanf("%s", player[i].nome);
        }
    }
}

int main () {
    char alphabet[23];
    int draw[23];
    char letter;
    int n;
    Player *player;

    memset(draw, -1, sizeof(draw));

    srand(time(NULL));

    printf("entre a quantidade de jogadores: ");
    scanf("%d", &n);
    
    player = players(n);

    players_name(player, n);

    /* TESTE DE NOMES
    printf("%s\n", player[0].nome);
    printf("%s\n", player[1].nome);
    printf("%s\n", player[2].nome);
    */

    fill_alphabet(alphabet);

    letter = get_letter(alphabet, draw);

    printf("\ntudo certo ate aqui!");    

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