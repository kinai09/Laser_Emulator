#include <iostream>
#include <cstring>
#include "Laser.hpp"

using namespace std;

volatile sig_atomic_t applicationExit = false;

void terminateProgram(int signum)
{
	applicationExit = true;
}

int main()
{
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = terminateProgram;
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGINT, &action, NULL);
	
	
	string request;
	Laser laser;
	
	while(!applicationExit)
	{
		cout << "Enter Command: ";
		getline(cin, request);
		
		laser.setRequest(request);	
		cout << laser.getResponse();
	}
	
	cout << "Application Terminated";
	
	
    return 0;
}
