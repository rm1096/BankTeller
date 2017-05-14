# BankTeller
Bank Teller Simulation for Programming Methodology II

Problems:
1. Implement a simulation that will mimic the arrival of customers, service by the Teller and successful departure of a customer.  
Your simulation MUST be able to handle more than 1 teller, different service and arrival times of customers. 

2. Assume 10 customers arrive every minute for 10 minutes. Assume each service time is of duration 1 unit.
Include average wait time in output.

3. Design and Implement unit tests, integration, system and acceptance tests for your project.  

Compiling instructions:

For the simulation - 
g++ simulation3.cpp -o simu
./simu

For the unit and integration tests -
g++ simulationUITest.cpp -o test
./test

For the system and acceptance test -
g++ simulationSysTest1.cpp -o test
./test
NOTE : For this test, I initialized calcWaitTime as 0, which is true for 3 tellers when using "sysTest2.txt".
