#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

bool dfs(int vertex, int parent, int& n, bool* visited, int** arr) {
    // Отмечаем текущую вершину как посещённую
    visited[vertex] = true;

    // Проходим по всем вершинам, смежным с текущей
    for (int i = 0; i < n; ++i) {
        if (arr[vertex][i] == 1) { // Если есть ребро
            if (!visited[i]) { // Если вершина не посещена
                // Рекурсивно вызываем DFS для смежной вершины
                if (dfs(i, vertex, n, visited, arr)) {
                    return true; // Найден цикл
                }
            }
            else if (i != parent) { // Если смежная вершина уже посещена и не является родительской
                return true; // Найден цикл
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n; // количество вершин графа
    std::ifstream input_file("input.txt");

    // Чтение количества вершин из файла
    input_file >> n;
    if (!input_file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    // Создание двумерного массива для графа
    int** arr = new int* [n]; // Массив указателей на строки
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n]; // Выделение памяти для каждой строки
    }

    // Чтение значений в двумерный массив из файла
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input_file >> arr[i][j];
        }
    }

    // Массив для отслеживания посещённых вершин
    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    // Проверка на наличие цикла
    bool hasCycle = false;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) { // Запускаем DFS только из непосещённых вершин
            if (dfs(i, -1, n, visited, arr)) { // -1 означает, что начальной вершине нет родителя
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle) {
        std::cout << "Цикл найден в графе." << std::endl;
    }
    else {
        std::cout << "Цикл в графе не найден." << std::endl;
    }

    // Очистка выделенной памяти
    for (int i = 0; i < n; i++) {
        delete[] arr[i]; // Освобождение памяти для каждой строки
    }
    delete[] arr; // Освобождение памяти для массива указателей
    delete[] visited;

    return 0;
}
