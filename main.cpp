#include <iostream>
#include <cstring>
#include "Laser.hpp"

using namespace std;

/** Flag for application termination **/
volatile sig_atomic_t applicationExit = false;


/** Terminates the application after receiving interrupts **/
void terminateProgram(int signum)
{
	applicationExit = true;
}

int main()
{
	string request;
	Laser laser;
	
	/** Setup function to cath sigint and sigterm **/
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = terminateProgram;
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGINT, &action, NULL);
	

	/** ask user for input until terminated **/
	while(!applicationExit)
	{
		cout << "\nEnter Command: ";
		getline(cin, request);
		
		laser.setRequest(request);	
		cout << laser.getResponse();
	}
	
	cout << "\n\nApplication Terminated";
    return 0;
}
