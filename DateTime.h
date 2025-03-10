#ifndef DATETIME_H 
#define DATETIME_H 

#include <iostream> 

class DateTime { 
public:
    // Конструктор класса с параметрами по умолчанию
    DateTime(int year = 1, int month = 1, int day = 1,
        int hour = 0, int minute = 0, int second = 0);

    // Конструктор, принимающий строку в формате ISO
    DateTime(const char* isoFormat);

    void input(); // Метод для ввода даты и времени
    void display() const; // Метод для отображения даты и времени
    int diffInDays(const DateTime& other) const; // Метод для вычисления разницы в днях с другой датой
    const char* dayOfWeek() const; // Метод для определения дня недели
    bool isValid() const; // Метод для проверки корректности даты и времени

private:
    int year, month, day, hour, minute, second; // Переменные для хранения даты и времени

    int daysInMonth(int m, int y) const; // Метод для получения количества дней в месяце
    bool isLeapYear(int y) const; // Метод для проверки, является ли год високосным
    int julianDay() const; // Метод для вычисления юлианского дня
    static int parseNumber(const char*& str); // Статический метод для парсинга числа из строки
};

#endif