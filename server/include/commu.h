#ifndef __COMMU_H__
#define __COMMU_H__

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
	SPACESHIP_DECLARATION,
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

#endif