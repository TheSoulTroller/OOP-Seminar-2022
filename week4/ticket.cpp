#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

class Ticket
{
private:
    char start[32];
    char destination[32];
    int year;
    double price;
public:
    void setStart(const char* start)
    {
        strcpy(this->start,start);
    }
    void setDestination(const char* final)
    {
        strcpy(this->destination,final);
    }
    void setYear(int year)
    {
        if(year < 1920)
        {
            cout << "\nInvalid year!" << endl;
            return;
        }
        this->year = year;
    }
    void setPrice(double price)
    {
        if(price < 0.00) 
        {
            cout << "\nInvalid price!" << endl;
            return;
        }
        this->price = price;
    }

    const char* getStart()const
    {
        return this->start;
    }
    const char* getDestination()const
    {
        return this->destination;
    }
    int getYear()const
    {
        return this->year;
    }
    double getPrice()const
    {
        return this->price;
    }

    void fixStart()
    {
        char fixedCity[32];
        strcpy(fixedCity,getStart());

        if(fixedCity[0] >= 'a' && fixedCity[0] <= 'z') fixedCity[0] -= 32;

        for(int i = 1; fixedCity[i] != '\0'; i++)
        {
            if(fixedCity[i] >= 'A' && fixedCity[i] <= 'Z') fixedCity[i] += 32;
            if(fixedCity[i-1] == ' ') fixedCity[i] -= 32;
        }
        cout << fixedCity << endl;
        setStart(fixedCity);
    }

    void fixDestination()
    {
        char fixedCity[32];
        strcpy(fixedCity,getDestination());
        

        if(fixedCity[0] >= 'a' && fixedCity[0] <= 'z') fixedCity[0] -= 32;

        for(int i = 1; fixedCity[i] != '\0'; i++)
        {
            if(fixedCity[i] >= 'A' && fixedCity[i] <= 'Z') fixedCity[i] += 32;
            if(fixedCity[i-1] == ' ') fixedCity[i] -= 32;
        }
        cout << fixedCity << endl;
        setDestination(fixedCity);
    }  
    
    Ticket(const char* start, const char* destination, int year, double price)
    {
        setStart(start);
        setDestination(destination);
        setYear(year);
        setPrice(price);
    }

    Ticket()
    {
        setStart(" ");
        setDestination(" ");
        setYear(2000);
        setPrice(0.0);
    }

    void printTicket()
    {
        cout << "\nStarting city: ";
        fixStart();
        cout << "Destination city: ";
        fixDestination();
        cout << "Year: " << year << endl;
        cout << "Price: " << price << endl;
    }
};


int main()
{
    char start[32];
    cout << "Enter starting city: ";
    cin.getline(start,32);

    char destination[32];
    cout << "Enter destination city: ";
    cin.getline(destination,32);

    int year;
    cout << "Enter year: ";
    cin >> year;

    double price;
    cout << "Enter price: ";
    cin >> price;

    Ticket ticket(start,destination,year,price);
    ticket.printTicket();
    return 0;
}