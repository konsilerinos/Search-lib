#pragma once

#include <iostream>
#include <iomanip>

namespace search_lib {

	namespace data {

		const int size = 15;

		const int a = 0;
		const int b = 10;
	}

	namespace aux_fun {

		class ForFibonacciSearching {

		public:

			ForFibonacciSearching();

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

		private:

			int i = 0;
			int p = 0;
			int q = 0;

			bool stopFlag = false;

			int GetFibonacciValue(int);

			void IncIndex();
			void DecIndex();
		};
	}
	
	namespace begin {

		namespace aux_fun {

			template <typename T> void Swap(T & digit1, T & digit2) {

				digit1 = digit1 + digit2;
				digit2 = digit1 - digit2;
				digit1 = digit1 - digit2;
			}

			template <typename T> void MergeSorting(T* array, int start, int end) {

				if (end - start < 2) {

					return;
				}
				else if (end - start == 2) {

					if (array[start] > array[start + 1]) {

						aux_fun::Swap(array[start], array[start + 1]);
					}
				}

				MergeSorting(array, start, (start + end) / 2);
				MergeSorting(array, (start + end) / 2, end);

				T* temp = new T[end - start];

				int start1 = start;
				int end1 = (start + end) / 2;

				int start2 = end1;
				int end2 = end;

				for (int i = 0; i < end - start; i++) {

					if ((start1 >= end1) || ((start2 < end2) && (array[start2] < array[start1]))) {

						temp[i] = array[start2];
						start2++;
					}
					else {

						temp[i] = array[start1];
						start1++;
					}
				}

				for (int i = start; i < end; i++) {

					array[i] = temp[i - start];
				}

				delete[] temp;
			}
		}

		template <typename T> void CreateArray(T*& array) {

			srand(time(NULL));

			array = new T[data::size];

			for (int i = 0; i < data::size; i++) {

				int whole_part = rand() % (data::b - data::a + 1) + data::a;
				double fractional_part = static_cast<double>(1) / (rand() % (data::b - data::a + 1) + 1);

				array[i] = whole_part + fractional_part;
			}
		}

		template <typename T> void PrintArray(T array) {

			std::cout << "Array: ";

			for (int i = 0; i < data::size; i++) {

				std::cout << std::fixed << std::setprecision(2) << std::setw(7) << array[i];
			}

			std::cout << std::endl;
		}

		template <typename T> void MergeSorting(T* array) {

			aux_fun::MergeSorting(array, 0, data::size);
		}
	}

	template <typename T> int FibonacciSearching(T* array, T value) {

		aux_fun::ForFibonacciSearching forFibonacciSearching;

		return forFibonacciSearching.FibonacciSearching(array, value);
	}
}