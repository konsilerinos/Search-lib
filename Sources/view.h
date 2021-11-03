#pragma once
#include <string>
#include <vector>

// Класс View, часть модели MVC
class View {

  public:
    /**
     * @brief Вывод информации на экран
     * @param array - вектор
     */
    static void Print(std::vector<int>& array);
    /**
     * @brief Вывод информации на экран, строка
     * @param str - строка
     */
    static void Print(std::string str);
};
