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
	
	if (!isValidCommand())
		m_response = m_response +  COMMAND_ERROR;
	
	
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

bool Laser::isValidCommand()
{
	if (!m_command.compare(STR))
		return true;
	if (!m_command.compare(STP))
		return true;
	if (!m_command.compare(ST))
		return true;
	if (!m_command.compare(KAL))
		return true;
	if (!m_command.compare(PW_GET))
		return true;
	if (!m_command.compare(PW_SET))
		return true;
	if (!m_command.compare(ESM))
		return true;
	if (!m_command.compare(DSM))
		return true;
	
	return false;
}