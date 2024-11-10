/*
    Даны два массива неубывающих целых чисел, упорядоченные по возрастанию.
    A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение.

    Требования: Время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.
    В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска
    элемента B[i-1]. Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон
    для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.

    Ввод:
    5
    3
    1 2 3 4 5
    1 3 5

    Вывод:
    1 3 5
*/

#include <iostream>
#include <cassert>

using std::cout;
using std::cin;
using std::endl;
using std::min;

// Бинарный поиск в диапазоне [left, right]
int BinarySearch(const int* arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

// Экспоненциальный поиск для определения диапазона
int ExponentialSearch(const int* arr, int size, int start, int target) {
    // Если первый элемент уже больше или равен target
    if (arr[start] >= target) {
        return start;
    }

    // Находим верхнюю границу для бинарного поиска
    int bound = 1;
    while (start + bound < size && arr[start + bound] < target) {
        bound *= 2;
    }

    // Выполняем бинарный поиск в найденном диапазоне
    int left = start + bound / 2;
    int right = min(start + bound, size - 1);
    return BinarySearch(arr, left, right, target);
}

int main() {
    // Ввод длин массивов
    int n, m;
    cin >> n >> m;

    // Проверка корректности входных данных
    assert(n >= m && n <= 10000);

    // Создание массивов
    int* arr1 = new int[n];
    int* arr2 = new int[m];

    // Ввод массива 1
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
    }

    // Ввод массива 2
    for (int i = 0; i < m; i++) {
        cin >> arr2[i];
    }

    // Ищем пересечение массивов
    int ind = 0;
    for (int i = 0; i < m; i++) {
        // Экспоненциальный поиск для arr2[i]
        ind = ExponentialSearch(arr1, n, ind, arr2[i]);

        // Если найденный элемент совпадает с arr2[i], выводим его
        if (ind < n && arr1[ind] == arr2[i]) {
            cout << arr2[i] << " ";
        }

        // Прерываем, если прошли весь массив arr1
        if (ind >= n) {
            break;
        }
    }

    // Освобождение памяти
    delete[] arr1;
    delete[] arr2;

    return 0;
}
