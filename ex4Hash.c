#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct Node {
    char key[20];
    char val[50];
    struct Node* next;
};

struct Node* hashTable[SIZE] = {NULL};

unsigned int hash(char* key) {
    unsigned int h = 0;
    while (*key) h = (h << 5) + *key++;
    return h % SIZE;
}

void add(char* k, char* v) {
    unsigned int idx = hash(k);
    struct Node* newNode = malloc(sizeof(struct Node));
    strcpy(newNode->key, k);
    strcpy(newNode->val, v);
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
    printf("Adaugat: [%s]\n", k);
}

void search(char* k) {
    unsigned int idx = hash(k);
    struct Node* temp = hashTable[idx];
    while (temp) {
        if (strcmp(temp->key, k) == 0) {
            printf("Definitie %s: %s\n", k, temp->val);
            return;
        }
        temp = temp->next;
    }
    printf("Cuvantul '%s' nu a fost gasit.\n", k);
}

int main() {
    add("C", "Limbaj de programare");
    add("Hash", "Functie de dispersie");
    
    printf("\nCautare:\n");
    search("C");
    search("Python");
    
    return 0;
}
