/* ������� ����� ������������ 2 ���� 9 ������. (�15 �)
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
*  -------------------------------------------------------------------------------
   ��� ������� : B) ������������ �������(std::deque)
*  15. �������� � ������� ����� ��������� ������������ � ������������� �� ���������� �������� �����.
*/

#include "stdafx.h"

//��������� ���������� ������ ����� �� ��������� [-M, M]
int rand(int M) {
	return std::rand() % (2 * M) + (-M);
}

//���������� ����� N ���������� ������� �� ��������� [-M, M] (� �����)
std::fstream& fillFileWithRandNumbers_cycle(std::string fileName, int N, int M) {
	static std::fstream f(fileName, std::ios::out);
	for (int i = 0; i < N; ++i)
		f << (value_type)rand(M) << "\n";
	f.close();
	return f;
}

//���������� ���������� ���������� ������� �� ��������� [-M, M]
container& fillContainerWithRandNumbers(container &c, int N, int M) {
	c.resize(N);
	std::generate(c.begin(), c.end(), [&]() {return (value_type)rand(M); });
	return c;
}

//���������� ����� ���������� �� ���������� 
std::fstream& fillFileFromContainer(std::string fileName, container &c) {
	static std::fstream f(fileName, std::ios::out);
	for (cIterator it = c.begin(); it != c.end(); ++it)
		f << *it << "\n";
	f.close();
	return f;
}

//���������� ���������� ���������� �� �����
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

//����� ��������� ���������� �� �����
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
//����� ��������� �������� � ��������� �� ����������
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

//�������������� ���������� (15. �������� � ������� ����� ��������� ������������ � ������������� �� ���������� �������� �����.)
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

//�������������� ��������� ����� ����������
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

//������� (���������� ��������� ����� b)
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
	std::cout << " 0 - ����� �� ���������\n";
	std::cout << std::endl;

	int item = -1;
	std::cin >> item;

	while ((item > 11) || (item < 0))
	{
		std::cout << "��������� ����! " << std::endl;
		std::cin >> item;
	}
	std::cout << std::endl;

	return item;
}

void inputNM(int &N, int &M) {
	std::cout << "\n������� ���������� �����: ";
	std::cin >> N;
	std::cout << "\n������� ������� ��������� M: ";
	std::cin >> M;
	std::cout << std::endl;
} 

void inputFileName(std::string &fileName) {
	std::cout << "������� ��� �����: ";
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
			std::cout << "���������: ";
			outputContainer(c);
			break;
		case 5:
			std::cout << "�������� ���������:\n";
			outputContainer(c);
			if (modify(c) == 0) {
				std::cout << "��������������� ���������:\n";
				outputContainer(c);
			}
			else {
				std::cout << "���������� ��������� ��������������." << std::endl;
			}
			break;
		case 6: {
			cIterator first, last;
			int num_first, num_last;
			bool ok;

			std::cout << "�������, � ������ �� ����� ������� (������������) ��������� ��������� ��������������:\n";
			do {
				std::cout << "c ";
				std::cin >> num_first;
				std::cout << "�� ";
				std::cin >> num_last;
				ok = (num_first > 0) && (num_first <= c.size()) && (num_last > num_first) && (num_last <= c.size());
				if (!ok) {
					std::cout << "������! ��������� ����:\n";
				}
			} while (!ok);
			std::cout << std::endl;
			first = c.begin() + num_first - 1;
			last = c.end() - (c.size() - num_last);

			std::cout << "\n�������� ���������:\n";
			outputContainer(c);
			if (modify(first, last, c) == 0) {
				std::cout << "��������������� ���������:\n";
				outputContainer(c);
			}
			else {
				std::cout << "���������� ��������� ��������������." << std::endl;
			}
		}
			break;
		case 7:
			std::cout << "�������� ���������:\n";
			outputContainer(c);
			if (transform(c) == 0) {
				std::cout << "��������������� ���������:\n";
				outputContainer(c);
			}
			else {
				std::cout << "���������� ��������� ��������������." << std::endl;
			}
			break;
		case 8:
			std::cout << "�������� ���������:\n";
			outputContainer(c);
			if (modify_for_each(c) == 0) {
				std::cout << "��������������� ���������:\n";
				outputContainer(c);
			}
			else {
				std::cout << "���������� ��������� ��������������." << std::endl;
			}
			break;
		case 9:
			std::cout << "��������: ";
			outputContainer(c);
			std::cout << "����� ��������� ����������: " << sum(c) << std::endl;
			break;
		case 10:
			std::cout << "��������: ";
			outputContainer(c);
			std::cout << "������� �������������� ��������� ����������: " << average(c) << std::endl;
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

