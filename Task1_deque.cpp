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
*  ��� ������� : B) ������������ �������(std::deque)
*  15. �������� � ������� ����� ��������� ������������ � ������������� �� ���������� �������� �����.
*/

#include "stdafx.h"

//��������� ���������� ������ ����� �� ��������� [-M, M]
int rand(int M) {
	//srand(time(nullptr));
	return std::rand() % (2 * M) + (-M);
}

//���������� ����� N ���������� ������� �� ��������� [-M, M] (� �����)
std::fstream& fillFileWithRandNumbers_cycle(std::string fileName, int N, int M) {
	std::fstream f(fileName);
	for (int i = 0; i < N; ++i)
		f << rand(M) << "\n";
	f.close();
	return f;
}

//���������� ���������� ���������� ������� �� ��������� [-M, M]
myContainer& fillContainerWithRandNumbers(myContainer &c, int N, int M) {
	std::generate(c.begin(), c.end(), rand(M));
	return c;
}

//���������� ����� ���������� �� ���������� 
std::fstream& fillFileFromContainer(std::string fileName, myContainer &c) {
	std::fstream f(fileName);
	for (cIterator it = c.begin(); it != c.end(); ++it)
		f << *it << "\n";
	f.close();
	return f;
}

//���������� ���������� ���������� �� �����
myContainer& fillContainerFromFile(std::ifstream &f) {
	c.clear();
	if(f.is_open) {
		while (!f.eof()) {
			std::string s;
			std::getline(f, s);
			c.push_back(stoi(s));
		}
	}
		//reinterpret_cast<value_type>(s)
}

//����� ����������� ���������� �� �����
void outputContainer(myContainer c) {
	for (cIterator it = c.begin(); it != c.end(); ++it) {
		std::cout << *it << " ";
	}
}

int menuItem(){
	std::cout << "�������� ��������:\n";
	std::cout << "1 - ���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M (� �����)\n";
	std::cout << "2 - ���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M (� �������������� std::generate)\n";
	std::cout << "3 - ���������� ���������� ������� �� �����\n";
	std::cout << "4 - �������������� ����������\n";
	std::cout << "5 - �������������� ��������� ����� ����������\n";
	std::cout << "6 - �������������� ���������� � �������������� ��������� std::transform\n";
	std::cout << "7 - �������������� ���������� � �������������� ��������� std::for_each\n";
	std::cout << "8 - ��������� ����� �����, ������������ � ����������\n";
	std::cout << "9 - ��������� ������� �������������� �����, ������������ � ����������\n";
	std::cout << "0 - ����� �� ���������\n";
	std::cout << std::endl;
	int item = -1;
	std::cin >> item;
	while ((item > 9) || (item < 0))
	{
		std::cout << "��������� ����! " << std::endl;
		std::cin >> item;
	}
	std::cout << std::endl;
	return item;
}

void doMenuActions(){
	int item;
	while ((item = menuItem()) != 0)
	{
		std::string fileName;
		int N, M;
		std::cout << "������� ��� �����: ";
		std::cin >> fileName;
		std::cout << "\n������� ���������� �����: ";
		std::cin >> N;
		myContainer c(N);
		std::cout << "\n������� ������� ��������� M: ";
		std::cin >> M;
		switch (item)
		{
		case 1:
			fillFileWithRandNumbers_cycle(fileName, N, M);
			break;
		case 2:
			fillContainerWithRandNumbers(c, N, M);
			fillFileFromContainer(fileName, c);
			break;
		case 3:
		{
			std::cout << "������� ��� �����: ";
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

