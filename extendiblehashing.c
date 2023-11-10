#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUCKET_SIZE 2

// Bucket structure
typedef struct Bucket {
    int keys[BUCKET_SIZE];
    int count;
} Bucket;

// Directory structure
typedef struct Directory {
    int depth;
    Bucket** buckets;
} Directory;

// Initialize a new bucket
Bucket* createBucket() {
    Bucket* newBucket = (Bucket*)malloc(sizeof(Bucket));
    newBucket->count = 0;
    return newBucket;
}

// Initialize a new directory
Directory* createDirectory() {
    Directory* newDirectory = (Directory*)malloc(sizeof(Directory));
    newDirectory->depth = 1;
    newDirectory->buckets = (Bucket**)malloc(sizeof(Bucket*));
    newDirectory->buckets[0] = createBucket();
    return newDirectory;
}

// Hash a key to a binary string and return the hashed value
int hash(int key, int depth) {
    return key & ((1 << depth) - 1);
}

// Insert a key into the extendible hash table
void insert(Directory* directory, int key) {
    int hashedValue = hash(key, directory->depth);
    Bucket* targetBucket = directory->buckets[hashedValue];

    if (targetBucket->count < BUCKET_SIZE) {
        // If the bucket has space, insert the key
        targetBucket->keys[targetBucket->count++] = key;
    } else {
        // If the bucket is full, split it
        if (directory->depth > 0 && targetBucket->count >= BUCKET_SIZE) {
            // Increase directory depth
            int newDepth = directory->depth + 1;
            int newDirectorySize = 1 << newDepth;

            // Create a new directory with the increased depth
            Directory* newDirectory = createDirectory();
            newDirectory->depth = newDepth;
            newDirectory->buckets = (Bucket**)malloc(newDirectorySize * sizeof(Bucket*));

            // Initialize new buckets in the directory
            for (int i = 0; i < newDirectorySize; i++) {
                newDirectory->buckets[i] = createBucket();
            }

            // Redistribute keys between old and new buckets
            for (int i = 0; i < newDirectorySize / 2; i++) {
                newDirectory->buckets[i] = directory->buckets[i];
                newDirectory->buckets[i + newDirectorySize / 2] = createBucket();
            }

            // Update the old directory to point to the new one
            directory->depth = newDepth;
            directory->buckets = newDirectory->buckets;

            // Insert the key into the appropriate bucket
            insert(directory, key);
        }
    }
}

// Display the extendible hash table
void display(Directory* directory) {
    printf("Extendible Hash Table:\n");
    for (int i = 0; i < (1 << directory->depth); i++) {
        printf("Bucket %d: [", i);
        for (int j = 0; j < directory->buckets[i]->count; j++) {
            printf(" %d", directory->buckets[i]->keys[j]);
        }
        printf(" ]\n");
    }
}

int main() {
    Directory* directory = createDirectory();

    // Insert keys into the extendible hash table
    insert(directory, 5);
    insert(directory, 25);
    insert(directory, 15);
    insert(directory, 35);

    // Display the final extendible hash table
    display(directory);

    // Free the memory allocated for the extendible hash table
    free(directory->buckets);
    free(directory);

    return 0;
}
