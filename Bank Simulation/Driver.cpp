//Martin Manomat's Bank Simulation Program
//Driver.cpp

#include <iostream>
#include <cstdlib>
#include <string>
#include "Queue.h"
#include "BankObjects.h"

using namespace std;

int main()
{
	//Declaring bank work day variables
	int aveArrival, aveServiceTime, workDay, numOfServers;
	string bankName;

	//User prompt for their personalized bank simulation
	cout << "Hello! I just have a few questions that need to be answered for the simulation" << endl << endl;
	cout << "What is your name? ";
	cin >> bankName;
	cout << "How many servers are working today? There are three available to work. ";
	cin >> numOfServers;
	if (numOfServers > 3)
	{
		do
		{
			cout << "There are only 3 available servers to work for you today. Please choose again: ";
			cin >> numOfServers;
		}
		while (numOfServers > 3);
	}

	cout << "Great! How often do customers arrive to the bank (in minutes)?  ";
	cin >> aveArrival;
	cout << "How fast, on average, do tellers finish assisting customers (in minutes)?  ";
	cin >> aveServiceTime;
	cout << "Last question: How long is today's work day (in hours)?  ";
	cin >> workDay;
	cout << endl << "Perfect! We will begin " << bankName << "'s bank simulation now..." << endl << endl;

	//Making inputted work day to hours
	workDay *= 60;

	//Initializing more bank variables
	int clock = 0;
	int customers = 0;
	int customerWait = 0;
	int accumulatedWait = 0;

	//Creating the bank itself with a line, tellers, and prospective clients
	Queue<Customer> BankLine;
	Queue<Customer> TellerLine(numOfServers);
	Customer Client;
	Teller TellOne(aveServiceTime);

	//Bank simulation
	if (numOfServers == 1)
	{
		Teller TellTwo(aveServiceTime); //Creating second teller

		while (clock < workDay) //Checking to see if the work day is over
		{
			float randomArrival = (float)rand() / (float)(RAND_MAX); //Producing random arrivals of clients
			double arrivalProbability = (1.0 / aveArrival); //Creating probability of client arrival 
			//dependent on user's input of the banks average arrival

			if (randomArrival < arrivalProbability) //If the clients arrival is within the arrival probability
			{
				if (!BankLine.IsFull()) //If the bank is not full
				{
					cout << "Enter Client " << rand() << "!" << endl;
					Customer Client; //Creating client
					BankLine.enqueue(Client); //Enter client to the bank line
					customers++; //Incrementing number of customers for average wait time calculation at end of simulation
					clock++; //Increment clock at end of every action
				}

				else cout << "Bank is full at the moment. Please come back later /n";
			}

			if (BankLine.IsEmpty()) //If bank the bank is empty
			{
				cout << bankName << "'s bank is empty!" << endl;
			}

			else if (!BankLine.IsEmpty()) //If bank is not empty and clients are waiting to be served
			{

				if (TellOne.available()) //Client go to teller one if available
				{
					cout << "Teller one is available. Please step down" << endl;
					BankLine.dequeue();
					TellerLine.enqueue(Client);
					TellOne.tallyArrive();
					TellOne.decService();
					clock++;
				}

				//Notifying clients that all tellers are busy
				else if (!TellOne.available() && !BankLine.IsEmpty())
				{
					cout << "All tellers are busy at the moment, please wait.." << endl;
					TellOne.decService();
					TellTwo.decService();
					clock++;
				}

				Client.tallyWait();

				//If teller one is done with current client
				if (TellOne.getServiceTime() < 1)
				{
					cout << "Have a good day!" << endl;
					cout << "Teller one is now open" << endl;
					TellerLine.dequeue();
					TellOne.resetServTime();
					TellOne.tallyDepart();
					clock++;
					accumulatedWait = accumulatedWait + Client.getWait();
				}

			}

			//Increment clock
			clock++;

		}

		//Calculating banks average wait time for the whole simulation
		int aveWaitTime = accumulatedWait / customers;
		cout << "\n\nSimulation complete! " << bankName << "'s bank's average wait time was "
			<< aveWaitTime << " minutes" << endl;
	}
	if (numOfServers == 2) //If user decides there are two servers working today
	{
		Teller TellTwo(aveServiceTime); //Creating second teller

		while (clock < workDay) //Checking to see if the work day is over
		{
			float randomArrival = (float)rand() / (float)(RAND_MAX); //Producing random arrivals of clients
			double arrivalProbability = (1.0 / aveArrival); //Creating probability of client arrival 
			//dependent on user's input of the banks average arrival

			if (randomArrival < arrivalProbability) //If the clients arrival is within the arrival probability
			{
				if (!BankLine.IsFull()) //If the bank is not full
				{
					cout << "Enter Client " << rand() << "!" << endl;
					Customer Client; //Creating client
					BankLine.enqueue(Client); //Enter client to the bank line
					customers++; //Incrementing number of customers for average wait time calculation at end of simulation
					clock++; //Increment clock at end of every action
				}

				else cout << "Bank is full at the moment. Please come back later /n";
			}

			if (BankLine.IsEmpty()) //If bank the bank is empty
			{
				cout << bankName << "'s bank is empty!" << endl;
			}

			else if (!BankLine.IsEmpty()) //If bank is not empty and clients are waiting to be served
			{

				if (TellOne.available()) //Client go to teller one if available
				{
					cout << "Teller one is available. Please step down" << endl;
					BankLine.dequeue();
					TellerLine.enqueue(Client);
					TellOne.tallyArrive();
					TellOne.decService();
					clock++;
				}

				//Client go to teller two if teller one is busy
				else if (!TellOne.available() && !BankLine.IsEmpty() && TellTwo.available())
				{
					cout << "Teller one is currently busy.." << endl;
					cout << "Please step over to teller two" << endl;
					TellOne.decService();
					BankLine.dequeue();
					TellerLine.enqueue(Client);
					TellTwo.tallyArrive();
					TellTwo.decService();
					clock++;
				}

				//Notifying clients that all tellers are busy
				else if (!TellOne.available() && !BankLine.IsEmpty() && !TellTwo.available())
				{
					cout << "All tellers are busy at the moment, please wait.." << endl;
					TellOne.decService();
					TellTwo.decService();
					clock++;
				}

				Client.tallyWait();

				//If teller one is done with current client
				if (TellOne.getServiceTime() < 1)
				{
					cout << "Have a good day!" << endl;
					cout << "Teller one is now open" << endl;
					TellerLine.dequeue();
					TellOne.resetServTime();
					TellOne.tallyDepart();
					clock++;
					accumulatedWait = accumulatedWait + Client.getWait();
				}

				//If teller two is done with current client
				if (TellTwo.getServiceTime() < 1)
				{
					cout << "Have a good day!" << endl;
					cout << "Teller one is now open" << endl;
					TellerLine.dequeue();
					TellTwo.resetServTime();
					TellTwo.tallyDepart();
					clock++;
					accumulatedWait = accumulatedWait + Client.getWait();
				}
			}

			//Increment clock
			clock++;

		}		
		
		//Calculating banks average wait time for the whole simulation
		int aveWaitTime = accumulatedWait / customers;
		cout << "\n\nSimulation complete! " << bankName << "'s bank's average wait time was " 
			<< aveWaitTime << " minutes" << endl;
	}

	else if (numOfServers == 3)
	{
		Teller TellTwo(aveServiceTime);
		Teller TellThree(aveServiceTime);

		while (clock < workDay) //Checking to see if the work day is over
		{
			float randomArrival = (float)rand() / (float)(RAND_MAX); //Producing random arrivals of clients
			double arrivalProbability = (1.0 / aveArrival); //Creating probability of client arrival 
			//dependent on user's input of the banks average arrival

			if (randomArrival < arrivalProbability) //If the clients arrival is within the arrival probability
			{
				if (!BankLine.IsFull()) //If the bank is not full
				{
					cout << "Enter Client " << rand() << "!" << endl;
					Customer Client; //Creating client
					BankLine.enqueue(Client); //Enter client to the bank line
					customers++; //Incrementing number of customers for average wait time calculation at end of simulation
					clock++; //Increment clock at end of every action
				}

				else cout << "Bank is full at the moment. Please come back later /n";
			}

			if (BankLine.IsEmpty()) //If bank the bank is empty
			{
				cout << bankName << "'s bank is empty!" << endl;
			}

			else if (!BankLine.IsEmpty()) //If bank is not empty and clients are waiting to be served
			{

				if (TellOne.available()) //Client go to teller one if available
				{
					cout << "Teller one is available. Please step down" << endl;
					BankLine.dequeue();
					TellerLine.enqueue(Client);
					TellOne.tallyArrive();
					TellOne.decService();
					clock++;
				}

				//Client go to teller two if teller one is busy
				else if (!TellOne.available() && !BankLine.IsEmpty() && TellTwo.available())
				{
					cout << "Teller one is currently busy.." << endl;
					cout << "Please step over to teller two" << endl;
					TellOne.decService();
					BankLine.dequeue();
					TellerLine.enqueue(Client);
					TellTwo.tallyArrive();
					TellTwo.decService();
					clock++;
				}

				//Client go to teller three if teller one and two is busy
				else if (!BankLine.IsEmpty() && !TellOne.available() && !TellTwo.available() && TellThree.available())
				{
					cout << "Teller one and two are currently busy.." << endl;
					cout << "Please step over to teller three" << endl;
					TellOne.decService();
					TellTwo.decService();
					BankLine.dequeue();
					TellerLine.enqueue(Client);
					TellThree.tallyArrive();
					TellThree.decService();
					clock++;
				}

				//Notifying clients that all tellers are busy
				else if (!TellOne.available() && !BankLine.IsEmpty() && !TellTwo.available() && !TellThree.available())
				{
					cout << "All tellers are busy at the moment, please wait.." << endl;
					TellOne.decService();
					TellTwo.decService();
					TellThree.decService();
					clock++;
				}

				Client.tallyWait();

				//If teller one is done with current client
				if (TellOne.getServiceTime() < 1)
				{
					cout << "Have a good day!" << endl;
					cout << "Teller one is now open" << endl;
					TellerLine.dequeue();
					TellOne.resetServTime();
					TellOne.tallyDepart();
					clock++;
					accumulatedWait = accumulatedWait + Client.getWait();
				}

				//If teller two is done with current client
				if (TellTwo.getServiceTime() < 1)
				{
					cout << "Have a good day!" << endl;
					cout << "Teller one is now open" << endl;
					TellerLine.dequeue();
					TellTwo.resetServTime();
					TellTwo.tallyDepart();
					clock++;
					accumulatedWait = accumulatedWait + Client.getWait();
				}

				//If teller three is done with current client
				if (TellThree.getServiceTime() < 1)
				{
					cout << "Have a good day!" << endl;
					cout << "Teller one is now open" << endl;
					TellerLine.dequeue();
					TellThree.resetServTime();
					TellThree.tallyDepart();
					clock++;
					accumulatedWait = accumulatedWait + Client.getWait();
				}
			}

			//Increment clock
			clock++;

		}

		//Calculating banks average wait time for the whole simulation
		int aveWaitTime = accumulatedWait / customers;
		cout << "\n\nSimulation complete! " << bankName << "'s bank's average wait time was "
			<< aveWaitTime << " minutes" << endl;
	}




}