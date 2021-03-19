#include <iostream>
#include <iomanip>
#include <ctime>

#include "searchlib.h"

const int a = search_lib::data::a;
const int b = search_lib::data::b;

int main() {

	srand(time(NULL));

	int* array = nullptr;
	int value = rand() % (b - a + 1) + a;

	search_lib::begin::CreateArray(array);
	search_lib::begin::MergeSorting(array);
	search_lib::begin::PrintArray(array);

	std::cout << "value: " << value << ", valueIndex: " << search_lib::InterpolationSearching(array, value) << std::endl;

	delete[] array;

	return 0;
}