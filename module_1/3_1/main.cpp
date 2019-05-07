/*
 * Кобзев Антон АПО-11
 *
 * Задача № 3_1
 *
 * Реализовать очередь с динамическим зацикленным буфером.
 * Обрабатывать команды push back и pop front.
 *
 * Формат ввода
 * В первой строке количество команд n. n ≤ 1000000.
 *
 * Каждая команда задаётся как 2 целых числа: a b.
 *
 * a = 2 - pop front
 * a = 3 - push back
 *
 * Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
 *
 * Формат вывода
 * Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 */

#include <iostream>
#include <stdexcept>
#include <cassert>

class Queue {
 public:
  ~Queue();

  void Enqueue(int data);
  int Dequeue();
  bool IsEmpty() const;
 private:
  size_t head = 0, tail = 0, size = 0, capacity = 0;
  int *values = nullptr;

  static const size_t kStartCapacity = 15;
};

const unsigned int
    kCommandCodePopFront = 2,
    kCommandCodePushBack = 3;

struct QueueCommand {
  unsigned int code;
  int argument;
};

void ReadCommands(QueueCommand *commands, size_t n);

bool IsValidCommandCode(unsigned int code);

bool ExecuteCommands(QueueCommand *commands, size_t n);

int main() {
  size_t n;
  std::cin >> n;
  assert(!std::cin.fail());
  assert(n != 0);
  auto *commands = new QueueCommand[n];
  ReadCommands(commands, n);
  bool is_execute_success = ExecuteCommands(commands, n);
  std::cout << (is_execute_success ? "YES" : "NO");

  delete[] commands;
  return 0;
}

Queue::~Queue() {
  delete[] values;
}

void Queue::Enqueue(int data) {
  if (size + 1 >= capacity) {
    size_t new_capacity = capacity == 0 ? Queue::kStartCapacity : capacity * 2;
    int *new_values = new int[new_capacity];
    if (head > tail) {
      for (size_t i = 0; i < tail; ++i)
        new_values[i] = values[i];
      for (size_t i = capacity - 1, j = new_capacity - 1; i >= head; --i, --j)
        new_values[j] = values[i];
      head += new_capacity - capacity;
    } else {
      for (size_t i = head; i < tail; ++i)
        new_values[i] = values[i];
    }
    capacity = new_capacity;
    delete[] values;
    values = new_values;
  }
  values[tail] = data;
  tail = (tail + 1) % capacity;
  size++;
}

int Queue::Dequeue() {
  if (IsEmpty())
    throw std::logic_error("Dequeue called on empty queue");
  int result = values[head];
  head = (head + 1) % capacity;
  size--;
  return result;
}

bool Queue::IsEmpty() const {
  return size == 0;
}

void ReadCommands(QueueCommand *commands, size_t n) {
  assert(commands != nullptr);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> commands[i].code >> commands[i].argument;
    assert(!std::cin.fail() && IsValidCommandCode(commands[i].code));
  }
}

bool IsValidCommandCode(unsigned int code) {
  return code == kCommandCodePushBack || code == kCommandCodePopFront;
}

bool ExecuteCommands(QueueCommand *commands, size_t n) {
  assert(commands != nullptr);
  Queue queue;
  int expected;
  for (size_t i = 0; i < n; ++i) {
    if (commands[i].code == kCommandCodePopFront) {
      expected = queue.IsEmpty() ? -1 : queue.Dequeue();
      if (commands[i].argument != expected) return false;
    } else if (commands[i].code == kCommandCodePushBack) {
      queue.Enqueue(commands[i].argument);
    }
  }
  return true;
}