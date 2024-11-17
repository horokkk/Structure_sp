#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

typedef struct {
    int queue[MAX_VERTICES];
    int front, rear;
} QueueType;

// 큐 초기화
void queue_init(QueueType* q) {
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

typedef struct GraphType {
    int n; // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬
} GraphType;

bool visited[MAX_VERTICES]; // 방문 여부를 기록하는 배열

// 그래프 초기화
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
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
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류\n");
        return;
    }
    g->adj_mat[u][v] = 1;
    g->adj_mat[v][u] = 1; // 무방향 그래프의 경우, 이 줄을 유지합니다.
}

// 인접 행렬을 활용한 BFS
void bfs_mat(GraphType* g, int v) {
    int w;
    QueueType q;
    queue_init(&q);

    visited[v] = true; // 정점 v 방문 표시
    printf("%d 방문 -> ", v); // 방문한 정점 출력
    enqueue(&q, v); // 시작 정점을 큐에 저장

    while (!is_empty(&q)) {
        v = dequeue(&q); // 큐에서 정점 추출
        for (w = 0; w < g->n; w++) { // 인접 정점 탐색
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = true; // 방문 표시
                printf("%d 방문 -> ", w);
                enqueue(&q, w); // 방문한 정점을 큐에 저장
            }
        }
    }
}

int main(void) {
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    graph_init(g);

    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 5);

    printf("너비 우선 탐색\n");
    bfs_mat(g, 0);
    printf("\n");

    free(g);
    return 0;
}
