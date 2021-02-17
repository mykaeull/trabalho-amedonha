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

void fill_category(char **category) {
    category[0] = "profissoes";
    category[1] = "nomes de pessoas";
    category[2] = "nomes de cidade";
    category[3] = "nomes de animais";
    category[4] = "nomes de comida";
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
    int letter_draw[23];
    char letter;
    char *category[5];
    int category_draw[5];
    char *category_selected;
    int n;
    Player *player;

    memset(letter_draw, -1, sizeof(letter_draw));
    memset(category_draw, -1, sizeof(category_draw));

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
    fill_category(category);

    letter = get_letter(alphabet, letter_draw);

    printf("------------------------------------------------------\n");
    printf("letra sorteada: %c\n", letter);
    printf("------------------------------------------------------\n");

    category_selected = get_category(category, category_draw);

    printf("------------------------------------------------------\n");
    printf("categoria sorteada: %s\n", category_selected);
    printf("------------------------------------------------------\n");

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