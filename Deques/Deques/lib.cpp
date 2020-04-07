#include "pch.h"
#include "lib.h"


//поиск первого отрицательного числа в деке
int find_first_negative(deque<int> &container)
{
	int result = 0;
	for (int elem : container)
	{
		if (elem < 0)
		{
			result = elem;
			break;
		}
	}
	if (result == 0)
	{
		throw exception("В контейнере нет отрицательных чисел");
	}
	else
		return result;
}

//умножение elem на negative, если elem чётный
int multiply_even(int &elem, int negative)
{
	if (!(elem & 1))
		elem *= negative;
	return elem;
}

//возвращает случайное число в диапазоне min...max
int custom_random(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

//заполнение файла случайными N числами в диапазоне -M...M с использованием цикла или std::generate
fstream file_fill(int M, int N, bool use_cycle, const char* filename)
{
	fstream file_stream;
	file_stream.open(filename, ios::out);
	if (file_stream.is_open())
	{
		if (use_cycle)
		{
			int rand_num = 0;
			for (int i = 0; i < N; i++)
			{
				rand_num = custom_random(-M, M);
				file_stream << ' ' << rand_num;
			}
		}
		else
		{
			vector<int> num_container(N);
			generate(num_container.begin(), num_container.end(), [M] { return custom_random(-M, M); });
			for (int elem : num_container)
			{
				file_stream << ' ' << elem;
			}
		}
	}
	else
	{
		throw exception("Ошибка открытия/создания файла");
	}
	file_stream.close();
	return file_stream;
}

//заполнение дека из файла
deque<int> file_to_deque(const char* filename)
{
	fstream file_stream;
	file_stream.open(filename, ios::in);
	if (file_stream.is_open())
	{
		deque<int> result {};
		int elem;
		while (!file_stream.eof())
		{
			file_stream >> elem;
			result.push_back(elem);
		}
		file_stream.close();
		return result;
	}
	else
	{
		throw exception("Ошибка открытия файла");
	}
}

//выполнение основной задачи с использованием цикла, std::transform или std::for_each
void modify(deque<int> &container, OPERATION_TYPE op_type = CYCLE)
{
	int first_negative = find_first_negative(container);
	switch (op_type)
	{
		case CYCLE:
			for (auto i = container.begin(); i < container.end(); i++)
				multiply_even(*i, first_negative);
			break;
		case TRANSFORM:
			transform(container.begin(), container.end(), container.begin(), 
				[first_negative](int &elem) { return multiply_even(elem, first_negative); });
			break;
		case FOREACH:
			for_each(container.begin(), container.end(), 
				[first_negative](int &elem) { return multiply_even(elem, first_negative); });
			break;
	}
	return;
}

//перегрузка modify, принимающая на вход итераторы начала и конца обрабатываемой части дека
void modify(deque<int> &container, deque<int>::iterator begin, deque<int>::iterator end, OPERATION_TYPE op_type = CYCLE)
{
	int first_negative = find_first_negative(container);
	switch (op_type)
	{
	case CYCLE:
		for (auto i = begin; i < end; i++)
			multiply_even(*i, first_negative);
		break;
	case TRANSFORM:
		transform(begin, end, begin,
			[first_negative](int &elem) { return multiply_even(elem, first_negative); });
		break;
	case FOREACH:
		for_each(begin, end,
			[first_negative](int &elem) { return multiply_even(elem, first_negative); });
		break;
	}
	return;
}

//сумма всех чисел в деке
int sum(deque<int> &container)
{
	int result = 0;
	for (int elem : container)
		result += elem;
	return result;
}

//среднее арифметическое чисел дека
float average(deque<int> &container)
{
	return static_cast<float>(sum(container)) / container.size();
}

//вывод дека на экран
void output(deque<int> &container)
{
	for (int elem : container)
		cout << elem << ' ';
	cout << '\n';
}

//в файл
void output(deque<int> &container, const char* filename)
{
	ofstream file_stream;
	file_stream.open(filename, ios::out);
	if (file_stream.is_open())
	{
		for (int elem : container)
			file_stream << ' ' << elem;
	}
	else
	{
		throw exception("Файл не открыт.");
	}
}