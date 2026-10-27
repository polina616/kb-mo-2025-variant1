/**
 * @file main.cpp
 * @brief Построение минимального остовного дерева алгоритмом Прима.
 */

#include <iostream>
#include <vector>
#include <climits>

const int INF = INT_MAX;

int main() {
    int n = 5;
    // Матрица стоимостей (расстояний) D
    std::vector<std::vector<int>> graph = {
        {0,   80,  10,  40,  15},
        {80,  0,   85,  50,  45},
        {10,  85,  0,   25,  30},
        {40,  50,  25,  0,   60},
        {15,  45,  30,  60,  0 }
    };

    std::vector<int> key(n, INF);
    std::vector<int> parent(n, -1);
    std::vector<bool> inMST(n, false);

    key[0] = 0; // Начинаем с 1-го узла (индекс 0)

    for (int count = 0; count < n - 1; ++count) {
        int min_key = INF, u = -1;

        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && key[v] < min_key) {
                min_key = key[v];
                u = v;
            }
        }

        if (u == -1) break;
        inMST[u] = true;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    std::cout << "=== РЕЗУЛЬТАТ РАСЧЕТА ЗАДАЧИ 4 ===\n";
    int total_cost = 0;
    std::cout << "Выбранные ребра кабельной сети:\n";
    for (int i = 1; i < n; ++i) {
        std::cout << "Узел " << (parent[i] + 1) << " - Узел " << (i + 1) << " (Длина: " << graph[i][parent[i]] << ")\n";
        total_cost += graph[i][parent[i]];
    }
    std::cout << "Минимальная суммарная стоимость кабеля: " << total_cost << "\n";
    std::cout << "==================================\n";

    return 0;
}
