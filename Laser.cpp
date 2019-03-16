#include "Laser.hpp"

#include <iostream>
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
	
	m_response = m_command;
	
	if (!m_command.compare(STR))
	{
		ret = startEmission();
		commandValid = true;
	}
	if (!m_command.compare(STP))
	{
		ret = stopEmission();
		commandValid = true;
	}
	if (!m_command.compare(ST))
	{
		getEmissionStatus();
		commandValid = ret = true;
	}
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
	
	
	if (!commandValid)
		return false;
	
	if (ret) /** TODO NO RETURN **/
		m_response += COMMAND_SUCCESS;
	else
		m_response += COMMAND_FAILURE;
	
	
	return true;
}

bool Laser::stopEmission()
{
	if (m_emissionStarted)
	{
		m_emissionStarted = false;
		return true;
	}
	return false;
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

void Laser::getEmissionStatus()
{
	string status;
	
	if (m_emissionStarted)
		status = "|1";
	else
		status = "|0";
	
	m_response += status;
}