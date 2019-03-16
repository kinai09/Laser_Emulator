#include "Laser.hpp"

#include <iostream>
using namespace std;


Laser::Laser()
{
	m_request = "";
	m_response = "";
	
	m_emissionStarted = false;
	m_power = 0;
	
}

Laser::~Laser()
{
}

static int toInt(string val)
{
	std::string::size_type sz;   
	int dec = std::stoi (val,&sz);
	
	return dec;
}

void Laser::setRequest(string request)
{
	/** Reset value **/
	m_parameter = "";
	m_command = request;
	
	size_t pipePosition = request.find("|");
	if ( pipePosition != string::npos)
	{
		m_command = request.substr(0, pipePosition);
		m_parameter = request.substr(pipePosition+1, request.length()-pipePosition);
		
	}
	
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
	{
		ret = setPower();
		commandValid = true;
	}
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
		m_power = 0;
		return true;
	}
	return false;
}

bool Laser::startEmission()
{
	if (!m_emissionStarted)
	{
		m_emissionStarted = true;
		m_power = 1;
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

bool Laser::setPower()
{
	if (!isValidParameter())
	{
		return false;
	}
	m_power = toInt(m_parameter);
	return true;
}

bool Laser::isValidParameter()
{
	 return !m_parameter.empty() && std::find_if(m_parameter.begin(), 
        m_parameter.end(), [](char c) { return !std::isdigit(c); }) == m_parameter.end();
}


