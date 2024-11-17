#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

typedef struct GraphType {
    int n; // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬
} GraphType;

bool visited[MAX_VERTICES]; // 방문 여부를 기록하는 배열

// 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType* g, int v) {
    int w;
    visited[v] = true; // 정점 v를 방문 표시
    printf("정점 %d -> ", v); // 방문한 정점 출력
    for (w = 0; w < g->n; w++) { // 모든 인접 정점 탐색
        if (g->adj_mat[v][w] && !visited[w]) {
            dfs_mat(g, w); // 정점 w에서 DFS 새로 시작
        }
    }
}

// 그래프 초기화
void init(GraphType* g) {
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
    g->adj_mat[v][u] = 1;
}

int main(void) {
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
    dfs_mat(g, 0);
    printf("\n");

    free(g);
    return 0;
}
