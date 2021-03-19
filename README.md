# Пишем библиотеку для поиска информации в линейных структурах данных на языке С++

## Алгоритмы

Поиск:
1. Последовательный.
2. Фибоначчи.
3. Бинарный.
4. Интерполяционный

## Последовательный поиск

Суть алгоритма: последовательный перебор значений.

Сложность вычислений (худшая): **O(n)**

Реализация на языке С++

```C++
template <typename T> int SequentialSearch(T* array, T value) {
  
  for (int i = 0; i < size; i++) {

    if (array[i] == value) {

      return i;
    }
  }

  return -1;
}
```

## Поиск Фибоначчи

Суть алгоритма: вычисление индекса с помощью последовательности Фибоначчи. Массив **должен быть отсортирован**.

Сложность вычислений (худшая): **O(log n)**

Реализация на языке С++

```C++
const int size = 15;

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

  while (GetFibonacciValue(index + 1) < size + 1) {

    index++;
  }

  int m = GetFibonacciValue(index + 1) - (size + 1);

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
    else if (i >= size) {
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

## Бинарный поиск

Суть алгоритма: деление отсортированного массива на половины. Массив **должен быть отсортирован**.

Сложность вычислений (худшая): **O(log n)**

Реализация на языке С++

```C++
template <typename T> int BinarySearching(T* array, T value) {

  int left = 0;
  int right = data::size;
  int middle = 0;

  while (right - left > 1) {

    middle = (left + right) / 2;

    if (array[middle] < value) {

      left = middle;
    }
    else {

      right = middle;
    }
  }

  if (array[left] == value) {

    return left;
  }
  else if (array[right] == value) {

    return right;
  }
  else {

    return -1;
  }
}
```

## Интеорполяционный поиск

Суть алгоритма: линейная интерполяция для предугадывания индекса искомого элемента. Максимальная эффективность достигается для **(отсортированных массивов)**.

Вычислительная сложность (худшая): **O(n)**

Реализация на языке С++

```C++
template <typename T> int InterpolationSearching(T* array, T value) {

  int left = 0;
  int right = size - 1;

  while ((array[left] < value) && (array[right] > value)) {

    if (array[left] == array[right]) {

      break;
    }

    int index = (value - array[left]) * (left - right) / (array[left] - array[right]) + left;

    if (array[index] > value) {

      right = index - 1;
    }
    else if (array[index] < value) {
      left = index + 1;
    }
    else {

      return index;
    }
  }

  if (array[left] == value) {

	  return left;
  }
  else if (array[right] == value) {

    return right;
  }
  else {

    return -1;
  }
}
```







