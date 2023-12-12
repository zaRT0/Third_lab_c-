#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

template <typename T>
void swaps(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
void Print(vector<T> vec) {
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << "\n\n";
}

ostream& operator<<(std::ostream& os, stats& stat)
{
	os << "comparison_count = " << stat.comparison_count << " copy_count = " << stat.copy_count;
	return os;
}

template<typename T>
stats& BubbleSort(vector<T>& vec) {
	stats statistic;
	for (int i = 0; i < vec.size() - 1; ++i) {
		for (int j = 0; j < vec.size() - i - 1; ++j) {
			statistic.comparison_count += 1;
			if (vec[j] > vec[j + 1]) {
				swaps(vec[j], vec[j + 1]);
				statistic.copy_count += 3;
			}
		}
	}
	return statistic;
}

template <typename T>
stats& shakerSort(std::vector<T>& arr) {
	stats s;
	size_t n = arr.size();
	bool swapped;
	do {
		swapped = false;
		for (size_t i = 0; i < n - 1; ++i) {
			s.comparison_count++;
			if (arr[i] > arr[i + 1]) {
				swaps(arr[i], arr[i + 1]);
				s.copy_count += 3;
				swapped = true;
			}
		}
		if (!swapped) break;

		swapped = false;
		for (size_t i = n - 1; i > 0; --i) {
			s.comparison_count++;
			if (arr[i - 1] > arr[i]) {
				swaps(arr[i - 1], arr[i]);
				s.copy_count += 3;
				swapped = true;
			}
		}
	} while (swapped);

	return s;
}


int main() {
	return 0;
}