/*
 * Кобзев Антон АПО-11
 *
 * Задача № 2_1
 *
 * Обход дерева в порядке in-order
 *
 * Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N. Требуется построить
 * бинарное дерево, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево
 * с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
 * Выведите элементы в порядке in-order (слева направо). Рекурсия запрещена.
 */

#include <iostream>
#include <map>
#include <stack>

template<class T>
class BinaryTree {
 public:
  void Insert(T value);
  void PrintValuesInOrder();
 private:
  std::map<size_t, T> values;
  size_t GetRightSonIndex(size_t parent_index) const;
  size_t GetLeftSonIndex(size_t parent_index) const;
};

int main() {
  size_t n;
  std::cin >> n;
  BinaryTree<int> tree;
  for (size_t i = 0; i < n; i++) {
    int k;
    std::cin >> k;
    tree.Insert(k);
  }
  tree.PrintValuesInOrder();
  return 0;
}

template<class T>
void BinaryTree<T>::Insert(T value) {
  size_t root = 0;
  while (values.find(root) != values.end()) {
    if (values[root] > value)
      root = GetLeftSonIndex(root);
    else
      root = GetRightSonIndex(root);
  }
  values[root] = value;
}

template<class T>
size_t BinaryTree<T>::GetRightSonIndex(size_t parent_index) const {
  return 2 * parent_index + 2;
}

template<class T>
size_t BinaryTree<T>::GetLeftSonIndex(size_t parent_index) const {
  return 2 * parent_index + 1;
}

template<class T>
void BinaryTree<T>::PrintValuesInOrder() {
  std::stack<size_t> nodes;
  size_t current = 0;
  while (!nodes.empty() || values.find(current) != values.end()) {
    if (values.find(current) != values.end()) {
      nodes.push(current);
      current = GetLeftSonIndex(current);
    } else {
      current = nodes.top();
      nodes.pop();
      std::cout << values[current] << ' ';
      current = GetRightSonIndex(current);
    }
  }
}
