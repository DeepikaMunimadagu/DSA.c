#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// Hash function
int hash(int key) {
    return key % SIZE;
}

// Insert a key into the hash table using quadratic probing
void insert(int hashTable[], int key) {
    int index = hash(key);
    int i = 1;

    // Quadratic probing until an empty slot is found
    while (hashTable[index] != -1) {
        index = (index + i * i) % SIZE;
        i++;
    }

    // Insert the key into the hash table
    hashTable[index] = key;
}

// Display the hash table
void display(int hashTable[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d: %d\n", i, hashTable[i]);
    }
}

int main() {
    int hashTable[SIZE];

    // Initialize the hash table with -1 (indicating empty slots)
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = -1;
    }

    // Insert keys into the hash table using quadratic probing
    insert(hashTable, 5);
    insert(hashTable, 25);
    insert(hashTable, 15);
    insert(hashTable, 35);

    // Display the final hash table
    display(hashTable);

    return 0;
}
