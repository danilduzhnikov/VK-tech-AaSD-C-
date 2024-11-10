#include <iostream>
#include <cstring>

struct User {
    int start;
    int end;

    bool operator<=(const User& r) const {
        if (r.end == end) {
            return (this->start <= r.start);
        }
        else {
            return (this->end <= r.end);
        }
    }
};

// Компаратор по умолчанию для сортировки
template <class T>
struct DefaultComparator {
    bool operator()(const T& left, const T& right) const {
        return left <= right;
    }
};

// Слияние двух отсортированных частей массива
template <typename T, typename Comparator = DefaultComparator<T>>
void Merge(T* left_arr, size_t left_size, T* right_arr, size_t right_size, T* result, Comparator comp = Comparator()) {
    size_t left_index = 0, right_index = 0, result_index = 0;

    while (left_index < left_size && right_index < right_size) {
        if (comp(left_arr[left_index], right_arr[right_index])) {
            result[result_index++] = left_arr[left_index++];
        }
        else {
            result[result_index++] = right_arr[right_index++];
        }
    }

    // Копируем оставшиеся элементы из левой или правой части
    if (left_index < left_size) {
        std::memcpy(&result[result_index], &left_arr[left_index], sizeof(T) * (left_size - left_index));
    }
    else if (right_index < right_size) {
        std::memcpy(&result[result_index], &right_arr[right_index], sizeof(T) * (right_size - right_index));
    }
}

template <typename T, typename Comparator = DefaultComparator<T>>
void MergeSort(T* arr, size_t size, Comparator comp = Comparator()) {
    if (size <= 1) return;

    size_t left_size = size / 2;
    size_t right_size = size - left_size;

    MergeSort(arr, left_size, comp);
    MergeSort(arr + left_size, right_size, comp);

    T* temp = new T[size];
    Merge(arr, left_size, arr + left_size, right_size, temp, comp);
    std::memcpy(arr, temp, sizeof(T) * size);

    delete[] temp;
}

int main() {
    int n;
    std::cin >> n;

    // Создаем массив покупателей
    User* users = new User[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> users[i].start >> users[i].end;
    }

    // Сортируем пользователей по времени их пребывания в магазине
    MergeSort(users, n);

    int counter = 0;   // Счетчик минимального количества показов рекламы
    int lastAdTime1 = -1, lastAdTime2 = -1; // Последние моменты времени показа рекламы

    for (int i = 0; i < n; ++i) {
        User currentUser = users[i];

        if (currentUser.start > lastAdTime2) {
            // Если текущий пользователь не покрывается существующими рекламами
            lastAdTime1 = currentUser.end - 1;
            lastAdTime2 = currentUser.end;
            counter += 2;
        }
        else if (currentUser.start == lastAdTime2 || (currentUser.start > lastAdTime1 && currentUser.end > lastAdTime2)) {
            // Если текущий пользователь покрывается только одной из последних реклам или его время начала равно последнему времени показа рекламы
            lastAdTime1 = lastAdTime2;
            lastAdTime2 = currentUser.end;
            counter++;
        }
        else if (currentUser.start > lastAdTime1 && currentUser.start < lastAdTime2) {
            // Если текущий пользователь частично пересекается с последним временем показа рекламы
            lastAdTime1 = currentUser.end;
            counter++;
        }
    }

    std::cout << counter << std::endl;
    delete[] users;

}
