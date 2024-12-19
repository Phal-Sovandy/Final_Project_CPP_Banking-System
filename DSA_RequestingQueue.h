#ifndef DSA_Request
#define DSA_Request
#include <iostream>
#include "DSA_Customer.h"
class RequestingData{
    public:
    Customer *requester = nullptr;
    std::string message = "";
    RequestingData *Next = nullptr;

    RequestingData(Customer *requester, std::string message){
        this->requester = requester;
        this->message = message;
    }
    ~RequestingData(){
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
    ~RequestingQueue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
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
    }
    void dequeue()
    {
        if (!isEmpty())
        {
            RequestingData *temp = front;
            front = front->Next;
            delete temp;

            this->length--;

            if (this->length == 0)
            {
                front = nullptr;
                rear = nullptr;
            }
        }
        else
        {
            std::cout << "error occurs: Queue is empty\n";
        }
    }
    void peek()
    {
        if (!isEmpty())
        {
            std::cout << "\nFirst customer request:\n";
            std::cout << "----------------------------------------------------------";
            std::cout << '\n' << std::left << std::setw(15) << "Account No" << std::setw(20) << "Name" << "Message\n";
            std::cout << "----------------------------------------------------------\n";
            std::cout << std::left << std::setw(15) << front->requester->getAccNumber() << std::setw(20) << front->requester->getName() << front->message << '\n';
        }
        else
        {
            std::cout << "errors occurs: Queue is Empty\n";
        }
    }
    bool isEmpty()
    {
        return this->length == 0;
    }
    int size()
    {
        return this->length;
    }

    void printQueue()
    {
        std::cout << "\nPrinting customer requesting queue:\n";
        std::cout << "----------------------------------------------------------";
        std::cout << '\n' << std::left << std::setw(15) << "Account No" << std::setw(20) << "Name"<< "Message\n";
        std::cout << "----------------------------------------------------------\n";

        RequestingData *temp = front;
        while (temp)
        {
            std::cout << std::left << std::setw(15) << temp->requester->getAccNumber() << std::setw(20) << temp->requester->getName() << temp->message << '\n';
            temp = temp->Next;
        }
    }
};

#endif