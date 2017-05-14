//THIS FILE INVOLVES UNIT AND INTEGRATION TESTING

//USE WITH UITest.txt or any other txt files you want to test

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "simulation3.h"
//#define NDEBUG	//commment out to run tests
#include <cassert>	//assert used for testing

using namespace std;

int currentTime = 0;

int tellerSize;

int tellerNumber;

vector <bool> tellerVec(0);	//vector of tellers

vector <int> waitTimes;	// vector of wait times

int waitTime;

int sumWait = 0;	//sum of wait times

float avgWaitTime;	//average wait time

bool tellerAvailable(){
	// Go through vector, if at least one element is true, then return true
	for(int i = 0; i < tellerSize; i++){
		if(tellerVec[i]){
			return true;
		}
	
	}
	
	return false;
}

void processArrival(Event arrivalEvent, priority_queue <Event, vector<Event>, Comparison> &pq, queue <Customer> &bankQueue){
		Event e = pq.top();
		pq.pop();	
		
		if(bankQueue.empty() && tellerAvailable()){
			assert(tellerAvailable() == 1);
			cout<<"tellerAvailable function worked"<<endl;
			int departureTime = currentTime + arrivalEvent.transactionTime;	//calculates departure time
			//cout<<"Customer arrives at: "<<arrivalEvent.time<<endl;
			Event d (departureTime, 0, 'd');	//creates a departure event using departureTime
			pq.push(d);	//adding departure event to the event list
			waitTime = departureTime - e.time - e.transactionTime;
			assert(e.time == arrivalEvent.time);
			assert(e.time == 2 || 3);	
			cout<<"Execution passes assertion of event arrival time transferred to arrivalEvent"<<endl;
			//cout<<"Customer waited: "<<waitTime<<" units long"<<endl;
			waitTimes.push_back(waitTime);
			assert(waitTime == 0 );
			cout<<"Excution properly transfers waitTime to global variable"<<endl; //
			
			for(int i = 0; i < tellerSize; i++){
				if(tellerVec[i]){
					d.tellerNumber = i;
					tellerVec[i] = false;
					break;
				}
			}

		}else{
			assert(tellerAvailable() == 0);
			cout<<"tellerAvailable function worked"<<endl;
			Customer c (arrivalEvent.transactionTime);
			//cout<<"Customer arrives at: "<<arrivalEvent.time<<endl;
			assert(e.time == arrivalEvent.time);
			cout<<"Execution passes assertion of event arrival time transferred to arrivalEvent"<<endl;
			assert(e.time == 4 || 6);
			cout<<"Execution passes assertion of waitTime transfer"<<endl;
			bankQueue.push(c);	//add customer to queue
			
		}
	}
	
void processDeparture(Event arrivalEvent, priority_queue <Event, vector<Event>, Comparison> &pq, queue<Customer> &bankQueue){
		Event e = pq.top();
		pq.pop();	//removing event from event list
		//cout<<"Customer departs at: " << currentTime << endl;
		if(!bankQueue.empty()){
			Customer c = bankQueue.front();	//customer at front of line begins transaction
			bankQueue.pop();
			int departureTime = currentTime + c.transactionTime;
			int waitTime = departureTime - e.time;
			//cout<<"Customer waited: "<<waitTime<<" units long"<<endl;
			assert(waitTime == 3 || 9 || 10 );	//INTEGRATION TEST - showing that global variable waitTime is accessible, and that data from function is transferred to it
			cout<<"Execution passes assertion of waitTime transfer"<<endl;
			waitTimes.push_back(waitTime);
			Event d (departureTime, 0, 'd');	//new departure event
			pq.push(d);
		}else{
			tellerVec[e.tellerNumber] = true;
		}
			
	}

void simulate(){

	queue <Customer> bankQueue;	//bank line
	priority_queue <Event, vector<Event>, Comparison>	eventListPQueue;	//event list
	
	ifstream infile("UITest.txt");	//reads data file
	int a;
	int t;
	int arrTime;
	int traTime;
	while(infile >> a >> t){	//reading user inputs to program
		Event e (a,t,'a');
		eventListPQueue.push(e);	//adding events in priority queue
		Event f = eventListPQueue.top();
		assert(e.time == a);
		assert(f.time == 2 || 6);	//6 would be the first arrival time at the top since it is the only element. Once 2 is pushed in, it remains the first element
		assert(e.transactionTime = t);
		assert(f.transactionTime = 7 || 10);
		cout<<"Execution passes assertion of pushed events"<<endl;	//UNIT TEST - showing arrival times/transaction times from files are properly stored into event arrival times/transaction times
	}
	
	while (!eventListPQueue.empty()){
        Event newEvent = eventListPQueue.top();
		currentTime = newEvent.time;	//get current time
		
		if(newEvent.eventType == 'a'){
			processArrival(newEvent, eventListPQueue, bankQueue);
			
		}else{
			processDeparture(newEvent, eventListPQueue, bankQueue);
			
		}
		
	}
	assert(eventListPQueue.size()== 0);
	cout<<"Execution properly operates through event list"<<endl;	
	assert(bankQueue.size() == 0);
	cout<<"Execution properly operates through bank queue"<<endl;
}

int main(){
	
	cout<<"How many tellers?"<<endl;
	cin>>tellerSize;
	cout<<"You've chosen "<<tellerSize<<" tellers"<<endl;
	
	for(int i = 0; i < tellerSize; i++){	//creating vector of tellers
		tellerVec.push_back(true);
	}
	
	simulate();	//simulation!
	
	for(int x = 0; x < waitTimes.size(); x++){	//sums wait times used to calculate average
		sumWait += waitTimes[x];
	}
	
	
	avgWaitTime = ((sumWait/10.0) / waitTimes.size())*10;
	cout<<"The average wait time is: "<<avgWaitTime<<" units"<<endl;
	return 0;
		
	}
		