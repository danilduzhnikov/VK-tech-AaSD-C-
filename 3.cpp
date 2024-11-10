/*
Реализовать очередь с динамическим зацикленным буфером.
Обрабатывать команды push back и pop front.

Формат ввода:
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.

a = 2 - pop front
a = 3 - push back

Если дана команда pop front, то число b - ожидаемое значение.
Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.

Формат вывода:
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы
одно ожидание не оправдалось, то напечатать NO.
*/

#include <iostream>
#include <cassert>
class Queue {
public:
    Queue(int initial_capacity = 4);
    ~Queue();
    void Enqueue(int Data);
    int Dequeue();
    int Size() const;
    bool IsEmpty() const;
    bool IsFull() const;

private:
    int* data;      //буфер
    int capacity;   //емкость буфера
    int head;
    int tail;
    int size;       //количество элементов в буфере

    void resize();
};

Queue::Queue(int initial_capacity) {
    data = new int[initial_capacity];
    capacity = initial_capacity;
    head = 0;
    tail = 0;
    size = 0;
}

Queue::~Queue() {
    delete[] data;
}

void Queue::Enqueue(int Data) {
    if (size == capacity) {
        resize();
    }
    data[tail] = Data;
    ++size;
    if (tail == capacity - 1) {
        tail = 0;
    }
    else {
        ++tail;
    }
}

int Queue::Dequeue() {
    if (size == 0) {
        return -1;
    }
    int return_data = data[head];
    if (head == capacity - 1) {
        head = 0;
    }
    else {
        ++head;
    }
    --size;
    return return_data;
}

void Queue::resize() {
    int k = 2;
    int new_capacity = capacity * k;
    int* resized_data = new int[new_capacity];

    if (head < tail) {
        for (int i = 0; i < size; ++i) {
            resized_data[i] = data[(head + i) % capacity];
        }
    }
    else {
        int i = 0;
        for (int j = head; j < capacity; ++j) {
            resized_data[i++] = data[j];
        }
        for (int j = 0; j < tail; ++j) {
            resized_data[i++] = data[j];
        }
    }

    delete[] data;
    data = resized_data;
    capacity = new_capacity;
    head = 0;
    tail = size;
}

int Queue::Size() const {
    return size;
}

bool Queue::IsEmpty() const {
    return size == 0;
}

bool Queue::IsFull() const {
    return size == capacity;
}


using std::cout;
using std::cin;

int main()
{   
    //количество операций
    int num;
    cin >> num;
    assert(num <= 1000000);

    int command, value;
    int result = true;
    
    Queue solution = Queue();

    for (int i = 0; i < num; ++i) {
        cin >> command >> value;

        if (command == 3) {
            solution.Enqueue(value);
        } else if (command == 2) {
            int dequeued = solution.Dequeue();
            if (dequeued != value) {
                result = false;
                break;
            }
        }
    }
    
    cout << (result ? "YES" : "NO") << std::endl;
    
    return 0;
}
