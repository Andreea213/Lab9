#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODURI 15
#define MAX_MUCHII 100
#define INF 1e9

typedef struct {
    int u, v, cost;
} Muchie;


void afiseazaDrum(int parinte[], int j) {
    if (parinte[j] == -1) {
        printf("%d", j);
        return;
    }
    afiseazaDrum(parinte, parinte[j]);
    printf(" -> %d", j);
}


void Dijkstra(int graf[MAX_NODURI][MAX_NODURI], int sursa, int dest) {
    int dist[MAX_NODURI], parinte[MAX_NODURI];
    bool vizitat[MAX_NODURI];

    for (int i = 0; i < MAX_NODURI; i++) {
        dist[i] = INF;
        vizitat[i] = false;
        parinte[i] = -1;
    }
    dist[sursa] = 0;

    for (int count = 0; count < MAX_NODURI - 1; count++) {
        int min = INF, u = -1;
        for (int v = 0; v < MAX_NODURI; v++)
            if (!vizitat[v] && dist[v] <= min) { min = dist[v]; u = v; }

        if (u == -1 || dist[u] == INF) break;
        vizitat[u] = true;

        for (int v = 0; v < MAX_NODURI; v++) {
            if (!vizitat[v] && graf[u][v] != 0 && dist[u] + graf[u][v] < dist[v]) {
                dist[v] = dist[u] + graf[u][v];
                parinte[v] = u;
            }
        }
    }

    printf("\n[DIJKSTRA] Sursa %d -> Dest %d\n", sursa, dest);
    if (dist[dest] == INF) printf("Drum inaccesibil.\n");
    else {
        printf("Drum: "); afiseazaDrum(parinte, dest);
        printf("\nCost total: %d\n", dist[dest]);
    }
}


void BellmanFord(Muchie muchii[], int nr_muchii, int sursa, int dest) {
    int dist[MAX_NODURI], parinte[MAX_NODURI];

    for (int i = 0; i < MAX_NODURI; i++) {
        dist[i] = INF;
        parinte[i] = -1;
    }
    dist[sursa] = 0;

    for (int i = 1; i <= MAX_NODURI - 1; i++) {
        for (int j = 0; j < nr_muchii; j++) {
            if (dist[muchii[j].u] != INF && dist[muchii[j].u] + muchii[j].cost < dist[muchii[j].v]) {
                dist[muchii[j].v] = dist[muchii[j].u] + muchii[j].cost;
                parinte[muchii[j].v] = muchii[j].u;
            }
        }
    }

    printf("\n[BELLMAN-FORD] Sursa %d -> Dest %d\n", sursa, dest);
    if (dist[dest] == INF) printf("Drum inaccesibil.\n");
    else {
        printf("Drum: "); afiseazaDrum(parinte, dest);
        printf("\nCost total: %d\n", dist[dest]);
    }
}

void proceseazaGraf(char* numeFisier) {
    Muchie muchii[MAX_MUCHII];
    int graf_matrice[MAX_NODURI][MAX_NODURI] = {0};
    int nr_muchii = 0;

    FILE *f = fopen(numeFisier, "r");
    if (!f) {
        printf("\nEroare: Nu s-a putut deschide %s\n", numeFisier);
        return;
    }

    printf("\n\nANALIZA FISIER: %s \n", numeFisier);
    while (fscanf(f, "%d,%d,%d", &muchii[nr_muchii].u, &muchii[nr_muchii].v, &muchii[nr_muchii].cost) != EOF) {
        graf_matrice[muchii[nr_muchii].u][muchii[nr_muchii].v] = muchii[nr_muchii].cost;
        nr_muchii++;
    }
    fclose(f);

    Dijkstra(graf_matrice, 0, 14);
    BellmanFord(muchii, nr_muchii, 0, 14);
}

int main() {
    proceseazaGraf("graf_intrare.csv");

    proceseazaGraf("graf_intrare2.csv");

    return 0;
}
