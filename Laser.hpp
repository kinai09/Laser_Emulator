#ifndef LASER_H
#define LASER_H

#include <string>
#include <list>
#include <algorithm>

#define STR "STR"
#define STP (string)"STP"
#define ST  (string)"ST?"
#define KAL (string)"KAL"
#define PW_GET (string)"PW?"
#define PW_SET (string)"PW="
#define ESM (string)"ESM"
#define DSM (string)"DSM"


#define COMMAND_ERROR "UK!"
#define COMMAND_SUCCESS "#"
#define COMMAND_FAILURE "!"



class Laser
{
    public:
        Laser();
        ~Laser();
		
		void setRequest(std::string request);
		std::string getResponse();
		
	protected:
		void processRequest();
		void setResponse(std::string response);
		
	private:
	
		bool startEmission();
		bool stopEmission();
		bool setPower();
		void getPower();
		
		void getEmissionStatus();
		
		bool isValidCommand();
		bool isValidParameter();
		
		std::string m_request;
		std::string m_response;
		
		std::string m_command;
		std::string m_parameter;
		
		std::string m_power;
		
		bool m_emissionStarted;

};

#endif // LASER_H
