#include <stdio.h>
#include <string.h>

// Simple hash function for strings
unsigned int simpleHash(const char *str, int tableSize) {
    unsigned int hash = 0;
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        hash = hash * 31 + str[i];
    }

    return hash % tableSize;
}

int main() {
    const char *key = "example";
    int tableSize = 100;  // Adjust the table size as needed

    // Get the hash code using the hash function
    unsigned int hashCode = simpleHash(key, tableSize);

    printf("Key: %s, Hash Code: %u\n", key, hashCode);

    return 0;
}
