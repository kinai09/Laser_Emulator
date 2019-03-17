#ifndef LASER_H
#define LASER_H

#include <string>
#include <list>
#include <algorithm>

#include <thread>
#include <chrono>
#include <future>

#define STR     "STR"
#define STP     "STP"
#define ST      "ST?"
#define KAL     "KAL"
#define PW_GET  "PW?"
#define PW_SET  "PW="
#define ESM     "ESM"
#define DSM     "DSM"


#define COMMAND_ERROR     "UK!"
#define COMMAND_SUCCESS   "#"
#define COMMAND_FAILURE   "!"


class Laser
{
    public:
        Laser();
        ~Laser();
			
		void listenForCommands();
		
	private:			
		
		/** Starts laser emission **/
		bool startEmission();
		
		/** Stops laser emission **/
		bool stopEmission();
		
		/** Sets laser power **/
		bool setPower();
		
		/** Gets laser power **/
		void getPower();
		
		/** Gets emission status **/
		void getEmissionStatus();
		
		/** Process user's command **/
		bool processCommand();
		
		/** Checks if parameter is a valid integer **/
		bool isParameterValid();
		
		/** Checks if laser is emitting **/
		bool isEmitting();
		
		/** Checks if power value is within range [1, 100] **/
		bool isPowerValueValid();
		
		void timeoutCallback(std::future<void> futureObj);
		
		/** Sets request from user **/
		void setRequest(std::string request);
		
		/** Returns result of emulator for processing commands **/
		std::string getResponse();
		
	private:
		std::string m_response;
		std::string m_command;
		std::string m_parameter;
		std::string m_power;
		
		bool m_emissionStarted;
		bool m_isInSillyMode;
		
		struct sigaction action;
};

#endif // LASER_H
