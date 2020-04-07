//B9. Умножить каждое четное число на первое отрицательное число (для deque)
#include "pch.h"
#include "lib.h"
#include <time.h>
#define FILENAME "D:\\numbers.txt"

using namespace std;

int menu()
{
	cout << "\nВведите число, соответствующее пунтку меню: \n";
	cout << "1 — заполнить текстовый файл " << FILENAME << " случайными числами" << '\n';
	cout << "2 — заполнить контейнер числами из файла " << FILENAME << '\n';
	cout << "3 — выполнить задачу (умножить каждое четное число в контейнере на первое отрицательное число)" << '\n';
	cout << "4 — посчитать сумму всех чисел в контейнере" << '\n';
	cout << "5 — посчитать среднее арифметическое чисел в контейнере" << '\n';
	cout << "6 — вывести контейнер в консоль" << '\n';
	cout << "7 — вывести контейнер в файл " << FILENAME << '\n';
	cout << "Другое число — Завершить работу" << '\n' << '\n';
	int answer;
	cin >> answer;
	return answer;
}

int main()
{
	system("chcp 1251");
	system("cls");
	time_t null_time = time(NULL);
	srand(null_time);
	int answer = 1;
	int N, M;
	deque<int> container;
	while (answer < 8 && answer > 0)
	{
		answer = menu();
		switch (answer)
		{
			case 1:
				cout << "Введите границу диапазона M: ";
				cin >> M;
				cout << "\nВведите кол-во чисел N: ";
				cin >> N;
				cout << "\nВыберите метод заполнения: ";
				cout << "\n1 — std::generate\n2 — цикл\n";
				cin >> answer;
				while (answer != 1 && answer != 2)
				{
					cout << "\nНеверный номер. Повторите ввод: ";
					cin >> answer;
				}
				try 
				{ 
					file_fill(M, N, (answer - 1), FILENAME);
					cout << "Файл заполнен.\n";
				}
				catch(exception) 
				{ 
					cout << "Ошибка заполнения файла.\n";
				}
				break;
			case 2:
				try 
				{ 
					container = file_to_deque(FILENAME);
					cout << "Контейнер заполнен: ";
					output(container);
				}
				catch(exception)
				{
					cout << "Ошибка открытия файла.\n";
				}
				break;
			case 3:
				cout << "Выберите метод: \n";
				cout << "1 — цикл\n";
				cout << "2 — std::transform\n";
				cout << "3 — std::for_each\n";
				cin >> answer;
				while (answer < 1 && answer > 3)
				{
					cout << "\nНеверный номер. Повторите ввод: ";
					cin >> answer;
				}
				try
				{
					modify(container, static_cast<OPERATION_TYPE>(answer - 1));
					cout << "Контейнер модифицирован: ";
					output(container);
				}
				catch (exception)
				{
					cout << "В контейнере нет отрицательных чисел.\n";
				}
				break;
			case 4:
				cout << "Сумма: " << sum(container) << '\n';
				break;
			case 5:
				cout << "Среднее арифметическое: " << average(container) << '\n';
				break;
			case 6:
				cout << "Контейнер: ";
				output(container);
				break;
			case 7:
				try
				{
					output(container, FILENAME);
					cout << "Сохранено.\n";
				}
				catch (exception)
				{
					cout << "Ошибка открытия файла.\n";
				}
				break;
		}
	}
}
