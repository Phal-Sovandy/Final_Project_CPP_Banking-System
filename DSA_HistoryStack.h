#ifndef DSA_History
#define DSA_History
#include "DSA_Customer.h"
class HistoryData
{
public:
    std::string action = "";
    float balance;
    HistoryData *Next = nullptr;

    HistoryData(std::string action, float balance)
    {
        this->action = action;
        this->balance = balance;
    }
};
class HistoryStack
{
private:
    HistoryData *top;
    int length;

public:
    HistoryStack()
    {
        top = nullptr;
        length = 0;
    }

    ~HistoryStack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(std::string action, float balance)
    {
        HistoryData *newTop = new HistoryData(action, balance);
        newTop->Next = top;
        this->top = newTop;

        this->length++;
    }

    void pop()
    {
        if (!isEmpty())
        {
            HistoryData *temp = top->Next;
            delete top;
            top = temp;

            this->length--;
            if (this->length == 0)
            {
                top = nullptr;
            }
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "error occurs: History is empty\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }

    void peek()
    {
        std::cout << "\nLatest customer action:\n";
        std::cout << "----------------------------------------------------------";
        std::cout << '\n'
                  << std::left << std::setw(30) << "Action" << "Balance\n";
        std::cout << "----------------------------------------------------------\n";
        if (!isEmpty())
        {
            std::cout << std::left << std::setw(30) << top->action << top->balance << '\n';
        }
        else
        {
            std::cout << "No history data available\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    int size()
    {
        return this->length;
    }
    void printHistory()
    {
        std::cout << "\nCustomer's action History:\n";
        std::cout << "----------------------------------------------------------";
        std::cout << '\n'
                  << std::left << std::setw(30) << "Action" << "Balance\n";
        std::cout << "----------------------------------------------------------\n";

        HistoryData *temp = this->top;
        if (!isEmpty())
        {
            while (temp)
            {
                std::cout << std::left << std::setw(30) << temp->action << temp->balance << '\n';
                temp = temp->Next;
            }
        }
        else
        {
            std::cout << "No history data available\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
};

#endif