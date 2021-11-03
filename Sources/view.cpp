#include "view.h"
#include <iomanip>
#include <iostream>

void View::Print(std::vector<int>& array) {

    for (int i = 0; i < array.size(); i++) {

        std::cout << std::setw(4) << array[i];
    }

    std::cout << std::endl;
}

void View::Print(std::string str) { std::cout << str; }
