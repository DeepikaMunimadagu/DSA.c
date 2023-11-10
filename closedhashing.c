#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// Hash function
int hash(int key) {
    return key % SIZE;
}

// Insert a key into the hash table using linear probing
void insert(int hashTable[], int key) {
    int index = hash(key);

    // Linear probing until an empty slot is found
    while (hashTable[index] != -1) {
        index = (index + 1) % SIZE;
    }

    // Insert the key into the hash table
    hashTable[index] = key;
}

// Search for a key in the hash table
int search(int hashTable[], int key) {
    int index = hash(key);

    // Linear probing until the key is found or an empty slot is encountered
    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            return index; // Key found
        }
        index = (index + 1) % SIZE;
    }

    return -1; // Key not found
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

    // Insert keys into the hash table
    insert(hashTable, 5);
    insert(hashTable, 25);
    insert(hashTable, 15);
    insert(hashTable, 35);

    // Display the final hash table
    display(hashTable);

    // Search for a key
    int keyToSearch = 15;
    int result = search(hashTable, keyToSearch);
    if (result != -1) {
        printf("\nKey %d found at index %d.\n", keyToSearch, result);
    } else {
        printf("\nKey %d not found.\n", keyToSearch);
    }

    return 0;
}
