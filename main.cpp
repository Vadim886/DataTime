#include "DateTime.h"

using namespace std;

int main() {
    DateTime date1("2023-12-25T12:30:45");
    cout << "Data 1: ";
    date1.display();
    cout << "Day of the week: " << date1.dayOfWeek() << "\n";

    DateTime date2;
    date2.input();
    cout << "Data 2: ";
    date2.display();
    cout << "Day of the week: " << date2.dayOfWeek() << "\n";

    cout << "The difference in days: " << date1.diffInDays(date2) << "\n";

    return 0;
}