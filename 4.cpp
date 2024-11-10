/*
    Решение задачи предполагает использование кучи, реализованной в виде шаблонного класса.
    Решение должно поддерживать передачу функции сравнения снаружи.
    Куча должна быть динамической.

    Топ K пользователей из лога
    Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
    Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их
    в порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
    Требования: время работы O(N * logK), где N - кол-во пользователей. Ограничение на размер кучи O(K).
    Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
    Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости

    Ввод:           Вывод:
    3 3             80
    100 36          1
    80 3            100
    1 5
*/
#include <iostream>
using std::swap;
using std::cin;
using std::cout;
using std::endl;

template <class T>
struct DefaultComparator {
    bool operator()(const T& l, const T& r) {
        return l > r;
    }
};

template <class T, class Comparator = DefaultComparator<T>>
class Heap {
public:
    Heap();
    ~Heap();

    Heap(const Heap&) = delete;
    Heap(Heap&&) = delete;
    Heap& operator=(const Heap&) = delete;
    Heap& operator=(Heap&&) = delete;

    const T& Top() const;
    void Pop();
    void Push(const T& value);

    size_t Size() const;
    bool Empty() const;

private:
    void Sift_up(size_t index);
    void Sift_down(int index);

    void Heapify();
    void Grow();

    T* buffer;
    size_t count;
    size_t size;

    Comparator comp;
};

template<typename T, typename Comparator>
Heap<T, Comparator>::Heap() :
    buffer(new T[3]),
    count(0),
    size(3),
    comp(comp) {}

template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap() {
    delete[] buffer;
}

template<typename T, typename Comparator>
const T& Heap<T, Comparator>::Top() const {
    return buffer[0];
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::Pop() {
    if (count <= 0)
        return;
    count--;
    buffer[0] = buffer[count];
    Sift_down(0);
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::Push(const T& value) {
    if (count >= size) {
        Grow();
    }
    buffer[count] = value;
    count++;
    Sift_up(count - 1);
}

template<typename T, typename Comparator>
size_t Heap<T, Comparator>::Size() const {
    return count;
}

template<typename T, typename Comparator>
bool Heap<T, Comparator>::Empty() const {
    return count == 0;
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::Sift_up(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (comp(buffer[index], buffer[parent]))
            return;
        std::swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::Sift_down(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (right < (int)Size() && comp(buffer[largest], buffer[right]))
        largest = right;
    if (left < (int)Size() && comp(buffer[largest], buffer[left]))
        largest = left;
    if (largest != index) {
        std::swap(buffer[index], buffer[largest]);
        Sift_down(largest);
    }
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::Heapify() {
    if (count <= 1) return;
    for (int i = (count / 2) - 1; i >= 0; i--)
        Sift_down(i);
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::Grow() {
    size *= 2;
    T* new_buffer = new T[size];
    for (int i = 0; i < (int)count; i++) {
        new_buffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = new_buffer;
}

struct User {
    int id;
    int visits;
    bool operator>(const User& r) const {
        return (this->visits > r.visits);
    }
    bool operator<(const User& r) const {
        return (this->visits < r.visits);
    }
};

int main() {
    int N, K;
    std::cin >> N >> K;
    if (N == 0 || K == 0)
        return 0;

    // Создаем людей
    User* users = new User[N];
    for (int i = 0; i < N; i++) {
        std::cin >> users[i].id >> users[i].visits;
    }

    // Создаем очередь
    Heap<User> min_heap;
    for (int i = 0; i < N; i++) {
        if (i >= K) {
            min_heap.Push(users[i]);
            min_heap.Pop();
        }
        else {
            min_heap.Push(users[i]);
        }
    }

    // Выводим ответ
    int output_size = (K < N) ? K : N;
    for (int i = 0; i < output_size; i++) {
        std::cout << min_heap.Top().id << " ";
        min_heap.Pop();
    }
    delete[] users;
    return 0;
}


