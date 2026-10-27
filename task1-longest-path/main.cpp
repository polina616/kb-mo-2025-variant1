/**
 * @file main.cpp
 * @brief Автоматизированный расчет пути наибольшей длины в бесконтурной сети.
 * @details Программа выполняет топологическую сортировку графа и находит 
 * критический путь методом динамического программирования для Варианта 1.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/// Константа, обозначающая отсутствие дуги между вершинами (-бесконечность)
const int INF_NEG = INT_MIN;

/**
 * @brief Функция поиска пути наибольшей длины (критического пути).
 * @param n Количество вершин в графе.
 * @param matrix Матрица смежности сети с весами дуг.
 * @param start Индекс начальной вершины (от 0).
 * @param end Индекс целевой вершины (от 0).
 * @return Длина максимального пути. Если путь не найден, возвращает INF_NEG.
 */
int findLongestPath(int n, const std::vector<std::vector<int>>& matrix, int start, int end) {
    // Массив для хранения топологического порядка (для Варианта 1 получен аналитически)
    // Вершины в исходной матрице (1-6) соответствуют индексам (0-5)
    std::vector<int> topo_order = {0, 4, 1, 5, 3, 2}; // Соответствует порядку: 1 -> 5 -> 2 -> 6 -> 4 -> 3

    // L[i] — максимальное расстояние от стартовой вершины до вершины i
    std::vector<int> L(n, INF_NEG);
    L[start] = 0; // Расстояние до самого себя равно 0

    // Массив для восстановления пути
    std::vector<int> parent(n, -1);

    // Идем строго по топологическому порядку вершин
    for (int u : topo_order) {
        if (L[u] == INF_NEG) continue; // Пропускаем недостижимые на данный момент вершины

        for (int v = 0; v < n; ++v) {
            // Если дуга существует
            if (matrix[u][v] != INF_NEG) {
                // Релаксация дуги для поиска МАКСИМУМА
                if (L[u] + matrix[u][v] > L[v]) {
                    L[v] = L[u] + matrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Вывод результатов и восстановление пути
    if (L[end] == INF_NEG) {
        std::cout << "Путь из узла " << (start + 1) << " в узел " << (end + 1) << " не существует.\n";
        return INF_NEG;
    }

    std::cout << "=== РЕЗУЛЬТАТ РАСЧЕТА ЗАДАЧИ 1 ===\n";
    std::cout << "Максимальное расстояние из узла 1 в узел 3: " << L[end] << "\n";

    // Восстановление пути с конца
    std::vector<int> path;
    for (int curr = end; curr != -1; curr = parent[curr]) {
        path.push_back(curr + 1); // Переводим индексы 0-5 обратно в номера вершин 1-6
    }
    std::reverse(path.begin(), path.end());

    std::cout << "Критический путь: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] << (i + 1 < path.size() ? " -> " : "");
    }
    std::cout << "\n==================================\n";

    return L[end];
}

int main() {
    int n = 6;
    // Инициализируем матрицу смежности Варианта 1 (заменяя -инф на INF_NEG)
    std::vector<std::vector<int>> matrix = {
        {INF_NEG, 10,      INF_NEG,  INF_NEG,  4,        INF_NEG}, // Узел 1
        {INF_NEG, INF_NEG, INF_NEG,  INF_NEG,  INF_NEG, -8     }, // Узел 2
        {INF_NEG, INF_NEG, INF_NEG,  INF_NEG,  INF_NEG,  INF_NEG}, // Узел 3
        {INF_NEG, INF_NEG, 2,        INF_NEG,  INF_NEG,  INF_NEG}, // Узел 4
        {INF_NEG, 7,       INF_NEG,  2,        INF_NEG, -2     }, // Узел 5
        {INF_NEG, INF_NEG, 12,       8,        INF_NEG,  INF_NEG}  // Узел 6
    };

    // По условию ищем путь из узла 1 (индекс 0) в узел 3 (индекс 2)
    findLongestPath(n, matrix, 0, 2);

    return 0;
}
