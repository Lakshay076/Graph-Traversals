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

typedef struct {
    int top ;
    int arr[MAX_SIZE];
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

int print_graph_list(GraphList *graph) {
    for(int i = 0; i < graph->num_vertices; i++){
        Node *temp = graph->adj_lists[i];
        printf("\n Adjacency list of vertix %d: s", i);
        while(temp){
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
    }

    return 0;
}

void DFS(GraphList* graph, int start_vertex) {
    Stack* stack = create_stack();
    int arr[5] = {0,0,0,0,0};
    int curr_vertex;
    push(stack, start_vertex);
    
    while(!is_empty(stack)) {
        curr_vertex = pop(stack);
        if(!arr[curr_vertex]) {
            arr[curr_vertex] = 1;
            printf("Visited : %d\n", curr_vertex);
        }

        Node* temp = graph->adj_lists[curr_vertex];
        while(temp != NULL) {
            int adj_vertex = temp->vertex;
            if(!arr[adj_vertex]) {
                push(stack, adj_vertex);
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
    print_graph_list(gMatrix);
    printf("\n");
    DFS(gMatrix, 0);
    return 0;
}

