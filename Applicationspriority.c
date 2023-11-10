#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

struct PriorityQueue {
    int heap[MAX_HEAP_SIZE];
    int size;
};

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct PriorityQueue* pq, int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < pq->size && pq->heap[leftChild] > pq->heap[largest]) {
        largest = leftChild;
    }

    if (rightChild < pq->size && pq->heap[rightChild] > pq->heap[largest]) {
        largest = rightChild;
    }

    if (largest != index) {
        swap(&pq->heap[index], &pq->heap[largest]);
        heapify(pq, largest);
    }
}

void insert(struct PriorityQueue* pq, int value) {
    if (pq->size == MAX_HEAP_SIZE) {
        printf("Priority queue is full. Cannot insert element.\n");
        return;
    }

    int index = pq->size;
    pq->heap[index] = value;
    pq->size++;

    while (index != 0 && pq->heap[(index - 1) / 2] < pq->heap[index]) {
        swap(&pq->heap[index], &pq->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int extractMax(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty. Cannot extract maximum element.\n");
        return -1;
    }

    int max = pq->heap[0];
    pq->size--;

    if (pq->size > 0) {
        pq->heap[0] = pq->heap[pq->size];
        heapify(pq, 0);
    }

    return max;
}

int main() {
    struct PriorityQueue pq;
    pq.size = 0;

    insert(&pq, 3);
    insert(&pq, 8);
    insert(&pq, 2);
    insert(&pq, 5);

    printf("Max Element: %d\n", extractMax(&pq));
    printf("Max Element: %d\n", extractMax(&pq));

    return 0;
}
