//BankObjects.h

#include <iostream>

using namespace std;

class Customer {
public:
	//Default constructor
	Customer(); 
	//Inline function to increment time
	void tallyWait() { waitTime++; }
	//Inline function to get time
	int getWait() { return waitTime; } 
private:
	int waitTime = 0;
};

class Teller {
public:
	//Default constructor
	Teller(); 
	//Constructor initializer
	Teller(int aveServiceTime){ arrival = 0; departure = 0; serviceTime = aveServiceTime; } 
	//Inline function to increment number of arrivals
	void tallyArrive() { arrival++; } 
	//Inline function to increment number of departures
	void tallyDepart() { departure++; } 
	//Inline function to decrement service time
	void decService() { serviceTime--; } 
	//Inline function to return service time
	int getServiceTime() { return serviceTime; } 
	//Inline function to reset service time
	int resetServTime() { return serviceTime = 6; } 
	//Inline bool function check if Teller is available
	bool available() { if (arrival == departure) return true; else return false; } 

private:
	int arrival;
	int departure;
	int serviceTime;
};