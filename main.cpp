#include <iostream>
#include <iomanip>
#include <ctime>

#include "searchlib.h"

const int a = search_lib::data::a;
const int b = search_lib::data::b;

int main() {

	search_lib::data::size = 10;

	srand(time(NULL));

	int* array = nullptr;
	int value = rand() % (b - a + 1) + a;

	search_lib::create::CreateArray(array);
	search_lib::sort::MergeSorting(array);
	search_lib::print::PrintArray(array);

	std::cout << "value: " << value << ", valueIndex: " << search_lib::InterpolationSearching(array, value) << ", ";
	std::cout << "average time (ns) = " << search_lib::time::InterpolationSearchingTest(array, 1000).count() << std::endl;

	delete[] array;

	return 0;
}