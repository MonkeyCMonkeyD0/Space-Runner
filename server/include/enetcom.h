#ifndef ENETCOM_H
#define ENETCOM_H
#pragma once

#include <vector>
#include <string>
#include <enet/enet.h>

#define BUFFERSIZE 1000
#define PORT 4242
#define TOMAX 0


typedef enum type
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

	commu(const std::string & buffer) : type(static_cast<com_type>(buffer[9] - '0')), msg(buffer.substr(10)) {}
	commu(const char * buffer) : type(static_cast<com_type>(buffer[9] - '0')), msg(std::string(buffer + 10)) {}
	commu(const com_type & type, const std::string & msg) : type(type), msg(msg) {}

	char * to_buf() const
	{
		std::string buffer = "________";
		buffer += (char) 0x04;
		buffer += (char) this->type + '0';
		buffer += this->msg;
		char * buf = new char[buffer.size()];
		strcpy(buf, buffer.c_str());
		return buf;
	}
};

#endif
