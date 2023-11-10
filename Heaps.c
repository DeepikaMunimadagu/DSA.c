#include <stdio.h>

#define MAX_HEAP_SIZE 100

// Function to swap two elements in the heap
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted at given index
void heapify(int heap[], int size, int index) {
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < size && heap[leftChild] < heap[smallest]) {
        smallest = leftChild;
    }

    if (rightChild < size && heap[rightChild] < heap[smallest]) {
        smallest = rightChild;
    }

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapify(heap, size, smallest);
    }
}

// Function to insert a new element into the heap
void insert(int heap[], int* size, int value) {
    if (*size == MAX_HEAP_SIZE) {
        printf("Heap is full. Cannot insert element.\n");
        return;
    }

    *size = *size + 1;
    int index = *size - 1;
    heap[index] = value;

    // Fix the min-heap property if it is violated
    while (index != 0 && heap[(index - 1) / 2] > heap[index]) {
        swap(&heap[index], &heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Function to extract the minimum element from the heap (pop)
int extractMin(int heap[], int* size) {
    if (*size <= 0) {
        printf("Heap is empty. Cannot extract minimum element.\n");
        return -1;
    }

    if (*size == 1) {
        *size = 0;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[*size - 1];
    *size = *size - 1;

    heapify(heap, *size, 0);

    return root;
}

// Function to display the elements of the heap
void displayHeap(int heap[], int size) {
    printf("Heap: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main() {
    int heap[MAX_HEAP_SIZE];
    int size = 0;
    int choice, value;

    do {
        printf("\n--- Heap Menu ---\n");
        printf("1. Insert\n");
        printf("2. Extract Min\n");
        printf("3. Display Heap\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insert(heap, &size, value);
                break;

            case 2:
                printf("Extracted Min: %d\n", extractMin(heap, &size));
                break;

            case 3:
                displayHeap(heap, size);
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
