#include "Laser.hpp"


using namespace std;

Laser::Laser()
{
	m_request = "";
	m_response = "";
	
	m_emissionStarted = false;
	
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
	bool commandValid = false;
	bool ret = false;
	
	if (!m_command.compare(STR))
	{
		ret = startEmission();
		commandValid = true;
	}
	if (!m_command.compare(STP))
		commandValid = true;
	if (!m_command.compare(ST))
		commandValid = true;
	if (!m_command.compare(KAL))
		commandValid = true;
	if (!m_command.compare(PW_GET))
		commandValid = true;
	if (!m_command.compare(PW_SET))
		commandValid = true;
	if (!m_command.compare(ESM))
		commandValid = true;
	if (!m_command.compare(DSM))
		commandValid = true;
	
	if (ret) /** TODO NO RETURN **/
		m_command += COMMAND_SUCCESS;
	else
		m_command += COMMAND_FAILURE;
	
	
	m_response = m_command;
	
	return commandValid;
}

bool Laser::startEmission()
{
	if (!m_emissionStarted)
	{
		m_emissionStarted = true;
		return true;
	}
	
	return false;
}