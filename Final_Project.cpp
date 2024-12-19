#include <iostream>
#include "DSA_Customer.h" // Include this header file that containing all the classes
#include "DSA_RequestingQueue.h"

int main()
{
    const int TO_DAY_DATE = DaysFromYear1900(20, 2, 2024);
    // Creating sample Date 5 objects for testing
    Date *date1 = new Date(15, 3, 1990); // Customer 1
    Date *date2 = new Date(3, 6, 1987);  // Customer 2
    Date *date3 = new Date(2, 8, 2000);  // Customer 3
    Date *date4 = new Date(25, 2, 2004); // Customer 4
    Date *date5 = new Date(13, 9, 2007); // Customer 5

    // Creating Investment and Borrow objects
    Investment *investment1 = new Investment(1000, 5, 15, 3, 2024); // 1000 investment for 5 years, starting 15, 03 2024
    Borrow *borrow1 = new Borrow(5000, 5, 6, 2024);                 // Loan of 5000, starting 5, 06 2024

    Investment *investment2 = new Investment(2000, 3, 23, 6, 2024); // 2000 investment for 3 years, starting 23, 06 2024
    Borrow *borrow2 = new Borrow(3000, 23, 6, 2024);                // Loan of 3000, starting 23, 06 2024

    Investment *investment3 = new Investment(1200, 2, 2, 4, 2024); // 1200 investment for 2 years, starting 2, 04 2024
    Borrow *borrow3 = new Borrow(5000, 6, 7, 2024);                // Loan of 5000, starting 6, 07 2024

    Borrow *borrow4 = new Borrow(8000, 18, 5, 2020); // Loan of 8000, starting 18, 05 2020

    // Create a CustomerList object
    CustomerList *customerList = new CustomerList();

    // Add customers to the customer list
    // Gender 1 = Female, 0 = Male
    customerList->AddCustomer(1302, "John Doe", false, date1, 5000.0, investment1, borrow1);
    customerList->AddCustomer(1131, "Micheal Jackson", true, date2, 1000.0, investment2, borrow2);
    customerList->AddCustomer(4432, "John Mayer", false, date3, 5000.0, investment3, borrow3);
    customerList->AddCustomer(2302, "Ed Shereen", true, date4, 1000.0, nullptr, borrow4);   // Customer 4 doesn't have investment
    customerList->AddCustomer(8823, "Charlie Puth", true, date5, 1000.0, nullptr, nullptr); // Customer 5 neither have investment nor borrow

    std::cout << "\n==========================================================\n";
    std::cout << "                      BANKING SYSTEM\n";
    std::cout << "==========================================================\n";

    // Print customer list
    std::cout << "Customer List:\n";
    customerList->printCustomerList();

    // Search customer by account number
    std::cout << "\nSearching customer with account number 1052:\n";
    customerList->SearchCustomerByAccNumber(1052);

    std::cout << "\nSearching customer with account number 4432:\n";
    customerList->SearchCustomerByAccNumber(4432);

    // Search customer by their full name
    std::cout << "\nSearching customer with name 'Micheal Jackson':\n";
    customerList->SearchCustomerByFullName("Micheal Jackson");

    // Perform deposit and withdrawal operations by John Deo
    std::cout << "\nPerforming deposit and withdrawal for John Doe (1302):\n";
    Customer *johnDoe = customerList->peek();
    johnDoe->deposit(1000.0); // Deposit 1000 into John’s account
    std::cout << "John Doe's current balance: " << johnDoe->showBalance() << '\n';
    johnDoe->withdrawal(500.0); // Withdraw 500 from John’s account
    std::cout << "John Doe's current balance: " << johnDoe->showBalance() << '\n';

    // Test investment withdrawal for John Doe & Micheal Jackson
    std::cout << "\nTrying to withdraw investment for John (1302):\n";
    johnDoe->withdrawInvestment(TO_DAY_DATE);
    std::cout << "Current Balance: " << johnDoe->showBalance() << '\n';

    std::cout << "\nTrying to withdraw investment for Micheal Jackson (1131):\n";
    Customer *michealJackson = customerList->getCustomerByAccNumber(1131);
    michealJackson->withdrawInvestment(TO_DAY_DATE - 100); 
    std::cout << "Current Balance: " << michealJackson->showBalance() << '\n';

    // Test monthly payment for loan for Ed Shereen & John Mayer
    std::cout << "\nMaking loan payment for Ed Shereen (2302):\n";
    Customer *edShereen = customerList->getCustomerByAccNumber(2302);
    edShereen->payForBorrow(18);
    std::cout << "Ed Shereen's current Balance: " << edShereen->showBalance() << '\n';

    std::cout << "\nMaking loan payment for John Mayer (4432):\n";
    Customer *johnMayer = customerList->getCustomerByAccNumber(4432);
    johnMayer->payForBorrow(20);
    std::cout << "John Mayer's current Balance: " << johnMayer->showBalance() << '\n';

    // Sort by name
    std::cout << "\nSorting customers by name:\n";
    customerList->SortByName();

    // Sort by date of birth
    std::cout << "\nSorting customers by date of birth:\n";
    customerList->SortByDateOfBirth();

    // Remove a customer and print the updated list
    std::cout << "\nRemoving customer with account number 1001 (Kne Smith):\n";
    customerList->RemoveCustomer(1092);
    customerList->printCustomerList();


    // Testing Requesting Queue
    RequestingData *request1 = new RequestingData(customerList->getCustomerByAccNumber(1302), "Hello, Please fix this bug!");
    RequestingData *request2 = new RequestingData(customerList->getCustomerByAccNumber(1131), "Hehehe, I'm starting with a man in the mirror!");
    RequestingData *request3 = new RequestingData(customerList->getCustomerByAccNumber(2302), "Hey, How can I open another saving account?");

    RequestingQueue *requestingQueue = new RequestingQueue();
    requestingQueue->enqueue(request1);
    requestingQueue->enqueue(request2);
    requestingQueue->enqueue(request3);
    requestingQueue->peek();
    requestingQueue->printQueue();
    requestingQueue->dequeue();
    requestingQueue->printQueue();

    //Showing Customer History Data
    std::cout << "\nShowing Micheal Jackson's Latest History Data:";
    michealJackson->peekHistory();

    std::cout << "\nShowing John Mayer's History Data:";
    johnMayer->showHistory();

    std::cout << "\nShowing Ed Shereen's History Data:";
    edShereen->showHistory();


    // Clean up dynamically allocated memory
    delete customerList;

    return 0;
}
