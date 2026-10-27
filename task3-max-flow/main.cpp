/**
 * @file main.cpp
 * @brief Построение максимального потока алгоритмом Эдмондса-Карпа (Форд-Фалкерсон + BFS).
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

const int INF = INT_MAX;

/**
 * @brief Поиск кратчайшего увеличивающего пути с помощью BFS.
 */
bool bfs(const std::vector<std::vector<int>>& residual_capacity, int source, int sink, std::vector<int>& parent, int n) {
    std::fill(parent.begin(), parent.end(), -1);
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && residual_capacity[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                if (v == sink) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int main() {
    int n = 6; // s=0, 2=1, 3=2, 4=3, 5=4, t=5
    std::vector<std::vector<int>> capacity(n, std::vector<int>(n, 0));

    // Задаем пропускные способности (матрица C)
    capacity[0][1] = 3; // s -> 2
    capacity[0][2] = 3; // s -> 3
    capacity[1][3] = 5; // 2 -> 4
    capacity[1][4] = 6; // 2 -> 5
    capacity[2][4] = 1; // 3 -> 5
    capacity[3][5] = 3; // 4 -> t
    capacity[4][3] = 4; // 5 -> 4
    capacity[4][5] = 3; // 5 -> t

    std::vector<std::vector<int>> residual = capacity;
    std::vector<int> parent(n);
    int max_flow = 0;

    // Алгоритм Эдмондса-Карпа
    while (bfs(residual, 0, 5, parent, n)) {
        int path_flow = INF;
        for (int v = 5; v != 0; v = parent[v]) {
            int u = parent[v];
            path_flow = std::min(path_flow, residual[u][v]);
        }

        for (int v = 5; v != 0; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow; // Обратное ребро
        }
        max_flow += path_flow;
    }

    std::cout << "=== РЕЗУЛЬТАТ РАСЧЕТА ЗАДАЧИ 3 ===\n";
    std::cout << "Величина максимального потока f*: " << max_flow << "\n";
    std::cout << "==================================\n";

    return 0;
}
