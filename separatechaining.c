#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
typedef struct Node {
    int key;
    struct Node* next;
} Node;

// Bucket structure using separate chaining
typedef struct Bucket {
    Node* head;
} Bucket;

// Hash function
int hash(int key, int size) {
    return key % size;
}

// Insert a key into the hash table using separate chaining
void insert(Bucket* hashTable, int key, int tableSize) {
    int index = hash(key, tableSize);

    // Create a new node for the key
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;

    // Insert the node into the linked list at the specified index
    if (hashTable[index].head == NULL) {
        // If the list is empty, set the new node as the head
        hashTable[index].head = newNode;
    } else {
        // Otherwise, append the new node to the end of the list
        Node* current = hashTable[index].head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Display the hash table with separate chaining
void display(Bucket* hashTable, int tableSize) {
    printf("Hash Table with Separate Chaining:\n");
    for (int i = 0; i < tableSize; i++) {
        printf("Bucket %d: ", i);
        Node* current = hashTable[i].head;
        while (current != NULL) {
            printf("%d -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int tableSize = 10;
    Bucket* hashTable = (Bucket*)malloc(tableSize * sizeof(Bucket));

    // Initialize the hash table
    for (int i = 0; i < tableSize; i++) {
        hashTable[i].head = NULL;
    }

    // Insert keys into the hash table using separate chaining
    insert(hashTable, 5, tableSize);
    insert(hashTable, 25, tableSize);
    insert(hashTable, 15, tableSize);
    insert(hashTable, 35, tableSize);

    // Display the final hash table with separate chaining
    display(hashTable, tableSize);

    // Free the memory allocated for the hash table
    for (int i = 0; i < tableSize; i++) {
        Node* current = hashTable[i].head;
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(hashTable);

    return 0;
}
