#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

// 큐 자료구조 정의
typedef struct {
    int queue[MAX_VERTICES];
    int front, rear;
} QueueType;

// 큐 초기화
void init_queue(QueueType* q) {
    q->front = -1;
    q->rear = -1;
}

// 큐가 비어 있는지 확인
bool is_empty(QueueType* q) {
    return q->front == q->rear;
}

// 큐에 삽입
void enqueue(QueueType* q, int item) {
    if (q->rear == MAX_VERTICES - 1) {
        fprintf(stderr, "큐가 꽉 찼습니다.\n");
        return;
    }
    q->queue[++(q->rear)] = item;
}

// 큐에서 제거
int dequeue(QueueType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "큐가 비어 있습니다.\n");
        exit(1);
    }
    return q->queue[++(q->front)];
}

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n; // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

bool visited[MAX_VERTICES]; // 방문 여부를 기록하는 배열

// 그래프 초기화
void init_graph(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
        visited[i] = false; // 방문 여부 초기화
    }
}

// 정점 삽입
void insert_vertex(GraphType* g, int v) {
    if (g->n + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과\n");
        return;
    }
    g->n++;
}

// 간선 삽입
void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류\n");
        return;
    }
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

// 인접 리스트를 활용한 BFS
void bfs_list(GraphType* g, int v) {
    GraphNode* w;
    QueueType q;
    init_queue(&q); // 큐 초기화

    visited[v] = true; // 정점 v 방문 표시
    printf("%d 방문 -> ", v); // 방문한 정점 출력
    enqueue(&q, v); // 시작 정점을 큐에 삽입

    while (!is_empty(&q)) {
        v = dequeue(&q); // 큐에서 정점을 선택
        for (w = g->adj_list[v]; w != NULL; w = w->link) { // 인접 정점 탐색
            if (!visited[w->vertex]) { // 방문하지 않은 정점이라면
                visited[w->vertex] = true; // 방문 표시
                printf("%d 방문 -> ", w->vertex); // 방문한 정점 출력
                enqueue(&q, w->vertex); // 정점을 큐에 삽입
            }
        }
    }
}

int main(void) {
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init_graph(g);

    // 정점 및 간선 추가
    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 5);

    // BFS 실행
    printf("너비 우선 탐색\n");
    bfs_list(g, 0);
    printf("\n");

    // 메모리 해제
    for (int i = 0; i < g->n; i++) {
        GraphNode* temp = g->adj_list[i];
        while (temp != NULL) {
            GraphNode* next = temp->link;
            free(temp);
            temp = next;
        }
    }
    free(g);

    return 0;
}
