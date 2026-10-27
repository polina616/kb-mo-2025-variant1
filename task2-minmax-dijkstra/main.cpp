/**
 * @file main.cpp
 * @brief Поиск MINMAX-пути методом Дейкстры (критерий узкого места).
 * @details Программа минимизирует максимальный вес ребра на пути между узлами 1 и 6.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

const int INF = INT_MAX;

/**
 * @brief Модифицированный алгоритм Дейкстры для поиска MINMAX-пути.
 * @param n Количество вершин.
 * @param matrix Матрица смежности с весами дуг.
 * @param start Начальный узел (0).
 * @param end Целевой узел (5).
 */
void findMinMaxPath(int n, const std::vector<std::vector<int>>& matrix, int start, int end) {
    std::vector<int> T(n, INF); // Метки вершин
    std::vector<bool> fixed(n, false); // Постоянные (зафиксированные) метки
    std::vector<int> parent(n, -1);

    T[start] = 0; // Инициализация стартовой вершины

    for (int i = 0; i < n; ++i) {
        // Находим вершину с минимальной меткой среди незафиксированных
        int u = -1;
        int min_val = INF;
        for (int v = 0; v < n; ++v) {
            if (!fixed[v] && T[v] < min_val) {
                min_val = T[v];
                u = v;
            }
        }

        if (u == -1 || u == end) break;
        fixed[u] = true;

        // Релаксация дуг по критерию MINMAX
        for (int v = 0; v < n; ++v) {
            if (!fixed[v] && matrix[u][v] != INF) {
                int max_edge = std::max(T[u], matrix[u][v]);
                if (max_edge < T[v]) {
                    T[v] = max_edge;
                    parent[v] = u;
                }
            }
        }
    }

    std::cout << "=== РЕЗУЛЬТАТ РАСЧЕТА ЗАДАЧИ 2 ===\n";
    std::cout << "Минимально возможный вес узкого места: " << T[end] << "\n";

    std::vector<int> path;
    for (int curr = end; curr != -1; curr = parent[curr]) {
        path.push_back(curr + 1);
    }
    std::reverse(path.begin(), path.end());

    std::cout << "Оптимальный MINMAX-путь: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] << (i + 1 < path.size() ? " -> " : "");
    }
    std::cout << "\n==================================\n";
}

int main() {
    int n = 6;
    std::vector<std::vector<int>> matrix = {
        {INF, 3,   10,  INF, 20,  INF},
        {INF, INF, 5,   6,   INF, 9  },
        {INF, INF, INF, INF, 3,   8  },
        {INF, INF, INF, INF, 6,   10 },
        {INF, INF, INF, INF, INF, 8  },
        {INF, INF, INF, INF, INF, INF}
    };

    findMinMaxPath(n, matrix, 0, 5);
    return 0;
}
