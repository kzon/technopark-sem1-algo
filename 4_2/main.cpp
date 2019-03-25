/*
 * Кобзев Антон АПО-11
 *
 * Задача № 4_2
 *
 * Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы
 * двух чисел равно их сумме. Таким образом для нахождения суммы чисел 1,2,3 может потребоваться
 * разное время, в зависимости от порядка вычислений.
 * ((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) -> 2+3 + 5+1 = 11
 * Требуется написать программу, которая определяет минимальное время, достаточное
 * для вычисления суммы заданного набора чисел.
 *
 * Формат ввода
 * Вначале вводится n (n < 100) - количество чисел. Затем вводится n строк - значения чисел
 * (значение каждого числа не превосходит 1 000 000 000, сумма всех чисел не превосходит 2 * 1 000 000 000).
 */

#include <iostream>
#include <cassert>

template<typename T>
class Vector {
 public:
  ~Vector();
  void Assign(const T *values, size_t n);
  void PushBack(T value);
  void PopBack();
  size_t Size() const;
  bool IsEmpty() const;
  T &Front() const;
  T &Back() const;
  T &operator[](size_t i);
 private:
  T *values = nullptr;
  size_t size = 0;
  size_t capacity = 0;

  static const size_t kStartCapacity = 5;

  void Grow();
  void Reserve(size_t n);
};

template<typename T>
class MinHeap {
 public:
  explicit MinHeap(const T *values, size_t n);

  void Insert(T value);
  T ExtractMin();
  size_t Size() const;
 private:
  Vector<T> values;

  void SiftDown(size_t i);
  void SiftUp(size_t i);
};

size_t FindMinSum(const int *numbers, size_t n);

int main() {
  size_t n;
  std::cin >> n;
  assert(!std::cin.fail());
  assert(n > 0);
  int *numbers = new int[n];
  for (size_t i = 0; i < n; ++i) {
    std::cin >> numbers[i];
    assert(!std::cin.fail());
  }

  size_t min_sum = FindMinSum(numbers, n);
  std::cout << min_sum;

  delete[] numbers;
  return 0;
}

template<typename T>
void Vector<T>::Assign(const T *values, size_t n) {
  assert(values != nullptr && n > 0);
  Reserve(n);
  for (size_t i = 0; i < n; ++i)
    this->values[i] = values[i];
  this->size = n;
}

template<typename T>
void Vector<T>::PushBack(T value) {
  if (this->size + 1 >= this->capacity)
    Grow();
  this->values[this->size++] = value;
}

template<typename T>
void Vector<T>::PopBack() {
  assert(this->size > 0);
  this->size--;
}

template<typename T>
size_t Vector<T>::Size() const {
  return this->size;
}

template<typename T>
bool Vector<T>::IsEmpty() const {
  return this->size == 0;
}

template<typename T>
T &Vector<T>::Front() const {
  assert(this->size > 0);
  return this->values[0];
}

template<typename T>
T &Vector<T>::Back() const {
  assert(this->size > 0);
  return this->values[this->size - 1];
}

template<typename T>
T &Vector<T>::operator[](size_t i) {
  assert(i < this->size);
  return this->values[i];
}

template<typename T>
void Vector<T>::Grow() {
  size_t new_capacity = this->capacity == 0 ? Vector::kStartCapacity : this->capacity * 2;
  Reserve(new_capacity);
}

template<typename T>
void Vector<T>::Reserve(size_t n) {
  assert(n > 0);
  auto new_values = new T[n];
  for (size_t i = 0; i < this->size; ++i)
    new_values[i] = this->values[i];
  delete[] this->values;
  this->values = new_values;
  this->capacity = n;
}

template<typename T>
Vector<T>::~Vector() {
  delete[] this->values;
}

size_t FindMinSum(const int *numbers, size_t n) {
  MinHeap<int> heap(numbers, n);
  size_t min_sum = 0;
  while (heap.Size() > 1) {
    int first = heap.ExtractMin();
    int second = heap.ExtractMin();
    heap.Insert(first + second);
    min_sum += first + second;
  }
  return min_sum;
}

template<typename T>
MinHeap<T>::MinHeap(const T *values, size_t n) {
  assert(values != nullptr);
  this->values.Assign(values, n);
  for (size_t i = this->values.Size() / 2; i > 0; --i)
    SiftDown(i - 1);
}

template<typename T>
void MinHeap<T>::Insert(T value) {
  this->values.PushBack(value);
  SiftUp(this->values.Size() - 1);
}

template<typename T>
T MinHeap<T>::ExtractMin() {
  assert(!this->values.IsEmpty());
  T result = this->values.Front();
  this->values.Front() = this->values.Back();
  this->values.PopBack();
  if (!this->values.IsEmpty())
    SiftDown(0);
  return result;
}

template<typename T>
void MinHeap<T>::SiftDown(size_t i) {
  assert(i < this->values.Size());
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;
  size_t least = i;
  if (left < this->values.Size() && this->values[left] < this->values[least])
    least = left;
  if (right < this->values.Size() && this->values[right] < this->values[least])
    least = right;
  if (least != i) {
    std::swap(this->values[i], this->values[least]);
    SiftDown(least);
  }
}

template<typename T>
void MinHeap<T>::SiftUp(size_t i) {
  assert(i < this->values.Size());
  while (i > 0) {
    size_t parent = (i - 1) / 2;
    if (this->values[parent] < this->values[i])
      return;
    std::swap(this->values[parent], this->values[i]);
    i = parent;
  }
}

template<typename T>
size_t MinHeap<T>::Size() const {
  return this->values.Size();
}