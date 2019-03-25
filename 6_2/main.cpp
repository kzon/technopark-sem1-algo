/*
 * Кобзев Антон АПО-11
 *
 * Задача № 6_2
 *
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 * Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции
 * с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
 * Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
 *
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */

#include <cassert>
#include <iostream>

int KthElement(int *arr, size_t n, size_t k);
size_t Partition(int *arr, size_t left, size_t right);
size_t GetPivotPosition(const int *arr, size_t left, size_t right);

int main() {
  size_t n, k;
  std::cin >> n >> k;
  assert(!std::cin.fail());
  assert(n > 0 && k < n);
  int *arr = new int[n];
  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
    assert(!std::cin.fail());
  }
  std::cout << KthElement(arr, n, k);
  delete[] arr;
  return 0;
}

int KthElement(int *arr, size_t n, size_t k) {
  assert(arr != nullptr);
  size_t left = 0, right = n, pivot_pos;
  do {
    pivot_pos = Partition(arr, left, right);
    if (pivot_pos < k)
      left = pivot_pos + 1;
    else if (pivot_pos > k)
      right = pivot_pos;
  } while (pivot_pos != k);
  return arr[k];
}

size_t Partition(int *arr, size_t left, size_t right) {
  assert(arr != nullptr);
  size_t pivot_pos = GetPivotPosition(arr, left, right);
  if (right - left < 2)
    return pivot_pos;
  std::swap(arr[pivot_pos], arr[right - 1]);
  pivot_pos = right - 1;
  int i = (int) right - 2, j = (int) right - 2;
  while (j >= 0) {
    if (arr[j] > arr[pivot_pos])
      std::swap(arr[i--], arr[j--]);
    else
      j--;
  }
  std::swap(arr[i + 1], arr[pivot_pos]);
  return (size_t) i + 1;
}

size_t GetPivotPosition(const int *arr, size_t left, size_t right) {
  assert(arr != nullptr);
  size_t medium = (left + right) / 2;
  right--;
  if (arr[left] > arr[right])
    return arr[medium] < arr[right] ? right : medium;
  return arr[medium] < arr[left] ? left : medium;
}