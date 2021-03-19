# Пишем библиотеку для поиска информации в линейных структурах данных на языке С++

## Алгоритмы

Поиск:
1. Фибоначчи.

## Поиск Фибоначчи

Суть алгоритма:
Вычисление индекса с помощью последовательности Фибоначчи.

Сложность вычислений (худшая): **O(log n)**

Реализация на языке С++.

```C++
int i = 0;
int p = 0;
int q = 0;

bool stopFlag = false;
```

```C++
int GetFibonacciValue(int index) {

  int firstValue = 0;
  int secondValue = 1;

  for (int i = 0; i < index; i++) {

    int temp = secondValue;
    secondValue += firstValue;
    firstValue = temp;
  }

  return firstValue;
}
```

```C++
void Init() {

  int index = 0;

  while (GetFibonacciValue(index + 1) < data::size + 2) {

    index++;
  }

  int m = GetFibonacciValue(index + 1) - (data::size + 2);

  i = GetFibonacciValue(index) - m;

  p = GetFibonacciValue(index - 1);
  q = GetFibonacciValue(index - 2);
}
```

```C++
void DecIndex() {

  if (q == 0) {

    stopFlag = true;
 }

  i = i - q;

  int temp = q;
  q = p - q;
  p = temp;
}
```

```C++
void IncIndex() {

  if (p == 1) {

    stopFlag = true;
  }

  i = i + q;

  p = p - q;
  q = q - p;
}
```

```C++
template <typename T> int FibonacciSearching(T* array, T value) {

  int valueIndex = -1;

  while (!stopFlag) {

    if (i < 0) {

      IncIndex();
    }
    else if (i > data::size) {
      DecIndex();
    }
    else if (array[i] == value) {

      valueIndex = i;
      break;
    }
    else if (array[i] < value) {
    
      IncIndex();
    }
    else if (array[i] > value) {

      DecIndex();
    }
  }

  return valueIndex;
}
```













