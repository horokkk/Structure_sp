#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

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
void init(GraphType* g) {
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

// 인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_list(GraphType* g, int v) {
    GraphNode* w;
    visited[v] = true; // 정점 v의 방문 표시
    printf("정점 %d -> ", v); // 방문한 정점 출력
    for (w = g->adj_list[v]; w != NULL; w = w->link) { // 인접 정점 탐색
        if (!visited[w->vertex]) {
            dfs_list(g, w->vertex); // 정점 w에서 DFS 새로 시작
        }
    }
}

int main() {
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);

    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    printf("깊이 우선 탐색\n");
    dfs_list(g, 0);
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
