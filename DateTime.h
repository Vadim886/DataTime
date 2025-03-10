#ifndef DATETIME_H 
#define DATETIME_H 

#include <iostream> 

class DateTime { 
public:
    // ����������� ������ � ����������� �� ���������
    DateTime(int year = 1, int month = 1, int day = 1,
        int hour = 0, int minute = 0, int second = 0);

    // �����������, ����������� ������ � ������� ISO
    DateTime(const char* isoFormat);

    void input(); // ����� ��� ����� ���� � �������
    void display() const; // ����� ��� ����������� ���� � �������
    int diffInDays(const DateTime& other) const; // ����� ��� ���������� ������� � ���� � ������ �����
    const char* dayOfWeek() const; // ����� ��� ����������� ��� ������
    bool isValid() const; // ����� ��� �������� ������������ ���� � �������

private:
    int year, month, day, hour, minute, second; // ���������� ��� �������� ���� � �������

    int daysInMonth(int m, int y) const; // ����� ��� ��������� ���������� ���� � ������
    bool isLeapYear(int y) const; // ����� ��� ��������, �������� �� ��� ����������
    int julianDay() const; // ����� ��� ���������� ���������� ���
    static int parseNumber(const char*& str); // ����������� ����� ��� �������� ����� �� ������
};

#endif