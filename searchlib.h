#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>

namespace search_lib {

	namespace data {

		static int size = 15;

		static int a = 0;
		static int b = 10;
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
					else if (i >= data::size) {
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
	
	namespace create {

		template <typename T> void CreateArray(T*& array) {

			srand(time(NULL));

			array = new T[data::size];

			for (int i = 0; i < data::size; i++) {

				int whole_part = rand() % (data::b - data::a + 1) + data::a;
				double fractional_part = static_cast<double>(1) / (rand() % (data::b - data::a + 1) + 1);

				array[i] = whole_part + fractional_part;
			}
		}

		template <typename T> T* GetArrayCopy(T* array) {

			T* newArray = new T[data::size];

			for (int i = 0; i < data::size; i++) {

				newArray[i] = array[i];
			}

			return newArray;
		}
	}

	namespace print {

		template <typename T> void PrintArray(T array) {

			std::cout << "Array: ";

			for (int i = 0; i < data::size; i++) {

				std::cout << std::fixed << std::setprecision(2) << std::setw(7) << array[i];
			}

			std::cout << std::endl;
		}
	}

	namespace sort {

		namespace aux_fun {

			template <typename T> void Swap(T& digit1, T& digit2) {

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

		template <typename T> void MergeSorting(T* array) {

			aux_fun::MergeSorting(array, 0, data::size);
		}
	}

	template <typename T> int SequentialSearching(T* array, T value) {

		for (int i = 0; i < data::size; i++) {

			if (array[i] == value) {

				return i;
			}
		}

		return -1;
	}

	template <typename T> int FibonacciSearching(T* array, T value) {

		aux_fun::ForFibonacciSearching forFibonacciSearching;

		return forFibonacciSearching.FibonacciSearching(array, value);
	}

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

	template <typename T> int InterpolationSearching(T* array, T value) {

		int left = 0;
		int right = data::size - 1;

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

	namespace time {

		namespace aux_fun {

			template <typename T> std::chrono::nanoseconds SequentialSearchingTest(T* array) {

				T value = rand() % (data::b - data::a + 1) + data::a;

				std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

				SequentialSearching(array, value);

				std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

				std::chrono::nanoseconds resultTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

				return resultTime;
			}
			template <typename T> std::chrono::nanoseconds FibonacciSearchingTest(T* array) {

				T value = rand() % (data::b - data::a + 1) + data::a;

				std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

				FibonacciSearching(array, value);

				std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

				std::chrono::nanoseconds resultTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

				return resultTime;
			}
			template <typename T> std::chrono::nanoseconds BinarySearchingTest(T* array) {

				T value = rand() % (data::b - data::a + 1) + data::a;

				std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

				BinarySearching(array, value);

				std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

				std::chrono::nanoseconds resultTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

				return resultTime;
			}
			template <typename T> std::chrono::nanoseconds InterpolationSearchingTest(T* array) {

				T value = rand() % (data::b - data::a + 1) + data::a;

				std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

				InterpolationSearching(array, value);

				std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

				std::chrono::nanoseconds resultTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

				return resultTime;
			}
		}

		template <typename T> std::chrono::nanoseconds SequentialSearchingTest(T array, int count) {

			std::chrono::nanoseconds averageTime = std::chrono::nanoseconds(0);

			for (int i = 0; i < count; i++) {

				T arrayCopy = create::GetArrayCopy(array);

				std::this_thread::sleep_for(std::chrono::microseconds(1));
				averageTime += aux_fun::SequentialSearchingTest(array);
				std::this_thread::sleep_for(std::chrono::microseconds(1));

				delete[] arrayCopy;
			}

			averageTime /= count;

			return averageTime;
		}
		template <typename T> std::chrono::nanoseconds FibonacciSearchingTest(T array, int count) {

			std::chrono::nanoseconds averageTime = std::chrono::nanoseconds(0);

			for (int i = 0; i < count; i++) {

				T arrayCopy = create::GetArrayCopy(array);

				std::this_thread::sleep_for(std::chrono::microseconds(1));
				averageTime += aux_fun::FibonacciSearchingTest(array);
				std::this_thread::sleep_for(std::chrono::microseconds(1));

				delete[] arrayCopy;
			}

			averageTime /= count;

			return averageTime;
		}
		template <typename T> std::chrono::nanoseconds BinarySearchingTest(T array, int count) {

			std::chrono::nanoseconds averageTime = std::chrono::nanoseconds(0);

			for (int i = 0; i < count; i++) {

				T arrayCopy = create::GetArrayCopy(array);

				std::this_thread::sleep_for(std::chrono::microseconds(1));
				averageTime += aux_fun::BinarySearchingTest(array);
				std::this_thread::sleep_for(std::chrono::microseconds(1));

				delete[] arrayCopy;
			}

			averageTime /= count;

			return averageTime;
		}
		template <typename T> std::chrono::nanoseconds InterpolationSearchingTest(T array, int count) {

			std::chrono::nanoseconds averageTime = std::chrono::nanoseconds(0);

			for (int i = 0; i < count; i++) {

				T arrayCopy = create::GetArrayCopy(array);

				std::this_thread::sleep_for(std::chrono::microseconds(1));
				averageTime += aux_fun::InterpolationSearchingTest(array);
				std::this_thread::sleep_for(std::chrono::microseconds(1));

				delete[] arrayCopy;
			}

			averageTime /= count;

			return averageTime;
		}
	}


}