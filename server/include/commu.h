#ifndef COMMU_H
#define COMMU_H
#pragma once

#include <vector>
#include <string>
#include <cstring>

#define BUFFERSIZE 500
#define PORT 8080 //4242
#define TOMAX 0


typedef enum type : char
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

	commu(const std::string & buffer);
	commu(const char * buffer);
	commu(const com_type & type, const std::string & msg);

	char * to_buf() const;
};


commu::commu(const std::string & buffer) : 
	type(com_type(buffer[9] - '0')), msg(buffer.substr(10)) {}

commu::commu(const char * buffer) : 
	type(com_type(buffer[9] - '0')), msg(std::string(buffer + 10)) {}

commu::commu(const com_type & type, const std::string & msg) : 
	type(type), msg(msg) {}


char * commu::to_buf() const
{
	std::string buffer = "________";
	buffer += (char) 0x04;
	buffer += (char) this->type + '0';
	buffer += this->msg;
	char * buf = new char[buffer.size()];
	strcpy(buf, buffer.c_str());
	return buf;
}

#endif
