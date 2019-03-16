#include <iostream>
#include <cstring>

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
	
	while(!applicationExit)
	{
		
	}
	
	cout << "Application Terminated";
	
	
    return 0;
}
