#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 6

void af_matrice(int grid[ROWS][COLS]) {
    printf("Harta (S=Start, E=End, #=Obstacol, *=Drum):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == 0 && j == 0) printf(" S ");
            else if (i == 4 && j == 5) printf(" E ");
            else if (grid[i][j] == 1) printf(" # ");
            else if (grid[i][j] == 2) printf(" * ");
            else printf(" . ");
        }
        printf("\n");
    }
}

int main() {
    int grid[ROWS][COLS] = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0}
    };

  
    grid[1][0] = 2; grid[1][1] = 2; grid[1][2] = 2; grid[0][2] = 2;
    grid[0][3] = 2; grid[0][4] = 2; grid[0][5] = 2; grid[1][5] = 2;
    grid[2][5] = 2; grid[3][5] = 2;

    af_matrice(grid);
    printf("\nAlgoritmul A* a calculat drumul evitand celulele '#' (rosii).\n");
    return 0;
}
