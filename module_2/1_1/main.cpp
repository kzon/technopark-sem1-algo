#include <string>
#include <vector>
#include <iostream>

// Простое число, примерно равное количеству символов во входном алфавите
const size_t STRING_HASH_A = 31;

using HashType = long long;

template<class T, HashType HashFunction(const T &, size_t, size_t)>
class HashTable {
 public:
  HashTable() : table(START_TABLE_SIZE), size(START_TABLE_SIZE) {};
  bool Insert(const T &data);
  bool Has(const T &data);
  bool Delete(const T &data);
 private:
  std::vector<T> table;
  size_t size;
  static const size_t START_TABLE_SIZE = 8;
};

HashType StringHashFunction(const std::string &data, size_t i, size_t m);

template<class T, HashType HashFunction(const T &, size_t, size_t)>
std::string ExecuteCommand(const std::string &command, const HashTable<T, HashFunction> &hast_table);

int main() {
  HashTable<std::string, StringHashFunction> hast_table;
  std::string command;
  while (std::cin) {
    std::getline(std::cin, command);
    std::cout << ExecuteCommand(command, hast_table) << '\n';
  }
  return 0;
}

template<class T, HashType HashFunction(const T &, size_t, size_t)>
std::string ExecuteCommand(const std::string &command, const HashTable<T, HashFunction> &hast_table) {
  return "h(" + command + ") = " + std::to_string(HashFunction(command, 0, 8));
}

/*
 * data - ключ
 * i - номер пробы
 * m - максимальное значение хеша
 */
HashType StringHashFunction(const std::string &data, size_t i, size_t m) {
  if (i == 0) {
    HashType hash = 0, a_power = 1;
    for (const char c : data) {
      hash += (c - 'a' + 1) * a_power;
      a_power *= STRING_HASH_A;
    }
    return hash;
  }
  return StringHashFunction(data, i - 1, m) + i % m;
}

template<class T, HashType HashFunction(const T &, size_t, size_t)>
bool HashTable<T, HashFunction>::Insert(const T &data) {
  return true;
}

template<class T, HashType HashFunction(const T &, size_t, size_t)>
bool HashTable<T, HashFunction>::Has(const T &data) {
  return false;
}

template<class T, HashType HashFunction(const T &, size_t, size_t)>
bool HashTable<T, HashFunction>::Delete(const T &data) {
  return false;
}