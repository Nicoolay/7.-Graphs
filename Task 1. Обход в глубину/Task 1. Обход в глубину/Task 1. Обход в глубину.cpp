#include <iostream>
#include <string>
#include <windows.h>
#include <fstream> 

void dfs(int vertex, int& n, bool* visited, int** arr) {
    // Отмечаем текущую вершину как посещенную и выводим её индекс
    visited[vertex] = true;
    std::cout << (vertex + 1) << " ";

    // Проходим по всем вершинам, смежным с текущей
    for (int i = 0; i < n; ++i) {
        if (arr[vertex][i] == 1 && !visited[i]) {
            dfs(i, n, visited, arr);
        }
    }
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
    bool* visited = new bool[n];
    // Инициализируем массив посещенных вершин значениями false
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    std::cout << "Порядок обхода вершин: ";

    dfs(0, n, visited, arr);

    // Очистка выделенной памяти
    for (int i = 0; i < n; i++) {
        delete[] arr[i]; // Освобождение памяти для каждой строки
    }
    delete[] arr; // Освобождение памяти для массива указателей
    delete[] visited;
    return 0;
}
