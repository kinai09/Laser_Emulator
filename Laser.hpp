#ifndef LASER_H
#define LASER_H

#include <string>
#include <list>

#define STR "STR"
#define STP (string)"STP"
#define ST  (string)"ST?"
#define KAL (string)"KAL"
#define PW_GET (string)"PW?"
#define PW_SET (string)"PW="
#define ESM (string)"ESM"
#define DSM (string)"DSM"


#define COMMAND_ERROR "UK!"



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
	
		bool isValidCommand();
		
		std::string m_request;
		std::string m_response;
		std::string m_command;

};

#endif // LASER_H
