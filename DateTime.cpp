#include "DateTime.h"
#include <iostream>

using namespace std;

// ����������� ������ DateTime � ����������� ��� ������������� ���� � �������
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {
    // �������� ������������ ���� � �������
    if (!isValid()) {
        cout << "Error: Incorrect date\n";
        exit(1);
    }
}

// ��������������� ������� ��� �������� ����� �� ������
int DateTime::parseNumber(const char*& str) {
    int result = 0; 
    // ���� ��� ���������� ���� �� ������
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0'); // ������������ �����
        str++; 
    }
    return result; 
}

// �����������, ����������� ������ � ������� ISO
DateTime::DateTime(const char* isoFormat) {
    const char* ptr = isoFormat; // ��������� �� ������ �������
    year = parseNumber(ptr); ptr++; // ���
    month = parseNumber(ptr); ptr++; // �����
    day = parseNumber(ptr); ptr++; // ����
    hour = parseNumber(ptr); ptr++; // ���
    minute = parseNumber(ptr); ptr++; // ������
    second = parseNumber(ptr); // �������

    // �������� ������������ ���� � �������
    if (!isValid()) {
        cout << "Error: Incorrect date\n";
        exit(1);
    }
}

// ����� ��� �����
void DateTime::input() {
    char buffer[20];
    cout << "Enter the date (yyyy-MM-DDThh:mm:ss): ";
    cin.getline(buffer, 20); // ������ ������ �� �����
    *this = DateTime(buffer); // ������������� ������� DateTime 
}

// ����� ��� ����������� ���� � ������� � ������� DD.MM.YYYY
void DateTime::display() const {
    if (day < 10) cout << '0'; // ���������� �������� ���� � ���
    cout << day << "."; // ����� ���
    if (month < 10) cout << '0'; // ���������� �������� ���� � ������
    cout << month << "." << year << "\n"; // ����� ������ � ����
}

// ����� ��� ��������, �������� �� ��� ����������
bool DateTime::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// ����� ��� ��������� ���������� ���� � ������
int DateTime::daysInMonth(int m, int y) const {
    switch (m) { // �������� ������
    case 2: return isLeapYear(y) ? 29 : 28; // �������
    case 4: case 6: case 9: case 11: return 30; // ������ � 30 �����
    default: return 31; // ��������� ������
    }
}

// ����� ��� �������� ������������ ���� � �������
bool DateTime::isValid() const {
    return (year >= 1) && 
        (month >= 1 && month <= 12) && 
        (day >= 1 && day <= daysInMonth(month, year)) && 
        (hour >= 0 && hour < 24) && 
        (minute >= 0 && minute < 60) && 
        (second >= 0 && second < 60); 
}

// ����� ��� ���������� ���������� ��� ��� ������� ����
int DateTime::julianDay() const {
    int a = (14 - month) / 12; // ���������� ������������� ��� ������
    int y = year + 4800 - a; // ������������� ����
    int m = month + 12 * a - 3; // ������������� ������
    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045; // ������� ���������� ���
}

// ����� ��� ����������� ��� ������ ��� ������� ����
const char* DateTime::dayOfWeek() const {
    const char* days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" }; // ������ ���� ������
    int jd = julianDay(); // ��������� ���������� ���
    return days[jd % 7]; // ������� ��� ������
}

// ����� ��� ���������� ������� � ���� ����� ����� ������
int DateTime::diffInDays(const DateTime& other) const {
    int jd1 = julianDay(); // ��������� ���� ������� ����
    int jd2 = other.julianDay(); // ��������� ���� ������ ����
    return jd1 > jd2 ? jd1 - jd2 : jd2 - jd1; // ������� ������� � ����
}

