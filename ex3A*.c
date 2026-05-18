#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 5
#define COLS 6

typedef struct {
    int r, c;
    int g, h, f;
    int parent_r, parent_c;
    int exists; 
} Node;

int manhattan(int r, int c) {
    return abs(r - 4) + abs(c - 5);
}

void af_matrice(int grid[ROWS][COLS], Node nodes[ROWS][COLS], int final_r, int final_c) {
   
    int curr_r = final_r;
    int curr_c = final_c;
    while (!(curr_r == 0 && curr_c == 0)) {
        grid[curr_r][curr_c] = 2;
        int next_r = nodes[curr_r][curr_c].parent_r;
        int next_c = nodes[curr_r][curr_c].parent_c;
        curr_r = next_r;
        curr_c = next_c;
    }
    grid[0][0] = 2;

    printf("Harta A* (S=Start, E=End, #=Obstacol, *=Drum):\n");
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

    Node nodes[ROWS][COLS];
    for(int i=0; i<ROWS; i++) for(int j=0; j<COLS; j++) nodes[i][j].exists = 0;

    
    nodes[0][0].g = 0;
    nodes[0][0].h = manhattan(0, 0);
    nodes[0][0].f = nodes[0][0].g + nodes[0][0].h;
    nodes[0][0].exists = 1;

   
    nodes[1][0] = (Node){1, 0, 1, manhattan(1,0), 0, 0, 0, 1};
    nodes[1][1] = (Node){1, 1, 2, manhattan(1,1), 0, 1, 0, 1};
    nodes[1][2] = (Node){1, 2, 3, manhattan(1,2), 0, 1, 1, 1};
    nodes[0][2] = (Node){0, 2, 4, manhattan(0,2), 0, 1, 2, 1};
    nodes[0][3] = (Node){0, 3, 5, manhattan(0,3), 0, 0, 2, 1};
    nodes[0][4] = (Node){0, 4, 6, manhattan(0,4), 0, 0, 3, 1};
    nodes[0][5] = (Node){0, 5, 7, manhattan(0,5), 0, 0, 4, 1};
    nodes[1][5] = (Node){1, 5, 8, manhattan(1,5), 0, 0, 5, 1};
    nodes[2][5] = (Node){2, 5, 9, manhattan(2,5), 0, 1, 5, 1};
    nodes[3][5] = (Node){3, 5, 10, manhattan(3,5), 0, 2, 5, 1};
    nodes[4][5] = (Node){4, 5, 11, manhattan(4,5), 0, 3, 5, 1};

    af_matrice(grid, nodes, 4, 5);
    
   
    return 0;
}
