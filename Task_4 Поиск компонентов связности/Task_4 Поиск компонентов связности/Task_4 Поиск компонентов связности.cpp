#include <iostream>
#include <fstream>
#include <windows.h>

void dfs(int vertex, int n, bool* visited, int** arr, int* components, int component_num) {
    // Отмечаем текущую вершину как посещенную и присваиваем номер компонента
    visited[vertex] = true;
    components[vertex] = component_num;

    // Проходим по всем вершинам, смежным с текущей
    for (int i = 0; i < n; ++i) {
        if (arr[vertex][i] == 1 && !visited[i]) {
            dfs(i, n, visited, arr, components, component_num);
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n; // Количество вершин графа
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

    input_file.close();

    // Массив для отслеживания посещённых вершин и компоненты связности
    bool* visited = new bool[n];
    int* components = new int[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        components[i] = 0; // Инициализация номера компонента
    }

    int component_num = 1;  // Начальный номер компонента

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {  // Если вершина не посещена, это новая компонента
            dfs(i, n, visited, arr, components, component_num); // Вызываем dfs
            component_num++;  // Увеличиваем номер компонента для следующей компоненты
        }
    }

    // Вывод результата
    std::cout << "Количество компонентов связности: " << component_num - 1 << std::endl;
    std::cout << "Номера компонентов связности для каждой вершины:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "Вершина " << (i + 1) << ": компонент " << components[i] << std::endl;
    }

    // Очистка выделенной памяти
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] visited;
    delete[] components;

    return 0;
}
