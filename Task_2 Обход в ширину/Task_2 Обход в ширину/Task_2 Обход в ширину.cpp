#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

void bfs(int start_vertex, int& n, bool* visited, int** arr) {
    // Массив для имитации очереди
    int* queue = new int[n];
    int front = 0, back = 0;

    // Добавляем начальную вершину в очередь и отмечаем как посещённую
    queue[back++] = start_vertex;
    visited[start_vertex] = true;

    while (front < back) {
        int vertex = queue[front++];
        std::cout << (vertex + 1) << " ";

        for (int i = 0; i < n; ++i) {
            if (arr[vertex][i] == 1 && !visited[i]) {
                queue[back++] = i;
                visited[i] = true;
            }
        }
    }

    delete[] queue; // Освобождение памяти под массив-очередь
}

int main(int argc, char* argv[])
{
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
    int** arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }

    // Чтение значений в двумерный массив из файла
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input_file >> arr[i][j];
        }
    }

    // Запрашиваем начальную вершину для обхода
    int start_vertex;
    std::cout << "Введите начальную вершину для обхода (1-" << n << "): ";
    std::cin >> start_vertex;

    // Проверка корректности индекса
    while (start_vertex < 1 || start_vertex > n) {
        std::cout << "Неверный индекс! Введите число от 1 до " << n << ": ";
        std::cin >> start_vertex;
    }

    start_vertex -= 1;

    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    std::cout << "Порядок обхода вершин: ";
    bfs(start_vertex, n, visited, arr);

    // Очистка выделенной памяти
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] visited;

    return 0;
}
