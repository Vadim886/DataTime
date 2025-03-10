#include "DateTime.h"
#include <iostream>

using namespace std;

// Конструктор класса DateTime с параметрами для инициализации даты и времени
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {
    // Проверка корректности даты и времени
    if (!isValid()) {
        cout << "Error: Incorrect date\n";
        exit(1);
    }
}

// Вспомогательная функция для парсинга числа из строки
int DateTime::parseNumber(const char*& str) {
    int result = 0; 
    // Цикл для извлечения цифр из строки
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0'); // Формирование числа
        str++; 
    }
    return result; 
}

// Конструктор, принимающий строку в формате ISO
DateTime::DateTime(const char* isoFormat) {
    const char* ptr = isoFormat; // Указатель на строку формата
    year = parseNumber(ptr); ptr++; // год
    month = parseNumber(ptr); ptr++; // месяц
    day = parseNumber(ptr); ptr++; // день
    hour = parseNumber(ptr); ptr++; // час
    minute = parseNumber(ptr); ptr++; // минута
    second = parseNumber(ptr); // секунда

    // Проверка корректности даты и времени
    if (!isValid()) {
        cout << "Error: Incorrect date\n";
        exit(1);
    }
}

// Метод для ввода
void DateTime::input() {
    char buffer[20];
    cout << "Enter the date (yyyy-MM-DDThh:mm:ss): ";
    cin.getline(buffer, 20); // Чтение строки из ввода
    *this = DateTime(buffer); // Инициализация объекта DateTime 
}

// Метод для отображения даты и времени в формате DD.MM.YYYY
void DateTime::display() const {
    if (day < 10) cout << '0'; // Добавление ведущего нуля к дню
    cout << day << "."; // Вывод дня
    if (month < 10) cout << '0'; // Добавление ведущего нуля к месяцу
    cout << month << "." << year << "\n"; // Вывод месяца и года
}

// Метод для проверки, является ли год високосным
bool DateTime::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Метод для получения количества дней в месяце
int DateTime::daysInMonth(int m, int y) const {
    switch (m) { // Проверка месяца
    case 2: return isLeapYear(y) ? 29 : 28; // Февраль
    case 4: case 6: case 9: case 11: return 30; // Месяцы с 30 днями
    default: return 31; // Остальные месяцы
    }
}

// Метод для проверки корректности даты и времени
bool DateTime::isValid() const {
    return (year >= 1) && 
        (month >= 1 && month <= 12) && 
        (day >= 1 && day <= daysInMonth(month, year)) && 
        (hour >= 0 && hour < 24) && 
        (minute >= 0 && minute < 60) && 
        (second >= 0 && second < 60); 
}

// Метод для вычисления юлианского дня для текущей даты
int DateTime::julianDay() const {
    int a = (14 - month) / 12; // Вычисление корректировки для месяца
    int y = year + 4800 - a; // Корректировка года
    int m = month + 12 * a - 3; // Корректировка месяца
    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045; // Возврат юлианского дня
}

// Метод для определения дня недели для текущей даты
const char* DateTime::dayOfWeek() const {
    const char* days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" }; // Массив дней недели
    int jd = julianDay(); // Получение юлианского дня
    return days[jd % 7]; // Возврат дня недели
}

// Метод для вычисления разницы в днях между двумя датами
int DateTime::diffInDays(const DateTime& other) const {
    int jd1 = julianDay(); // Юлианский день текущей даты
    int jd2 = other.julianDay(); // Юлианский день другой даты
    return jd1 > jd2 ? jd1 - jd2 : jd2 - jd1; // Возврат разницы в днях
}

