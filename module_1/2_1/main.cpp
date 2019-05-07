/*
 * Кобзев Антон АПО-11
 *
 * Задача № 2_1
 *
 * Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A,
 * равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n.
 * Время работы поиска k для каждого элемента B[i]: O(log(k)).
 * n, m ≤ 10000. В первой строчке записаны числа n и m. Во второй и третьей массивы A и B соответственно.
 */

#include <cassert>
#include <iostream>

template<typename T>
void ReadArray(T *arr, size_t n);

template<typename T>
void PrintArray(T *arr, size_t n);

void SearchArray(int *a, int *b, size_t *result, size_t n, size_t m);

void SearchInterval(const int *a, size_t n, int elem, size_t *left_result, size_t *right_result);

size_t SearchEqualOrLarger(const int *a, size_t n, int elem, size_t left, size_t right);

int main() {
  size_t n, m;
  std::cin >> n >> m;
  assert(!std::cin.fail());
  assert(n > 0 && m > 0);
  auto *a = new int[n];
  auto *b = new int[m];
  auto *result = new size_t[m];
  ReadArray(a, n);
  ReadArray(b, m);
  SearchArray(a, b, result, n, m);
  PrintArray(result, m);

  delete[] a;
  delete[] b;
  delete[] result;
  return 0;
}

template<typename T>
void ReadArray(T *arr, size_t n) {
  assert(arr != nullptr);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
    assert(!std::cin.fail());
  }
}

template<typename T>
void PrintArray(T *arr, size_t n) {
  assert(arr != nullptr);
  for (size_t i = 0; i < n; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
}

void SearchArray(int *a, int *b, size_t *result, size_t n, size_t m) {
  assert(a != nullptr && b != nullptr && result != nullptr);
  size_t left, right;
  for (size_t i = 0; i < m; ++i) {
    SearchInterval(a, n, b[i], &left, &right);
    result[i] = SearchEqualOrLarger(a, n, b[i], left, right);
  }
}

void SearchInterval(const int *a, size_t n, int elem, size_t *left_result, size_t *right_result) {
  assert(a != nullptr);
  size_t left = 0, right = 1;
  while (right < n && a[right] < elem) {
    size_t diff = right - left;
    left = right;
    right = left + 2 * diff;
  }
  *left_result = left;
  *right_result = right < n ? right : n - 1;
}

size_t SearchEqualOrLarger(const int *a, size_t n, int elem, size_t left, size_t right) {
  assert(a != nullptr);
  while (left < right) {
    size_t middle = (left + right) / 2;
    if (a[middle] < elem)
      left = middle + 1;
    else
      right = middle;
  }
  return a[left] >= elem ? left : n;
}
