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
  char name[256]; 
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

/*
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
    printf("TABELA DE ESCORES DA RODADA %d\n", countMatchs+1);
    printf("------------------------------------------------------\n");

    for(int i  = 0; i < players; i++){
        printf("------------------------------------------------------\n");
        printf("Player %s", player[i].name);
        printf("------------------------------------------------------\n");
        for(int j = 0; j < 4; j++){
            // mostrara os resultados parciais
            if(player[i].pontoParcial[j].ponto == 0){
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
*/

void show_order(Player *player, int *vet2, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i+1, player[vet2[i]].name);
    }
}

void respostas(Player *player, int *vet2, char letter, char *category_selected, int n) { // tem q colocar um cont pro ponto parcial
    char teste[256];
    for (int k = 0; k < n; k++) { 
        printf("%s, voce deve entrar um '%s' com a letra '%c' em tantos segundos\n", player[vet2[k]].name, category_selected, letter);
        fgets(teste, 256, stdin);
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
    int *p = &n;
    int vet1[*p];
    int vet2[*p];
    int countMatchs = 0;
    char teste[256];
    Player *player;

    memset(letter_draw, -1, sizeof(letter_draw));
    memset(category_draw, -1, sizeof(category_draw));

    srand(time(NULL));

    printf("entre a quantidade de jogadores: ");
    fgets(convert, 256, stdin);
    //scanf("%s", &convert);
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

    system("cls");

    for (int i = 0; i < 2; i++) {

        letter = alphabet[get_index(letter_draw, 23)];

        printf("------------------------------------------------------\n");
        printf("letra sorteada: %c\n", letter);
        printf("------------------------------------------------------\n");

        category_selected = category[get_index(category_draw, 5)];

        printf("------------------------------------------------------\n");
        printf("categoria sorteada: %s\n", category_selected);
        printf("------------------------------------------------------\n");

        memset(vet1, -1, sizeof(vet1));
        random_order(vet1, vet2, n); // ordem aleatoria ta no vet2

        printf("------------------------------------------------------\n");
        printf("A ordem desta rodada sera: \n");
        show_order(player, vet2, n);
        printf("------------------------------------------------------\n");

        printf("Aperte enter\n");
        getchar();
        clear_window();

        respostas(player, vet2, letter, category_selected, n);

    }

    /*
    do{
        letter = alphabet[get_index(letter_draw, 23)];

        printf("------------------------------------------------------\n");
        printf("letra sorteada: %c\n", letter);
        printf("------------------------------------------------------\n");

        category_selected = category[get_index(category_draw, 5)];

        printf("------------------------------------------------------\n");
        printf("categoria sorteada: %s\n", category_selected);
        printf("------------------------------------------------------\n");

        memset(vet1, -1, sizeof(vet1));
        random_order(vet1, vet2, n); // a ordem está no vet2

        printf("------------------------------------------------------\n");
        printf("A ordem desta rodada sera: \n");
        show_order(player, vet2, n);
        printf("------------------------------------------------------\n");

        //scanf("%d", &teste);

        //system("cls");

        //printf("Aperte enter\n");
        
        //clear_window();

        // Loop para os jogadores
            // escolher um jogador randomicamente
            // pegar as respostas por jogador
            // ele tem N segundos para responder
            // computar a resposta

        // Mostrar Respostas Parciais
        showPlayersScore(player, n, countMatchs, category_selected);
        countMatchs++;
    }while(countMatchs < 3); 

    //showPlayersScore(player, n, countMatchs, category_selected);
    */

    printf("\ntudo certo ate aqui!\n");    

    return 0;
}