#include <stdio.h>

#define MAX_VERTICES 100

int parent[MAX_VERTICES]; // 부모 노드
int rank[MAX_VERTICES];   // 각 집합의 rank (트리 높이)

// 초기화
void set_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;   // 모든 노드의 부모를 -1로 초기화
        rank[i] = 0;      // 초기 rank는 0
    }
}

// curr가 속하는 집합의 루트를 반환 (경로 압축 적용)
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr; // 루트 노드이면 자기 자신 반환

    // 경로 압축 (재귀적으로 루트 노드를 부모로 설정)
    return parent[curr] = set_find(parent[curr]);
}

// 두 개의 원소가 속한 집합을 합침 (rank를 기반으로 합병)
void set_union(int a, int b) {
    int root1 = set_find(a); // 노드 a의 루트를 찾음
    int root2 = set_find(b); // 노드 b의 루트를 찾음

    if (root1 != root2) { // 두 노드가 다른 집합에 속할 경우만 합침
        if (rank[root1] > rank[root2]) {
            parent[root2] = root1; // root2를 root1에 연결
        } else if (rank[root1] < rank[root2]) {
            parent[root1] = root2; // root1을 root2에 연결
        } else {
            parent[root2] = root1; // 높이가 같으면 root2를 root1에 연결
            rank[root1]++;         // root1의 rank를 증가
        }
    }
}

int main() {
    int n = 5; // 예제: 5개의 노드
    set_init(n);

    set_union(0, 1);
    set_union(1, 2);
    set_union(3, 4);

    printf("Find(2): %d\n", set_find(2)); // 0의 루트를 반환 (0, 1, 2가 연결됨)
    printf("Find(4): %d\n", set_find(4)); // 3의 루트를 반환 (3, 4가 연결됨)

    return 0;
}

