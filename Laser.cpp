#include "Laser.hpp"
#include <iostream>

using namespace std;

/** Converts string to integer **/
static int toInt(string val)
{
	std::string::size_type sz;   
	int dec = std::stoi (val,&sz);
	
	return dec;
}


Laser::Laser()
{
	m_response = "";
	m_power = "0";
	
	m_emissionStarted = false;
	m_isInSillyMode = false;
}

Laser::~Laser()
{
}

void Laser::setRequest(string request)
{
	if (m_isInSillyMode)
	{
		reverse(request.begin(), request.end());
	}
	
	/** Reset value **/
	m_parameter = "";
	m_command = request;
	
	/** Get command and parameter **/
	size_t pipePosition = request.find("|");
	if ( pipePosition != string::npos)
	{
		m_command = request.substr(0, pipePosition);
		m_parameter = request.substr(pipePosition+1, request.length()-pipePosition);
	}
	
	/** Update response **/
	m_response = m_command;
	
	/** Process command **/
	if (!processCommand())
		m_response = COMMAND_ERROR;
}

string Laser::getResponse()
{
	return m_response;
}

bool Laser::processCommand()
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
	{
		getPower();
		commandValid = ret = true;
	}
	if (!m_command.compare(PW_SET))
	{
		ret = setPower();
		commandValid = true;
	}
	if (!m_command.compare(ESM))
	{
		m_isInSillyMode = true;
		commandValid = ret = true;
	}
	if (!m_command.compare(DSM))
	{
		m_isInSillyMode = false;
		commandValid = ret = true;
	}

	if (!commandValid)
		return false;
	
	/** Append processing result only if command is valid **/
	if (ret)
		m_response += COMMAND_SUCCESS;
	else
		m_response += COMMAND_FAILURE;
	
	return true;
}

bool Laser::stopEmission()
{
	if (isEmitting())
	{
		m_emissionStarted = false;
		m_power = "0";
		return true;
	}
	return false;
}

bool Laser::startEmission()
{
	if (!isEmitting())
	{	
		m_emissionStarted = true;
		m_power = "1";
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
	/** If laser is emitting and parameter value is a valid integer **/
	if (!isParameterValid() || !isEmitting())
		return false;

	/** save value of power before update **/
	string originalPowerValue = m_power;
	
	/** update power value**/
	m_power = m_parameter;
	
	/** if power value is outside [1-100], restore to previous valid value **/
	if (!isPowerValueValid())
	{
		m_power = originalPowerValue;
		return false;
	}
	
	return true;
}

void Laser::getPower()
{
	m_response += "|" + m_power;
}

bool Laser::isParameterValid()
{
	 return !m_parameter.empty() && std::find_if(m_parameter.begin(), 
        m_parameter.end(), [](char c) { return !std::isdigit(c); }) == m_parameter.end();
}

bool Laser::isEmitting()
{
	return m_emissionStarted;
}

bool Laser::isPowerValueValid()
{
	int power = toInt(m_power);
	
	if (power>1 && power <=100)
		return true;
	
	return false;
}
