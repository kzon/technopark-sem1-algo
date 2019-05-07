/*
 * Кобзев Антон АПО-11
 *
 * Задача № 7_1
 *
 * MSD для строк.
 * Дан массив строк. Количество строк не больше 105. Отсортировать массив методом
 * поразрядной сортировки MSD по символам. Размер алфавита - 256 символов.
 * Последний символ строки = ‘\0’.
 */

#include <cassert>
#include <iostream>
#include <string>

#define ALPHABET_SIZE 256

template<typename T>
class Vector {
 public:
  ~Vector();
  void PushBack(T value);
  size_t Size() const;
  bool IsEmpty() const;
  T &operator[](size_t i);
 private:
  T *values = nullptr;
  size_t size = 0;
  size_t capacity = 0;

  static const size_t kStartCapacity = 5;

  void Grow();
  void Reserve(size_t n);
};

void MsdSort(Vector<std::string> &strings);
void MsdSortHelper(Vector<std::string> &strings,
                   size_t left,
                   size_t right,
                   size_t char_pos,
                   std::string *strings_copy_buffer);

int main() {
  Vector<std::string> strings;
  std::string buffer;
  while (std::getline(std::cin, buffer))
    strings.PushBack(buffer);
  MsdSort(strings);
  for (size_t i = 0; i < strings.Size(); i++)
    std::cout << strings[i] << '\n';
  return 0;
}

template<typename T>
void Vector<T>::PushBack(T value) {
  if (this->size + 1 >= this->capacity)
    Grow();
  this->values[this->size++] = value;
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

void MsdSort(Vector<std::string> &strings) {
  auto *strings_copy_buffer = new std::string[strings.Size()];
  MsdSortHelper(strings, 0, strings.Size(), 0, strings_copy_buffer);
  delete[] strings_copy_buffer;
}

void MsdSortHelper(Vector<std::string> &strings,
                   size_t left,
                   size_t right,
                   size_t char_pos,
                   std::string *strings_copy_buffer) {
  if (right - left < 2)
    return;
  size_t counts[ALPHABET_SIZE] = {0};
  for (size_t i = left; i < right; i++) {
    char c = (char_pos >= strings[i].length()) ? (char) '\0' : strings[i][char_pos];
    counts[c]++;
  }

  size_t sum = 0;
  for (size_t &count : counts) {
    size_t tmp = count;
    count = sum;
    sum += tmp;
  }

  for (size_t i = left; i < right; i++) {
    char c = (char_pos >= strings[i].length()) ? (char) '\0' : strings[i][char_pos];
    strings_copy_buffer[counts[c]++] = strings[i];
  }
  for (size_t i = left, j = 0; i < right; i++, j++)
    strings[i] = strings_copy_buffer[j];

  for (size_t i = 1; i < ALPHABET_SIZE; i++)
    if (counts[i] - counts[i - 1] >= 2)
      MsdSortHelper(strings, left + counts[i - 1], left + counts[i], char_pos + 1, strings_copy_buffer);
}