#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 9

// Queue implementation for BFS
int queue[MAX_VERTICES];
int front = -1, rear = -1;

void enqueue(int vertex) {
    if (rear == MAX_VERTICES - 1) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = vertex;
}

int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    int vertex = queue[front];
    front++;
    return vertex;
}

bool isQueueEmpty() {
    return front == -1 || front > rear;
}

// Graph implementation using adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Node* graph[MAX_VERTICES];

void addEdge(int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph[src];
    graph[src] = newNode;
}

// BFS traversal
void bfs(int startVertex) {
    bool visited[MAX_VERTICES] = {false};

    // Queue up the starting vertex and mark it as visited
    enqueue(startVertex);
    visited[startVertex] = true;

    while (!isQueueEmpty()) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        // Visit all adjacent vertices of the current vertex
        Node* temp = graph[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                enqueue(adjVertex);
                visited[adjVertex] = true;
            }
            temp = temp->next;
        }
    }
}

int main() {
    // Initialize the graph as an array of NULL pointers
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph[i] = NULL;
    }

    // Add edges to the graph
    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(1, 4);
    addEdge(2, 5);
    addEdge(3, 4);
    addEdge(3, 6);
    addEdge(4, 7);
    addEdge(5, 8);
    addEdge(6, 7);
    addEdge(7, 8);

    printf("BFS Traversal starting from vertex 0: ");
    bfs(0);
    printf("\n");

    return 0;
}

