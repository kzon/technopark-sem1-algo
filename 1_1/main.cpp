/*
 * Кобзев Антон АПО-11
 *
 * Задача № 1_1
 *
 * Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 * Необходимо найти первую пару индексов i0 и j0, i0 ≤ j0, такую что
 * A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
 * Время работы - O(n). n ≤ 100000.
 */

#include <cassert>
#include <iostream>
#include <algorithm>

template<typename T>
void ReadArray(T *arr, size_t n);

template<typename T>
void PrintArray(T *arr, size_t n);

void FindMaxSum(int *a, int *b, size_t n, size_t *i0, size_t *j0);

int main() {
  size_t n;
  std::cin >> n;
  assert(!std::cin.fail());
  assert(n > 0);
  auto *a = new int[n];
  auto *b = new int[n];
  ReadArray(a, n);
  ReadArray(b, n);
  size_t i0 = 0, j0 = 0;
  FindMaxSum(a, b, n, &i0, &j0);
  std::cout << i0 << ' ' << j0;

  delete[] a;
  delete[] b;
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

void FindMaxSum(int *a, int *b, size_t n, size_t *i0, size_t *j0) {
  assert(a != nullptr && b != nullptr && n > 0 &&
      i0 != nullptr && j0 != nullptr);
  int max_sum = a[n - 1] + b[n - 1], prev_step_max_sum = max_sum;
  size_t prev_step_max_sum_index = n - 1;
  *i0 = *j0 = n - 1;
  for (size_t i = n - 2; i < n; --i) {
    int current_step_max_sum = std::max(a[i] + b[i], prev_step_max_sum + a[i] - a[i + 1]);
    if (current_step_max_sum >= max_sum) {
      max_sum = current_step_max_sum;
      if (current_step_max_sum == a[i] + b[i]) {
        *i0 = *j0 = i;
      } else {
        *i0 = i;
        *j0 = prev_step_max_sum_index;
      }
    }

    prev_step_max_sum = current_step_max_sum;
    if (current_step_max_sum == a[i] + b[i])
      prev_step_max_sum_index = i;
  }
}
