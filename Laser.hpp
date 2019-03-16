#ifndef LASER_H
#define LASER_H

#include <string>


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
		std::string m_request;
		std::string m_response;
		
		std::string m_command;
};

#endif // LASER_H
