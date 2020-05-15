/* Напишите программу, которая вычисляет дату следующего дня.
Пример выполнения программы:
Введите цифрами дату (число, месяц, год): 31 12 2018
Последний день месяца! Завтра 01.01.2019             */

#include <iostream>
#include <string>

unsigned short check_value_from_user_as_date(const std::string& what_we_check, const unsigned min, const unsigned max)
{
	int value_to_check;
	std::cin >> value_to_check;
	while (std::cin.fail()||(value_to_check < min)||(value_to_check > max))
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::string left_to_enter;
		if (what_we_check == "День")
			left_to_enter = "! Введите дату в формате ДД ММ ГГГГ ещё раз: ";
		else if (what_we_check == "Месяц")
			left_to_enter = "! Введите месяц и год в формате ММ ГГГГ ещё раз: ";
		else if (what_we_check == "Год")
			left_to_enter = "! Введите год в формате ГГГГ ещё раз: ";
		std::cout << what_we_check << " должен быть натуральным числом от " << min << " до " << max << left_to_enter;
		std::cin >> value_to_check;
	}
	return static_cast<unsigned short>(value_to_check);
}

// выводим дату в привычном формате ДД.ММ.ГГГГ, иначе может быть 9.7.1999
void print_date(const unsigned short day, const unsigned short month, const unsigned short year)
{
	if (day < 10)
		std::cout << "0" << day << ".";
	else std::cout << day << ".";
	if (month < 10)
		std::cout << "0" << month << ".";
	else std::cout << month << ".";
   std::cout << year << std::endl;
}

// возвращает истину, если год - високосный
bool is_leap_year(const unsigned short year)
{
	if (year % 400 == 0)
		return true;
	// если не делится на 400, но делится на 100
	if (year % 100 == 0)
		return false;
	// если просто делится на 4 без остатка (но не делится на 100 и 400)
	if (year % 4 == 0)
		return true;
	// иначе не делится на 4 без остатка
	return false;
}

// возвращает количество дней в месяце. Для определения с февралём нужен год (для других месяцев без разницы)
unsigned short days_in_month(const unsigned short month, const unsigned short year = 2020)
{
	switch (month)
	{
	case 2:
		if (is_leap_year(year)) return 29;
		else return 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 31;
	}
}

// возвращает истину, если дата существует и ложь, если нет (например 30.02 - не существует)
bool next_day_calculation(unsigned short& day, unsigned short& month, unsigned short& year)
{
	if (day < days_in_month(month, year))
	{
		++day;
		return true;
	}
	else if (day == days_in_month(month, year))
	{
		day = 1;
		if (month < 12)
			++month;
		else
		{
			month = 1;
			++year;
		}
		return true;
	}
	else // число в дате - больше возможного
		return false;
}

int main()
{
	setlocale(LC_CTYPE, "rus"); // для вывода сообщений на кириллице
	std::cout << "Программа вычисляет дату следующего дня.\n";

	while (true)
	{
		std::cout << "Введите дату в формате ДД ММ ГГГГ: ";
		unsigned short day = check_value_from_user_as_date("День", 1, 31);
		unsigned short month = check_value_from_user_as_date("Месяц", 1, 12);
		unsigned short year = check_value_from_user_as_date("Год", 1000, 3000);
		std::cout << "Заданная дата ";
		print_date(day, month, year);
		if (next_day_calculation(day, month, year))
		{
			std::cout << "Дата следующего дня: ";
			print_date(day, month, year);
		}
		else 
			std::cout << "Такой даты нет, попробуйте ввести другую!" << std::endl;
	}
}