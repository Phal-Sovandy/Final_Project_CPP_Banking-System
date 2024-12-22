#ifndef DSA_Project // If DSA_Project is not define this code will execute, this is called "include guard"
#define DSA_Project

#include <iostream>
#include <iomanip>
#include "DSA_Date.h"
#include "DSA_Investment&Borrow.h"
#include "DSA_HistoryStack.h"

class Customer
{
private:
    int accountNumber; // Store 4 digits number
    std::string fullName;
    bool sex; // 0 for Male, 1 for Female
    Date *dateOfBirth;
    float balance;
    Investment *investment;
    Borrow *borrow;
    HistoryStack *history = new HistoryStack();

public:
    Customer *Next = nullptr;

    Customer()
    {
        this->accountNumber = 0;
        this->fullName = "N/A";
        this->sex = true;
        this->dateOfBirth = nullptr;
        this->balance = 0;
        this->investment = nullptr;
        this->borrow = nullptr;
    }
    Customer(int accountNumber, std::string fullName, bool sex, Date *dateOfBirth, float balance, Investment *investment, Borrow *borrow)
    {
        this->accountNumber = accountNumber;
        this->fullName = fullName;
        this->sex = sex;
        this->dateOfBirth = dateOfBirth;
        this->balance = balance;
        this->investment = investment;
        this->borrow = borrow;
    }
    ~Customer()
    {
        delete dateOfBirth;
        dateOfBirth = nullptr;
        delete history;
        history = nullptr;
        if (investment)
        {
            delete investment;
            investment = nullptr;
        }
        if (borrow)
        {
            delete borrow;
            borrow = nullptr;
        }
    }
    
    int getAccNumber()
    {
        return this->accountNumber;
    }
    std::string getName()
    {
        return this->fullName;
    }
    bool getSex()
    {
        return this->sex;
    }
    Date *getDateOfBirth()
    {
        return this->dateOfBirth;
    }
    
    void deposit(float amount)
    {
        if (amount >= 0)
        {
            this->balance += amount;
            this->history->push("Deposit", this->balance);
            std::cout << "Deposit Successful\n";
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "Invalid Amount\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    void withdrawal(float amount)
    {
        if (amount <= this->balance && amount >= 0)
        {
            this->balance -= amount;
            this->history->push("Withdrawal", this->balance);
            std::cout << "Withdrawal Successful\n";
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "Invalid Amount\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    void withdrawInvestment(int currentDay)
    {
        if (this->investment)
        {
            if (currentDay - this->investment->dayLeft >= this->investment->dayStart->daysFromYear1900)
            {
                this->balance += this->investment->totalAmount;
                delete this->investment->dayStart;
                delete this->investment;
                this->investment = nullptr;

                this->history->push("Withdraw Investment", this->balance);
                std::cout << "Withdraw Investment Successful\n";
            }
            else
            {
                std::cout << "----------------------------------------------------------\n";
                std::cout << "Invalid Withdrawal\n";
                std::cout << "----------------------------------------------------------\n";
            }
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "No investment information available\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    void payForBorrow(int today)
    {
        if (this->borrow)
        {
            if(this->borrow->borrowedMoney == 0){
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "No Loan left to pay\n";
                    std::cout << "----------------------------------------------------------\n";
                    delete this->borrow;
                    this->borrow = nullptr;
                    this->history->push("Loan Paid", this->balance);
            }
            else if (today == this->borrow->dayStart->date)
            {
                if (this->balance < this->borrow->monthlyPay)
                {
                    std::cout << "Invalid Balance\n";
                }
                else
                {
                    this->balance -= this->borrow->monthlyPay;
                    this->borrow->borrowedMoney -= this->borrow->monthlyPay;
                    if(this->borrow->borrowedMoney <= 0){
                        delete this->borrow->dayStart;
                        delete this->borrow;
                        this->borrow = nullptr;
                    }
                    this->history->push("Loan Payment", this->balance);
                }
                std::cout << "Loan Payment Successful\n";
            }
            else
            {
                std::cout << "----------------------------------------------------------\n";
                std::cout << "Invalid Payment Date\n";
                std::cout << "----------------------------------------------------------\n";
            }
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "No loan information available\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    void transferToOthers(int reciverAccNumber, float amount){
        if (amount <= this->balance && amount >= 0)
        {
            this->balance -= amount;
            this->history->push("Transfer to " + std::to_string(reciverAccNumber), this->balance);
            std::cout << "Transfer Successful\n";
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "Invalid Amount\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    // Add balance to the customer for transfering action
    void reciverBalance(int senderAccNumber, float balance)
    {
        this->balance += balance;
        this->history->push("Recived from " + std::to_string(senderAccNumber), this->balance);
    }
    float getBalance()
    {
        return this->balance;
    }
    void showHistory()
    {
        this->history->printHistory();
    }
};

class CustomerList
{
private:
    Customer *Head;
    int customersCount;

    Customer *Merge(Customer *left, Customer *right, bool byName)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        if (byName)
        {
            if (left->getName() < right->getName())
            {
                left->Next = Merge(left->Next, right, byName);
                return left;
            }
            else
            {
                right->Next = Merge(left, right->Next, byName);
                return right;
            }
        }
        else
        {
            if (left->getDateOfBirth()->daysFromYear1900 > right->getDateOfBirth()->daysFromYear1900)
            {
                left->Next = Merge(left->Next, right, byName);
                return left;
            }
            else
            {
                right->Next = Merge(left, right->Next, byName);
                return right;
            }
        }
    }
    Customer *MergeSort(Customer *head, bool byName)
    {
        if (!head || !head->Next)
        {
            return head;
        }
        Customer *middle = GetMiddle(head);

        Customer *left = MergeSort(head, byName);
        Customer *right = MergeSort(middle, byName);

        return Merge(left, right, byName);
    }
    Customer *GetMiddle(Customer *head)
    {
        if (!head || !head->Next)
        {
            return head;
        }
        Customer *slow = head;
        Customer *fast = head;

        while (fast && fast->Next)
        {
            fast = fast->Next->Next;
            if (fast)
            {
                slow = slow->Next;
            }
        }
        Customer *temp = slow->Next;
        slow->Next = nullptr;
        return temp;
    }

public:
    CustomerList()
    {
        Head = nullptr;
        customersCount = 0;
    }
    CustomerList(Customer *customer1)
    {
        Head = customer1;
        customersCount++;
    }
    ~CustomerList()
    {
        Customer *current = this->Head;
        while (current)
        {
            Customer *temp = current;
            current = current->Next;
            delete temp;
        }
    }
    Customer *peek()
    {
        return this->Head;
    }
    void AddCustomer(int accountNumber, std::string fullName, bool sex, Date *dateOfBirth, float balance, Investment *investment, Borrow *borrow)
    {
        Customer *temp = this->Head;
        bool exist = false;
        Customer *newCustomer = new Customer(accountNumber, fullName, sex, dateOfBirth, balance, investment, borrow);

        if (!this->Head)
        {
            this->Head = newCustomer;
            this->customersCount++;
            std::cout << "Customer added successfully\n";
        }
        else
        {
            while (temp->Next)
            {
                if (temp->getAccNumber() == accountNumber)
                {
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Account number already exists!\n";
                    std::cout << "----------------------------------------------------------\n";

                    exist = true;
                    break;
                }
                temp = temp->Next;
            }

            if (!exist)
            {
                temp->Next = newCustomer;
                this->customersCount++;
                std::cout << "Customer added successfully\n";
            }
            else
            {
                std::cout << "----------------------------------------------------------\n";
                std::cout << "Customer already exist\n";
                std::cout << "----------------------------------------------------------\n";
            }
        }
    }

    void RemoveCustomer(int accountNumber)
    {
        Customer *temp = this->Head;
        if (temp)
        {
            if (temp->getAccNumber() == accountNumber)
            {
                this->Head = temp->Next;
                delete temp;
                temp = nullptr;
                this->customersCount--;
                std::cout << "Customer removed successfully\n";
            }
            else
            {
                Customer *prev = nullptr;

                while (temp && temp->getAccNumber() != accountNumber)
                {
                    prev = temp;
                    temp = temp->Next;
                }
                if (temp)
                {
                    prev->Next = temp->Next;
                    delete temp;
                    this->customersCount--;
                    std::cout << "Customer removed successfully\n";
                }
                else
                {
                    std::cout << "No customer in the list with account number: " << accountNumber << " found\n";
                }
            }
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "No customer in the list\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    void SearchCustomerByAccNumber(int accountNumber)
    {
        Customer *temp = this->Head;
        while (temp && temp->getAccNumber() != accountNumber)
        {
            temp = temp->Next;
        }
        if (temp)
        {
            std::cout << "----------------------------------------------------------";
            std::cout << '\n'
                      << std::left << std::setw(15) << "Account No" << std::setw(20) << "Name" << std::setw(10) << "Gender" << std::setw(15) << "Date of Birth" << '\n';
            std::cout << "----------------------------------------------------------\n";
            std::cout << std::left << std::setw(15) << temp->getAccNumber() << std::setw(20) << temp->getName() << std::setw(10) << (temp->getSex() ? "Female" : "Male") << temp->getDateOfBirth()->date << "/" << temp->getDateOfBirth()->month << "/" << temp->getDateOfBirth()->year << '\n';
        }
        else
        {
            std::cout << "No customer in the list with account number: " << accountNumber << " found\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    void SearchCustomerByFullName(std::string name)
    {
        Customer *temp = this->Head;
        while (temp && temp->getName() != name)
        {
            temp = temp->Next;
        }
        if (temp)
        {
            std::cout << "----------------------------------------------------------";
            std::cout << '\n'
                      << std::left << std::setw(15) << "Account No" << std::setw(20) << "Name" << std::setw(10) << "Gender" << std::setw(15) << "Date of Birth" << '\n';
            std::cout << "----------------------------------------------------------\n";
            std::cout << std::left << std::setw(15) << temp->getAccNumber() << std::setw(20) << temp->getName() << std::setw(10) << (temp->getSex() ? "Female" : "Male") << temp->getDateOfBirth()->date << "/" << temp->getDateOfBirth()->month << "/" << temp->getDateOfBirth()->year << '\n';
        }
        else
        {
            std::cout << "No customer in the list with name: " << name << " found\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    
    Customer *getCustomerByAccNumber(int accountNumber)
    {
        Customer *temp = this->Head;
        while (temp && temp->getAccNumber() != accountNumber)
        {
            temp = temp->Next;
        }
        return temp ? temp : nullptr;
    }
    // These sort function will sort in ascending order
    void SortByName()
    {
        this->Head = MergeSort(this->Head, true);
        printCustomerList();
    }
    void SortByDateOfBirth()
    {
        this->Head = MergeSort(this->Head, false);
        printCustomerList();
    }
    void printCustomerList()
    {
        Customer *temp = this->Head;

        std::cout << "----------------------------------------------------------";
        std::cout << '\n'
                  << std::left << std::setw(15) << "Account No" << std::setw(20) << "Name" << std::setw(10) << "Gender" << std::setw(15) << "Date of Birth" << '\n';
        std::cout << "----------------------------------------------------------\n";

        if (!temp)
        {
            std::cout << "No customer in the list\n";
            std::cout << "----------------------------------------------------------\n";
        }
        else
        {
            while (temp)
            {
                std::cout << std::left << std::setw(15) << temp->getAccNumber() << std::setw(20) << temp->getName() << std::setw(10) << (temp->getSex() ? "Female" : "Male") << temp->getDateOfBirth()->date << "/" << temp->getDateOfBirth()->month << "/" << temp->getDateOfBirth()->year << '\n';
                temp = temp->Next;
            }
        }
    }
};

#endif // End of include guard