#include <iostream>
#include <string>
#include <iomanip>
#include "DSA_Customer.h"
#include "DSA_RequestingQueue.h"

void showBankerMenu()
{
    std::cout << "\nBanker Options:\n";
    std::cout << "----------------------------------------------------------\n";
    std::cout << "1. Add Customer to List\n";
    std::cout << "2. Remove Customer from List\n";
    std::cout << "3. Print Customer List\n";
    std::cout << "4. Search Customer By Account Number\n";
    std::cout << "5. Search Customer By Full Name\n";
    std::cout << "6. Sort Customer List By Full Name\n";
    std::cout << "7. Sort Customer List By Date Of Birth\n";
    std::cout << "8. Show Customer Requesting Queue\n";
    std::cout << "9. Show Customer History Data Stack\n";
    std::cout << "0. Exit\n";
}

void showCustomerMenu()
{
    std::cout << "\nCustomer Options:\n";
    std::cout << "----------------------------------------------------------\n";
    std::cout << "1. Deposit\n";
    std::cout << "2. Withdrawal\n";
    std::cout << "3. Withdrawal Investment\n";
    std::cout << "4. Loan Payment\n";
    std::cout << "5. Show Balance\n";
    std::cout << "6. Show History\n";
    std::cout << "7. Send Request\n";
    std::cout << "0. Exit\n";
}

int main()
{

    const int CURRENT_DAY_FROM_YEAR1900 = DaysFromYear1900(20, 12, 24); // count the days from 1900 to current date

    CustomerList *customerList = new CustomerList();
    RequestingQueue *requestingQueue = new RequestingQueue();

    // Testing for Customer role
    /*
    Borrow *borrow = new Borrow(1000, 1, 1, 2021);                                                       // initialBorrow, dayNow, monthNow, yearNow
    Investment *investment = new Investment(1000, 10, 1, 1, 2021);                                       // initialMoney, period, dayNow, monthNow, yearNow
    customerList->AddCustomer(1234, "John Doe", false, new Date(1, 1, 2000), 2000, investment, borrow); // accountNumber, fullName, sex, dateOfBirth, balance, investment, borrow
    */

   //Testing Requesting Queue (Run the Testing for Customer role first)
    /*
    Customer *customer = customerList->getCustomerByAccNumber(1234);
    RequestingData *request = new RequestingData(customer, "I want to withdraw my investment");
    requestingQueue->enqueue(request);
    */


    std::cout << "\n==========================================================\n";
    std::cout << "                     BANKING SYSTEM\n";
    std::cout << "==========================================================\n";

    int roleChoice;
    std::cout << "Choose Role (1 for Banker, 2 for Customer): ";
    std::cin >> roleChoice;

    if (roleChoice == 1) // Banker
    {
        int bankerChoice;
        do
        {
            showBankerMenu();
            std::cout << "Enter your choice: ";
            std::cin >> bankerChoice;

            switch (bankerChoice)
            {
            case 1:
            {
                // Add Customer to List
                int accNumber;
                std::string fullName;
                int sex; // 0 for Male, 1 for Female
                int day, month, year;
                float balance;

                std::cout << "Enter account number: ";
                std::cin >> accNumber;
                if (accNumber < 0 || accNumber > 9999)
                {
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Invalid account number. Account number must be positive and 4 digits only.\n";
                    std::cout << "----------------------------------------------------------\n";

                    break;
                }
                std::cout << "Enter full name: ";
                std::cin.ignore();
                std::getline(std::cin, fullName);
                std::cout << "Enter gender (0 for Male, 1 for Female): ";
                std::cin >> sex;
                if (sex != 0 && sex != 1)
                {
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Invalid gender input. Gender must be 0 or 1.\n";
                    std::cout << "----------------------------------------------------------\n";

                    break;
                }
                std::cout << "Enter date of birth (day month year): ";
                std::cin >> day >> month >> year;
                if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2500)
                {
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Invalid date of birth. Please enter a valid date.\n";
                    std::cout << "----------------------------------------------------------\n";

                    break;
                }
                std::cout << "Enter balance: ";
                std::cin >> balance;
                if (balance < 0)
                {
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Invalid balance. Balance must be positive.\n";
                    std::cout << "----------------------------------------------------------\n";

                    break;
                }
                Date *dateOfBirth = new Date(day, month, year);

                char borrowOrInvestChoice;
                std::cout << "Does the customer want to borrow, invest, both, or none? (b for Borrow, i for Invest, t for Both, n for None): ";
                std::cin >> borrowOrInvestChoice;

                Borrow *borrow = nullptr;
                Investment *investment = nullptr;

                if (borrowOrInvestChoice == 'b') // Borrow only
                {
                    // Get borrow details
                    float borrowAmount, borrowInterest;
                    int borrowDay, borrowMonth, borrowYear;
                    std::cout << "Enter borrow amount: ";
                    std::cin >> borrowAmount;
                    std::cout << "Enter interest rate: ";
                    std::cin >> borrowInterest;
                    std::cout << "Enter the start date of the borrow (day month year): ";
                    std::cin >> borrowDay >> borrowMonth >> borrowYear;

                    borrow = new Borrow(borrowAmount, borrowDay, borrowMonth, borrowYear);
                }
                else if (borrowOrInvestChoice == 'i') // Invest only
                {
                    // Get investment details
                    float investmentAmount;
                    int investmentPeriod, investDay, investMonth, investYear;
                    std::cout << "Enter investment amount: ";
                    std::cin >> investmentAmount;
                    std::cout << "Enter investment period (in months): ";
                    std::cin >> investmentPeriod;
                    std::cout << "Enter the start date of the investment (day month year): ";
                    std::cin >> investDay >> investMonth >> investYear;

                    investment = new Investment(investmentAmount, investmentPeriod, investDay, investMonth, investYear);
                }
                else if (borrowOrInvestChoice == 't') // Both Borrow and Invest
                {
                    // Get borrow details
                    float borrowAmount, borrowInterest;
                    int borrowDay, borrowMonth, borrowYear;
                    std::cout << "Enter borrow amount: ";
                    std::cin >> borrowAmount;
                    std::cout << "Enter interest rate: ";
                    std::cin >> borrowInterest;
                    std::cout << "Enter the start date of the borrow (day month year): ";
                    std::cin >> borrowDay >> borrowMonth >> borrowYear;

                    borrow = new Borrow(borrowAmount, borrowDay, borrowMonth, borrowYear);

                    // Get investment details
                    float investmentAmount;
                    int investmentPeriod, investDay, investMonth, investYear;
                    std::cout << "Enter investment amount: ";
                    std::cin >> investmentAmount;
                    std::cout << "Enter investment period (in months): ";
                    std::cin >> investmentPeriod;
                    std::cout << "Enter the start date of the investment (day month year): ";
                    std::cin >> investDay >> investMonth >> investYear;

                    investment = new Investment(investmentAmount, investmentPeriod, investDay, investMonth, investYear);
                }
                else if (borrowOrInvestChoice == 'n') // None
                {
                    // do nothing
                }
                else
                {
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Invalid input. Please enter b, i, t, or n.\n";
                    std::cout << "----------------------------------------------------------\n";
                    break;
                }

                // Add customer to the list
                customerList->AddCustomer(accNumber, fullName, sex, dateOfBirth, balance, investment, borrow);
                break;
            }
            case 2:
            {
                // Remove Customer from List
                int accNumber;
                std::cout << "Enter account number to remove: ";
                std::cin >> accNumber;
                customerList->RemoveCustomer(accNumber);
                break;
            }
            case 3:
            {
                // Print Customer List
                customerList->printCustomerList();
                break;
            }
            case 4:
            {
                // Search Customer by Account Number
                int accNumber;
                std::cout << "Enter account number to search: ";
                std::cin >> accNumber;
                customerList->SearchCustomerByAccNumber(accNumber);
                break;
            }
            case 5:
            {
                // Search Customer by Full Name
                std::string name;
                std::cout << "Enter full name to search: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                customerList->SearchCustomerByFullName(name);
                break;
            }
            case 6:
            {
                // Sort Customer List by Name
                customerList->SortByName();
                break;
            }
            case 7:
            {
                // Sort Customer List by Date of Birth
                customerList->SortByDateOfBirth();
                break;
            }
            case 8:
            {
                // Show Customer Requesting Queue
                requestingQueue->printQueue();
                break;
            }
            case 9:
            {
                // Show Customer History Data Stack
                int accNumber;
                std::cout << "Enter account number to show history: ";
                std::cin >> accNumber;
                Customer *customer = customerList->getCustomerByAccNumber(accNumber);
                if (customer)
                {
                    customer->showHistory();
                }
                else
                {
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "No customer in the list\n";
                    std::cout << "----------------------------------------------------------\n";
                }
                break;
            }
            case 0:
                // Exit
                std::cout << "----------------------------------------------------------\n";
                std::cout << "Exiting Banker Menu.\n";
                std::cout << "----------------------------------------------------------\n";

                break;
            default:
                std::cout << "----------------------------------------------------------\n";
                std::cout << "Invalid option. Try again.\n";
                std::cout << "----------------------------------------------------------\n";

                break;
            }
        } while (bankerChoice != 0);
    }
    else if (roleChoice == 2) // Customer
    {
        int customerId;
        std::cout << "Enter your Account ID: ";
        std::cin >> customerId;

        Customer *customer = customerList->getCustomerByAccNumber(customerId);

        if (customer)
        {
            int customerChoice;
            bool customerExit = false;

            do
            {
                showCustomerMenu();
                std::cout << "Enter choice: ";
                std::cin >> customerChoice;

                switch (customerChoice)
                {
                case 1:
                {
                    // Deposit
                    float amount;
                    std::cout << "Enter deposit amount: ";
                    std::cin >> amount;
                    customer->deposit(amount);
                    break;
                }
                case 2:
                {
                    // Withdrawal
                    float amount;
                    std::cout << "Enter withdrawal amount: ";
                    std::cin >> amount;
                    customer->withdrawal(amount);
                    break;
                }
                case 3:
                {
                    // Investment Withdrawal
                    customer->withdrawInvestment(CURRENT_DAY_FROM_YEAR1900);
                    break;
                }
                case 4:
                {
                    // Loan Payment
                    customer->payForBorrow(CURRENT_DAY_FROM_YEAR1900);
                    break;
                }
                case 5:
                    // show balance
                    std::cout << "Your Balance: " << customer->showBalance() << "\n";
                    break;
                case 6:
                    // show history
                    customer->showHistory();
                    break;
                case 7:
                {
                    // Send Request
                    std::string requestMessage;
                    std::cout << "Enter your request message: ";
                    std::cin.ignore();
                    std::getline(std::cin, requestMessage);

                    RequestingData *request = new RequestingData(customer, requestMessage);

                    requestingQueue->enqueue(request);

                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Your request has been sent.\n";
                    std::cout << "----------------------------------------------------------\n";
                    break;
                }
                case 0:
                    // Exit
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Exiting Customer Menu.\n";
                    std::cout << "----------------------------------------------------------\n";

                    customerExit = true;
                    break;
                default:
                    std::cout << "----------------------------------------------------------\n";
                    std::cout << "Invalid choice. Try again.\n";
                    std::cout << "----------------------------------------------------------\n";
                }
            } while (!customerExit);
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "Account not found!\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }
    else
    {
        std::cout << "----------------------------------------------------------\n";
        std::cout << "Invalid role selected.\n";
        std::cout << "----------------------------------------------------------\n";
    }

    return 0;
}
