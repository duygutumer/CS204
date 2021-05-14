#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <iomanip>
#include"HW8DynIntQueue.h"
#include <iostream>
#include <sstream>
#include <random>
#include <time.h>


using namespace std;

mutex myMutex, coutMutex;
HW8DynIntQueue myQueue;
int say;

int random_range(const int & min, const int & max) 
{
	static mt19937 generator(time(0));
	uniform_int_distribution <int> distribution(min, max);
	return distribution(generator);
}

void customer(int total_customer_count, int min_arrival, int max_arrival)
{
	for(int i = 0; i < total_customer_count; i++)
	{
		myMutex.lock();
		if (!(myQueue.getCurrentSize() >= total_customer_count)) 
		{  
			myQueue.enqueue(i);
			say++;
			myMutex.unlock();

			coutMutex.lock();

			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			cout <<"New customer with ID "<< i+1 << " has arrived (queue size is " <<  myQueue.getCurrentSize() << "): " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();

			unsigned int time_in_seconds = random_range(min_arrival, min_arrival);
			this_thread::sleep_for(chrono::seconds(time_in_seconds)); 
		}
		else
		{
			myMutex.unlock();
			i--;

		}
	}
		

}

void cashier(int id, int total_customer_count, int cashier2_threshold, int max_checkout_time, int min_checkout_time)
{
	int customerId;
	static int count = 0;

	while(count < total_customer_count)
	{
		unsigned int time_in_seconds = random_range(min_checkout_time, max_checkout_time);
		this_thread::sleep_for(chrono::seconds(time_in_seconds));
		
		if((say >= cashier2_threshold && id == 2) || id == 1)
		{
			myMutex.lock();
			if (say != 0) 
			{  
				myQueue.dequeue(customerId);

				say--;
				count++;

				myMutex.unlock();
				
				coutMutex.lock();
				
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout << "Cashier" << id << "  started transaction with customer "<< customerId+1 <<" (queue size is " << say << "): " << put_time(ptm,"%X") <<endl;
				
				coutMutex.unlock();

				time_in_seconds = random_range(min_checkout_time, max_checkout_time);
				this_thread::sleep_for(chrono::seconds(time_in_seconds)); 

				coutMutex.lock();

				tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
				ptm = new struct tm;
				localtime_s(ptm, &tt); 
				
				cout << "Cashier" << id << "  finished transaction with customer "<< customerId+1 << " " << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
			}
			else
			{
				myMutex.unlock();
			}
		}
	}	
}

int main()
{
	int total_customer_count;
	int cashier2_threshold;
	cout <<"Please enter the total number of customers: ";
	cin >> total_customer_count;
	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> cashier2_threshold;

	int min_arrival;
	int max_arrival;
	cout << "Please enter the inter-arrival time range between two customers: " << endl;
	cout <<"Min: ";
	cin >> min_arrival;
	cout << "Max: ";
	cin >> max_arrival;

	int min_checkout_time;
	int max_checkout_time;
	cout << "Please enter the checkout time range of cashiers: " << endl;
	cout <<"Min: ";
	cin >> min_checkout_time;
	cout << "Max: ";
	cin >> max_checkout_time;

	say = 0;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 

	cout << "Simulation starts " << put_time(ptm,"%X") << endl;

	thread cust(&customer,total_customer_count, min_arrival, max_arrival);
	thread cash1(&cashier, 1, total_customer_count, cashier2_threshold, max_checkout_time, min_checkout_time);
	thread cash2(&cashier, 2, total_customer_count, cashier2_threshold, max_checkout_time, min_checkout_time);
	
	cust.join();	
	cash2.join();
	cash1.join();
	
	tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	ptm = new struct tm;
	localtime_s(ptm, &tt); 

	cout << "End of the simulation ends: " << put_time(ptm,"%X") << endl;

	return 0;
}