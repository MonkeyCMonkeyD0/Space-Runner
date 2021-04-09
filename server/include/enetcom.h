#ifndef ENETCOM_H
#define ENETCOM_H
#pragma once

#include <vector>
#include <string>
#include <enet/enet.h>

#define BUFFERSIZE 1000
#define PORT 4242
#define TOMAX 0


typedef enum class type
{
	USERNAME_DECLARATION,
	PLANET_DECLARATION,
	RESSOURCE_DECLARATION,
	RESSOURCE_CHOICE,
	SPACESHIP_POSITION
} com_type;


class commu {

public:

	com_type type;
	std::string msg;

	commu(const std::string & buffer) : msg(buffer.substr(9))
	{
		std::string str_type = buffer.substr(0,8);
		for (int i = 0; i < com_type_tra.size(); ++i)	
			if (this->com_type_tra[i] == str_type) {
				this->type = (com_type) i;
				break;
			}
	}
	commu(const char * buffer) : commu(std::string(buffer)) {}
	commu(const com_type & type, const std::string & msg) : type(type), msg(msg) {}

	char * to_buf() const
	{
		std::string buffer;
		buffer += this->com_type_tra[(int) this->type];
		buffer += (char) 0x04;
		buffer += this->msg;
		char * buf = new char[buffer.size()];
		strcpy(buf, buffer.c_str());
		return buf;
	}

private:

	static std::vector<std::string> com_type_tra;

};

std::vector<std::string> commu::com_type_tra = {"USER_DCL", "PLAN_DCL", "RESO_DCL", "RESO_CHO", "SHIP_POS"};

#endif
