/*
 * Кобзев Антон АПО-11
 *
 * Задача № 5_3
 *
 * На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов
 * каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
 * N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 10^9].
 */

#include <iostream>
#include <cassert>

struct Point {
  size_t x;
  bool is_begin;
  bool operator<(const Point &) const;
};

void ReadPoints(Point *points, size_t n);

size_t FindPaintedSum(Point *points, size_t n);

template<typename T>
void Sort(T *data, size_t n);

template<typename T>
void MergeSortHelper(T *data, T *result, size_t left, size_t right);

int main() {
  size_t n;
  std::cin >> n;
  assert(!std::cin.fail());
  assert(n > 0);
  size_t number_of_points = n * 2;
  auto *points = new Point[number_of_points];
  ReadPoints(points, number_of_points);
  size_t sum = FindPaintedSum(points, number_of_points);
  std::cout << sum << std::endl;
  delete[] points;
  return 0;
}

void ReadPoints(Point *points, size_t n) {
  assert(points != nullptr);
  for (size_t i = 0; i < n; i += 2) {
    size_t l, r;
    std::cin >> l >> r;
    assert(!std::cin.fail());
    points[i] = Point{l, true};
    points[i + 1] = Point{r, false};
  }
}

size_t FindPaintedSum(Point *points, size_t n) {
  assert(points != nullptr);
  Sort(points, n);
  size_t layers = 0, sum = 0;
  for (size_t i = 0; i < n - 1; ++i) {
    layers += points[i].is_begin ? 1 : -1;
    if (layers > 0)
      sum += points[i + 1].x - points[i].x;
  }
  return sum;
}

bool Point::operator<(const Point &other) const {
  return this->x < other.x;
}

template<typename T>
void Sort(T *data, size_t n) {
  assert(data != nullptr);
  if (n < 2) return;
  T *result = new T[n];
  MergeSortHelper(data, result, 0, n);
  delete[] result;
}

template<typename T>
void MergeSortHelper(T *data, T *result, size_t left, size_t right) {
  if (right - left < 2) return;
  assert(data != nullptr && result != nullptr);
  size_t medium = (left + right) / 2;
  MergeSortHelper(data, result, left, medium);
  MergeSortHelper(data, result, medium, right);
  size_t i = left, j = medium, k = left;
  while (i < medium || j < right) {
    if (j >= right || (i < medium && data[i] < data[j]))
      result[k++] = data[i++];
    else
      result[k++] = data[j++];
  }
  for (i = left; i < right; ++i)
    data[i] = result[i];
}
