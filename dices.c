/*
 *  base code to build CLI dice games
 *
 * diegoCode - Diego Codevilla / AR
 * CC-BY-SA 4.0
 *
 * v1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// number of players
#define qtyPlayers  3

// number of dices
#define qtyDices        3

// dice width
#define diceWidth       9

// rolls per player 
#define rollsPerPlayer  1

// struct to store player data
typedef struct {
    char name[20];
    int  score[qtyDices];
} player_t;

// to store players data
player_t players[qtyPlayers];

// base square of dice
const char dice_frame[5][8] = {
        {" ----- "},
        {"|     |"},
        {"|     |"},
        {"|     |"},
        {" ----- "}
};

// definition of each of six numbers of dice
const char dice_img[6][3][4] = {
        {"   ", " 0 ", "   "},  // 1
        {" 0 ", "   ", " 0 "},  // 2
        {"0  ", " 0 ", "  0"},  // 3
        {"0 0", "   ", "0 0"},  // 4
        {"0 0", " 0 ", "0 0"},  // 5
        {"0 0", "0 0", "0 0"}   // 6
};

// "buffer" used for draw dices
char roll_img[5][diceWidth * qtyDices + 1];

void drawDice(int dicePos, int number);
void drawRoll();
void setUpRoll(int n);
void rollDices(int playerNumber);
void clearRoll();
int playerScore(player_t pl);
void clearPlayersScores();
//void ver(); // for debug


int main() {
    srand(time(NULL));

    // clear "drawing" area and draw dices' borders
    setUpRoll(qtyDices);
    clearPlayersScores();

    // read players' names
    // if name is not entered assigns "Player n"
    for (int p = 0; p < qtyPlayers; p++) {
        printf("Input name of player %2d: ", p);

        fgets(players[p].name, 20, stdin);
        if (strlen(players[p].name) < 3) {
            strcpy(players[p].name, "Player    ");
            players[p].name[7] = p + 0x31;
        }
        players[p].name[strlen(players[p].name) - 1] = '\0';
    }

    // rolls & show dices of every player
    for(int p = 0; p < qtyPlayers; p++) {
        printf("\n\n%s:\n", players[p].name);
        for(int i = 0; i < rollsPerPlayer; i++) {
            rollDices(p);

            drawRoll();
        }
        printf("Score: %3d \n", playerScore(players[p]));
    }

    return 0;
}

// clear virtual screen
void clearRoll() {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < (diceWidth * qtyDices); x++) {
            roll_img[y][x] = ' ';
        }
    }
}

// draws dice in position "dicePos" with
// number "number"
// Ej. drawDice(2, 4); puts four dots in the
// coordinates reserved to dice 2 (third from left)
void drawDice(int dicePos, int number) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            roll_img[i + 1][j + 2 + dicePos * diceWidth] = dice_img[number - 1][i][j];
        }
    }
}

// Outputs virtual screen to console
void drawRoll() {
    for (int row = 0; row < 5; row++) {
        printf("%s\n", roll_img[row]);
    }
}

// clear and draws dices' frames
void setUpRoll(int n) {
    clearRoll();
    for (int q = 0; q < n; q++ ) {
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 7; x++) {
                roll_img[y][(q * diceWidth) + x] = dice_frame[y][x];
            }
        }
    }
}

// simulates dices roll for player "playerNumber"
void rollDices(int playerNumber){
    int aux;
    for(int i = 0; i < qtyDices; i++) {
        aux = rand() % 6 + 1;
        drawDice(i, aux);
        players[playerNumber].score[i] += aux;
    }
}

// calculates players' score
int playerScore(player_t pl) {
    int aux = 0;
    for(int p = 0; p < qtyDices; p++) {
        aux += pl.score[p];
    }
    return aux;
}

void clearPlayersScores() {
    for(int p = 0; p < qtyPlayers; p++) {
        for(int sn = 0; sn < qtyDices; sn++) {
            players[p].score[sn] = 0;
        }
    }
}

/*
void ver() {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < (diceWidth * qtyDices) + 1; x++) {
            printf("%02X ", roll_img[y][x]);
            printf("%c ", roll_img[y][x]);
        }
        printf("\n");
    }
}
*/
