#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10
#define LOAD_FACTOR_THRESHOLD 0.7

// Hash function
int hash(int key, int size) {
    return key % size;
}

// Rehashing function
void rehash(int** hashTable, int* size) {
    int newSize = *size * 2;  // Double the size of the table

    // Create a new hash table with the updated size
    int* newHashTable = (int*)malloc(newSize * sizeof(int));
    for (int i = 0; i < newSize; i++) {
        newHashTable[i] = -1;  // Initialize with -1 (indicating empty slots)
    }

    // Rehash and insert elements from the old table to the new table
    for (int i = 0; i < *size; i++) {
        if ((*hashTable)[i] != -1) {
            int key = (*hashTable)[i];
            int newIndex = hash(key, newSize);
            
            // Linear probing in case of collisions during rehashing
            while (newHashTable[newIndex] != -1) {
                newIndex = (newIndex + 1) % newSize;
            }

            newHashTable[newIndex] = key;
        }
    }

    // Free the memory allocated for the old hash table
    free(*hashTable);

    // Update the hash table and size with the new values
    *hashTable = newHashTable;
    *size = newSize;
}

// Insert a key into the hash table
void insert(int** hashTable, int* size, int key) {
    int index = hash(key, *size);

    // Linear probing until an empty slot is found
    while ((*hashTable)[index] != -1) {
        index = (index + 1) % *size;

        // Rehash if the load factor exceeds the threshold
        if ((float)(*size - 1) / *size > LOAD_FACTOR_THRESHOLD) {
            rehash(hashTable, size);
            index = hash(key, *size);
        }
    }

    // Insert the key into the hash table
    (*hashTable)[index] = key;
}

// Display the hash table
void display(int* hashTable, int size) {
    printf("Hash Table:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: %d\n", i, hashTable[i]);
    }
}

int main() {
    int size = INITIAL_SIZE;
    int* hashTable = (int*)malloc(size * sizeof(int));

    // Initialize the hash table with -1 (indicating empty slots)
    for (int i = 0; i < size; i++) {
        hashTable[i] = -1;
    }

    // Insert keys into the hash table
    insert(&hashTable, &size, 5);
    insert(&hashTable, &size, 25);
    insert(&hashTable, &size, 15);
    insert(&hashTable, &size, 35);

    // Display the final hash table
    display(hashTable, size);

    // Free the memory allocated for the hash table
    free(hashTable);

    return 0;
}
