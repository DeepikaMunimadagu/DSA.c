#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// Primary hash function
int hash(int key) {
    return key % SIZE;
}

// Secondary hash function
int hash2(int key) {
    return 7 - (key % 7);  // You can choose any secondary hash function
}

// Insert a key into the hash table using double hashing
void insert(int hashTable[], int key) {
    int index = hash(key);
    int step = hash2(key);

    // Double hashing until an empty slot is found
    while (hashTable[index] != -1) {
        index = (index + step) % SIZE;
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

    // Insert keys into the hash table using double hashing
    insert(hashTable, 5);
    insert(hashTable, 25);
    insert(hashTable, 15);
    insert(hashTable, 35);

    // Display the final hash table
    display(hashTable);

    return 0;
}
