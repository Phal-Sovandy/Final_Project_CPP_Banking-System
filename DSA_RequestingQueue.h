#ifndef DSA_Request
#define DSA_Request
#include <iostream>
#include "DSA_Customer.h"
class RequestingData
{
public:
    Customer *requester = nullptr;
    std::string message = "";
    RequestingData *Next = nullptr;

    RequestingData(Customer *requester, std::string message)
    {
        this->requester = requester;
        this->message = message;
    }
    ~RequestingData()
    {
        delete requester;
        requester = nullptr;
    }
};
class RequestingQueue
{
private:
    RequestingData *front;
    RequestingData *rear;
    int length;

public:
    RequestingQueue()
    {
        front = nullptr;
        rear = nullptr;
        length = 0;
    }
    // Destructor is not important since we delete the customer list already so the customer will be deleted in main program
    ~RequestingQueue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
        front = nullptr;
        rear = nullptr;
    }
    void enqueue(RequestingData *requestingData)
    {
        if (isEmpty())
        {
            front = requestingData;
            rear = requestingData;
        }
        else
        {
            rear->Next = requestingData;
            rear = requestingData;
        }
        this->length++;
        std::cout << "----------------------------------------------------------\n";
        std::cout << "Request has been sent\n";
        std::cout << "----------------------------------------------------------\n";
    }
    void dequeue()
    {
        if (!isEmpty())
        {
            front = front->Next;

            this->length--;

            if (this->length == 0)
            {
                front = nullptr;
                rear = nullptr;
            }
            std::cout << "----------------------------------------------------------\n";
            std::cout << "Request has been removed from queue\n";
            std::cout << "----------------------------------------------------------\n";
        }
        else
        {
            std::cout << "----------------------------------------------------------\n";
            std::cout << "error occurs: Queue is empty\n";
            std::cout << "----------------------------------------------------------\n";
        }
    }

    bool isEmpty()
    {
        return this->front == nullptr;
    }
    int size()
    {
        return this->length;
    }

    void printQueue()
    {
        std::cout << "\nPrinting customer requesting queue:\n";
        std::cout << "----------------------------------------------------------";
        std::cout << '\n'
                  << std::left << std::setw(15) << "Account No" << std::setw(20) << "Name" << "Message\n";
        std::cout << "----------------------------------------------------------\n";

        RequestingData *temp = front;
        if (!temp)
        {
            std::cout << "No customer request available\n";
            std::cout << "----------------------------------------------------------\n";
        }
        else
        {
            while (temp)
            {
                std::cout << std::left << std::setw(15) << temp->requester->getAccNumber() << std::setw(20) << temp->requester->getName() << temp->message << '\n';
                temp = temp->Next;
            }
        }
    }
};

#endif