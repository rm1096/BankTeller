#include <iostream>

using namespace std;

class Customer{
public:
	Customer();
	int transactionTime;
	
	public:Customer(int t){
		transactionTime = t;
	}
	
};

class Event{
public:
	int time;
	int transactionTime;
	char eventType;
	int tellerNumber;	//teller index
	
	//public:
	Event(int,int,char);
	

};	
	Event::Event(int t, int trans, char e){
		time = t;
		transactionTime = trans;
		eventType = e;
		//int tellerNumber;	//assigns teller in array to a customer
}

struct Comparison{
	  bool operator() (const Event & left, const Event & right) const {
	    return left.time > right.time;
	  }
	};
