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
myContainer& fillDequeWithRandNumbers(myContainer &c, int N, int M) {
	std::generate(c.begin(), c.end(), rand(M));
	return c;
}

//Заполнение файла N случайными числами из диапазона [-M, M] 
std::fstream& fillFileWithRandNumbers_std(std::string fileName, myContainer c) {
	std::fstream f(fileName);
	for (cIterator it = c.begin(); it != c.end(); ++it)
		f << *it << "\n";
	f.close();
	return f;
}

//Заполнение контейнера числами из файла
std::deque<int>& fillContainerFromFile(std::ifstream& f) {

}

int menuItem()
{
	std::cout << "Выберите действие:\n";
	std::cout << "1 - Заполнение текстового файла N целыми случайными числами в диапазоне от -M до M (в цикле)\n";
	std::cout << "2 - Заполнение текстового файла N целыми случайными числами в диапазоне от -M до M (с использованием std::generate)\n";
	std::cout << "3 - Заполнение контейнера числами из файла\n";
	std::cout << "4 - Преобразование контейнера\n";
	std::cout << "5 - Преобразование выбранной части контейнера\n";
	std::cout << "6 - Преобразование контейнера с использованием алгоритма std::transform\n";
	std::cout << "7 - Преобразование контейнера с использованием алгоритма std::for_each\n";
	std::cout << "8 - Вычислить сумму чисел, содержащихся в контейнере\n";
	std::cout << "9 - Вычислить среднее арифметическое чисел, содержащихся в контейнере\n";
	std::cout << "0 - Выход из программы\n";
	std::cout << std::endl;
	int item = -1;
	std::cin >> item;
	while ((item > 9) || (item < 0))
	{
		std::cout << "Повторите ввод! " << std::endl;
		std::cin >> item;
	}
	std::cout << std::endl;
	return item;
}

void doMenuActions()
{
	int item;
	while ((item = menuItem()) != 0)
	{
		std::string fileName;
		int N, M;
		std::cout << "Введите имя файла: ";
		std::cin >> fileName;
		std::cout << "\nВведите количество чисел: ";
		std::cin >> N;
		myContainer c(N);
		std::cout << "\nВведите границу диапазона M: ";
		std::cin >> M;
		fillDequeWithRandNumbers(c, N, M);
		switch (item)
		{
		case 1:
			fillFileWithRandNumbers_cycle(fileName, N, M);
			break;
		case 2:
			fillFileWithRandNumbers_std(fileName, c);
			break;
		case 3:
		{
			std::cout << "Введите имя файла: ";
			std::cin >> fileName;
			//fillDeque(f, c);
			break;
		}
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
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

