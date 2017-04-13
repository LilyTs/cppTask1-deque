/* Цаплина Лилия Владимировна 2 курс 9 группа. (№15 В)
*  Результатом должна быть консольная программа с текстовым меню, выполняющая все перечисленные ниже пункты(1 - 8) для одного из контейнеров
*  и одного из преобразований.
*  Написать программу, содержащую следующие функции :
*  1. Функцию заполнения текстового файла N целыми случайными числами в диапазоне от - M до M.Имя файла, N и M поступают на вход функции,
*  файл возвращается функцией как результат(использовать потоки ввода - вывода). Реализовать два варианта генерации чисел — в цикле и
*  с использованием алгоритма std::generate.
*  2. Функцию, получающую файл на вход, и возвращающую последовательный контейнер, заполненный числами из файла.
*  3. Функцию modify, выполняющую преобразование полученного контейнера.На вход функции должен поступать контейнер, в качестве результата
*  функция должна возвращать модифицированный контейнер.
*  4. Перегруженную функцию modify, принимающую на вход итераторы начала и конца обрабатываемой части контейнера.
*  5. Функцию, реализующую требуемое преобразование с использованием алгоритма std::transform вместо функции modify.
*  6. Функцию, реализующую требуемое преобразование с использованием алгоритма std::for_each вместо функции modify.
*  7. Функции, вычисляющие сумму и среднее арифметическое чисел, содержащихся в контейнере.
*  8. Функцию вывода результата в файл и на экран(опционально).
*  -------------------------------------------------------------------------------
   Мой вариант : B) двусторонняя очередь(std::deque)
*  15. Добавить к каждому числу полусумму минимального и максимального по абсолютной величине числа.
*/

#include "stdafx.h"

//Генератор случайного целого числа из диапазона [-M, M]
int rand(int M) {
	return std::rand() % (2 * M) + (-M);
}

//Заполнение файла N случайными числами из диапазона [-M, M] (в цикле)
std::fstream& fillFileWithRandNumbers_cycle(std::string fileName, int N, int M) {
	static std::fstream f(fileName, std::ios::out);
	for (int i = 0; i < N; ++i)
		f << (value_type)rand(M) << "\n";
	f.close();
	return f;
}

//Заполнение контейнера случайными числами из диапазона [-M, M]
container& fillContainerWithRandNumbers(container &c, int N, int M) {
	c.resize(N);
	std::generate(c.begin(), c.end(), [&]() {return (value_type)rand(M); });
	return c;
}

//Заполнение файла значениями из контейнера 
std::fstream& fillFileFromContainer(std::string fileName, container &c) {
	static std::fstream f(fileName, std::ios::out);
	for (cIterator it = c.begin(); it != c.end(); ++it)
		f << *it << "\n";
	f.close();
	return f;
}

//Заполнение контейнера значениями из файла
void fillContainerFromFile(std::ifstream &f, container &c) {
	c.clear();
	if(f.is_open()) {
		std::copy(
		std::istream_iterator<value_type>(f),
		std::istream_iterator<value_type>(),
		std::back_inserter<container>(c));
	}
}
void fillContainerFromFile(std::string fileName, container &c) {
	c.clear();
	std::fstream f(fileName, std::ios_base::in);
	if (f.is_open()) {
		std::copy(
			std::istream_iterator<value_type>(f),
			std::istream_iterator<value_type>(),
			std::back_inserter<container>(c));
	}
}

//Вывод элементов контейнера на экран
void outputContainer(container &c) {
	for (cIterator it = c.begin(); it != c.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

double halfsumOfMinAndMax(container &c) {
	value_type min = *c.begin();
	value_type max = min;

	for (cIterator it = ++c.begin(); it != c.end(); ++it) {
		if ((abs(*it)) > abs(max)) {
			max = *it;
		}
		if ((abs(*it)) < abs(min)) {
			min = *it;
		}
	}

	return ((min + max) / 2);
}
//поиск полусуммы минимума и максимума на промежутке
double halfsumOfMinAndMax(cIterator first, cIterator last/*, container &c*/) {
	value_type min = *first;
	value_type max = min;

	for (cIterator it = ++first; it != last; ++it) {
		if ((abs(*it)) > abs(max)) {
			max = *it;
		}
		if ((abs(*it)) < abs(min)) {
			min = *it;
		}
	}

	return ((min + max) / 2);
}

//Преобразование контейнера (15. Добавить к каждому числу полусумму минимального и максимального по абсолютной величине числа.)
int modify(container &c) {
	double hs = halfsumOfMinAndMax(c);
	if (!c.empty()) {
		for (cIterator it = c.begin(); it != c.end(); ++it) {
			(*it) += hs;
		}
		return 0;
	}
	else {
		return -1;
	}
}

//Преобразование выбранной части контейнера
int modify(cIterator first, cIterator last, container &c) {
	double hs = halfsumOfMinAndMax(first, last);
	if (!c.empty()) {
		for (cIterator it = first; it != last; ++it) {
			*it += hs;
		}
		return 0;
	}
	else {
		return -1;
	}
}

//функтор (прибавляет некоторое число b)
class addNumber {
public:
	explicit addNumber(double b) : a(b) {}
	double operator()( value_type &el) const {
		return el + a;
	}
private:
	double a;
};

class addNumber_for_each {
public:
	explicit addNumber_for_each(double b) : a(b) {}
	void operator()(value_type &el) const {
		el += static_cast<value_type>(a);
	}
private:
	double a;
};

int transform(container &c) {
	if (!c.empty()) {
		double hs = halfsumOfMinAndMax(c);
		std::transform(c.begin(), c.end(), c.begin(), addNumber(hs));
		return 0;
	}
	else {
		return -1;
	}
}

int modify_for_each(container &c) {
	if (!c.empty()) {
		double hs = halfsumOfMinAndMax(c);
		std::for_each(c.begin(), c.end(), addNumber_for_each(hs));
		return 0;
	}
	else {
		return -1;
	}
}

value_type sum(container &c) {
	value_type res = 0;

	for each (value_type x in c)
	{
		res += x;
	}

	return res;
}

double average(container &c) {
	return (sum(c) / c.size());
}

int menuItem(){
	std::cout << "\nВыберите действие:\n\n";
	std::cout << " 1 - Заполнение текстового файла N целыми случайными числами в диапазоне от -M до M (в цикле)\n";
	std::cout << " 2 - Заполнение текстового файла N целыми случайными числами в диапазоне от -M до M (с использованием std::generate)\n";
	std::cout << " 3 - Заполнение контейнера N случайными числами  в диапазоне от -M до M \n";
	std::cout << " 4 - Заполнение контейнера числами из файла\n";
	std::cout << " 5 - Преобразование контейнера\n";
	std::cout << " 6 - Преобразование выбранной части контейнера\n";
	std::cout << " 7 - Преобразование контейнера с использованием алгоритма std::transform\n";
	std::cout << " 8 - Преобразование контейнера с использованием алгоритма std::for_each\n";
	std::cout << " 9 - Вычислить сумму чисел, содержащихся в контейнере\n";
	std::cout << "10 - Вычислить среднее арифметическое чисел, содержащихся в контейнере\n";
	std::cout << "11 - Сохранить результат в файл\n";
	std::cout << " 0 - Выход из программы\n";
	std::cout << std::endl;

	int item = -1;
	std::cin >> item;

	while ((item > 11) || (item < 0))
	{
		std::cout << "Повторите ввод! " << std::endl;
		std::cin >> item;
	}
	std::cout << std::endl;

	return item;
}

void inputNM(int &N, int &M) {
	std::cout << "\nВведите количество чисел: ";
	std::cin >> N;
	std::cout << "\nВведите границу диапазона M: ";
	std::cin >> M;
	std::cout << std::endl;
} 

void inputFileName(std::string &fileName) {
	std::cout << "Введите имя файла: ";
	std::cin >> fileName;
}

void doMenuActions(){
	int item;
	container c;

	while ((item = menuItem()) != 0)
	{
		std::string fileName;
		int N, M;

		switch (item)
		{
		case 1:
			inputFileName(fileName);
			inputNM(N, M);
			fillFileWithRandNumbers_cycle(fileName, N, M);
			break;
		case 2:
			inputFileName(fileName);
			inputNM(N, M);
			fillContainerWithRandNumbers(c, N, M);
			fillFileFromContainer(fileName, c);
			break;
		case 3:
			inputNM(N, M);
			fillContainerWithRandNumbers(c, N, M);
			break;
		case 4:
			inputFileName(fileName);
			fillContainerFromFile(fileName, c);
			std::cout << "Контейнер: ";
			outputContainer(c);
			break;
		case 5:
			std::cout << "Исходный контейнер:\n";
			outputContainer(c);
			if (modify(c) == 0) {
				std::cout << "Преобразованный контейнер:\n";
				outputContainer(c);
			}
			else {
				std::cout << "Невозможно выполнить преобразование." << std::endl;
			}
			break;
		case 6: {
			cIterator first, last;
			int num_first, num_last;
			bool ok;

			std::cout << "Введите, с какого по какой элемент (включительно) требуется выполнить преобразование:\n";
			do {
				std::cout << "c ";
				std::cin >> num_first;
				std::cout << "по ";
				std::cin >> num_last;
				ok = (num_first > 0) && (num_first <= c.size()) && (num_last > num_first) && (num_last <= c.size());
				if (!ok) {
					std::cout << "Ошибка! Повторите ввод:\n";
				}
			} while (!ok);
			std::cout << std::endl;
			first = c.begin() + num_first - 1;
			last = c.end() - (c.size() - num_last);

			std::cout << "\nИсходный контейнер:\n";
			outputContainer(c);
			if (modify(first, last, c) == 0) {
				std::cout << "Преобразованный контейнер:\n";
				outputContainer(c);
			}
			else {
				std::cout << "Невозможно выполнить преобразование." << std::endl;
			}
		}
			break;
		case 7:
			std::cout << "Исходный контейнер:\n";
			outputContainer(c);
			if (transform(c) == 0) {
				std::cout << "Преобразованный контейнер:\n";
				outputContainer(c);
			}
			else {
				std::cout << "Невозможно выполнить преобразование." << std::endl;
			}
			break;
		case 8:
			std::cout << "Исходный контейнер:\n";
			outputContainer(c);
			if (modify_for_each(c) == 0) {
				std::cout << "Преобразованный контейнер:\n";
				outputContainer(c);
			}
			else {
				std::cout << "Невозможно выполнить преобразование." << std::endl;
			}
			break;
		case 9:
			std::cout << "Контенер: ";
			outputContainer(c);
			std::cout << "Сумма элементов контейнера: " << sum(c) << std::endl;
			break;
		case 10:
			std::cout << "Контенер: ";
			outputContainer(c);
			std::cout << "Среднее арифметическое элементов контейнера: " << average(c) << std::endl;
			break;
		case 11:
			inputFileName(fileName);
			fillFileFromContainer(fileName, c);
			break;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	doMenuActions();
    return 0;
}

