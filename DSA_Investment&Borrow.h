#ifndef IVESTNBORROW_DSA
#define IVESTNBORROW_DSA

#include "DSA_Date.h"
#define INTERESTRATE 0.05
#define ANUALLLYPAY 0.2
#define INTERESTRATE_FOR_BORROW 0.05

class Investment
{
public:
    float depositedAmount = 0;
    Date *dayStart = nullptr;
    int dayLeft = 0;
    int period = 0; // In years
    float totalAmount = 0;

    Investment(float depositedAmount, int period, int dayNow, int monthNow, int yearNow)
    {
        this->depositedAmount = depositedAmount;
        this->period = period;
        this->totalAmount = depositedAmount * (INTERESTRATE * period + 1); // I = PRT (simple interest), totalAmount = I + Principle
        this->dayLeft = period * 365;
        if (dayNow > CountDaysInMonth(monthNow, yearNow))
        {
            dayNow = CountDaysInMonth(monthNow, yearNow);
        }
        else
        {
            this->dayStart = new Date(dayNow, monthNow, yearNow);
        }
    }
    ~Investment()
    {
        delete dayStart;
        dayStart = nullptr;
    }
};

class Borrow
{
public:
    int borrowedMoney = 0;
    Date *dayStart = nullptr;
    float monthlyPay = 0;

    Borrow(int initialBorrow, int dayNow, int monthNow, int yearNow)
    {

        this->borrowedMoney = initialBorrow * (1 + INTERESTRATE_FOR_BORROW); // INTERESTRATE_FOR_BORROW (interest rate)
        this->monthlyPay = (this->borrowedMoney * ANUALLLYPAY) / 12;
        if (dayNow >= 30)
        {
            this->dayStart = new Date(28, monthNow, yearNow);
        }
        else
        {
            this->dayStart = new Date(dayNow, monthNow, yearNow);
        }
    }
    ~Borrow()
    {
        delete dayStart;
        dayStart = nullptr;
    }
};

#endif