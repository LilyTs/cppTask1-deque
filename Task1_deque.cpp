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
*  Мой вариант : B) двусторонняя очередь(std::deque)
*  15. Добавить к каждому числу полусумму минимального и максимального по абсолютной величине числа.
*/

#include "stdafx.h"

//Генератор случайного целого числа из диапазона [-M, M]
int rand(int M) {
	//srand(time(nullptr));
	return std::rand() % (2 * M) + (-M);
}

//Заполнение файла N случайными числами из диапазона [-M, M] (в цикле)
std::fstream& fillFileWithRandNumbers_cycle(std::string fileName, int N, int M) {
	std::fstream f(fileName);
	for (int i = 0; i < N; ++i)
		f << rand(M) << "\n";
	f.close();
	return f;
}

//Заполнение контейнера случайными числами из диапазона [-M, M]
container& fillContainerWithRandNumbers(container &c, int N, int M) {
	std::generate(c.begin(), c.end(), [&]() {return rand(M); });
	return c;
}

//Заполнение файла значениями из контейнера 
std::fstream& fillFileFromContainer(std::string fileName, container &c) {
	std::fstream f(fileName);
	for (cIterator it = c.begin(); it != c.end(); ++it)
		f << *it << "\n";
	f.close();
	return f;
}

//Заполнение контейнера значениями из файла
container& fillContainerFromFile(std::ifstream &f, container &c) {
	c.clear();
	if(f.is_open()) {
		std::copy(
		std::istream_iterator<value_type>(f),
		std::istream_iterator<value_type>(),
		std::inserter(c, c.begin()));
	}
	return c;
}
container& fillContainerFromFile(std::string fileName, container &c) {
	c.clear();
	std::fstream f(fileName, std::ios_base::in);
	if (f.is_open()) {
		std::copy(
			std::istream_iterator<value_type>(f),
			std::istream_iterator<value_type>(),
			std::inserter(c, c.begin()));
	}
	return c;
}

//Вывод содержимого контейнера на экран
void outputContainer(container &c) {
	for (cIterator it = c.begin(); it != c.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

//Вывод содержимого контейнера в файл
void saveContainerToFile(container &c, std::string fileName) {
	std::ofstream f(fileName);
	for (cIterator it = c.begin(); it != c.end(); ++it) {
		f << *it << "\n";
	}
}

value_type min(container c) {
	value_type res = abs(*c.begin());
	for (cIterator it = ++c.begin(); it != c.end(); ++it) {
		if (abs(*it) < res) {
			res = *it;
		}
	}
	return res;
}

value_type max(container c) {
	value_type res = abs(*c.begin());
	for (cIterator it = ++c.begin(); it != c.end(); ++it) {
		if (abs(*it) > res) {
			res = *it;
		}
	}
	return res;
}

std::pair<value_type, value_type> minAndMax(container c) {
	value_type min = abs(*c.begin());
	value_type max = min;
	for (cIterator it = ++c.begin(); it != c.end(); ++it) {
		if (abs(*it) > max) {
			max = *it;
		}
		if (abs(*it) < min) {
			min = *it;
		}
	}
	return std::make_pair(min, max);
}

//Преобразование контейнера (15. Добавить к каждому числу полусумму минимального и максимального по абсолютной величине числа.)
container& modify(container &c) {
	std::pair<value_type, value_type> mM = minAndMax(c);
	for (cIterator it = c.begin(); it != c.end(); ++it) {
		*it += (mM.first + mM.second) / 2;
	}
	return c;
}

int menuItem(){
	std::cout << "Выберите действие:\n\n";
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

void inputNM(int *N, int *M) {
	std::cout << "\nВведите количество чисел: ";
	std::cin >> *N;
	std::cout << "\nВведите границу диапазона M: ";
	std::cin >> *M;
	std::cout << std::endl;
} 

void inputFileName(std::string *fileName) {
	std::cout << "Введите имя файла: ";
	std::cin >> *fileName;
}

void doMenuActions(){
	int item;
	while ((item = menuItem()) != 0)
	{
		std::string fileName;
		int N, M;
		container c;
		switch (item)
		{
		case 1:
			inputFileName(&fileName);
			inputNM(&N, &M);
			fillFileWithRandNumbers_cycle(fileName, N, M);
			break;
		case 2:
			inputFileName(&fileName);
			inputNM(&N, &M);
			fillContainerWithRandNumbers(c, N, M);
			fillFileFromContainer(fileName, c);
			break;
		case 3:
			inputNM(&N, &M);
			fillContainerWithRandNumbers(c, N, M);
			break;
		case 4:
			inputFileName(&fileName);
			fillContainerFromFile(fileName, c);
			outputContainer(c);
			break;
		case 5:
			std::cout << "Исходный контейнер: ";
			outputContainer(c);
			modify(c);
			std::cout << "Преобразованный контейнер: ";
			outputContainer(c);
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			inputFileName(&fileName);
			saveContainerToFile(c, fileName);
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

