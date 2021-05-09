// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>
template<typename T>
class TPQueue {
  private:
    T *arr;          // массив с данными
    int size;        // максимальное количество элементов в очереди (размер массива)
    int begin,       // начало очереди
        end;         // конец очереди
    int count;       // счетчик элементов
  public:
    TQueue();          // конструктор по умолчанию
    ~TQueue();                 // деструктор
    void push(const T &); // добавить элемент в очередь
    T pop();              // удалить элемент из очереди
    T get() const;        // прочитать первый элемент
    bool isEmpty() const;      // пустая ли очередь?
    bool isFull() const;       // заполнен ли массив?
};
template<typename T>
TQueue<T>::TQueue() :
    size(100), begin(0), end(0), count(0) {
    arr = new T[size + 1];
}
template<typename T>
TQueue<T>::~TQueue() {
  delete [] arr;
}
template<typename T>
void TQueue<T>::push(const T & item) {
  // проверяем, ести ли свободное место в очереди
  assert( count < size );
  if (end != 0) {
      for (int i = end - 1; i > -1; --i) {
          if (arr[i].prior >= item.prior) {
              arr[i + 1] = item;
              continue;
          }
          if (arr[i].prior < item.prior) {
              arr[i + 1] = arr[i];
              if (i == 0)
                  arr[i] = item;
              continue;
          }
      }
  }
  else {
      arr[begin] = item;
  }
  count++;
  end++;
}
template<typename T>
T TQueue<T>::pop() {
  // проверяем, есть ли в очереди элементы
  assert(count > 0);
  T item = arr[begin++];
  count--;
  // проверка кругового заполнения очереди
  if (begin > size) {
      begin -= size + 1; // возвращаем begin на начало очереди
  }
  return item;
}
template<typename T>
T TQueue<T>::get() const {
  // проверяем, есть ли в очереди элементы
  assert(count > 0);
  return arr[begin];
}
template<typename T>
bool TQueue<T>::isEmpty() const {
  return count == 0;
}
template<typename T>
bool TQueue<T>::isFull() const {
  return count == size;
}
struct SYM {
  char ch;
  int  prior;
};
#endif // INCLUDE_TPQUEUE_H_
