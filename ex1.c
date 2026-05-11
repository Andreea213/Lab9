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

    printf("\n[DIJKSTRA]");
    if (dist[dest] == INF) printf(" Sursa %d -> Dest %d: Nu exista drum.\n", sursa, dest);
    else {
        printf(" Cost: %d | Drum: ", dist[dest]);
        afiseazaDrum(parinte, dest);
        printf("\n");
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
            int u = muchii[j].u;
            int v = muchii[j].v;
            int cost = muchii[j].cost;
            if (dist[u] != INF && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                parinte[v] = u;
            }
        }
    }

    printf("[BELLMAN-FORD]");
    if (dist[dest] == INF) printf(" Sursa %d -> Dest %d: Nu exista drum.\n", sursa, dest);
    else {
        printf(" Cost: %d | Drum: ", dist[dest]);
        afiseazaDrum(parinte, dest);
        printf("\n");
    }
}

void executaAnaliza(char* numeFisier) {
    Muchie muchii[MAX_MUCHII];
    int graf_matrice[MAX_NODURI][MAX_NODURI] = {0};
    int nr_muchii = 0;

    FILE *f = fopen(numeFisier, "r");
    if (!f) {
        printf("\n(!) Eroare: Fisierul %s nu a putut fi deschis.\n", numeFisier);
        return;
    }

    printf("\n========================================");
    printf("\n ANALIZA GRAF: %s", numeFisier);
    printf("\n========================================");

    while (fscanf(f, "%d,%d,%d", &muchii[nr_muchii].u, &muchii[nr_muchii].v, &muchii[nr_muchii].cost) != EOF) {
        graf_matrice[muchii[nr_muchii].u][muchii[nr_muchii].v] = muchii[nr_muchii].cost;
        nr_muchii++;
    }
    fclose(f);

    Dijkstra(graf_matrice, 0, 14);
    BellmanFord(muchii, nr_muchii, 0, 14);
}

int main() {
    executaAnaliza("graf_intrare.csv");

    executaAnaliza("graf_intrare2.csv");

    return 0;
}
