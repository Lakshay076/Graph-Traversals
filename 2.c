#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 5

typedef struct Node{
    int vertex;
    struct Node* next;
}Node;

typedef struct {
    int num_vertices;
    Node **adj_lists;
}GraphList;

typedef struct
{
    int items[MAX_SIZE];
    int front;
    int rear;
} Queus;

Queus *create_queus()
{
    Queus *queu = (Queus *)malloc(sizeof(Queus));
    if (queu == NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }
    queu->front = -1;
    queu->rear = -1;
    return queu;
}

int is_empty_q(Queus *queu)
{   
    return queu->front == -1 && queu->rear == -1;   
}

int is_full_q(Queus *queu)
{
    return queu->rear - queu->front == MAX_SIZE - 1;
}

int get_size(Queus *queue)
{   
    if (queue->front == -1) return 0;
    else return queue->rear - queue->front + 1;
}

int enqueue(Queus *queu, int item)
{
    if(is_full_q(queu)) {
        printf("Queue is full, cannot add\n");
        return 0;
    }
    if(get_size(queu) == 0) {
        queu->items[++queu->rear] = item;
        queu->front = 0;
        return 0;
    }
    else {
        queu->items[++queu->rear] = item;
        return 0;
    }
}

int dequeue(Queus *queu)
{
    if (is_empty_q(queu)) {
        printf("Queue is empty, cannot dequeue\n"); 
        return -1;
    }
    int n;
    n = queu->items[queu->front];
    for( int i = 0; i < queu->rear; i++) {
        queu->items[queu->front + i] = queu->items[queu->front + i + 1];
    }
    if(queu->front == 0 && queu->rear == 0) {
        queu->rear = queu->rear - 1;
        queu->front = -1;
    }
    else {
        queu->rear = queu->rear - 1;
    }
    return n;
}

GraphList* create_graph_list(int vertices){
    GraphList* graph = (GraphList*)malloc(sizeof(GraphList));

    graph->adj_lists = (Node**)malloc(vertices * sizeof(Node*));
    for(int i = 0; i < vertices ; i++){
        graph->adj_lists[i] = NULL;
    }

    return graph;
}

int add_edge_list(GraphList *graph, int src, int dest){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adj_lists[src];
    graph->adj_lists[src] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = newNode;

    return 0;
}

// int print_graph_list(GraphList *graph) {

//     for(int i = 0; i < graph->num_vertices; i++){
//         Node *temp = graph->adj_lists[i];
//         printf("\n Adjacency list of vertix %d: head ", i);
//         while(temp){
//             printf("-> %d", temp->vertex);
//             temp = temp->next;
//         }
//     }

//     return 0;
// }

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

int visited(int arr[], int i ) {
    arr[i] = 1;
    return 0;
}

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    //check whether memory is given or not
    stack->top = -1;
    return stack;
}

int is_empty(Stack* stack) {
    return stack->top == -1;
}

int is_full(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int item) {
    if (is_full(stack)) {
        printf("Stack is full, Cannot push %d.\n", item);
        return;
    }
    stack->arr[++stack->top] = item;
}


int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    }

    return stack->arr[stack->top--];
}
 
void BFS(GraphList* graph, int start_vertex) {
    Queus* queue = create_queus();
    int arr[5] = {0,0,0,0,0};
    int curr_vertex;
    enqueue(queue, start_vertex);

    while(!is_empty_q(queue)) {
        curr_vertex = queue->items[queue->front];
        dequeue(queue);
        if(!arr[curr_vertex]) {
            arr[curr_vertex] = 1;
            printf("Visited = %d\n", curr_vertex);
        }

        Node* temp = graph->adj_lists[curr_vertex];
        while(temp != NULL) {
            int adj_vertex = temp->vertex;
            if(!arr[adj_vertex]) {
                enqueue(queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
    return;
} 

int main(){

    GraphList *gMatrix = create_graph_list(4);
    add_edge_list(gMatrix, 0, 1);
    add_edge_list(gMatrix, 0, 2);
    add_edge_list(gMatrix, 0, 3);
    add_edge_list(gMatrix, 1, 2);
    add_edge_list(gMatrix, 3, 4);

    BFS(gMatrix, 0);
    return 0;
}

