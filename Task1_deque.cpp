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
int randNumber(int M) {
	srand(time(NULL));
	return rand() % (2 * M) + (-M);
}

//���������� ����� N ���������� ������� �� ��������� [-M, M] (� �����)
std::fstream& fillFileWithRandNumbers_cycle(std::string fileName, int N, int M) {
	std::fstream f(fileName);
	srand(time(NULL));
	for (int i = 0; i < N; ++i)
		f << randNumber(M) << "\n";
	f.close();
	return f;
}

//���������� ���������� ���������� ������� �� ��������� [-M, M]
std::deque<int>& fillDequeWithRandNumbers(std::deque<int> &d, int N, int M) {
	//std::generate(d.begin(), d.end(), randNumber(M));
	return d;
}

//���������� ����� N ���������� ������� �� ��������� [-M, M] 
std::fstream& fillFileWithRandNumbers_std(std::string fileName, std::deque<int> d) {
	std::fstream f(fileName);
	for (std::deque<int>::iterator it = d.begin(); it != d.end(); ++it)
		f << *it << " ";
	f.close();
	return f;
}

int menuItem()
{
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

void doMenuActions()
{
	int item;
	while ((item = menuItem()) != 0)
	{
		std::string fileName;
		int N, M;
		std::cout << "������� ��� �����: ";
		std::cin >> fileName;
		std::cout << "\n������� ���������� �����: ";
		std::cin >> N;
		std::deque<int> d(N);
		switch (item)
		{
		case 1:
			std::cout << "\n������� �: ";
			std::cin >> M;
			fillFileWithRandNumbers_std(fileName, d);
			//fillFileWithRandNumbers_cycle(fileName, N, M);
			break;
		case 2:
			//fillFileWithRandNumbers_std(fileName, d);
			break;
		case 3:
		{
			std::cout << "������� ��� �����: ";
			std::cin >> fileName;
			//fillDeque(f, d);
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

