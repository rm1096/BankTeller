//THIS FILE INVOLVES SYSTEM AND ACCEPTANCE TESTING

//USE WITH sysText1.txt and sysText2.txt or any other txt files you want to test

/*Based on various amounts of tellers, I calculated the wait time. Then, I tested whether the wait time of the program matches my calculations. I included
assignments I made as comments to calcWaitTime based on how many tellers I inputted.*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "simulation3.h"

using namespace std;

float calcWaitTime;	//Hand calculated wait time used for comparing

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
			
			int departureTime = currentTime + arrivalEvent.transactionTime;	//calculates departure time
			//cout<<"Customer arrives at: "<<arrivalEvent.time<<endl;
			Event d (departureTime, 0, 'd');	//creates a departure event using departureTime
			pq.push(d);	//adding departure event to the event list
			waitTime = departureTime - e.time - e.transactionTime;
			//cout<<"Customer waited: "<<waitTime<<" units long"<<endl;
			waitTimes.push_back(waitTime);
			
			for(int i = 0; i < tellerSize; i++){
				if(tellerVec[i]){
					d.tellerNumber = i;
					tellerVec[i] = false;
					break;
				}
			}

		}else{
			Customer c (arrivalEvent.transactionTime);
			//cout<<"Customer arrives at: "<<arrivalEvent.time<<endl;
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
	
	ifstream infile("sysTest2.txt");	//reads data file
	int a;
	int t;
	int arrTime;
	int traTime;
	while(infile >> a >> t){	//reading user inputs to program
		Event e (a,t,'a');
		eventListPQueue.push(e);	//adding events in priority queue
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
	//cout<<"Im done"<<endl;
	bool x = eventListPQueue.empty();
	//cout<<x<<endl;
	bool y = bankQueue.empty();
	//cout<<y<<endl;
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
	
	//CALCULATED WAIT TIMES
	
	// IF USING sysText1.txt, UNCOMMENT the calcWaitTime for the teller
	//calcWaitTime = 2.25;	//1 teller
	//calcWaitTime = 0.5;	//2 tellers
	//calcWaitTime = 0.0;	//4 tellers
	
	// IF USING sysText2.txt, UNCOMMENT the calcWaitTime for the teller
	//calcWaitTime = 6;	//1 teller
	//calcWaitTime = 4.4;	//2 tellers
	calcWaitTime = 0;	//3 tellers
	
	avgWaitTime = ((sumWait/10.0) / waitTimes.size())*10;
	cout<<"The average wait time is: "<<avgWaitTime<<" units"<<endl;
	if (avgWaitTime == calcWaitTime){
		cout<<"SUCCESSFUL SYSTEM TEST"<<endl;
	}else{
	cout<<"FAIL"<<endl;
		}
	return 0;
		
	}
		