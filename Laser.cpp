#include "Laser.hpp"

using namespace std;

Laser::Laser()
{
	m_request = "";
	m_response = "";
}

Laser::~Laser()
{
}


void Laser::setRequest(string request)
{
	
	m_command = request;
	
	size_t pipePosition = request.find("|");
	if ( pipePosition != string::npos)
		m_command = request.substr(0, pipePosition);
	m_response = m_command;
}

string Laser::getResponse()
{
	return m_response;
}

void Laser::processRequest()
{
}

void Laser::setResponse(string response)
{
}