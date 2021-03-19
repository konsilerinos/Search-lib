#include "searchlib.h"

int search_lib::aux_fun::ForFibonacciSearching::GetFibonacciValue(int index) {

	int firstValue = 0;
	int secondValue = 1;

	for (int i = 0; i < index; i++) {

		int temp = secondValue;
		secondValue += firstValue;
		firstValue = temp;
	}

	return firstValue;
}

void search_lib::aux_fun::ForFibonacciSearching::DecIndex() {

	if (q == 0) {

		stopFlag = true;
	}

	i = i - q;

	int temp = q;
	q = p - q;
	p = temp;
}

void search_lib::aux_fun::ForFibonacciSearching::IncIndex() {

	if (p == 1) {

		stopFlag = true;
	}

	i = i + q;

	p = p - q;
	q = q - p;
}

search_lib::aux_fun::ForFibonacciSearching::ForFibonacciSearching() {

	int index = 0;

	while (GetFibonacciValue(index + 1) < data::size + 2) {

		index++;
	}

	int m = GetFibonacciValue(index + 1) - (data::size + 2);

	i = GetFibonacciValue(index) - m;

	p = GetFibonacciValue(index - 1);
	q = GetFibonacciValue(index - 2);
}