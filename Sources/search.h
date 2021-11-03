#pragma once
#include <chrono>
#include <vector>

/**
 * @brief Структура, время в наносекундах и итератор
 */
struct IterTime {

    /**
     * @brief Время в наносекундах
     */
    std::chrono::nanoseconds time;
    /**
     * @brief Итератор
     */
    std::vector<int>::iterator iter;
};

/**
 * @brief Класс, содержащий алгоритмы поиска, а также метод их тестирования
 */
class Search {

  private:
    /**
     * @brief Время в наносекундах, последовательный поиск
     */
    std::chrono::nanoseconds sequentialTime;
    /**
     * @brief Время в наносекундах, поиск Фибоначчи
     */
    std::chrono::nanoseconds fibonacciTime;
    /**
     * @brief Время в наносекундах, бинарный поиск
     */
    std::chrono::nanoseconds binaryTime;

    /**
     * @brief Размер вектора, используется для вывода информации
     * о результатах тестирования
     */
    int size;

    /**
     * @brief Индекс, используется алгоритме поиска Фибоначчи
     */
    int iF;
    // Число Фибоначчи
    int pF;
    // Число Фибоначчи
    int qF;

    // Флаг остановки, используется в алгоритме поиска Фибоначчи
    bool stopFlag = false;

    /**
     * @brief Получить число Фибоначчи по индексу
     * @param index - индекс
     * @return
     */
    int GetFibonacciValue(int index);

    /**
     * @brief Инициализация параметров, необходимых для работы алгоритма поиска Фибоначчи
     */
    void Init();

    /**
     * @brief Декрементирование индекса.
     * Необходима для работы алгоритма поиска Фибоначчи
     */
    void DecIndex();

    /**
     * @brief Инкрементирование индекса.
     * Необходима для работы алгоритма поиска Фибоначчи
     */
    void IncIndex();

    /**
     * @brief Поиск Фибоначчи
     * @param array - вектор
     * @param value - искомое значение
     * @return Время в наносекундах, итератор
     */
    IterTime FibonacciSearch(std::vector<int>& array, int value);

    /**
     * @brief Обмен значений двух чисел
     * @param digit1 - первое число
     * @param digit2 - второе число
     */
    void Swap(int& digit1, int& digit2);

    /**
     * @brief Сортировка слиянием
     * @param array - вектор
     * @param start - левая граница сортировки
     * @param end - правая граница сортировки
     */
    void Sort(std::vector<int>& array, int start, int end);

    /**
     * @brief Сортировка слиянием
     * @param array - вектор
     */
    void Sort(std::vector<int>& array);

    /**
     * @brief Последовательный поиск
     * @param array - вектор
     * @param value - искомое значение
     * @return Время в наносекундах, итератор
     */
    IterTime SequentialSearch(std::vector<int>& array, int value);

    /**
     * @brief Запись вектора случайными значениями
     * @param array - вектор
     */
    void WriteArray(std::vector<int>& array);

  public:
    /**
     * @brief Конструктор по умолчанию класса Search
     */
    Search() {}

    /**
     * @brief Перегруженный конструктор класса Search, сортировка вектора
     * @param array - вектор
     */
    Search(std::vector<int>& array);

    /**
     * @brief Бинарный поиск
     * @param array - вектор
     * @param value - искомое значение
     * @return Время в наносекундах, итератор
     */
    IterTime BinarySearch(std::vector<int>& array, int value);

    /**
     * @brief Замер времени работы алгоритмов сортировки
     * @param size - размер генерируемого вектора
     */
    void RunTimeTest(int size);

    /**
     * @brief Вывод на экран информации о работе алгоритмов поиска
     */
    void PrintResults();
};
