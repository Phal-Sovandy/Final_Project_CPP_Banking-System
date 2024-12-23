#ifndef DATE_DSA
#define DATE_DSA

bool IsLeapYear(int year)
{
    // Leap year is divisable by 4 , 400 but not 100
    return (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0));
}
int CountLeapYear(int year)
{
    // count leap year from 1900 to given year
    return (year - 1900) / 4 - (year - 1900) / 100 + (year - 1900) / 400;
}
int CountDaysInMonth(int month, int year)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && IsLeapYear(year))
    {
        return 29;
    }
    return daysInMonth[month - 1];
}
int DaysFromYear1900(int date, int month, int year)
{
    int totalDayFromYear1900 = 0;

    totalDayFromYear1900 = (year - 1900) * 365 + CountLeapYear(year); // + CountLeapYear because each leap year have 1 more days than others

    for (int i = 1; i < month; i++)
    {
        totalDayFromYear1900 += CountDaysInMonth(i, year);
    }
    totalDayFromYear1900 += date;

    return totalDayFromYear1900;
}
class Date
{
public:
    int date, month, year;
    int daysFromYear1900;
    Date() : date(1), month(1), year(1900), daysFromYear1900(0) {}
    Date(int date, int month, int year)
    {
        this->date = date;
        this->month = month;
        this->year = year;
        this->daysFromYear1900 = DaysFromYear1900(date, month, year);
    }
};
#endif