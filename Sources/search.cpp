#include "search.h"
#include "view.h"
#include <random>

/**
 * @brief Получить число Фибоначчи по индексу
 * @param index - индекс
 * @return
 */
int Search::GetFibonacciValue(int index) {

    // Первое число Фибоначчи
    int firstValue = 0;
    // Второе число Фибоначчи
    int secondValue = 1;

    for (int i = 0; i < index; i++) {

        // Получение следующего числа Фибоначчи
        int temp = secondValue;
        secondValue += firstValue;
        firstValue = temp;
    }

    return firstValue;
}

/**
 * @brief Инициализация параметров, необходимых для работы алгоритма поиска Фибоначчи
 */
void Search::Init() {

    int index = 0;

    // В индексе ближайшее число Фибоначчи, превосходящее size + 1
    while (GetFibonacciValue(index + 1) < size + 1) {

        index++;
    }

    // Число Фибоначчи по индексу (index + 1) за вычетом (size + 1)
    int m = GetFibonacciValue(index + 1) - (size + 1);

    // Число Фибоначчи за вычетом m
    iF = GetFibonacciValue(index) - m;

    // Число Фибоначчи на месте index - 1
    pF = GetFibonacciValue(index - 1);
    // Число Фибоначчи на месте index - 2
    qF = GetFibonacciValue(index - 2);
}

/**
 * @brief Декрементирование индекса.
 * Необходима для работы алгоритма поиска Фибоначчи
 */
void Search::DecIndex() {

    // Остановка, если левое число Фибоначчи равно нулю
    if (qF == 0) {

        stopFlag = true;
    }

    // Сдвиг индекса влево
    iF = iF - qF;

    // Сдвиг пары чисел Фибоначчи влево на 1 число
    int temp = qF;
    qF = pF - qF;
    pF = temp;
}

/**
 * @brief Инкрементирование индекса.
 * Необходима для работы алгоритма поиска Фибоначчи
 */
void Search::IncIndex() {

    // Остановка, если правое число Фибоначчи равно единице
    if (pF == 1) {

        stopFlag = true;
    }

    // Сдвиг индекса вправо
    iF = iF + qF;

    // Сдвиг пары чисел Фибоначчи влево на два числа
    pF = pF - qF;
    qF = qF - pF;
}

/**
 * @brief Поиск Фибоначчи
 * @param array - вектор
 * @param value - искомое значение
 * @return Время в наносекундах, итератор
 */
IterTime Search::FibonacciSearch(std::vector<int>& array, int value) {

    // Точка времени, начало, миллисекунды
    std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();

    // Итератор либо на искомый элемент, либо на конец вектора
    std::vector<int>::iterator iter = array.begin();

    // Инициализация необходимых для работы алгоритма значений
    Init();

    // Индекс искомого элемента
    int index = -1;

    while (!stopFlag) {

        // Индекс отрицательный
        if (iF < 0) {

            IncIndex();
            // Индекс вышел за пределы
        } else if (iF >= size) {

            DecIndex();
            // Найден искомый элемент
        } else if (array[iF] == value) {

            index = iF;
            break;
            // Искомый элемент стоит правее
        } else if (array[iF] < value) {

            IncIndex();
            // Искомый элемент стоит левее
        } else if (array[iF] > value) {

            DecIndex();
        }
    }

    // Точка времени, конец, миллисекунды
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    // Миллисекунды, время выполнения
    std::chrono::nanoseconds resultTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime);

    if (index == -1) {

        return {resultTime, array.end()};
    }

    return {resultTime, iter + index};
}

/**
 * @brief Обмен значений двух чисел
 * @param digit1 - первое число
 * @param digit2 - второе число
 */
void Search::Swap(int& digit1, int& digit2) {

    digit1 = digit1 + digit2;
    digit2 = digit1 - digit2;
    digit1 = digit1 - digit2;
}

/**
 * @brief Сортировка слиянием
 * @param array - вектор
 * @param start - левая граница сортировки
 * @param end - правая граница сортировки
 */
void Search::Sort(std::vector<int>& array, int start, int end) {

    // Сортировка не требуется
    if (end - start < 2) {

        return;
        // Пара элементов, требуется сортировка
    } else if (end - start == 2) {

        // Установить порядок по возрастанию
        if (array[start] > array[start + 1]) {

            Swap(array[start], array[start + 1]);
        }
    }

    // Вектор. Используется для слияния сортируемых частей
    std::vector<int> temp(end - start, 0);

    // Деление вектора на две части
    Sort(array, start, (start + end) / 2);
    Sort(array, (start + end) / 2, end);

    // Сохранение границ первой части
    int start1 = start;
    int end1 = (start + end) / 2;

    // Сохранение границ второй части
    int start2 = end1;
    int end2 = end;

    // Слияние сортируемых частей
    for (int i = 0; i < end - start; i++) {

        // Выход за границы первой части или элемент второй части меньша элемента первой
        // Сохранение в temp элементов второй части
        if ((start1 >= end1) || ((start2 < end2) && (array[start2] < array[start1]))) {

            temp[i] = array[start2];
            start2++;
            // Сохранение в temp элементов первой части
        } else {

            temp[i] = array[start1];
            start1++;
        }
    }

    // Сохранение отсортированного отрезка [start, end] в исходный массив
    for (int i = start; i < end; i++) {
        array[i] = temp[i - start];
    }

    // Очистка вектора
    temp.clear();
}

/**
 * @brief Сортировка слиянием
 * @param array - вектор
 */
void Search::Sort(std::vector<int>& array) {

    // Сортировка слиянием
    Sort(array, 0, array.size());
}

/**
 * @brief Последовательный поиск
 * @param array - вектор
 * @param value - искомое значение
 * @return Время в наносекундах, итератор
 */
IterTime Search::SequentialSearch(std::vector<int>& array, int value) {

    // Точка времени, начало
    std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();

    // Точка времени, конец
    std::chrono::steady_clock::time_point endTime;

    // Наносекунды, время выполнения
    std::chrono::nanoseconds resultTime;

    // Итератор либо на искомый элемент, либо на конец вектора
    std::vector<int>::iterator iter = array.begin();

    // Перебор элементов
    for (int i = 0; i < array.size(); i++) {

        if (array[i] == value) {

            // Точка времени, конец
            endTime = std::chrono::steady_clock::now();

            // Наносекунды, время выполнения
            resultTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime);

            return {resultTime, iter + i};
        }
    }

    // Точка времени, конец
    endTime = std::chrono::steady_clock::now();

    // Наносекунды, время выполнения
    resultTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime);

    return {resultTime, array.end()};
}

/**
 * @brief Запись вектора случайными значениями
 * @param array - вектор
 */
void Search::WriteArray(std::vector<int>& array) {

    // Генератор случайных (почти) чисел
    std::random_device dev;
    std::mt19937 png(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, array.size());

    // Запись
    for (int i = 0; i < array.size(); i++) {

        array[i] = dist(png);
    }
}

/**
 * @brief Перегруженный конструктор класса Search, сортировка вектора
 * @param array - вектор
 */
Search::Search(std::vector<int>& array) {

    // Сортировка слиянием
    Sort(array);
}

/**
 * @brief Бинарный поиск
 * @param array - вектор
 * @param value - искомое значение
 * @return Время в наносекундах, итератор
 */
IterTime Search::BinarySearch(std::vector<int>& array, int value) {

    // Точка времени, начало
    std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();

    // Левая граница поиска
    int left = 0;
    // Правая граница поиска
    int right = array.size() - 1;
    // Середина отрезка [left; right]
    int middle = 0;

    // Итератор либо на искомый элемент, либо на конец вектора
    std::vector<int>::iterator iter = array.begin();

    // Если произошло пересечение отрезков - поиск завершён
    while (right - left > 1) {

        // Обновление середины
        middle = (left + right) / 2;

        // Сравнение элемента по середине с искомым
        if (array[middle] < value) {

            // Сместить левую границу вправо
            left = middle;
        } else {

            // Сместить правую границу влево
            right = middle;
        }
    }

    // Точка времени, конец
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    // Наносекунды, время выполнения
    std::chrono::nanoseconds resultTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime);

    // Проверка на попадание элемента по левой границе
    if (array[left] == value) {

        return {resultTime, iter + left};
    }

    // Проверка на попадание элемента по правой границе
    if (array[right] == value) {

        return {resultTime, iter + right};
    }

    // Элемент не найден
    return {resultTime, array.end()};
}

/**
 * @brief Замер времени работы алгоритмов сортировки
 * @param size - размер генерируемого вектора
 */
void Search::RunTimeTest(int size) {

    // Генератор случайных (почти) чисел
    std::random_device dev;
    std::mt19937 png(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, size);

    // Генерируемый вектор
    std::vector<int> array(size, 0);

    // Количество повторений
    int iterCount = 100;

    // Сохранение рамера генерируемого вектора
    this->size = size;

    // Время работы алгоритма последовательного поиска, 0 нс
    sequentialTime = std::chrono::nanoseconds(0);
    // Время работы алгоритма поиска Фибоначчи, 0 нс
    fibonacciTime = std::chrono::nanoseconds(0);
    // Время работы алгоритма бинарного поиска, 0 нс
    binaryTime = std::chrono::nanoseconds(0);

    // Начало проверки. Получение среднего времени работы алгоритмов
    for (int i = 0; i < iterCount; i++) {

        // Запись вектора случайными значениями
        WriteArray(array);

        // Сортировка вектора
        Sort(array);

        // Копия вектора
        std::vector<int> arrayCopy;

        // Искомое значение - случайное число
        int value = dist(png);

        // Сохранение времени работы алгоритма последовательного поиска
        sequentialTime += SequentialSearch(arrayCopy = array, value).time;
        // Сохранение времени работы алгоритма поиска Фибоначчи
        fibonacciTime += FibonacciSearch(arrayCopy = array, value).time;
        // Сохранение времени работы алгоритма бинарного поиска
        binaryTime += BinarySearch(arrayCopy = array, value).time;
    }

    // Среднее время работы алгоритма последовательного поиска
    sequentialTime /= iterCount;
    // Среднее время работы алгоритма поиска Фибоначчи
    fibonacciTime /= iterCount;
    // Среднее время работы алгоритма бинарного поиска
    binaryTime /= iterCount;

    // Вывод информации на экран
    PrintResults();
}

/**
 * @brief Вывод на экран информации о работе алгоритмов поиска
 */
void Search::PrintResults() {

    // Размер генерируемого вектора
    View::Print("Size = " + std::to_string(size) + "\n");

    // Информация о замерах
    View::Print("Sequential searching time is " + std::to_string(sequentialTime.count()) + " nanoseconds\n");
    View::Print("Fibonacci searching time is " + std::to_string(fibonacciTime.count()) + " nanoseconds\n");
    View::Print("Binary searching time is " + std::to_string(binaryTime.count()) + " nanoseconds\n\n");
}
