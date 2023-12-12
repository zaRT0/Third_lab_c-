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

class ComparisonClass {
private:
	int _value;
public:

	ComparisonClass() : _value(0) {}

	ComparisonClass(int value) : _value(value) {}

	int get_value() const {
		return this->_value;
	}

	bool operator > (const ComparisonClass& rhs) const {
		return this->_value > rhs._value;
	}

	bool operator < (const ComparisonClass& rhs) const {
		return this->_value < rhs._value;
	}
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

template <typename T>
stats& combSort(std::vector<T>& arr) {
	stats s;
	size_t n = arr.size();
	size_t gap = n;
	bool swapped = true;

	while (gap > 1 || swapped) {
		gap = (gap * 10) / 13;
		if (gap < 1) gap = 1;

		swapped = false;
		for (size_t i = 0; i < n - gap; ++i) {
			s.comparison_count++;
			if (arr[i] > arr[i + gap]) {
				swaps(arr[i], arr[i + gap]);
				s.copy_count += 3;
				swapped = true;
			}
		}
	}

	return s;
}

template <typename T>
vector<T> RandomVec(size_t size) {
	vector<T> vector(size);
	srand(static_cast<unsigned int>(time(0)));
	for (size_t i = 0; i < size; ++i) {
		vector[i] = rand();
	}
	return vector;
}

template <typename T>
vector<T> SortedVec(size_t size) {
	vector<T> vector(size);
	for (size_t i = 0; i < size; ++i) {
		vector[i] = i;
	}
	return vector;
}

template <typename T>
vector<T> ReverseSortedVec(size_t size) {
	vector<T> vector(size);
	for (size_t i = 0; i < size; ++i) {
		vector[i] = size - i;
	}
	return vector;
}


int main() {
	setlocale(LC_ALL, "Rus");
	const int num_vectors = 100;
	const vector<size_t> vector_lengths = { 1000, 2000, 3000 , 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000 };

	for (size_t length : vector_lengths) {
		stats bubble_random{ 0, 0 };
		stats bubble_sorted{ 0, 0 };
		stats bubble_reverse{ 0, 0 };

		stats shaker_random{ 0, 0 };
		stats shaker_sorted{ 0, 0 };
		stats shaker_reverse{ 0, 0 };

		stats comb_random{ 0, 0 };
		stats comb_sorted{ 0, 0 };
		stats comb_reverse{ 0, 0 };

		for (int i = 0; i < num_vectors; ++i) {
			vector<int> random_vector = RandomVec<int>(length);

			vector<int> bubble_random_vector = random_vector;
			stats bubble_random_stats = BubbleSort(bubble_random_vector);
			bubble_random.comparison_count += bubble_random_stats.comparison_count;
			bubble_random.copy_count += bubble_random_stats.copy_count;

			vector<int> shaker_random_vector = random_vector;
			stats shaker_random_stats = shakerSort(shaker_random_vector);
			shaker_random.comparison_count += shaker_random_stats.comparison_count;
			shaker_random.copy_count += shaker_random_stats.copy_count;

			vector<int> comb_random_vector = random_vector;
			stats comb_random_stats = combSort(comb_random_vector);
			comb_random.comparison_count += comb_random_stats.comparison_count;
			comb_random.copy_count += comb_random_stats.copy_count;
		}

		vector<int> sorted_vector = SortedVec<int>(length);

		vector<int> bubble_sorted_vector = sorted_vector;
		stats bubble_sorted_stats = BubbleSort(bubble_sorted_vector);
		bubble_sorted.comparison_count += bubble_sorted_stats.comparison_count;
		bubble_sorted.copy_count += bubble_sorted_stats.copy_count;;

		vector<int> shaker_sorted_vector = sorted_vector;
		stats shaker_sorted_stats = shakerSort(shaker_sorted_vector);
		shaker_sorted.comparison_count += shaker_sorted_stats.comparison_count;
		shaker_sorted.copy_count += shaker_sorted_stats.copy_count;

		vector<int> comb_sorted_vector = sorted_vector;
		stats comb_sorted_stats = combSort(comb_sorted_vector);
		comb_sorted.comparison_count += comb_sorted_stats.comparison_count;
		comb_sorted.copy_count += comb_sorted_stats.copy_count;

		vector<int> reverse_sorted_vector = ReverseSortedVec<int>(length);

		vector<int> bubble_reverse_sorted_vector = reverse_sorted_vector;
		stats bubble_reverse_sorted_stats = BubbleSort(bubble_reverse_sorted_vector);
		bubble_reverse.comparison_count += bubble_reverse_sorted_stats.comparison_count;
		bubble_reverse.copy_count += bubble_reverse_sorted_stats.copy_count;

		vector<int> shaker_reverse_sorted_vector = reverse_sorted_vector;
		stats shaker_reverse_sorted_stats = shakerSort(shaker_reverse_sorted_vector);
		shaker_reverse.comparison_count += shaker_reverse_sorted_stats.comparison_count;
		shaker_reverse.copy_count += shaker_reverse_sorted_stats.copy_count;

		vector<int> comb_reverse_sorted_vector = reverse_sorted_vector;
		stats comb_reverse_sorted_stats = combSort(comb_reverse_sorted_vector);
		comb_reverse.comparison_count += comb_reverse_sorted_stats.comparison_count;
		comb_reverse.copy_count += comb_reverse_sorted_stats.copy_count;

		stats bubble_random_average_stats{
			bubble_random.comparison_count / num_vectors,
			bubble_random.copy_count / num_vectors
		};

		stats shaker_random_average_stats{
			shaker_random.copy_count / num_vectors,
			shaker_random.comparison_count / num_vectors
		};

		stats comb_random_average_stats{
			comb_random.comparison_count / num_vectors,
			comb_random.copy_count / num_vectors
		};

		cout << "Текущая длина вектора: " << length << endl << endl;

		cout << "СОРТИРОВКА ПУЗЫРЬКОМ:" << endl << endl;

		cout << "Статистика для РАНДОМНОГО ВЕКТОРА:" << endl;
		cout << "   Кол-во сравнений: " << bubble_random_average_stats.comparison_count << endl;
		cout << "   Кол-во копий: " << bubble_random_average_stats.copy_count << endl << endl;

		cout << "Статистика для ОТСОРТИРОВАННОГО ВЕКТОРА:" << endl;
		cout << "   Количество сравнений: " << bubble_sorted.comparison_count << endl;
		cout << "   Кол-вл копий: " << bubble_sorted.copy_count << endl << endl;

		cout << "Статистика для ОБРАТНОГО ОТСОРТИРОВАННОГО ВЕКТОРА:" << endl;
		cout << "   Кол-во сравнений: " << bubble_reverse.comparison_count << endl;
		cout << "   Кол-во копий: " << bubble_reverse.copy_count << endl << endl;

		cout << "ШЕЙКЕРНАЯ СОРТИРОВКА:" << endl << endl;

		cout << "Статистика для РАНДОМНОГО ВЕКТОРА:" << endl;
		cout << "   Кол-во сравнений: " << shaker_random_average_stats.comparison_count << endl;
		cout << "   Кол-во копий: " << shaker_random_average_stats.copy_count << endl << endl;

		cout << "Статистика для ОТСОРТИРОВАННОГО ВЕКТОРА:" << endl;
		cout << "   Кол-во сравнений: " << shaker_sorted.comparison_count << endl;
		cout << "   Кол-во копий: " << shaker_sorted.copy_count << endl << endl;

		cout << "Статистика для ОБРАТНОГО ОТСОРТИРОВАННОГО ВЕКТОРА:" << endl;
		cout << "   Кол-во сравнений: " << shaker_reverse.comparison_count << endl;
		cout << "   Кол-во копий: " << shaker_reverse.copy_count << endl << endl;

		cout << "СОРТИРОВКА РАСЧЕСКОЙ:" << endl << endl;

		cout << "Статистика для РАНДОМНОГО ВЕКТОРА:" << endl;
		cout << "   Кол-во сравнений: " << comb_random_average_stats.comparison_count << endl;
		cout << "   Кол-во копий: " << comb_random_average_stats.copy_count << endl << endl;

		cout << "Статистика для ОТСОРТИРОВАННОГО ВЕКТОРА:" << endl;
		cout << "   Кол-во сравнений: " << comb_sorted.comparison_count << endl;
		cout << "   Кол-во копий: " << comb_sorted.copy_count << endl << endl;

		cout << "Статистика для ОБРАТНОГО ОТСОРТИРОВАННОГО ВЕКТОРА:" << endl;
		cout << "   Кол-во сравнений: " << comb_reverse.comparison_count << endl;
		cout << "   Кол-во копий: " << comb_reverse.copy_count << endl << endl;

		cout << "Сортировка СТРИНГОВЫХ векторов" << endl << endl;

		vector<string> stringvector1 = { "a", "f", "c" , "f", "a", "r" , "i", "e" };
		vector<string> stringvector2 = { "i", "y", "t" , "x", "z", "r" , "q", "l", "s", "k" };
		vector<string> stringvector3 = { "w", "t", "h" , "j", "a", "b" , "s", "e", "d", "m", "k", "a", "x", "q", "z" , "x", "b", "l" };

		cout << "Вектор до сортировки:" << endl;
		Print(stringvector1);
		stats statistics1 = BubbleSort(stringvector1);
		cout << "Вектор после ПУЗЫРЬКОВОЙ сортировки " << endl;
		Print(stringvector1);
		cout << "Кол-во сравнений: " << statistics1.comparison_count << endl;
		cout << "Кол-во копий: " << statistics1.copy_count << endl << endl;

		cout << "Вектор до сортировки: " << endl;
		Print(stringvector2);
		stats statistics2 = shakerSort(stringvector2);
		cout << "Вектор после ШЕЙКЕРНОЙ сортировки " << endl;
		Print(stringvector2);
		cout << "Кол-во сравнений:  " << statistics2.comparison_count << endl;
		cout << "Кол-во копий: " << statistics2.copy_count << endl << endl;

		cout << "Вектор до сортировки: " << endl;
		Print(stringvector3);
		stats statistics3 = combSort(stringvector3);
		cout << "Вектор после сортировки РАСЧЕСКОЙ" << endl;
		Print(stringvector3);
		cout << "Кол-во сравнений: " << statistics3.comparison_count << endl;
		cout << "Кол-во копий: " << statistics3.copy_count << endl << endl;

		cout << "Сортировка векторов СОБСТВЕННОГО КЛАССА" << endl << endl;

		vector<ComparisonClass> v1;
		vector<ComparisonClass> v2;
		vector<ComparisonClass> v3;

		srand(static_cast<unsigned int>(time(0)));
		for (size_t i = 0; i < 15; ++i) {
			v1.push_back(rand() % 100);
		}

		srand(static_cast<unsigned int>(time(0)));
		for (size_t i = 0; i < 15; ++i) {
			v2.push_back(rand() % 100);
		}

		srand(static_cast<unsigned int>(time(0)));
		for (size_t i = 0; i < 15; ++i) {
			v3.push_back(rand() % 100);
		}

		cout << "Сортировка ПУЗЫРЬКОМ" << endl << endl;

		cout << "Вектор ДО сортировки: " << endl << endl;
		for (const auto& obj : v1) {
			cout << obj.get_value() << " ";
		}
		stats statistics4 = BubbleSort(v1);
		cout << endl;
		cout << "Вектор ПОСЛЕ сортировки: " << endl << endl;
		for (const auto& obj : v1) {
			cout << obj.get_value() << " ";
		}
		cout << endl;
		cout << endl;

		cout << "Сортировка ШЕЙКЕРНАЯ" << endl << endl;

		cout << "Вектор ДО сортировки: " << endl << endl;
		for (const auto& obj : v2) {
			cout << obj.get_value() << " ";
		}
		stats statistics5 = shakerSort(v2);
		cout << endl;
		cout << "Вектор ПОСЛЕ сортировки: " << endl << endl;
		for (const auto& obj : v2) {
			cout << obj.get_value() << " ";
		}
		cout << endl;
		cout << endl;

		cout << "Сортировка РАСЧЕСКОЙ" << endl << endl;

		cout << "Вектор ДО сортировки: " << endl << endl;
		for (const auto& obj : v3) {
			cout << obj.get_value() << " ";
		}
		stats statistics6 = combSort(v3);
		cout << endl;
		cout << "Вектор ПОСЛЕ сортировки: " << endl << endl;
		for (const auto& obj : v3) {
			cout << obj.get_value() << " ";
		}
		cout << endl;
	}
	return 0;
}