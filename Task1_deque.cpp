/*  ������� ����� ������������ 2 ���� 9 ������. (�15 �)
 *  ����������� ������ ���� ���������� ��������� � ��������� ����, ����������� ��� ������������� ���� ������(1 - 8) ��� ������ �� �����������
 *  � ������ �� ��������������.
 *  �������� ���������, ���������� ��������� ������� :
 *  1. ������� ���������� ���������� ����� N ������ ���������� ������� � ��������� �� - M �� M.��� �����, N � M ��������� �� ���� �������,
 *  ���� ������������ �������� ��� ���������(������������ ������ ����� - ������). ����������� ��� �������� ��������� ����� � � ����� �
 *  � �������������� ��������� std::generate.
 *  2. �������, ���������� ���� �� ����, � ������������ ���������������� ���������, ����������� ������� �� �����.
 *  3. ������� modify, ����������� �������������� ����������� ����������.�� ���� ������� ������ ��������� ���������, � �������� ����������
 *  ������� ������ ���������� ���������������� ���������.
 *  4. ������������� ������� modify, ����������� �� ���� ��������� ������ � ����� �������������� ����� ����������.
 *  5. �������, ����������� ��������� �������������� � �������������� ��������� std::transform ������ ������� modify.
 *  6. �������, ����������� ��������� �������������� � �������������� ��������� std::for_each ������ ������� modify.
 *  7. �������, ����������� ����� � ������� �������������� �����, ������������ � ����������.
 *  8. ������� ������ ���������� � ���� � �� �����(�����������).
 *  -------------------------------------------------------------------------------------------------------------------------------------
 *  ��� ������� : B) ������������ �������(std::deque)
 *  15. �������� � ������� ����� ��������� ������������ � ������������� �� ���������� �������� �����.
 */

#include "stdafx.h"

typedef double value_type;
typedef std::deque<value_type> container;
typedef container::iterator cIterator;

//��������� ���������� ������ ����� �� ��������� [-M, M]
int rand(int M) {
	if(M != 0)
		return std::rand() % (2 * M + 1) + (-M);
	return 0;
}

//���������� ����� N ���������� ������� �� ��������� [-M, M] (� �����)
std::fstream& fillFileWithRandNumbers_cycle(std::string fileName, int N, int M) {
	std::fstream f(fileName, std::ios::out);
	for (int i = 0; i < N; ++i)
		f << (value_type)rand(M) << "\n"; 
	f.close();
	return f;
}

//���������� ���������� ���������� ������� �� ��������� [-M, M]
container& fillContainerWithRandNumbers(container &c, int N, int M) {
	c.resize(N);
	std::generate(c.begin(), c.end(), [M]() {return (value_type)rand(M); });
	return c;
}

//���������� ����� ���������� �� ���������� 
std::fstream& fillFileFromContainer(std::string fileName, container &c) {
	std::fstream f(fileName, std::ios::out);
	for (cIterator it = c.begin(); it != c.end(); ++it)
		f << *it << "\n";
	f.close();
	return f;
}

int fillContainerFromFile(std::string fileName, container &c) {
	c.clear();
	std::fstream f(fileName, std::ios_base::in);
	if (f.is_open()) {
		std::copy(
			std::istream_iterator<value_type>(f),
			std::istream_iterator<value_type>(),
			std::back_inserter<container>(c));
		return 0;
	}
	else {
		return -1;
	}
}

//����� ��������� ���������� �� �����
void printContainer(container &c) {
	for (cIterator it = c.begin(); it != c.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

//����� ��������� �������� � ���������
double halfsumOfMinAndMax(cIterator first, cIterator last) {
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

//�������������� ���������� (15. �������� � ������� ����� ��������� ������������ � ������������� �� ���������� �������� �����.)
void modify(container &c) {
	double hs = halfsumOfMinAndMax(c.begin(), c.end());
	for (cIterator it = c.begin(); it != c.end(); ++it) {
		(*it) += hs;
	}
}

//�������������� ��������� ����� ����������
void modify(cIterator first, cIterator last) {
	double hs = halfsumOfMinAndMax(first, last);
	for (cIterator it = first; it != last; ++it) {
		*it += hs;
	}
}

//������� (���������� ��������� ����� b)
class addNumber {
public:
	explicit addNumber(double b) : a(b) {}
	double operator()( value_type el) const {
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

void transform(container &c) {
		double hs = halfsumOfMinAndMax(c.begin(), c.end());
		std::transform(c.begin(), c.end(), c.begin(), addNumber(hs));
}

void modify_for_each(container &c) {
		double hs = halfsumOfMinAndMax(c.begin(), c.end());
		std::for_each(c.begin(), c.end(), addNumber_for_each(hs));
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
	std::cout << "\n�������� ��������:\n\n";
	std::cout << " 1 - ���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M (� �����)\n";
	std::cout << " 2 - ���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M (� �������������� std::generate)\n";
	std::cout << " 3 - ���������� ���������� N ���������� �������  � ��������� �� -M �� M \n";
	std::cout << " 4 - ���������� ���������� ������� �� �����\n";
	std::cout << " 5 - �������������� ����������\n";
	std::cout << " 6 - �������������� ��������� ����� ����������\n";
	std::cout << " 7 - �������������� ���������� � �������������� ��������� std::transform\n";
	std::cout << " 8 - �������������� ���������� � �������������� ��������� std::for_each\n";
	std::cout << " 9 - ��������� ����� �����, ������������ � ����������\n";
	std::cout << "10 - ��������� ������� �������������� �����, ������������ � ����������\n";
	std::cout << "11 - ��������� ��������� � ����\n";
	std::cout << "12 - ������� �������� ���������� �� �����\n";
	std::cout << " 0 - ����� �� ���������\n" << std::endl;

	int item = -1;
	std::cin >> item;

	while ((item > 12) || (item < 0))
	{
		std::cout << "��������� ����! " << std::endl;
		std::cin >> item;
	}
	std::cout << std::endl;

	return item;
}

void inputNM(int &N, int &M) {
	do {
		std::cout << "\n������� ���������� �����: ";
		std::cin >> N;
	} while (N < 0);
	std::cout << "\n������� ������� ��������� M: ";
	std::cin >> M;
	M = abs(M);
	std::cout << std::endl;
} 

void inputFileName(std::string &fileName) {
	std::cout << "������� ��� �����: ";
	std::cin >> fileName;
}

int outputContainerToConsole(container &c) {
	if (!c.empty()) {
		std::cout << "��������: ";
		printContainer(c);
		return 0;
	}
	else
		std::cout << "��������� ����." << std::endl;
	return -1;
}

void doMenuActions(){
	int item;
	container c;
	std::fstream f;

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
			if (fillContainerFromFile(fileName, c) == 0) {
				outputContainerToConsole(c);
			}
			else {
				std::cout << "�� ������� ������� ����.";
			}
			break;
		case 5:
			if (outputContainerToConsole(c) == 0) {
				std::cout << "��������������� ���������:\n";
				modify(c);
				printContainer(c);
			}
			break;
		case 6: {
			cIterator first, last;
			int num_first, num_last;
			bool ok;
			if (outputContainerToConsole(c) == 0) {
				std::cout << "�������, � ������ �� ����� ������� (������������) ��������� ��������� ��������������:\n";
				do {
					std::cout << "c ";
					std::cin >> num_first;
					std::cout << "�� ";
					std::cin >> num_last;
					ok = (num_first > 0) && (num_first <= c.size()) && (num_first <= num_last) && (num_last <= c.size());
					if (!ok) {
						std::cout << "������! ��������� ����:\n";
					}
				} while (!ok);
				std::cout << std::endl;

				first = c.begin() + num_first - 1;
				last = c.end() - (c.size() - num_last);

				modify(first, last);
				std::cout << "��������������� ���������:\n";
				printContainer(c);
			}
			break;
		}
		case 7:
			if (outputContainerToConsole(c) == 0) {
				transform(c);
				std::cout << "��������������� ���������:\n";
				printContainer(c);
			}
			break;
		case 8:
			if (outputContainerToConsole(c) == 0) {
				modify_for_each(c);
				std::cout << "��������������� ���������:\n";
				printContainer(c);
			}
			break;
		case 9:
			if (outputContainerToConsole(c) == 0) {
				std::cout << "����� ��������� ����������: " << sum(c) << std::endl;
			}
			break;
		case 10:
			if (outputContainerToConsole(c) == 0) {
				std::cout << "������� �������������� ��������� ����������: " << average(c) << std::endl;
			}
			break;
		case 11:
			inputFileName(fileName);
			fillFileFromContainer(fileName, c);
			break;
		case 12:
			outputContainerToConsole(c);
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	doMenuActions();
    return 0;
}

