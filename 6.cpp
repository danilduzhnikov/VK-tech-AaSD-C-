/*
Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль

Требования: к дополнительной памяти: O(1). 
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition. 
Рекурсия запрещена. 
Решение должно поддерживать передачу функции сравнения снаружи.


Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i

6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”. 
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

In
10
1 2 3 4 5 6 7 8 9 10

Out
2
6
10
*/

#include <iostream>

// Компаратор 
template <typename T>
struct DefaultComparator {
    bool operator()(const T& left, const T& right) const {
        return left < right;
    }
};

// Функция выбора опорного элемента (медиана трех)
template <typename T>
size_t selectPivot(T* data, size_t l, size_t r) {
    // SelcetPivot недопустим
    if (l >= r) {
        throw std::invalid_argument("Invalid range for selectPivot");
    }
    size_t mid = (l + r - 1) / 2;

    if (data[l] < data[mid]) {
        if (data[r - 1] < data[l])
            return l;
        else if (data[r - 1] < data[mid])
            return r - 1;
        else
            return mid;
    }
    else {
        if (data[r - 1] < data[mid])
            return mid;
        else if (data[r - 1] < data[l])
            return r - 1;
        else
            return l;
    }
}

// Реализация partition
template <typename T, typename Comparator = DefaultComparator<T>>
size_t partition(T* data, size_t l, size_t r, Comparator comp = Comparator()) {
    size_t pivotIndex = selectPivot(data, l, r);
    std::swap(data[pivotIndex], data[r - 1]);
    T pivot = data[r - 1];

    size_t i = l;
    for (size_t j = l; j < r - 1; ++j) {
        if (comp(data[j], pivot)) {
            std::swap(data[i], data[j]);
            ++i;
        }
    }
    std::swap(data[i], data[r - 1]);
    return i;
}

// Поиск k-ой порядковой статистики
template <typename T, typename Comparator = DefaultComparator<T>>
T findKStatistics(T* data, size_t l, size_t r, size_t k, Comparator comp = Comparator()) {
    while (l < r) {
        size_t pivotPos = partition(data, l, r, comp);
        if (pivotPos == k)
            return data[pivotPos];
        else if (pivotPos > k)
            r = pivotPos;
        else
            l = pivotPos + 1;
    }
    return data[l];
}

int main() {
    size_t n;
    std::cin >> n;

    int* numbers = new int[n];

    for (size_t i = 0; i < n; ++i)
        std::cin >> numbers[i];

    // 10% перцентиль, медиана, 90% перцентиль
    size_t k10 = (n + 9) / 10 - 1;
    size_t k50 = n / 2;
    size_t k90 = (n * 9 + 9) / 10;

    int perc10 = findKStatistics(numbers, 0, n, k10);
    int median = findKStatistics(numbers, 0, n, k50);
    int perc90 = findKStatistics(numbers, 0, n, k90);

    std::cout << perc10 << "\n";
    std::cout << median << "\n";
    std::cout << perc90 << "\n";

    delete[] numbers;

    return 0;
}
